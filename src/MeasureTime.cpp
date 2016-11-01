#include <measure_message_passing/MeasureTime.h>
#include <cv_bridge/cv_bridge.h>
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

	pub_ = root_nh_.advertise<sensor_msgs::Image>("pub", 10);

	// init pub/sub
	sub_ = root_nh_.subscribe("sub", 10, &MeasureTime::callback, this);
}

void MeasureTime::callback(sensor_msgs::Image img)
{
	double delay = (ros::Time::now() - img.header.stamp).toSec();
	countUp(delay);
}

void MeasureTime::callback(const sensor_msgs::ImageConstPtr &img)
{
	double delay = (ros::Time::now() - img->header.stamp).toSec();
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
		cv::Mat m(640, 480, CV_8U, cv::Scalar(0,0,255));
		sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", m).toImageMsg();

		if(!flag_pointer_){
			sensor_msgs::Image img = sensor_msgs::Image();
			img.height = msg->height;
			img.width = msg->width;
			img.encoding = msg->encoding;
			img.is_bigendian = msg->is_bigendian;
			img.step = msg->step;
			img.data = msg->data;
			img.header = std_msgs::Header();
			pub_.publish(img);
		}else{
			pub_.publish(msg);
		}
	}
}

} // namespace measure_message_passing
