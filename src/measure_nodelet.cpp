#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <nodelet/nodelet.h>
#include <measure_message_passing/MeasureTime.h>
#include <unistd.h>

namespace measure_message_passing{

#ifndef use_ptr
class MeasureTimeNodelet: public nodelet::Nodelet
{
public:

	MeasureTimeNodelet() {}
#else
class MeasureTimeNodeletPointer: public nodelet::Nodelet
{
public:

	MeasureTimeNodeletPointer() {}
#endif

private:

	virtual void onInit(void);

	boost::shared_ptr<MeasureTime> pimpl;

}; // class MeasureTimeNodelet

#ifndef use_ptr
void MeasureTimeNodelet::onInit()
#else
void MeasureTimeNodeletPointer::onInit()
#endif
{
	NODELET_DEBUG("Initializing MeasureTime nodelet");

	ros::NodeHandle nh = getNodeHandle();
	pimpl.reset(new MeasureTime(nh, getPrivateNodeHandle()));

	bool flag_start;
	nh.param<bool>("start", flag_start, true);

	if(flag_start){
		sleep(2);
		ros::Publisher pub_ = nh.advertise<sensor_msgs::Image>("pub", 10);
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

#include <pluginlib/class_list_macros.h>
#ifndef use_ptr
PLUGINLIB_EXPORT_CLASS(measure_message_passing::MeasureTimeNodelet, nodelet::Nodelet);
#else
PLUGINLIB_EXPORT_CLASS(measure_message_passing::MeasureTimeNodeletPointer, nodelet::Nodelet);
#endif
