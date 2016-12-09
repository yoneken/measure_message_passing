# measure_message_passing
Test package to measure the time of message passing between ROS nodes.

# Usage

## Single node

```sh:
roslaunch measure_message_passing one_node.launch
(after some minutes, results will show.)
```

## Single node with pointer

```sh:
roslaunch measure_message_passing one_node_ptr.launch
(after some minutes, results will show.)
```

## Two nodes

```sh:
roslaunch measure_message_passing two_node.launch
(after some minutes, results will show.)
```

## Two nodes with pointer

```sh:
roslaunch measure_message_passing two_node_ptr.launch
(after some minutes, results will show.)
```

## Two nodelets

```sh:
roslaunch measure_message_passing two_nodelet.launch
(after some minutes, results will show.)
```

## Two nodelets with pointer

```sh:
roslaunch measure_message_passing two_nodelet_ptr.launch
(after some minutes, results will show.)
```

## Arguments

### stop_count
To set message passing count, set stop_count:=value.

# Result

## msi GS30 2M
* CPU: Intel(R) Core(TM) i7-5700HQ CPU @ 2.70GHz
* RAM: 16[GB] 
* Linux: 4.4.0-45-generic
* Ubuntu: 14.04.1
* ROS: indigo
  - one_node (not pointer):    Mean: 0.00140118, Median: 0.00139828, Max: 0.00454532
  - one_node (pointer):        Mean: 5.4087e-06, Median: 3.53647e-06, Max: 0.000275296
  - two_node (not_pointer):    Mean: 0.00235323, Median: 0.00236079, Max: 0.00825729
  - two_node (pointer):        Mean: 0.00088381, Median: 0.00087349, Max: 0.0030891
  - two_nodelet (not pointer): Mean: 0.000689175, Median: 0.000686938, Max: 0.00333391
  - two_nodelet (pointer):     Mean: 5.41813e-05, Median: 4.98603e-05, Max: 0.000194368

