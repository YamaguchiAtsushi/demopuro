//https://docs.ros.org/en/jade/api/speech_recognition_msgs/html/msg/SpeechRecognitionCandidates.html
//rosnode info /speech_recognitionすると、speech_recognition_msgs/SpeechRecognitionCandidates Messageを使用していることがわかる
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <speech_recognition_msgs/SpeechRecognitionCandidates.h>

std_msgs::String msg;
speech_recognition_msgs::SpeechRecognitionCandidates speech_msg;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("I heard: [%s]", msg->data.c_str());
    ::msg.data = msg->data;
}

void speechCallback(const speech_recognition_msgs::SpeechRecognitionCandidates::ConstPtr& msg)
{
    //ROS_INFO("I heard: [%s]", msg->transcript);

    // msg->transcriptが std::vector<std::string>なので、%sで出力できないらしい
    std::stringstream ss;
    for (const auto& str : msg->transcript) {
        ss << str << " ";
    }
    //ROS_INFO("I heard: [%s]", ss.str().c_str());
    ROS_INFO("transcript: %s", msg->transcript[0].c_str());
    //ROS_INFO("confidence: %f", msg->confidence);

}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "speech_operation");
  ros::NodeHandle nh;
  ros::Publisher chatter_pub = nh.advertise<speech_recognition_msgs::SpeechRecognitionCandidates>("chatter", 10);
  ros::Subscriber sub = nh.subscribe("speech_to_text", 10, speechCallback);
  ros::Rate loop_rate(100);


  while (ros::ok())
  {
    //std_msgs::String msg;
    //msg.data = "hello world!";
    char key;

    std::cin >> key;

    if (key == 'q'){
      ROS_INFO("publish: %s", msg.data.c_str());
      chatter_pub.publish(msg);
    }

    //ROS_INFO("publish: %s", msg.data.c_str());

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}