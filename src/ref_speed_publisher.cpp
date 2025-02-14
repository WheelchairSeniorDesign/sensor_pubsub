//
// Created by Robbie on 2/14/25.
//

#include "sensor_pubsub/ref_speed_publisher.hpp"

RefSpeedPublisher::RefSpeedPublisher(rclcpp::Node::SharedPtr node)
: node_(node)
{
    publisher_ = node_->create_publisher<wheelchair_sensor_msgs::msg::RefSpeed>("ref_speed", 10);
}

void RefSpeedPublisher::trigger_publish(RefSpeed ref_speed) {
    auto message = wheelchair_sensor_msgs::msg::RefSpeed();
    message.left_speed = ref_speed.leftSpeed;
    message.right_speed = ref_speed.rightSpeed;
    this->publisher_->publish(message);
}