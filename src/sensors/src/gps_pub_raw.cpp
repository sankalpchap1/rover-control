#include "ros/ros.h"
#include "sensor_msgs/NavSatFix.h"

double lat,logg;
int service,status;

void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg)
{
	lat = msg->latitude;
	logg = msg->longitude;
	service=msg->status.service;
	status = msg->status.status;
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"gps");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("phone1/android/fix",1000,gpsCallback);
	ros::Publisher gps_pub = n.advertise<sensor_msgs::NavSatFix>("gps/fix",1000);
	ros::Rate loop_rate(10);

while(ros::ok())
{

	ros::spinOnce();
	sensor_msgs::NavSatFix gps;
	
	gps.header.frame_id="gps_link";
	gps.latitude = lat;
	gps.longitude = logg;
	gps.status.status = status;
	gps.status.service = service;

	gps_pub.publish(gps);
	loop_rate.sleep();
	
}
	ros::spin();
	return 0 ;
}

