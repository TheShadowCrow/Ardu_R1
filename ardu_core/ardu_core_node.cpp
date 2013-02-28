#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Uint16.h"

#include <sstream>

std_msgs::UInt16 turn;
std_msgs::UInt16 movement;	

int distance_to_obj_main;
int main_dis_treshold = 10; 



ros::Publisher head_turn_pub;
ros::Publisher movement_pub;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "ardu_core");
	ros::NodeHandle n; 
		
	head_turn_pub = n.advertise<std_msgs::UInt16>("head_turn", 1000);
	movement_pub = n.advertise<std_msgs::UInt16>("movement", 1000);
	ros::Rate	looprate(10);
	while(ros::ok())
	{
		
	}
}

void setHeadTurn(int angle)
{
	turn.data = angle;
	head_turn_pub.publish(turn);
}

void move(int direction)
{
	movement.data = direction;
	movement_pub.publish(movement);
}


void protocolHandle(int protocol)
{
	
}
