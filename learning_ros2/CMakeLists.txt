cmake_minimum_required(VERSION 3.5)
project(learning_ros2)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(ros2_talker src/ros2_talker.cpp)
ament_target_dependencies(ros2_talker rclcpp std_msgs)

add_executable(ros2_listerner src/ros2_listerner.cpp)
ament_target_dependencies(ros2_listerner rclcpp std_msgs)


add_executable(ros2_server src/ros2_server.cpp)
ament_target_dependencies(ros2_server example_interfaces rclcpp)

add_executable(ros2_client src/ros2_client.cpp)
ament_target_dependencies(ros2_client example_interfaces rclcpp)

install(TARGETS
    ros2_talker
    ros2_listerner
    ros2_server
    ros2_client
    DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
