// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Matrix.hpp"
#include"Slice.hpp"
#include"Vector.hpp"
#include"SquareMatrix.hpp"
#include<iostream>
using namespace std;
using namespace matrix;//Matrix库的作用域，必须包含，否则调用会失败
int main()
{

	const size_t n_x = 5;
	const size_t n_y = 3;//定义矩阵的行列


	Vector<float, n_x> x;
	Vector<float, n_y> y;
	Matrix<float, n_y, n_x> C;//申明一个矩阵MxN
	SquareMatrix<float, n_y> S;//申明一个方阵MxM，方阵可以跟矩阵互相传递值


	C.setZero();  // 矩阵全部置0
	C.setOne();	 //  矩阵全部置1

	C(0, 0) = 1; //  单独设置矩阵内的某行某列的值
	C(1, 1) = 2;
	C(2, 2) = 3;
	cout << C(0, 0);//获取矩阵某行某列的值，并且输出

	C.T();//转置矩阵

	S.I();//逆矩阵（如果是矩阵需要先传递给方阵再求逆矩阵）
	cout << S(0, 0) << S(0, 1) << S(0, 2) << endl;//获取矩阵某行某列的值，并且输出
	cout << S(1, 0) << S(1, 1) << S(1, 2) << endl;//获取矩阵某行某列的值，并且输出
	cout << S(2, 0) << S(2, 1) << S(2, 2) << endl;//获取矩阵某行某列的值，并且输出

	float data[9] = { 0, 2, 3,
					  4, 5, 6,
					  7, 8, 10
					};
	SquareMatrix<float, 3> A(data);//支持数组传值给矩阵

	Matrix<float, 2, 3> B(A.slice<2, 3>(1, 0));//从第1行第0列开始切片3,3矩阵，大小为2 x 3，（警告，不会检查矩阵大小）


	
	SquareMatrix<float, n_x> P;
	SquareMatrix<float, n_y> R;
	Matrix<float, n_x, n_y> K;


	S = C*P*C.T() + R;//矩阵和方阵运算


	K = P*C.T()*S.I()-K;


	system("pause");
    return 0;
}

