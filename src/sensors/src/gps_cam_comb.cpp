#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/MagneticField.h>
#include <rover_msgs/WheelVelocity.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Float32.h>
#include <cstdlib>
#include <cmath>

#define PI 3.14159
#define R 6371

double lat_init,logg_init,dist_init;
double lat_dest,logg_dest;
double latt[5]={0,0,0,0,0},logi[5]={0,0,0,0,0};
double lat,logg,brng,dist,brng_cur,decl;
int service,status;
int i,flg=0;
float x,theta;

void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg)
{
	lat = (msg->latitude)*PI/180;
	logg = (msg->longitude)*PI/180;
	service = msg->status.service;
	status = msg->status.status;
	
	brng = atan2((sin(logg_dest - logg))*(cos(lat_dest)),(cos(lat))*(sin(lat_dest))-(sin(lat))*(cos(lat_dest)*(cos(logg_dest-logg))));
	
	float a = (sin((lat_dest-lat)/2))*(sin((lat_dest-lat)/2)) + (cos(lat))*(cos(lat_dest))*(sin((logg_dest-logg)/2))*(sin((logg_dest-logg)/2));
	float c = 2 * atan2(sqrt(a),sqrt(1-a));
	dist= R*c;
}

void ortnCallback(const sensor_msgs::MagneticField::ConstPtr& msg)
{
	float x = (msg->magnetic_field.x)*PI/180;
	float y = (msg->magnetic_field.y)*PI/180;
	
	float theta = fabs(atan2( y, x ));
	if(y<0)		theta = PI - theta;

	if( decl > 0 ){
		if(y>0 && (theta+decl-PI)<0 )		brng_cur = theta + decl;
		if(y>0 && (theta+decl-PI)>0 )	 brng_cur = theta + decl - 2*PI;
		if(y<0)		brng_cur = theta + decl -PI;	
	}
	else {
		if(y<0 && (theta-fabs(decl))<0 )		brng_cur = theta + PI - decl;
		if(y<0 && (theta-fabs(decl))>0 )	 brng_cur = theta - decl - PI;
		if(y>0)		brng_cur = theta - decl;	
	}

}

void camCallback(const geometry_msgs::Pose2D::ConstPtr& msg)
{
	if(flg==1)
		do{
		x=msg->x;
		theta=msg->theta;
		}while(x==0);
}

void recieve_gps(int i){
	lat_init=latt[i];
	logg_init=logi[i];
	lat_dest=latt[i+1];
	logg_dest=logi[i+1];
}

void nav_to(float dst,float theta){

}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"gps");
	ros::NodeHandle n;
	recieve_gps(0);                          //recieve initial gps init and dest 
	ros::Subscriber gps_sub = n.subscribe("/phone1/android/fix",1000,gpsCallback);
	ros::Subscriber ortn_sub = n.subscribe("/phone1/android/magnetic_field",1000,ortnCallback);
	ros::Publisher vel_pub = n.advertise<rover_msgs::WheelVelocity>("/rover1/wheel_vel",10);
	ros::Publisher flg_pub = n.advertise<std_msgs::Float32>("/gps_loc_flg",10);
	ros::Subscriber cam_sub = n.subscribe("/ball_pos",1000,camCallback);
	ros::Rate loop_rate(5);	

	float a = (sin((lat_dest-lat_init)/2))*(sin((lat_dest-lat_init)/2)) + (cos (lat_init))*(cos (lat_dest))*(sin((logg_dest-logg_init)/2))*(sin((logg_dest-logg_init)/2));
	float c = 2 * atan2(sqrt(a),sqrt(1-a));
	dist_init= R*c;

	while(ros::ok())
	{
	ros::spinOnce();
	rover_msgs::WheelVelocity vel;
	if(fabs(dist_init-dist)>0.002){
		if(fabs(brng-brng_cur)>=5*PI/180){
			if (brng-brng_cur<=0){
				vel.left_front_vel = 180;
    	 	   	vel.right_front_vel = -180;
        		vel.left_middle_vel = 180;
        		vel.right_middle_vel = -180;
        		vel.left_back_vel = 180;
        		vel.right_back_vel = -180;	
			}
			else{
				vel.left_front_vel = -180;
        		vel.right_front_vel = 180;
        		vel.left_middle_vel = -180;
        		vel.right_middle_vel = 180;
        		vel.left_back_vel = -180;
        		vel.right_back_vel = 180;
			}
		
		}
		else{
			vel.left_front_vel = 180;
        	vel.right_front_vel = 180;
        	vel.left_middle_vel = 180;
        	vel.right_middle_vel = 180;
        	vel.left_back_vel = 180;
        	vel.right_back_vel = 180;
		}
	}
	else{
		vel.left_front_vel = 0;
        vel.right_front_vel = 0;
        vel.left_middle_vel = 0;
        vel.right_middle_vel = 0;
        vel.left_back_vel = 0;
        vel.right_back_vel = 0;

		std_msgs::Float32 flag;
		flag.data=flg=1;
		flg_pub.publish(flag);
		ros::spinOnce();
		nav_to(x,theta);
		flag.data=flg=0;
		flg_pub.publish(flag);

		if(i<=2)	recieve_gps(++i);

	}
	vel_pub.publish(vel);
	loop_rate.sleep();
	
}
	ros::spin();
	return 0 ;
}

