#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

float ox,oy,oz,ow,ax,ay,az,lx,ly,lz;
//float orientation_covariance[9]={0,0,0,0,0,0,0,0,0};
//float angular_velocity_covariance[9]={0,0,0,0,0,0,0,0,0};
//float linear_acceleration_covariance[9]={0,0,0,0,0,0,0,0,0};
void imuCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
  ox = msg->orientation.x;
  oy = msg->orientation.y;
  oz = msg->orientation.z;
  ow = msg->orientation.w;
  ax = msg->angular_velocity.x;
  ay = msg->angular_velocity.y;
  az = msg->angular_velocity.z;
  lx =msg->linear_acceleration.x;
  ly =msg->linear_acceleration.y;
  lz =msg->linear_acceleration.z;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "IMU");   
  ros::NodeHandle n;   
  ros::Subscriber sub = n.subscribe("/phone1/android/imu", 100,imuCallback);
  ros::Publisher imu_pub = n.advertise<sensor_msgs::Imu>("imu/data",100);
  ros::Rate loop_rate(10);   

  while (ros::ok())
  {
    ros::spinOnce();

    sensor_msgs::Imu imu;
    
    imu.header.frame_id = "imu_link";
    imu.orientation.x = ox;
    imu.orientation.y = oy;
    imu.orientation.z = oz;
    imu.orientation.w = ow;
	imu.angular_velocity.x = ax;
	imu.angular_velocity.y = ay;
	imu.angular_velocity.z = az;
	imu.linear_acceleration.x =lx;
	imu.linear_acceleration.y =ly;
	imu.linear_acceleration.z =lz;


    imu_pub.publish(imu);

    
    loop_rate.sleep();

  }
  return 0;
}
