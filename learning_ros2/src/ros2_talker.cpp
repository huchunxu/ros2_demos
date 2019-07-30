#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"

#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class Talker : public rclcpp::Node
{
public:
	Talker() : Node("talker")
	{
		//ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
		rclcpp::QoS qos(rclcpp::KeepLast(7));
		pub_ = this->create_publisher<std_msgs::msg::String>("chatter", qos);

		auto publish_message = [this]() -> void {
			msg_ = std::make_unique<std_msgs::msg::String>();
			msg_->data = "Hello World: " + std::to_string(count_++);
			RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg_->data.c_str());

			//chatter_pub.publish(msg);
			pub_->publish(std::move(msg_));
		};

		// Use a timer to schedule periodic message publishing.
		timer_ = this->create_wall_timer(1s, publish_message);
	}

private:
	size_t count_ = 1;
	std::unique_ptr<std_msgs::msg::String> msg_;
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
	//ros::init(argc, argv, "talker");
	rclcpp::init(argc, argv);

	//ros::NodeHandle n;
	auto node = std::make_shared<Talker>();

	//ros::spin();
	rclcpp::spin(node);
	rclcpp::shutdown();

	return 0;
}
