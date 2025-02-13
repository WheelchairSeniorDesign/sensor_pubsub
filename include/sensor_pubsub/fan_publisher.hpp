//
// Created by Robbie on 2/12/25.
//

#ifndef FAN_PUBLISHER_HPP
#define FAN_PUBLISHER_HPP

#include "rclcpp/rclcpp.hpp"
#include "wheelchair_sensor_msgs/msg/fan_speed.hpp"

class FanPublisher : public rclcpp::Node
{
public:
    FanPublisher();
    void trigger_publish(int fan_percent_0); // New method to trigger publishing

private:
    rclcpp::Publisher<wheelchair_sensor_msgs::msg::FanSpeed>::SharedPtr publisher_;
    size_t count_;
};

/**
class FanPublisher : public rclcpp::Node
{
public:
    FanPublisher();

private:
    void timer_callback();
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<wheelchair_sensor_msgs::msg::FanSpeed>::SharedPtr publisher_;
    size_t count_;
};
**/

#endif // FAN_PUBLISHER_HPP
