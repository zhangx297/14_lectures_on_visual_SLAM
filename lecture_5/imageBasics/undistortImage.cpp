#include<opencv2/opencv.hpp>
#include<string>
using namespace std;
string image_file = "../distorted.png";

int main(int argc, char **argv){
	//畸变参数
	double k1 = -0.28230811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
	//内参
	double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;

	cv::Mat image = cv::imread(image_file, 0);  //图像是灰度图，CV_8UC1
	int rows = image.rows, cols = image.cols;
	cv::Mat image_undistort = cv::Mat(rows, cols, CV_8UC1); //去畸变以后的图

	//计算去畸变后图像的内容
	for(int v = 0; v < rows; v++){
		for (int u = 0; u < cols; u++){
			//按照公式，计算点(u,v)对应到畸变图像中的坐标（u_distorted, v_distorted）
			double x = (u - cx) / fx, y = (v - cy) / fy;
			double r = sqrt(x * x + y * y);
			double x_distorted = x * (1 + k1 * r * r + k2 * r * r * r * r) + 2 * p1 * x * y + p2 * (r * r + 2 * x * x);
			double y_distorted = y * (1 + k1 * r * r + k2 * r * r * r * r) + p1 * (r * r + 2 * y * y) + 2 * p2 * x * y;
			double u_distorted = fx * x_distorted + cx;
			double v_distorted = fy * y_distorted + cy;	
			
			//赋值（最近林插值）
			if (u_distorted >= 0 && v_distorted >= 0 && u_distorted < cols && v_distorted < rows){
				//.at<uchar>获取像素
				image_undistort.at<uchar>(v, u) = image.at<uchar>((int) v_distorted, (int) u_distorted);
			}
			else{
				image_undistort.at<uchar>(v, u) = 0;
			}
		}
	}
	cv::imshow("distorted", image);
	cv::imshow("undistorted", image_undistort);
	cv::waitKey();
	return 0;
}
