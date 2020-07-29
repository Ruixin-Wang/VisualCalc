#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <math.h>
#include <string.h>

class MATRIX{
	private:
		int row, column;
		double *data;
	public:
		MATRIX();
		MATRIX(int row, int column, double *data);
		MATRIX(const MATRIX& b);
		~MATRIX();
		void print() const;
		MATRIX& operator=(MATRIX& b);
		//Input: Matrix b
		//Output: Matrix X = A + b
		//Require: A.row = b.row, A.column = B.column
		MATRIX add(MATRIX b);
		//Input: Matrix b
		//Output: Matrix X = A - b
		//Require: A.row = b.row, A.column = B.column
		MATRIX subtract(MATRIX b);
		//Input: Matrix b
		//Output: Matrix X = A * b
		//Require: A.column = B.row
		MATRIX multiply(MATRIX b);
		//Input: Matrix b
		//Output: Matrix X = A / b, s.t. Xb = A
		//Require: A.column = b.column, b is nonsingular
		MATRIX rightDivide(MATRIX b);
		//Input: Matrix b
		//Output: Matrix X = A \ b, s.t. AX = b
		//Require: A.row = b.row, A is nonsingular
		MATRIX leftDivide(MATRIX b);
		//Output: Matrix X = A'
		MATRIX transpose();
		//Output: Matrix X, s.t. AX = E
		//Require: A is nonsingular
		MATRIX inverse();
		//Output: A*, the adjoint matrix of A
		//Require: A.row = A.column
		MATRIX adjoint(); 
		//Output: the value of |A|
		//        when A is singular, return 0
		//        when A.row != A.column, return 0
		MATRIX determinant();
		//Output: tr(A)
		//Require: A.row = A.column
		MATRIX trace();
};

inline void swap(double& a, double& b){
	double c = a;
	a = b;
	b = c;
}

#endif
