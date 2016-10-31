#include <ros/ros.h>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <std_msgs/Time.h>

using namespace boost::accumulators;

namespace measure_message_passing
{

class MeasureTime
{
public:
	//MeasureTime(const ros::NodeHandle& nh=ros::NodeHandle());
	MeasureTime(ros::NodeHandle nh, ros::NodeHandle private_nh);

	enum Mode{ ros_Time = 0, std_msgs_Time, std_msgs_TimeConstPtr, };

protected:
	ros::NodeHandle root_nh_;
	ros::Publisher pub_;
	ros::Subscriber sub_;

	int counter_, stop_count_;
	bool flag_pointer_;

	accumulator_set<double, stats<tag::mean, tag::median, tag::max> > acc_;

	void callback(std_msgs::Time time);
	void callback(const std_msgs::TimeConstPtr &time);

	void countUp(double delay);
};

} // namespace measure_message_passing

