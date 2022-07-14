#include <pointcloud_filters/lower_resolution_filter.h>

LowerResolutionFilter::LowerResolutionFilter(ros::NodeHandle h) : PointCloudFilters(h)
{
  component_name.assign(pnh_.getNamespace());
  rosReadParams();
}

LowerResolutionFilter::~LowerResolutionFilter()
{
}

void LowerResolutionFilter::rosReadParams()
{
  PointCloudFilters::rosReadParams();

  bool required = true;
  bool not_required = false;

  // Parameters
  readParam(pnh_, "reduce_points_factor", reduce_points_factor_, 4, required);
}

int LowerResolutionFilter::rosSetup()
{
  PointCloudFilters::rosSetup();

  bool required = true;
  bool not_required = false;

  // Publishers ...

  // Subscribers ...

  // Services ...
  
}

int LowerResolutionFilter::rosShutdown()
{
  PointCloudFilters::rosShutdown();

  // Shutsown state...
}

void LowerResolutionFilter::rosPublish()
{
  PointCloudFilters::rosPublish();
  
  // Ros publish state...
}

void LowerResolutionFilter::initState()
{
  PointCloudFilters::initState();

  // Init state...
}

void LowerResolutionFilter::standbyState()
{
  PointCloudFilters::standbyState();

  // Standby state...
}

void LowerResolutionFilter::readyState()
{
  PointCloudFilters::readyState();

  // Ready state...
}

void LowerResolutionFilter::emergencyState()
{
  PointCloudFilters::emergencyState();

  // Emergency state...
}

void LowerResolutionFilter::failureState()
{
  PointCloudFilters::failureState();

  // Failure state...
}

sensor_msgs::PointCloud2 LowerResolutionFilter::pointCloudFilter(const sensor_msgs::PointCloud2::ConstPtr& msg)
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

  RCOMPONENT_ERROR_STREAM("TEST");

  return pointcloud_filtered;
}