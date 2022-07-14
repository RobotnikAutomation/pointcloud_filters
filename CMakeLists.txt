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
    ${PROJECT_NAME}
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
add_library(${PROJECT_NAME} src/lower_resolution_filter.cpp src/pointcloud_filters.cpp)
add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library target against
target_link_libraries(${PROJECT_NAME}
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
  ${PROJECT_NAME}
)
target_link_libraries(pointcloud_filters_node
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}
)

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME} lower_resolution_filter_node pointcloud_filters_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Modify this if launch or config folders are deleted
install(
  DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
