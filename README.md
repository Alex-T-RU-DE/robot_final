# robot_for_student_template

This robot developed as student template for Master courses (Mobile robotics) in Hochschule Emden/Leer  by [Alex-T-RU-DE](https://github.com/Alex-T-RU-DE/) and [mikhail-chirkov](https://github.com/mikhail-chirkov)

Robot was designed in Solidworks. 

To start the robot use :

```
roslaunch robot_final start.launch
```

The robot has to explore the map with an explore lite ROS package or simply set a goal through 2D Nav goal. 
When the robot sees red or blue areas (just simply image_raw analysis, no OpenCV or NN) it will publish (visualize) 20 squares in rviz in 20 previous robot's positions where red or blue areas were found.
