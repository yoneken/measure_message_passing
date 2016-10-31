#include <measure_message_passing/MeasureTime.h>
#include <iostream>

namespace measure_message_passing
{

//MeasureTime::MeasureTime(const ros::NodeHandle& nh)
MeasureTime::MeasureTime(ros::NodeHandle nh, ros::NodeHandle private_nh)
: root_nh_(nh), counter_(0), acc_()
{
	// load parameters
	root_nh_.param<bool>("pointer", flag_pointer_, false);
	root_nh_.param("stop_count", stop_count_, 100000);

	pub_ = root_nh_.advertise<std_msgs::Time>("pub", 10);

	// init pub/sub
	sub_ = root_nh_.subscribe("sub", 10, &MeasureTime::callback, this);
}

void MeasureTime::callback(std_msgs::Time time)
{
	double delay = (ros::Time::now() - time.data).toSec();
	countUp(delay);
}

void MeasureTime::callback(const std_msgs::TimeConstPtr &time)
{
	double delay = (ros::Time::now() - time->data).toSec();
	countUp(delay);
}

void MeasureTime::countUp(double delay)
{
	acc_(delay);
	counter_++;

	if(counter_ > stop_count_){
		std::cout << "Mean: " << extract::mean(acc_) << ", "
			  << "Median: " << extract::median(acc_) << ", "
			  << "Max: " << extract::max(acc_) << std::endl;
		ros::shutdown();
	}else{
		if(!flag_pointer_){
			std_msgs::Time now;
			now.data = ros::Time::now();
			pub_.publish(now);
		}else{
			std_msgs::TimePtr now(new std_msgs::Time);
			now->data = ros::Time::now();
			pub_.publish(now);
		}
	}
}

} // namespace measure_message_passing
