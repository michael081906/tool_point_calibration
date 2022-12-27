#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>

std::string child_frame;

void poseStampedCallback(const geometry_msgs::PoseStampedConstPtr& msg){
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(msg->pose.position.x, 
                                   msg->pose.position.y, 
                                   msg->pose.position.z) );
  tf::Quaternion q(msg->pose.orientation.x, 
                   msg->pose.orientation.y, 
                   msg->pose.orientation.z, 
                   msg->pose.orientation.w);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_frame", child_frame));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "pose_to_tf");
  ros::NodeHandle node;
  ros::param::get("child_frame", child_frame);
  ros::Subscriber sub = node.subscribe("/pose_topic", 11, &poseStampedCallback);

  ros::spin();
  return 0;
};