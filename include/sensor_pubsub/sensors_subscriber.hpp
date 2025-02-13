//
// Created by Robbie on 2/12/25.
//

#ifndef SENSOR_SUBSCRIBER_HPP
#define SENSOR_SUBSCRIBER_HPP

#include "rclcpp/rclcpp.hpp"
#include "wheelchair_sensor_msgs/msg/sensors.hpp"

class SensorsSubscriber
{
public:
    SensorsSubscriber(rclcpp::Node::SharedPtr node);

private:
    void topic_callback(const wheelchair_sensor_msgs::msg::Sensors::SharedPtr msg) const;
    rclcpp::Subscription<wheelchair_sensor_msgs::msg::Sensors>::SharedPtr subscription_;
    rclcpp::Node::SharedPtr node_;
};

#endif // SENSOR_SUBSCRIBER_HPP
