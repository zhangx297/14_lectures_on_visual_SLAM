#include<iostream>
using namespace std;
//#include<ctime>
//Eigen核心部分
#include<Eigen/Dense>
#include<Eigen/Core>
using namespace Eigen;
#define MATRIX_SIZE 50

int main(int argc, char **argv){

    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_NN = matrix_NN * matrix_NN.transpose(); //保证半正定
    Matrix<double, MATRIX_SIZE, 1> v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);

    //Matrix<double, MATRIX_SIZE, 1> x  = matrix_NN.inverse() * v_Nd;
    //cout << "time of normal inverse is " << 1000 * (clock() -time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;
    //cout << "x = " << x.transpose() << endl;

    //Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    // #cout << "time of Qr decomposition is" << 1000 * (clock() - time_stt/ (double) CLOCKS_PER_SEC << "ms" <<endl;
    cout << "x = " << Q,R <<endl;

}
