cmake_minimum_required(VERSION 2.8.3)
project(pointcloud_filters)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  std_srvs
  rcomponent
)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    pointcloud2_filters
  CATKIN_DEPENDS
    roscpp
    std_msgs
    sensor_msgs
    std_srvs
    rcomponent
  DEPENDS
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(pointcloud2_filters src/lower_resolution_filter.cpp src/pointcloud_filters.cpp)
add_dependencies(pointcloud2_filters ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library target against
target_link_libraries(pointcloud2_filters
  ${catkin_LIBRARIES}
)

## Declare a C++ executable
add_executable(lower_resolution_filter_node src/lower_resolution_filter_node.cpp)
add_dependencies(lower_resolution_filter_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_executable(pointcloud_filters_node src/pointcloud_filters_node.cpp)
add_dependencies(pointcloud_filters_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a executable target against
target_link_libraries(lower_resolution_filter_node
  ${catkin_LIBRARIES}
  pointcloud2_filters
)
target_link_libraries(pointcloud_filters_node
  ${catkin_LIBRARIES}
  pointcloud2_filters
)

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS pointcloud2_filters lower_resolution_filter_node pointcloud_filters_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Modify this if launch or config folders are deleted
install(
  DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
