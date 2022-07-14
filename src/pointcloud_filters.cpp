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
  readParam(pnh_, "example_subscriber_name", example_subscriber_name_, "example", not_required);
}

int PointCloudFilters::rosSetup()
{
  RComponent::rosSetup();

  bool required = true;
  bool not_required = false;

  // Publisher
  status_pub_ = pnh_.advertise<std_msgs::String>("status", 10);
  status_stamped_pub_ = pnh_.advertise<robotnik_msgs::StringStamped>("status_stamped", 10);

  // Subscriber
  example_sub_ = nh_.subscribe<std_msgs::String>(example_subscriber_name_, 10, &PointCloudFilters::exampleSubCb, this);
  addTopicsHealth(&example_sub_, "example_sub", 50.0, not_required);

  // Service
  example_server_ = pnh_.advertiseService("example", &PointCloudFilters::exampleServerCb, this);
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

void PointCloudFilters::exampleSubCb(const std_msgs::String::ConstPtr& msg)
{
  RCOMPONENT_WARN_STREAM("Received msg: " + msg->data);

  tickTopicsHealth("example_sub");
}

bool PointCloudFilters::exampleServerCb(std_srvs::Trigger::Request& request, std_srvs::Trigger::Response& response)
{
  RCOMPONENT_WARN_STREAM("Received srv trigger petition.");
  if (state != robotnik_msgs::State::READY_STATE)
  {
    response.success = false;
    response.message = "Received srv trigger petition. Component not ready.";
    return true;
  }
  else
  {
    response.success = true;
    response.message = "Received srv trigger petition. Component ready.";
    return true;
  }
  return false;
}
