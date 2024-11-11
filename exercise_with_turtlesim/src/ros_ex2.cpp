#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
//Add the required header
#include "turtlesim/Kill.h"
// library to use the funcion sleep
#include "unistd.h"


ros::Publisher pub;

// using a flag in order to identify which side of the crooss the turtle is doing
int flag = 0;
// choosing a tolerance to indicate that the turtle is in a neighborhood of the centre (5.5, 5.5, 0)
double epsilon = 0.1;




// --------------------------------------------------------------------------------------------------------	
// -------code to make the turtle move as REQUEST IN EX_2 --> doing a CROSS (+ add the main below) --------	

	
void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
	ROS_INFO("Turtle subscriber@[%f, %f, %f], flag = %d", 
	msg->x, msg->y, msg->theta, flag);
	geometry_msgs::Twist my_vel;	
	
	// frequency of the cycle
	ros::Rate loop_rate(100);
	
	// putting all in a while
	while (ros::ok())
	{
		if ( flag == 0 )					 
		{
			my_vel.linear.x = 1.0;				// the turtle must go forward
			my_vel.linear.y = 0;
			my_vel.angular.z = 0;
		}

		// (old if below) if(msg->x >= 10.5 || msg->y >= 11.0 || msg->x <= 0 || msg->y <= 0)
		
		// if the turtle goes outside the edges of the square		
		if ( msg->x >= 10.0 || msg->y >= 10.0 || msg->x <= 1 || msg->y <= 1 )
		{
			flag = 1;							
		}
		
		if ( flag == 1 )					
		{
			my_vel.linear.x = -1.0;			// the turtle must go backward
			my_vel.linear.y = 0;
			my_vel.angular.z = 0;
		}
		
		// if the turtle is in a neighborhood of the centre (5.5, 5.5, 0)
		if ( flag == 1 && ( (abs(msg->x - 5.5) <= epsilon) && (abs(msg->y - 5.5) <= epsilon)))
		{
			my_vel.linear.x = 0;
			my_vel.linear.y = 0;
			my_vel.angular.z = 1.57;			// the turtle must rotate about 90°
			// publishing the message 
			pub.publish(my_vel);
			sleep(1);					// wait for 1 second
			
			flag = 0;				
		}
		

		// publishing the updated message
		pub.publish(my_vel);

		// in order to do the while only once
		ros::spinOnce();
		loop_rate.sleep();


	}
	
	
}


	/*


// ---------------------------------------------------------------------------------------------------------
// ------------------------------ VERSION WITHOUT THE ROTATION (to be finished)-----------------------------
	
void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
	ROS_INFO("Turtle subscriber@[%f, %f, %f], flag = %d, %d",  
	msg->x, msg->y, msg->theta, flag, (msg->y <= 5.5 && flag == 3));
	geometry_msgs::Twist my_vel;	
	
	// frequency of the cycle
	ros::Rate loop_rate(100);
	
	// putting all in a while
	while (ros::ok())
	{
		if ( flag == 0 )					// if the turtle is in the 1st path
		{
			my_vel.linear.x = 1.0;				// to go forward until 10.5
			my_vel.linear.y = 0;
			my_vel.angular.z = 0;
		}
	
		if ( msg->x >= 10.5 )
		{
			flag = 1;					// --> 2nd path		
		}
		
		if ( flag == 1 )					// if the turtle is in the 2nd path
		{
			my_vel.linear.x = -1.0;			// to go backward
			my_vel.linear.y = 0;
			my_vel.angular.z = 0;
		}
		
		if ( msg->x <= 5.5 && flag == 1 )
		{
			flag = 2;					// --> 3rd path		
		}
		
		if ( flag == 2 )					// if the turtle is in the 3rd path
		{
			my_vel.linear.x = 0;		
			my_vel.linear.y = 1.0;
			my_vel.angular.z = 0;
		}
		
		if ( msg->y >= 11.0 && flag == 2)
		{
			flag = 3;					// --> 4th path
		}
		
		if ( flag == 3 )					// if the turtle is in the 4th path
		{
			my_vel.linear.x = 0;		
			my_vel.linear.y = -1.0;
			my_vel.angular.z = 0;
		}
		
		if ( msg->y <= 5.5 && flag == 3 )
		{
			flag = 4;					// --> 5th path
		}

		if ( flag == 4 )
		{
			my_vel.linear.x = -1.0;		
			my_vel.linear.y = 0;
			my_vel.angular.z = 0;
		}
		

		// publishing the updated message
		pub.publish(my_vel);

		// in order to do the while only once
		ros::spinOnce();
		loop_rate.sleep();


	}
	
	
}

// ---------------------------------------------------------------------------------------------------------	
// ---------------------------------------------------------------------------------------------------------	


	*/


// ------- MAIN --------------------------------------------------------------------------------------------	

int main (int argc, char **argv)
{
	// Initialize the node, setup the NodeHandle for handling the communication with the ROS //system  
	ros::init(argc, argv, "turtlebot_subscriber");  
	ros::NodeHandle nh;
	
	// Define the subscriber to turtle's position  (--> turtle1)
	pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1);  //check the topic name
	ros::Subscriber sub = nh.subscribe("turtle1/pose", 1,turtleCallback);  //check the topic name
	
	// the spawn of turtle1 is automatic --> I don't need specific services
	
	ros::spin();
	return 0;
	
	
}

