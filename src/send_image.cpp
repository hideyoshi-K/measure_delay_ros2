#include "measure_delay_ros2/send_image.hpp"

#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <cv_bridge/cv_bridge.h>

using namespace std::chrono_literals;

namespace measure_delay_ros2
{
    SendImage::SendImage(const rclcpp::NodeOptions & options)
        : Node("sender", options)
    {
        m_pub = create_publisher<sensor_msgs::msg::Image>("image", 1);
        
        m_timer = create_wall_timer(33ms, std::bind(&SendImage::sendImage, this));

        m_img = cv::Mat::zeros(3840, 1920, CV_8UC3);
    }

    void SendImage::sendImage()
    {
        auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", m_img).toImageMsg();
        
        m_pub->publish(*msg);
    }
}

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(measure_delay_ros2::SendImage)
