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

  RCOMPONENT_INFO_STREAM("Frequency: " << desired_freq_);
  RCOMPONENT_INFO_STREAM("Reduce points factor: " << reduce_points_factor_);
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

sensor_msgs::PointCloud2 LowerResolutionFilter::pointCloudFilter(sensor_msgs::PointCloud2 pointcloud)
{
  sensor_msgs::PointCloud2 pointcloud_filtered;

  pointcloud_filtered.header = pointcloud.header;
  pointcloud_filtered.width = std::floor(pointcloud.width / reduce_points_factor_);
  pointcloud_filtered.height = pointcloud.height;
  pointcloud_filtered.fields = pointcloud.fields;
  pointcloud_filtered.is_bigendian = pointcloud.is_bigendian;
  pointcloud_filtered.point_step = pointcloud.point_step;
  pointcloud_filtered.row_step = pointcloud_filtered.point_step * pointcloud_filtered.width;
  pointcloud_filtered.is_dense = pointcloud.is_dense;
  pointcloud_filtered.data.resize(pointcloud_filtered.width * pointcloud_filtered.height * pointcloud_filtered.point_step);

  int max_rs = pointcloud_filtered.row_step;
  int max_ps = pointcloud_filtered.point_step;

  for (int h = 0; h < pointcloud_filtered.height; h++)
  {
    for (int w = 0; w < pointcloud_filtered.width; w++)
    {
      for (int ps = 0; ps < pointcloud_filtered.point_step; ps++)
      {
        pointcloud_filtered.data[h*max_rs + w*max_ps + ps] = pointcloud.data[(h*max_rs + w*max_ps)*reduce_points_factor_ + ps];
      }
    }
  }

  return pointcloud_filtered;
}