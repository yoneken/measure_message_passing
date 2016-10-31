#include <ros/ros.h>
#include <std_msgs/Time.h>
#include <boost/shared_ptr.hpp>
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
}

} // namespace measure_message_passing

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(measure_message_passing::MeasureTimeNodelet, nodelet::Nodelet);
