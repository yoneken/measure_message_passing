#include <ros/ros.h>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <sensor_msgs/Image.h>

using namespace boost::accumulators;

namespace measure_message_passing
{

class MeasureTime
{
public:
	//MeasureTime(const ros::NodeHandle& nh=ros::NodeHandle());
	MeasureTime(ros::NodeHandle nh, ros::NodeHandle private_nh);

protected:
	ros::NodeHandle root_nh_;
	ros::Publisher pub_;
	ros::Subscriber sub_;

	int counter_, stop_count_;
	bool flag_pointer_;

	accumulator_set<double, stats<tag::mean, tag::median, tag::max> > acc_;

	void callback(sensor_msgs::Image img);
	void callback(const sensor_msgs::ImageConstPtr &img);

	void countUp(double delay);
};

} // namespace measure_message_passing

