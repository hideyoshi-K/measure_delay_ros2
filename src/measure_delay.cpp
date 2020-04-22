#include "measure_delay_ros2/measure_delay.hpp"

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

namespace measure_delay_ros2
{
    MeasureDelay::MeasureDelay(const rclcpp::NodeOptions & options)
        : Node("recver", options)
    {
        m_sub = this->create_subscription<sensor_msgs::msg::Image>("image", 1, std::bind(&MeasureDelay::topicCallback, this, std::placeholders::_1));
    }

    void MeasureDelay::topicCallback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        msg->header.stamp = rclcpp::Clock().now();
        
        rclcpp::Clock ros_clock(RCL_ROS_TIME);
        double diff = (ros_clock.now() - msg->header.stamp).nanoseconds() / 1000000.0;
        
        RCLCPP_INFO(this->get_logger(), "%lf, (%d, %d)", diff, msg->width, msg->height);
    }
}

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(measure_delay_ros2::MeasureDelay)
