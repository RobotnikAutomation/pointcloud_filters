#include <pointcloud_filters/pointcloud_filters.h>

PointCloudFilters::PointCloudFilters(ros::NodeHandle h) : rcomponent::RComponent(h)
{
  component_name.assign(pnh_.getNamespace());
  rosReadParams();
}

PointCloudFilters::~PointCloudFilters()
{
}

void PointCloudFilters::rosReadParams()
{
  bool required = true;
  bool not_required = false;

  readParam(pnh_, "desired_freq", desired_freq_, 40.0, not_required);
  readParam(pnh_, "pointcloud_in", pointcloud_in_name_, "front_rgbd_camera/depth/points", required);
  readParam(pnh_, "pointcloud_filtered", pointcloud_filtered_name_, "throttle/front_rgbd_camera/depth/points", required);
}

int PointCloudFilters::rosSetup()
{
  RComponent::rosSetup();

  bool required = true;
  bool not_required = false;

  // Publisher
  status_pub_ = pnh_.advertise<std_msgs::String>("status", 10);
  status_stamped_pub_ = pnh_.advertise<robotnik_msgs::StringStamped>("status_stamped", 10);

  pointcloud_pub_ = nh_.advertise<sensor_msgs::PointCloud2>(pointcloud_filtered_name_, 10);

  // Subscriber
  pointcloud_sub_ = nh_.subscribe<sensor_msgs::PointCloud2>(pointcloud_in_name_, 10, &PointCloudFilters::pointCloudSubCb, this);
  addTopicsHealth(&pointcloud_sub_, "pointcloud_sub", 5.0, required);
}

int PointCloudFilters::rosShutdown()
{
  RComponent::rosShutdown();
}

void PointCloudFilters::rosPublish()
{
  RComponent::rosPublish();

  if (getState() == robotnik_msgs::State::READY_STATE)
  {
    robotnik_msgs::StringStamped status_stamped;

    status_pub_.publish(status_);

    status_stamped.header.stamp = ros::Time::now();
    status_stamped.string = status_.data;
    status_stamped_pub_.publish(status_stamped);
  }
  
  pointcloud_pub_.publish(pointcloud_filtered_);
}

void PointCloudFilters::initState()
{
  RComponent::initState();

  switchToState(robotnik_msgs::State::STANDBY_STATE);
}

void PointCloudFilters::standbyState()
{
  if (checkTopicsHealth() == false)
  {
    switchToState(robotnik_msgs::State::EMERGENCY_STATE);
  }
  else
  {
    switchToState(robotnik_msgs::State::READY_STATE);
  }
}

void PointCloudFilters::readyState()
{
  if (checkTopicsHealth() == false)
  {
    switchToState(robotnik_msgs::State::EMERGENCY_STATE);
  }
}

void PointCloudFilters::emergencyState()
{
  if (checkTopicsHealth() == true)
  {
    switchToState(robotnik_msgs::State::STANDBY_STATE);
  }
}

void PointCloudFilters::failureState()
{
  RComponent::failureState();
}

sensor_msgs::PointCloud2 PointCloudFilters::pointCloudFilter(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
  sensor_msgs::PointCloud2 pointcloud_filtered;

  pointcloud_filtered.header = msg->header;
  pointcloud_filtered.width = msg->width;
  pointcloud_filtered.height = msg->height;
  pointcloud_filtered.fields = msg->fields;
  pointcloud_filtered.is_bigendian = msg->is_bigendian;
  pointcloud_filtered.point_step = msg->point_step;
  pointcloud_filtered.row_step = msg->row_step;
  pointcloud_filtered.is_dense = msg->is_dense;
  pointcloud_filtered.data.resize(msg->data.size());
  pointcloud_filtered.data = msg->data;

  return pointcloud_filtered;
}

void PointCloudFilters::pointCloudSubCb(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
  pointcloud_filtered_ = pointCloudFilter(msg);

  tickTopicsHealth("pointcloud_sub");
}

