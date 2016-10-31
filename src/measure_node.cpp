#include <ros/ros.h>
#include <std_msgs/Time.h>
#include <boost/shared_ptr.hpp>
#include <measure_message_passing/MeasureTime.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "measure_message_passing");
	ros::NodeHandle nh;

	measure_message_passing::MeasureTime mt(nh, nh);

	bool flag_pointer, flag_start;
	nh.param<bool>("pointer", flag_pointer, false);
	nh.param<bool>("start", flag_start, true);

	if(flag_start){
		sleep(2);
		ros::Publisher pub_;
		if(!flag_pointer){
			pub_ = nh.advertise<std_msgs::Time>("pub", 10);
			std_msgs::Time now;
			now.data = ros::Time::now();
			pub_.publish(now);
		}else{
			pub_ = nh.advertise<std_msgs::Time>("pub", 10);
			boost::shared_ptr<std_msgs::Time>now(new std_msgs::Time());
			now->data = ros::Time::now();
			pub_.publish(now);
		}
	}

	ros::spin();

	return 0;
}
