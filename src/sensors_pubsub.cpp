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
#include <thread>
#include <mutex>
#include "rclcpp/rclcpp.hpp"
#include "sensor_pubsub/fan_publisher.hpp"
#include "sensor_pubsub/sensors_subscriber.hpp"
#include "sensor_pubsub/light_publisher.hpp"
#include "sensor_pubsub/fingerprint_subscriber.hpp"
#include "sensor_pubsub/ref_speed_publisher.hpp"

enum class Mode {
  FAN,
  LIGHT
};

void run_ref_speed_publisher(rclcpp::Node::SharedPtr node, std::shared_ptr<SensorsSubscriber> sensors_subscriber, std::shared_ptr<RefSpeedPublisher> ref_speed_publisher) {
  while (rclcpp::ok()) {
    auto sensor_data = sensors_subscriber->get_latest_sensor_data();
    RefSpeed ref_speed;
    ref_speed.leftSpeed = sensor_data.left_speed;
    ref_speed.rightSpeed = sensor_data.right_speed;
    ref_speed_publisher->trigger_publish(ref_speed);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("sensors_demo_node");
  auto fan_publisher = std::make_shared<FanPublisher>(node);
  auto light_publisher = std::make_shared<LightPublisher>(node);
  auto sensors_subscriber = std::make_shared<SensorsSubscriber>(node);
  auto fingerprint_subscriber = std::make_shared<FingerprintSubscriber>(node);

  //I made a second node to publish this because of the text input. Probably could do it all in one node normally
  auto ref_speed_node = std::make_shared<rclcpp::Node>("ref_speed_node");
  auto ref_speed_publisher = std::make_shared<RefSpeedPublisher>(ref_speed_node);

  std::thread spin_thread([&]() {
    rclcpp::spin(node);
  });

  std::thread ref_speed_thread(run_ref_speed_publisher, ref_speed_node, sensors_subscriber, ref_speed_publisher);

  Mode mode = Mode::FAN;
  std::string input;
  while (rclcpp::ok()) {
    std::cout << "Enter 'fan' to set fan speed or 'light' to set light state: ";
    std::cin >> input;
    if (input == "fan") {
      mode = Mode::FAN;
    } else if (input == "light") {
      mode = Mode::LIGHT;
    } else {
      std::cout << "Invalid mode. Please enter 'fan' or 'light'." << std::endl;
      continue;
    }

    if (mode == Mode::FAN) {
      int fan_input;
      std::cout << "Enter a number to set fan_percent_0 (0-100): ";
      std::cin >> fan_input;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number." << std::endl;
      } else if (fan_input < 0 || fan_input > 100) {
        std::cout << "Invalid input. Please enter a number between 0 and 100." << std::endl;
      } else {
        FanSpeed fanSpeed;
        fanSpeed.fan_percent_0 = fan_input;
        fanSpeed.fan_percent_1 = 0;
        fanSpeed.fan_percent_2 = 0;
        fanSpeed.fan_percent_3 = 0;
        fan_publisher->trigger_publish(fanSpeed);
      }
    } else if (mode == Mode::LIGHT) {
      int light_input;
      std::cout << "Enter a number to set light state (0 to 2): ";
      std::cin >> light_input;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number." << std::endl;
      } else if (light_input < 0 || light_input > 2) {
        std::cout << "Invalid input. Please enter 0, 1, or 2." << std::endl;
      } else {
        LightStates lightState = static_cast<LightStates>(light_input);
        light_publisher->trigger_publish(lightState);
      }
    }
  }

  rclcpp::shutdown();
  spin_thread.join();
  ref_speed_thread.join();
  return 0;
}