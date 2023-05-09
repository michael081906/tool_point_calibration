#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

int main(int argc, char** argv){

  ros::init                 (argc, argv, "tf_tip_broadcaster");
  ros::NodeHandle           node;
  tf::TransformListener     listener;
  tf::TransformBroadcaster  br;
  double                    offset_x, offset_y, offset_z;
  std::string               ref_frame, tip_frame;
  tf::Transform             transform_br;
  tf::StampedTransform      transform_listener;
  ros::Rate                 rate(100.0);
  ros::param::get           ( "~offset_x", offset_x );
  ros::param::get           ( "~offset_y", offset_y );
  ros::param::get           ( "~offset_z", offset_z );
  ros::param::get           ( "~ref_frame", ref_frame );
  ros::param::get           ( "~tip_frame", tip_frame );
  transform_br.setOrigin    ( tf::Vector3(offset_x, offset_y, offset_z) );
  
    
  while (node.ok()){
        try{
            transform_br.setRotation( tf::Quaternion::getIdentity());
            br.sendTransform        ( tf::StampedTransform(transform_br, ros::Time::now(), ref_frame, tip_frame) );
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
        ros::spinOnce();
        rate.sleep();
    }
  return 0;
};