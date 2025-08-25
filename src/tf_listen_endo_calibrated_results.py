#!/usr/bin/env python
import rospy
import tf

def tf_listener():
    rospy.init_node('tf_listen_endo_calibrated_results', anonymous=False)

    listener = tf.TransformListener()

    rate = rospy.Rate(5.0)  # 1 Hz
    while not rospy.is_shutdown():
        try:
            # Change these frame names to yours
            
            # frame_a = "iiwa_flange_marker" # eih
            frame_a = "iiwa_link_ee"  # eob
            frame_b = "tcp_tool_tip"

            (trans, rot) = listener.lookupTransform(frame_a, frame_b, rospy.Time(0))

            rospy.loginfo("Transform from %s to %s:", frame_a, frame_b)
            rospy.loginfo("  Translation: x=%.4f, y=%.4f, z=%.4f", trans[0], trans[1], trans[2])
            rospy.loginfo("  Rotation (quaternion): x=%.4f, y=%.4f, z=%.4f, w=%.4f",
                          rot[0], rot[1], rot[2], rot[3])

        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            rospy.logwarn("Transform not available yet.")
            continue

        rate.sleep()

if __name__ == '__main__':
    try:
        tf_listener()
    except rospy.ROSInterruptException:
        pass
