#include <iostream>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>



class ColorDetector
{
	ros::NodeHandle n_;
	ros::Subscriber camSub_;
	ros::Subscriber odomSub_;
	ros::Publisher vis_pub_;
	visualization_msgs::Marker marker_;
	int red_depth_ = 200;  //0-255
	int blue_depth_ = 200; //0-255
	int points_ = 20; 
	
	public:
		ColorDetector() 
		{   
			vis_pub_ = n_.advertise<visualization_msgs::Marker>( "visualization_marker", 0);
			camSub_ = n_.subscribe("/camera/image_raw", 1, &ColorDetector::cameraCallback, this);
			odomSub_ = n_.subscribe("/mobile_base_controller/odom", 1, &ColorDetector::odomCallback, this);	
			
			marker_.header.frame_id = "odom";
			marker_.ns = "my_namespace";
			marker_.id = 0;
			marker_.type = visualization_msgs::Marker::CUBE;
			marker_.action = visualization_msgs::Marker::ADD;
			marker_.scale.x = 0.1;
			marker_.scale.y = 0.1;
			marker_.scale.z = 0.1;
			marker_.color.a = 1.0;		
		}

		
		void cameraCallback(const sensor_msgs::Image::ConstPtr& img)
		{
			int i = 0;
			bool check = false;
			
			for(i; i < img->height; i++)
			{
				int j = 0;
				for(j; j < img->step-3; j += 3)
				{
					if ((int)img->data[i*img->step + j] > 200)
					{
						ROS_INFO("RED");
						marker_.header.stamp = ros::Time();
						if(marker_.id > points_)
							marker_.id = 0;
						else
							marker_.id += 1;
						marker_.color.r = 1.0;
						marker_.color.g = 0.0;
						marker_.color.b = 0.0;
						vis_pub_.publish(marker_);
						check = true;
						break;
					}
					else if ((int)img->data[i*img->step + (j + 2)] > 200)
					{
						ROS_INFO("BLUE");
						marker_.header.stamp = ros::Time();
						if(marker_.id > points_)
							marker_.id = 0;
						else
							marker_.id += 1;
						marker_.color.r = 0.0;
						marker_.color.g = 0.0;
						marker_.color.b = 1.0;
						vis_pub_.publish(marker_);
						check = true;
						break;
					}
				}
			 if(check)
				break;
			}
		}
		
		void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
		{
			marker_.pose = odom -> pose.pose;
		}
	
};

int main(int argc, char *argv[]) 
{

	ros::init(argc, argv, "detect_color_node");
	ColorDetector cd;
	ros::Rate rate(1);
	while (ros::ok()) 
	{
		ros::spinOnce();
        rate.sleep();
    }
	return 0;
}


