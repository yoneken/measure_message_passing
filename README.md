# measure_message_passing
Test package to measure the time of message passing between ROS nodes.

# Result

## msi GS30 2M
* CPU: Intel(R) Core(TM) i7-5700HQ CPU @ 2.70GHz
* RAM: 16[GB] 
* Linux: 4.4.0-45-generic
* Ubuntu: 14.04.1
* ROS: indigo
  - one_node (not pointer):    Mean: 9.87470e-06, Median: 9.85322e-06, Max: 0.000259214
  - one_node (pointer):        Mean: 9.50545e-06, Median: 9.49499e-06, Max: 0.000259395
  - two_node (not_pointer):    Mean: 2.34549e-05, Median: 2.44388e-05, Max: 0.00311695
  - two_node (pointer):        Mean: 2.28278e-05, Median: 2.32482e-05, Max: 0.00400325
  - two_nodelet (not pointer): Mean: 1.51631e-05, Median: 1.59681e-05, Max: 0.0019757
  - two_nodelet (pointer):     Mean: 1.56770e-05, Median: 1.57873e-05, Max: 0.00203611

