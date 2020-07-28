//
// Created by x z on 7/21/2020.
//

#ifndef STATISTICS_STATISTIC_H
#define STATISTICS_STATISTIC_H

#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <exception>

struct ARITHMETIC_EXCEPTION : public std::exception
{
    const char* what() const throw () {
        return "Divisor cannot be zero, radicand must bigger than zero!";
    }
};

struct EMPTY_INPUT_EXCEPTION : public std::exception
{
    const char* what() const throw () {
        return "No input!";
    }
};

struct INDEX_OUT_OF_BOUNDS_EXCEPTION : public std::exception
{
    const char* what() const throw () {
        return "Given number exceeds input!";
    }
};

struct HARMONIC_ZERO_EXCEPTION : public std::exception
{
    const char* what() const throw () {
        return "Cannot solve harmonic mean when including zero data!";
    }
};

struct UNBANLANCE_INPUT_EXCEPTION : public std::exception
{
    const char* what() const throw () {
        return "Different length for x and y!";
    }
};


// 数据个数number
double stat_Number(std::vector<double> x);


// 数据总和sum
double stat_Sum(std::vector<double> x);


// 平均数Mean Value
double stat_MeanValue(std::vector<double> x);


//方差Variance
double stat_Variance(std::vector<double> x);


// 标准偏差Standard Deviation
double stat_StandardDeviation(std::vector<double> x);

// 极值Maxima and Minima
double stat_Maxima(std::vector<double> x);
double stat_Minima(std::vector<double> x);


// 上m/k分位数Quantile
double stat_Quantile(std::vector<double> x, int k=2, int m=1);


// k 阶中心矩kth-Central Moment
double stat_CentralMoment(std::vector<double> x, int k=1);


// 调和平均Harmonic Mean
double stat_HarmonicMean(std::vector<double> x);


//几何平均Geometric Mean
double stat_GeometricMean(std::vector<double> x);


// 偏度Skewness
double stat_Skewness(std::vector<double> x);


// 峰度Kurtosis
double stat_Kurtosis(std::vector<double> x);


// 变异系数Coefficient of Variation
double stat_CoefficientOfVariance(std::vector<double> x);

// 相关系数Covariance
double stat_Covariance(std::vector<double> x, std::vector<double> y);

// Regression

// 单变量线性回归Simple Linear Regression
double stat_SimpleLinearRegression(std::vector<double> x, std::vector<double> y);


// Hypothesis Test

// t 检验Student’s t-test
// 单样本
double stat_TTest(std::vector<double> x, int mux);
// 双样本
double stat_TTest(std::vector<double> x, std::vector<double> y);


// 皮尔森卡方检验Pearson’s Chi-squared Test
double stat_ChiUniformTest(std::vector<double> observed);




#endif //STATISTICS_STATISTIC_H
