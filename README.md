# measure_message_passing
Test package to measure the time of message passing between ROS nodes.

# Usage

## Single node

```sh:
roslaunch measure_message_passing one_node.launch
(after some minutes, results will show.)
```

## Two nodes

```sh:
roslaunch measure_message_passing two_node.launch
(after some minutes, results will show.)
```

## Two nodelets

```sh:
roslaunch measure_message_passing two_nodelet.launch
(after some minutes, results will show.)
```

## Arguments

### pointer
Using shared_ptr, set pointer:=true.

### stop_count
To set message passing count, set stop_count:=value.

# Result

## msi GS30 2M
* CPU: Intel(R) Core(TM) i7-5700HQ CPU @ 2.70GHz
* RAM: 16[GB] 
* Linux: 4.4.0-45-generic
* Ubuntu: 14.04.1
* ROS: indigo
  - one_node (not pointer):    Mean: 0.000417616, Median: 0.000419667, Max: 0.00323832
  - one_node (pointer):        Mean: 0.000400242, Median: 0.000391842, Max: 0.00531147
  - two_node (not_pointer):    Mean: 0.001161430, Median: 0.001156670, Max: 0.00906191
  - two_node (pointer):        Mean: 0.001249300, Median: 0.001233170, Max: 0.00832612
  - two_nodelet (not pointer): Mean: 0.000306608, Median: 0.000308094, Max: 0.00165378
  - two_nodelet (pointer):     Mean: 0.000304206, Median: 0.000305576, Max: 0.00101942

