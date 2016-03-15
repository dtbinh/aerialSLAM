
#include <ros/ros.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include "opencv2/flann/flann.hpp"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Int32.h>
#include </usr/include/opencv2/stitching/stitcher.hpp>
#include "opencv2/stitching/detail/autocalib.hpp"
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/util.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"
#include <cvaux.h>
#include <math.h>
#include <cxcore.h>

using namespace cv;
using namespace std;
using namespace cv::detail;

int count1=0;
Mat img_1;
ros::Publisher synchro;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
	{
	
	cv_bridge::CvImagePtr cv_ptr;
		try
		    {
		      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
		    }
		    catch (cv_bridge::Exception& e)
		    {
		      ROS_ERROR("cv_bridge exception: %s", e.what());
		      return;
		    }

		img_1 = cv_ptr->image;	
	
	char str[80];
        sprintf (str, "/home/carmine/Desktop/photo_folder/img_%d.png", count1);
	imwrite( str, img_1 );

	std_msgs::Int32 s;
        s.data=count1;
	count1++;
 	
	synchro.publish(s);

	//waitKey(5);
	usleep(100000);
		
	}


int main( int argc, char** argv )
{
   //initModule_nonfree();
   ros::init(argc, argv, "photo_saving");
   ros::NodeHandle nh_;
   ros::Subscriber image_sub;


   image_sub = nh_.subscribe("/stereo/left/image_raw/theora",1,imageCallback);
   synchro = nh_.advertise<std_msgs::Int32>("sync", 100);
   ros::spin();
   return 0;
}

