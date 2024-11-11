#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
//Add the required header
#include "turtlesim/Kill.h"


ros::Publisher pub;

// --------------------------------------------------------------------------------------------------------	
// code to make the turtle move in a CIRCULAR PATH (+ add the main below) ---------------------------------
 
 	/*
 
void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
	ROS_INFO("Turtle subscriber@[%f, %f, %f]",  
	msg->x, msg->y, msg->theta);
	geometry_msgs::Twist my_vel;
	
	
	my_vel.linear.x = 1.0;
	my_vel.angular.z = 1.0;

	pub.publish(my_vel);	
}
	
	*/
	
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------


	
// --------------------------------------------------------------------------------------------------------	
// code to make the turtle move as REQUEST IN EX_1 (+ add the main below) ----------NEW VERSION------------	

// only problem: con (1,4 e 1, -4) è abb. preciso, ma non precisissimo, se metto (0.5,2 e 0.5, -2) fa schifo
	
void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
	ROS_INFO("Turtle subscriber@[%f, %f, %f]",  
	msg->x, msg->y, msg->theta);
	geometry_msgs::Twist my_vel;	
	
	// frequency of the cycle
	ros::Rate loop_rate(100);
	
	// putting all in a while
	while (ros::ok())
	{
	
		//modify the code for implementing the required behaviour
		my_vel.linear.x = 1.0;
		my_vel.angular.z = 0;
	
		// pub.publish(my_vel);	I remove it in order to stop the turtle
	
		// making the turtle moving as request
		if (msg->x > 9.0)
		{
			my_vel.linear.x = 1.0;			// linear velocity
			my_vel.angular.z = 4.0;		// angular vel > 0--> to turn left
		}
	
		if (msg->x < 2.0)
		{
			my_vel.linear.x = 1.0;			// linear velocity
			my_vel.angular.z = -4.0;		// angular vel < 0 --> to turn right
		}


		// publishing the updated message
		pub.publish(my_vel);

		// in order to do the while only once
		ros::spinOnce();
		loop_rate.sleep();


	}
	
	
}


	
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------



	/*

/ --------------------------------------------------------------------------------------------------------	
// code to make the turtle move as REQUEST IN EX_1 (+ add the main below) ---------OLD VERSION------------	
	
void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
	ROS_INFO("Turtle subscriber@[%f, %f, %f]",  
	msg->x, msg->y, msg->theta);
	geometry_msgs::Twist my_vel;	
	
	//modify the code for implementing the required behaviour
	my_vel.linear.x = 1.0;
	my_vel.angular.z = 0;
	
	// pub.publish(my_vel);	I remove it in order to stop the turtle
	
	// making the turtle moving as request
	if (msg->x > 9.0)
	{
		my_vel.linear.x = 1.0;			// linear velocity
		my_vel.angular.z = 1.0;		// angular vel > 0--> to turn left
	}
	
	if (msg->x < 2.0)
	{
		my_vel.linear.x = 1.0;			// linear velocity
		my_vel.angular.z = -1.0;		// angular vel < 0 --> to turn right
	}

	
	// publishing the updated message
	pub.publish(my_vel);
}
	

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

	*/


	/*

// Experiment NOT finished

// --------------------------------------------------------------------------------------------------------	
// code to make the turtle move doing a 'B' (+ add the main below) ----------------------------------------

void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
	ROS_INFO("Turtle subscriber@[%f, %f, %f]",  
	msg->x, msg->y, msg->theta);
	geometry_msgs::Twist my_vel;
	
	// 
	my_vel.linear.x = 0;
	my_vel.linear.y = 1.0;
	my_vel.angular.z = 0; 
	
	if (msg->y > 9)
	{
		my_vel.linear.x = 1.0;
		my_vel.linear.y = 0;
		my_vel.angular.z = 0;
	}
	
	if(msg->x > 7)
	{
		my_vel.linear.x = 3.0;
		my_vel.linear.y = 0;
		my_vel.angular.z = -1.0;
	}
	
	*/	
	
	/*	//--------------------------------------
	
	
	if(msg->x < 7)
	{
		my_vel.linear.x = 1.0;
		my_vel.linear.y = 0;
		my_vel.angular.z = 0;
	}
	
	
	pub.publish(my_vel);
	
}
	
	
		//--------------------------------------
	
	
	*/



// ------- MAIN --------------------------------------------------------------------------------------------	

int main (int argc, char **argv)
{
	// Initialize the node, setup the NodeHandle for handling the communication with the ROS //system  
	ros::init(argc, argv, "turtlebot_subscriber");  
	ros::NodeHandle nh;
	
	
	// Define the subscriber to turtle's position  (--> rpr_turtle)
	pub = nh.advertise<geometry_msgs::Twist>("rpr_turtle/cmd_vel",1);  //check the topic name
	ros::Subscriber sub = nh.subscribe("rpr_turtle/pose", 1,turtleCallback);  //check the topic name
	
	// client to spawn the turtle 
	ros::ServiceClient client1 =  nh.serviceClient<turtlesim::Spawn>("/spawn");
	
	// client to kill the turtle --> add the required client (to kill the turle)
	ros::ServiceClient killTurtleClient =  nh.serviceClient<turtlesim::Kill>("/kill");
	
	
	// call the service for "killing" turtle1 (cambio il nome in srv2)
	turtlesim::Kill srv2;
	srv2.request.name = "turtle1";	// name of the turtle to kill --> turtle1
	killTurtleClient.call(srv2);
	
	// spawn a turtle named rpr_turtle in the position x = 2.0, y=1.0, theta=0.0
	turtlesim::Spawn srv1;
	srv1.request.x = 2.0;  
	srv1.request.y = 1.0;
	srv1.request.theta = 0.0;
	srv1.request.name = "rpr_turtle";
	client1.call(srv1);
	
/*	
	// I could add this ----------------------
	
	if (client1.call(srv1)) 
	{
        	ROS_INFO("Tartaruga 'my_turtle' creata con successo.");
    	} else 
    	{
       	ROS_ERROR("Errore nella creazione di 'my_turtle'.");
    	}
*/	



	
	ros::spin();
	return 0;
	
	
}

