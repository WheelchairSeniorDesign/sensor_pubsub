//
// Created by aec117-fkmj9r3 on 2/12/25.
//

#include "sensor_pubsub/sensors_subscriber.hpp"

SensorsSubscriber::SensorsSubscriber(){
  subscription_ = this->create_subscription<wheelchair_sensor_msgs::msg::Sensors>(
    "sensors", 10, std::bind(&SensorsSubscriber::topic_callback, this, std::placeholders::_1));
  }

  void SensorsSubscriber::topic_callback(const wheelchair_sensor_msgs::msg::Sensors::SharedPtr msg) const
  {
  RCLCPP_INFO(this->get_logger(),
  "I heard: left_speed=%d, right_speed=%d, ultrasonic_front_0=%d, ultrasonic_front_1=%d, ultrasonic_back=%d, ultrasonic_left=%d, ultrasonic_right=%d, "
  "pir_front=%s, pir_back=%s, pir_left=%s, pir_right=%s, fan_speed_0=%d, fan_speed_1=%d, fan_speed_2=%d, fan_speed_3=%d, "
  "linear_acceleration_x=%.2f, linear_acceleration_y=%.2f, linear_acceleration_z=%.2f, angular_velocity_x=%.2f, angular_velocity_y=%.2f, angular_velocity_z=%.2f, "
  "magnetic_field_x=%.2f, magnetic_field_y=%.2f, magnetic_field_z=%.2f",
  msg->left_speed, msg->right_speed, msg->ultrasonic_front_0, msg->ultrasonic_front_1, msg->ultrasonic_back, msg->ultrasonic_left, msg->ultrasonic_right,
  msg->pir_front ? "true" : "false", msg->pir_back ? "true" : "false", msg->pir_left ? "true" : "false", msg->pir_right ? "true" : "false",
  msg->fan_speed_0, msg->fan_speed_1, msg->fan_speed_2, msg->fan_speed_3,
  msg->linear_acceleration_x, msg->linear_acceleration_y, msg->linear_acceleration_z, msg->angular_velocity_x, msg->angular_velocity_y, msg->angular_velocity_z,
  msg->magnetic_field_x, msg->magnetic_field_y, msg->magnetic_field_z);_3);
  }