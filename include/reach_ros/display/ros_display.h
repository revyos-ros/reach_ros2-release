/*
 * Copyright 2019 Southwest Research Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef REACH_ROS_ROS_REACH_DISPLAY_H
#define REACH_ROS_ROS_REACH_DISPLAY_H

#include <reach/interfaces/display.h>

#include <rclcpp/publisher.hpp>
#include <interactive_markers/interactive_marker_server.hpp>
#include <visualization_msgs/msg/interactive_marker_feedback.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

namespace reach_ros
{
namespace display
{
class ROSDisplay : public reach::Display
{
public:
  ROSDisplay(std::string kinematic_base_frame, double marker_scale, bool use_full_color_range, float hue_low_score,
             float hue_high_score);

  void showEnvironment() const override;
  void updateRobotPose(const std::map<std::string, double>& pose) const override;
  void showResults(const reach::ReachResult& db) const override;
  void showReachNeighborhood(const std::map<std::size_t, reach::ReachRecord>& neighborhood) const override;

  void setCollisionMarker(std::string collision_mesh_filename, const std::string collision_mesh_frame);

protected:
  const std::string kinematic_base_frame_;
  const double marker_scale_;
  const bool use_full_color_range_;
  const float hue_low_score_;
  const float hue_high_score_;
  visualization_msgs::msg::Marker collision_marker_;

  // ROS comoponents
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr mesh_pub_;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr neighbors_pub_;
  std::shared_ptr<interactive_markers::InteractiveMarkerServer> server_;
};

struct ROSDisplayFactory : public reach::DisplayFactory
{
  reach::Display::ConstPtr create(const YAML::Node& config) const override;
};

}  // namespace display
}  // namespace reach_ros

#endif  // REACH_ROS_ROS_REACH_DISPLAY_H
