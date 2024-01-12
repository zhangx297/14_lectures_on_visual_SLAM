#include<iostream>
#include<iomanip>
using namespace std;
#include<Eigen/Core>
#include<Eigen/Geometry>

using namespace Eigen;
#include<pangolin/pangolin.h>

struct RotationMatrix{
    Matrix3d matrix = Matrix3d::Identity();
};

ostream &operator<<(ostream &out, const RotationMatrix &r){
    out.setf(ios::fixed);
    Matrix3d matrix = r.matrix;
    out << '=';
    out << "[" << setprecision(2) << matrix(0, 0) << "," << matrix(0, 1) << ", " << matrix(0, 2) << "],"
	<< "[" << matrix(1, 0) << "," << matrix(1, 1) << "," << matrix(1, 2) << "],"
	<< "[" << matrix(2, 0) << "," << matrix(2, 1) << "," << matrix(2, 2) << "]";
    return out;
}

istream &operator>>(istream &in, RotationMatrix &r){ 
    return in;
}

struct TranslationVector{
    Vector3d trans = Vector3d(0, 0, 0);
};

ostream &operator<<(ostream &out, const TranslationVector &t){
    out << "=[" << t.trans(0) << ',' << t.trans(1) << ',' << t.trans(2) << "]";
    return out;
}

istream &operator>>(istream &in, TranslationVector &t){
    return in;
}

struct QuaternionDraw{
    Quaterniond q;
};

ostream &operator<<(ostream &out, const QuaternionDraw quat){
    auto c = quat.q.coeffs();
    out << "=[" << c[0] << "," << c[1] << "," << c[2] << "," << c[3] << "]";
    return out;
}

istream &operator>>(istream &in, const QuaternionDraw quat){
    return in;
}

int main(int argc, char **atgv){
    pangolin::CreateWindowAndBind("visualize geometry", 1000, 600); //创建窗口
    glEnable(GL_DEPTH_TEST);//初始化OpenGL
    //创建相机视图
    pangolin::OpenGlRenderState s_cam(
	//投影矩阵
	pangolin::ProjectionMatrix(1000, 600, 420, 420, 500, 300, 0.1, 1000), // 屏幕的宽度、高度、相机的水平视角、垂直视角、相机在z轴上的位置、相机到屏幕的距离的最小值和最大值。
	//视图矩阵
	pangolin::ModelViewLookAt(3, 3, 3, 0, 0, 0, pangolin::AxisY) // 相机的位置、相机观察的目标点、相机的朝向向量
	);
    const int UI_WIDTH = 500;
    
    //创建交互视角
    pangolin::View &d_cam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0, -1000.0f / 600.0f). 
	    // 表示窗口在x轴和y轴上的起点和终点位置，以及窗口的宽高比，宽高比为负数，则实际上是600：1000
	    SetHandler(new pangolin::Handler3D(s_cam));

    //ui//创建数据表格，操作台
    pangolin::Var<RotationMatrix> rotation_matrix("ui.R", RotationMatrix()); //创建一个矩阵
    pangolin::Var<TranslationVector> translation_vector("ui.t", TranslationVector());
    pangolin::Var<TranslationVector> euler_angles("ui.rpy", TranslationVector());
    pangolin::Var<QuaternionDraw> quaternion("ui.q", QuaternionDraw());
    pangolin::CreatePanel("ui").SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));

    while(!pangolin::ShouldQuit()){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清空颜色缓冲区和深度缓冲区
	d_cam.Activate(s_cam);  //激活显示窗口和渲染状态对象
	pangolin::OpenGlMatrix matrix = s_cam.GetModelViewMatrix(); //相机模型可视化矩阵赋值给matrix，作为变换矩阵
	Matrix<double, 4, 4> m = matrix;

	RotationMatrix R;
	//求反向变化，把相机坐标系转化为世界坐标系
	for(int i = 0; i < 3; i++)
	    for(int j = 0; j < 3; j++)
	        R.matrix(i, j) = m(j, i); //把4x4矩阵中的3行3列转置后给R.matrix
	rotation_matrix = R; //取出m中的旋转矩阵

	TranslationVector t;
	t.trans = Vector3d(m(0, 3), m(1, 3), m(2, 3));
	t.trans = -R.matrix * t.trans;
	translation_vector = t; //取出m中的平移向量

	TranslationVector euler;
	euler.trans = R.matrix.eulerAngles(2 ,1, 0);
	euler_angles = euler; //取出欧拉角

	QuaternionDraw quat;
	quat.q = Quaterniond(R.matrix);
	quaternion = quat; //取出四元数

	glColor3f(1.0, 1.0, 1.0);

	pangolin::glDrawColouredCube();//画立方体
	//画原始坐标轴
	glLineWidth(3);
	glColor3f(0.8f, 0.f, 0.f);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(10,0,0);
	glColor3f(0.f, 0.8f, 0.f);
	glVertex3f(0,0,0);
	glVertex3f(0,10,0);
	glColor3f(0.2f,0.2f,1.f);
	glVertex3f(0,0,0);
	glVertex3f(0,0,10);
	glEnd();

	pangolin::FinishFrame();
    }
        
}

