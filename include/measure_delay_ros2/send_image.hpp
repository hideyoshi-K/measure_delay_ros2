#if !defined GREETER_ROS2_STYLE__GREETER_NODE_HPP_
#define GREETER_ROS2_STYLE__GREETER_NODE_HPP_

#if __cplusplus
extern "C" {
    #endif

    // The below macros are taken from https://gcc.gnu.org/wiki/Visibility and from
    // demos/composition/include/composition/visibility_control.h at https://github.com/ros2/demos
    #if defined _WIN32 || defined __CYGWIN__
      #ifdef __GNUC__
#define GREETER_EXPORT __attribute__ ((dllexport))
#define GREETER_IMPORT __attribute__ ((dllimport))
      #else
#define GREETER_EXPORT __declspec(dllexport)
#define GREETER_IMPORT __declspec(dllimport)
      #endif
      #ifdef GREETER_BUILDING_DLL
        #define GREETER_PUBLIC GREETER_EXPORT
      #else
        #define GREETER_PUBLIC GREETER_IMPORT
      #endif
      #define GREETER_PUBLIC_TYPE GREETER_PUBLIC
      #define GREETER_LOCAL
    #else
#define GREETER_EXPORT __attribute__ ((visibility("default")))
      #define GREETER_IMPORT
      #if __GNUC__ >= 4
#define GREETER_PUBLIC __attribute__ ((visibility("default")))
#define GREETER_LOCAL  __attribute__ ((visibility("hidden")))
      #else
        #define GREETER_PUBLIC
        #define GREETER_LOCAL
      #endif
      #define GREETER_PUBLIC_TYPE
    #endif

    #if __cplusplus
    
} // extern "C"
#endif

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>

namespace measure_delay_ros2
{
    class SendImage : public rclcpp::Node
    {
    public:
        GREETER_PUBLIC explicit SendImage(const rclcpp::NodeOptions & options);

    private:
        void sendImage();

    private:
        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr m_pub;
        rclcpp::TimerBase::SharedPtr m_timer;

        cv::Mat m_img;
    };
} 

#endif 
