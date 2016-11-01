#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <nodelet/nodelet.h>
#include <measure_message_passing/MeasureTime.h>
#include <unistd.h>

namespace measure_message_passing{

class MeasureTimeNodelet: public nodelet::Nodelet
{
public:

	MeasureTimeNodelet() {}

private:

	virtual void onInit(void);

	boost::shared_ptr<MeasureTime> pimpl;

}; // class MeasureTimeNodelet

void MeasureTimeNodelet::onInit()
{
	NODELET_DEBUG("Initializing MeasureTime nodelet");

	ros::NodeHandle nh = getNodeHandle();
	pimpl.reset(new MeasureTime(nh, getPrivateNodeHandle()));

	bool flag_pointer, flag_start;
	nh.param<bool>("pointer", flag_pointer, false);
	nh.param<bool>("start", flag_start, true);

	if(flag_start){
		sleep(2);
		ros::Publisher pub_ = nh.advertise<sensor_msgs::Image>("pub", 10);
		cv::Mat m(640, 480, CV_8U, cv::Scalar(0,0,255));
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
}

} // namespace measure_message_passing

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(measure_message_passing::MeasureTimeNodelet, nodelet::Nodelet);
