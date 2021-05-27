//tkDNN libs
#include <iostream>
#include <ros/ros.h>

#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>

#include <robot_final/PoseColorMsg.h>

class ColorDetector
{
	ros::NodeHandle n_;
	ros::Publisher poseColorPub_;
	ros::Subscriber camSub_;
	ros::Subscriber odomSub_;
	
	geometry_msgs::Pose currentPose_;
	
	public:
		ColorDetector() 
		{ 
			poseColorPub_ = n_.advertise<robot_final::PoseColorMsg>("pose_color_pub", 1);
			camSub_ = n_.subscribe("/camera/image_raw", 1, &ColorDetector::cameraCallback, this);
			odomSub_ = n_.subscribe("/mobile_base_controller/odom", 1, &ColorDetector::odomCallback, this);
		}

		
		void cameraCallback(const sensor_msgs::Image::ConstPtr& img)
		{
			int i = 0;
			for(i; i < img->height; i++)
			{
				int j = 0;
				for(j; j < img->step-3; j += 3)
				{
					if ((int)img->data[i*img->step + j] > 100)
					{
						ROS_INFO("RED");
						robot_final::PoseColorMsg outMsg;
						outMsg.pose = currentPose_;
						outMsg.color = "RED";
						poseColorPub_.publish(outMsg);
						break;
					}
					else if ((int)img->data[i*img->step + (j + 2)] > 100)
					{
						ROS_INFO("BLUE");
						robot_final::PoseColorMsg outMsg;
						outMsg.pose = currentPose_;
						outMsg.color = "BLUE";
						poseColorPub_.publish(outMsg);
						
						break;
					}
				}
			}
		}
		
		void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
		{
			currentPose_ = odom->pose.pose;
		}
	
};

int main(int argc, char *argv[]) 
{
	//init ros node
	ros::init(argc, argv, "detect_color_node");
 
	ColorDetector cd;

	ros::spin();

	return 0;
}


