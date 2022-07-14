# pointcloud_filters

The pointcloud_filters package, based on RComponent structure. Node to filter a PointCloud2 message.

## 1 lower_resolution_filter

This node filters a PointCloud2 message in a "n" factor to decrease the bandwidth required for the website. It also reduces the frequency of the publication.

### 1.1 Parameters

* ~reduce_points_factor (int, default: 4)
   Decrease pointcloud size factor.
* ~desired_freq (double, default: 4.0)
   Publication frequency of the filtered PointCloud
* ~pointcloud_in (string, default: front_rgbd_camera/depth/points)
   Topic name of the input PointCloud
* ~pointcloud_filtered (string, default: throttle/front_rgbd_camera/depth/points)
   Topic name of the filtered PointCloud
   
### 1.2 Subscribed Topics

* front_rgbd_camera/depth/points (sensor_msgs/PointCloud2)
  Topic with the raw PointCloud

### 1.3 Published Topics

* throttle/front_rgbd_camera/depth/points (sensor_msgs/PointCloud2)
  Topic with the filtered PointCloud

### 1.4 Bringup

```bash
roslaunch pointcloud_filters lower_resolution_filter.launch
```
