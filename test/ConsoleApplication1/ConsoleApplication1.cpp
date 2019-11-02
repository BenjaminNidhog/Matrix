// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"Matrix.hpp"
#include"Slice.hpp"
#include"Vector.hpp"
#include"SquareMatrix.hpp"
#include<iostream>
using namespace std;
using namespace matrix;//Matrix��������򣬱��������������û�ʧ��
int main()
{

	const size_t n_x = 5;
	const size_t n_y = 3;//������������


	Vector<float, n_x> x;
	Vector<float, n_y> y;
	Matrix<float, n_y, n_x> C;//����һ������MxN
	SquareMatrix<float, n_y> S;//����һ������MxM��������Ը������ഫ��ֵ


	C.setZero();  // ����ȫ����0
	C.setOne();	 //  ����ȫ����1

	C(0, 0) = 1; //  �������þ����ڵ�ĳ��ĳ�е�ֵ
	C(1, 1) = 2;
	C(2, 2) = 3;
	cout << C(0, 0);//��ȡ����ĳ��ĳ�е�ֵ���������

	C.T();//ת�þ���

	S.I();//���������Ǿ�����Ҫ�ȴ��ݸ��������������
	cout << S(0, 0) << S(0, 1) << S(0, 2) << endl;//��ȡ����ĳ��ĳ�е�ֵ���������
	cout << S(1, 0) << S(1, 1) << S(1, 2) << endl;//��ȡ����ĳ��ĳ�е�ֵ���������
	cout << S(2, 0) << S(2, 1) << S(2, 2) << endl;//��ȡ����ĳ��ĳ�е�ֵ���������

	float data[9] = { 0, 2, 3,
					  4, 5, 6,
					  7, 8, 10
					};
	SquareMatrix<float, 3> A(data);//֧�����鴫ֵ������

	Matrix<float, 2, 3> B(A.slice<2, 3>(1, 0));//�ӵ�1�е�0�п�ʼ��Ƭ3,3���󣬴�СΪ2 x 3�������棬����������С��


	
	SquareMatrix<float, n_x> P;
	SquareMatrix<float, n_y> R;
	Matrix<float, n_x, n_y> K;


	S = C*P*C.T() + R;//����ͷ�������


	K = P*C.T()*S.I()-K;


	system("pause");
    return 0;
}

