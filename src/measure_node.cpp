#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
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
		ros::Publisher pub_ = nh.advertise<sensor_msgs::Image>("pub", 10);
		cv::Mat m(1024, 768, CV_8U, cv::Scalar(0,0,255));
		sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", m).toImageMsg();

		if(!flag_pointer){
			sensor_msgs::Image img = sensor_msgs::Image();
			img.height = msg->height;
			img.width = msg->width;
			img.encoding = msg->encoding;
			img.is_bigendian = msg->is_bigendian;
			img.step = msg->step;
			img.data = msg->data;
			img.header.stamp = ros::Time::now();
			pub_.publish(img);
		}else{
			msg->header.stamp = ros::Time::now();
			pub_.publish(msg);
		}
	}

	ros::spin();

	return 0;
}
