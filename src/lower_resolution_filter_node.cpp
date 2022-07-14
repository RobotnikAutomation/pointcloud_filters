#include <pointcloud_filters/lower_resolution_filter.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "lower_resolution_filter");
  ros::NodeHandle n;

  LowerResolutionFilter lower_resolution_filter(n);
  lower_resolution_filter.start();
}
