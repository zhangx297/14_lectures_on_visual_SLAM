#include<iostream>
#include<opencv2/core/core.hpp>
#include<ceres/ceres.h>
#include<chrono>

using namespace std;

//代价函数的计算模型
struct CURVE_FITTING_COST{
    CURVE_FITTING_COST(double x, double y) :: _x(x), _y(y) {} //使用初始化列表赋值写法的构造函数

    //残差的计算
    template<typename T> //函数模板，使得下面定义的函数可以支持多种不同的形参，避免重载函数的函数体重复设计
    bool operator()(
    	const T *const abc, //模型参数，有3维
	T *residual) const //重载运算符
    {
    	residual[0] = T(_y) - ceres::exp(abc[0] * T(_x) * T(_x) + abc[1] * T(_x) + abc[2]); //y-exp(ax^2+bx+c)
	return true;
    }

    const double _x, _y; //xy数据
};


int main(int argc, char **argv){
    double ar = 1.0, br = 2.0, cr = 1.0; //真实参数值
    double ae = 2.0, be = -1.0, ce = 5.0; //估计参数值
    int N = 100; //数据点
    double w_sigma = 1.0; //噪声sigma值
    double inv_sigma = 1.0 / w_sigma;  //标准差的逆
    cv::RNG rng; //Opencv随机数产生器

    vector<double> x_data, y_data;
    for (int = 0; i < N; i++){
    	double x = i/100.0;
	x_data.push_back(x);
	y_data.push_back(exp(ar * x * x + br * x + cr) + rng.gaussian(w_sigma * w_sigma));
    }

    double abc[3] = {ae, be, ce};

    //构建最小二乘问题
    ceres::Problem problem; //定义一个优化问题类problem
    for (int i = 0; i < N; i++){
	//代价函数，核函数，参数模块
    	problem.AddResidualBlock(new cere::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3>(new CURVE_FITTING_COST(x_data[i], y_data[i])),nullptr, abc);
    }

    //配置求解器
    ceres::Solver::Options options; //定义一个配置项集合类options
    options.linear_solver_type = ceres::DENSE_NORMAL_CHOLESKY; //增量方程求解方法
    options.minimizer_progress_to_stdout = true; //是否向终端输出优化过程信息

    ceres::Solver::Summery summery; //优化信息
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    ceres::Solve(options, &problem, &summery); //开始优化
    
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "solve time cost =" << time_used.count() << "seconds." << endl;

    //输出结果
    cout << summary.BriefReport() << endl;
    cout << "estimated a,b,c = ";
    for (auto a:abc)
	cout << a << " ";
    cout << endl;

    return 0;
}
