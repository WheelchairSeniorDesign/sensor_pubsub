cmake_minimum_required(VERSION 3.8)
project(sensor_pubsub)

#Default to C++14
if(NOT CMAKE_CXX_STANDARD)
set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Specify include directories for fan_speed target
include_directories(include)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(wheelchair_sensor_msgs REQUIRED)

add_executable(fan_speed
        src/sensors_pubsub.cpp
        src/fan_publisher.cpp)
ament_target_dependencies(fan_speed rclcpp wheelchair_sensor_msgs)

install(TARGETS
        fan_speed
        DESTINATION lib/${PROJECT_NAME})



ament_package()
