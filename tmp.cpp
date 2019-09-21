#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
int main()
{
  MatrixXd mat = MatrixXd::Zero(4,4);
  std::cout<<mat<<std::endl;
    mat <<  1, 2, 3, 4,
        5, 6, 7, 8,
        9,10,11,12,
       13,14,15,16;
    mat.resize(4,4);
    std::cout<<mat.rows()<<std::endl<<mat.cols()<<std::endl;
    // std::cout<<mat.block<3,3>(1,1);
}