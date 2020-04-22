cmake_minimum_required(VERSION 3.5)
project(measure_delay_ros2)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(include)
add_library(measure_delay SHARED src/send_image.cpp src/measure_delay.cpp)

target_compile_definitions(measure_delay PRIVATE "GREEER_BUILDING_DLL")
ament_target_dependencies(measure_delay
  rclcpp
  rclcpp_components
  cv_bridge
  sensor_msgs
  OpenCV
  )
rclcpp_components_register_nodes(measure_delay "measure_delay_ros2::SendImage")
rclcpp_components_register_nodes(measure_delay "measure_delay_ros2::MeasureDelay")

ament_export_dependencies(ament_cmake)
ament_export_dependencies(rclcpp)
ament_export_dependencies(rclcpp_components)
ament_export_dependencies(sensor_msgs)

ament_export_include_directories(include)

ament_export_libraries(measure_delay)

install(DIRECTORY
  include/measure_delay_ros2
  DESTINATION include
  )

install(TARGETS
  measure_delay
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  )

ament_package()
