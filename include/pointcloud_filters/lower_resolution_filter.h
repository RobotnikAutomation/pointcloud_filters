#ifndef _LOWER_RESOLUTION_FILTER_
#define _LOWER_RESOLUTION_FILTER_

#include <pointcloud_filters/pointcloud_filters.h>

// Insert here general includes...

// Insert here msg and srv includes...

class LowerResolutionFilter : public PointCloudFilters
{
public:
  LowerResolutionFilter(ros::NodeHandle h);
  virtual ~LowerResolutionFilter();

protected:
  /*** RComponent stuff ***/

  //! Setups all the ROS' stuff
  virtual int rosSetup();
  //! Shutdowns all the ROS' stuff
  virtual int rosShutdown();
  //! Reads data a publish several info into different topics
  virtual void rosPublish();
  //! Reads params from params server
  virtual void rosReadParams();
  //! Actions performed on init state
  virtual void initState();
  //! Actions performed on standby state
  virtual void standbyState();
  //! Actions performed on ready state
  virtual void readyState();
  //! Actions performed on the emergency state
  virtual void emergencyState();
  //! Actions performed on Failure state
  virtual void failureState();

  /* RComponent stuff !*/

  /* ROS Stuff */

  //! Publishers...

  //! Subscribers...

  //! Services...

  //! Callbacks...

  /* ROS stuff !*/

  /* LowerResolutionFilter stuff */

  int reduce_points_factor_;

  sensor_msgs::PointCloud2 pointCloudFilter(sensor_msgs::PointCloud2 pointcloud);

  //! LowerResolutionFilter variables and methods...

  /* LowerResolutionFilter stuff !*/


};

#endif  // _LOWER_RESOLUTION_FILTER_
