#include <pointcloud_filters/pointcloud_filters.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pointcloud_filters");
  ros::NodeHandle n;

  PointCloudFilters pointcloud_filters(n);
  pointcloud_filters.start();
}
