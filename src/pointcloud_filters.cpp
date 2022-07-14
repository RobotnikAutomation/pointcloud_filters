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
  
  pointcloud_pub_.publish(pointCloudFilter(pointcloud_));
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

sensor_msgs::PointCloud2 PointCloudFilters::pointCloudFilter(sensor_msgs::PointCloud2 pointcloud)
{
  return pointcloud;
}

void PointCloudFilters::pointCloudSubCb(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
  pointcloud_.header = msg->header;
  pointcloud_.width = msg->width;
  pointcloud_.height = msg->height;
  pointcloud_.fields = msg->fields;
  pointcloud_.is_bigendian = msg->is_bigendian;
  pointcloud_.point_step = msg->point_step;
  pointcloud_.row_step = msg->row_step;
  pointcloud_.is_dense = msg->is_dense;
  pointcloud_.data.resize(msg->data.size());
  pointcloud_.data = msg->data;

  tickTopicsHealth("pointcloud_sub");
}

