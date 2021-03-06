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
	root_nh_.param("stop_count", stop_count_, 10000);

	pub_ = root_nh_.advertise<sensor_msgs::Image>("pub", 10);

	// init pub/sub
	sub_ = root_nh_.subscribe("sub", 10, &MeasureTime::callback, this);
}

#ifndef use_ptr
void MeasureTime::callback(sensor_msgs::Image img)
{
	double delay = (ros::Time::now() - img.header.stamp).toSec();
	countUp(delay);
}
#else
void MeasureTime::callback(const sensor_msgs::ImageConstPtr &img)
{
	double delay = (ros::Time::now() - img->header.stamp).toSec();
	countUp(delay);
	//std::cout << delay << std::endl;
}
#endif

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
		cv::Mat m(1024, 768, CV_8U, cv::Scalar(0,0,255));
		sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", m).toImageMsg();

#ifndef use_ptr
		sensor_msgs::Image img = sensor_msgs::Image();
		img.height = msg->height;
		img.width = msg->width;
		img.encoding = msg->encoding;
		img.is_bigendian = msg->is_bigendian;
		img.step = msg->step;
		img.data = msg->data;
		img.header.stamp = ros::Time::now();
		pub_.publish(img);
#else
		msg->header.stamp = ros::Time::now();
		pub_.publish(msg);
#endif
	}
}

} // namespace measure_message_passing
