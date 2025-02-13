// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "sensor_pubsub/fan_publisher.hpp"
#include "sensor_pubsub/sensors_subscriber.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("fan_publisher_node");
  auto fan_publisher = std::make_shared<FanPublisher>(node);
  auto sensors_subscriber = std::make_shared<SensorsSubscriber>(node);

  std::thread spin_thread([&]() {
    rclcpp::spin(node);
  });

  int input;
  while (rclcpp::ok()) {
    std::cout << "Enter a number to set fan_percent_0 (0-100): ";
    std::cin >> input;
    if (std::cin.fail()) {
      std::cin.clear(); // clear the error flag
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
      std::cout << "Invalid input. Please enter a number." << std::endl;
    } else if (input < 0 || input > 100) {
      std::cout << "Invalid input. Please enter a number between 0 and 100." << std::endl;
    } else {
      FanSpeed fanSpeed;
      fanSpeed.fan_percent_0 = input;
      fanSpeed.fan_percent_1 = 0;
      fanSpeed.fan_percent_2 = 0;
      fanSpeed.fan_percent_3 = 0;
      fan_publisher->trigger_publish(fanSpeed);
    }
  }

  rclcpp::shutdown();
  spin_thread.join();
  return 0;
}