#ifndef _POINTCLOUD_FILTERS_
#define _POINTCLOUD_FILTERS_

#include <rcomponent/rcomponent.h>

// Insert here general includes:
#include <math.h>

// Insert here msg and srv includes:
#include <std_msgs/String.h>
#include <robotnik_msgs/StringStamped.h>
#include <sensor_msgs/PointCloud2.h>

#include <std_srvs/Trigger.h>

class PointCloudFilters : public rcomponent::RComponent
{
public:
  PointCloudFilters(ros::NodeHandle h);
  virtual ~PointCloudFilters();

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

  // Publishers

  //! To publish the basic information
  ros::Publisher status_pub_;
  ros::Publisher status_stamped_pub_;
  ros::Publisher pointcloud_pub_;
  string pointcloud_filtered_name_;

  //! Subscribers
  ros::Subscriber pointcloud_sub_;
  string pointcloud_in_name_;

  //! Services
  ros::ServiceServer example_server_;

  //! Callbacks
  void pointCloudSubCb(const sensor_msgs::PointCloud2::ConstPtr& msg);

  /* ROS stuff !*/

  /* PointCloudFilters stuff */

  std_msgs::String status_;
  sensor_msgs::PointCloud2 pointcloud_filtered_;

  virtual sensor_msgs::PointCloud2 pointCloudFilter(const sensor_msgs::PointCloud2::ConstPtr& msg);

  /* PointCloudFilters stuff !*/

};

#endif  // _POINTCLOUD_FILTERS_
