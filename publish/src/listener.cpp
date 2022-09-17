#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

#include <math.h>

class SubscribeAndPublish
{
public:
	SubscribeAndPublish()
	{
		// Topic you want to publish
		pub_ = n_.advertise<std_msgs::Float64>("/joint6/command", 1000);

		// Topic you want to subscribe
		sub_ = n_.subscribe("chatter", 1, &SubscribeAndPublish::chatterCallback, this);
	}

	void chatterCallback(const std_msgs::String::ConstPtr &msg)
	{
		int curr = std::stoi(msg->data.c_str());
		if (curr > prev)
		{
			std_msgs::Float64 msg_to_send;
			int rotate = 1;
			if (direction)
			{
				msg_to_send.data = -rotate;
			} else {
				msg_to_send.data = rotate;
			}
			
			pub_.publish(msg_to_send);
			
			direction = !direction;
		}
		prev = curr;
	}

private:
	ros::NodeHandle n_;
	ros::Publisher pub_;
	ros::Subscriber sub_;

	
	int prev = -1;
	bool direction = true;
};

int main(int argc, char **argv)
{
	// Initiate ROS
	ros::init(argc, argv, "rotation");

	// Create an object of class SubscribeAndPublish that will take care of everything
	SubscribeAndPublish SAPObject;

	ros::spin();

	return 0;
}
