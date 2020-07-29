#include"calculus.h"
//Simpson method--1000 cuts

double NumIntegrationSimpson(ExprTree* T, double low_bound, double up_bound) {
	if (!T) return 0;
	int n = 1000;
	double h = (up_bound - low_bound)/n;
	double XI0 = T->evaluate(low_bound) + T->evaluate(up_bound);
	double XI1 = 0;
	double XI2 = 0;
	double X;
	double XI;
	for (int i = 1; i < n; i++) {
		X = low_bound + i * h;
		if (i % 2 == 0) {
			XI2 = XI2 + T->evaluate(X);
		}
		else {
			XI1 = XI1 + T->evaluate(X);
		}
	}
	XI = h*(XI0 + 2 * XI2 + 4 * XI1) / 3;
	return XI;
}
//Romberg method
double NumIntegrationRomberg(ExprTree* T, double low_bound, double up_bound) {
	if (!T) return 0;
	double R[3][27];
	int n = 25;
	double h = up_bound - low_bound;
	R[1][1] = h * 0.5 * (T->evaluate(low_bound) + T->evaluate(low_bound));
	for (int i = 2; i <= n; i++) {
		double mid = 0;
		for (int k = 1; k <= pow(2.0, i - 2); k++) {
			mid = mid + h * T->evaluate(low_bound + (k - 0.5) * h);
		}
		R[2][1] = 0.5 * (R[1][1] + mid);
		for (int j = 2; j <= i; j++) {
			R[2][j] = R[2][j - 1] + (R[2][j - 1] - R[1][j - 1]) / (pow(4, j - 1) - 1);
		}
		h = h / 2;
		for (int j = 1; j <= i; j++) {
			R[1][j] = R[2][j];
		}
	}
	return(R[1][n]);
}

//5 point-- method
double NumDiff(ExprTree* T, double point) {
	if (!T) return 0;
	double h = 0.02;
	double result = 1 / (12 * h) * (T->evaluate(point - 2 * h) - 8 * T->evaluate(point - h)\
		+ 8 * T->evaluate(point + h) - T->evaluate(point + 2 * h));
	return result;
}

double ExprDiff(ExprTree* T,double point) {
	return 0;
	
}