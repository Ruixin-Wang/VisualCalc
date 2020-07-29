#include <iostream>
#include<cmath>
using namespace std;

/*数组的大小,即变量的大小*/
const int n = 5;

/*通过遍历求出向量的最大值，即无穷范数*/
double MAX(double a[n])
{
    double max = 0;
    int i;
    double abs_value;
    for (i = 0; i<n; i++)
    {	
    	abs_value = fabs(a[i]);
        if (abs_value > max)
            max = abs_value;
    }
    return max;
}


 /*高斯-塞德尔迭代法*/
void Gauss_Seidel(double a[n][n], double b[n])
{
    int num = 0; /*迭代次数*/
    double accuracy = 0.0000001; /*精度*/
    double c;
    int i, j;
    double g;
    int count = 0;
    
    double diff; /*差*/
    int flag; /*循环结束标志*/
    double x0[n];
    double x1[n] = { 0 };
    
    /*判断系数矩阵是否严格对角占优*/
    for(i = 0;i < n;i++)
	{
		g = 0.0;
		
		for(j = 0;j < n;j++)
		{
			if(i != j)
			g += fabs(a[i][j]);
			}	
		if(g >= fabs(a[i][i]))
			count++;
	 } 
    
    if(count != 0)
    	{
		cout<<"系数矩阵不严格对角占优，线性方程组可能不收敛或无解."<<endl;
		
		}
	/*迭代计算*/
    do {
        num++;          
        /*复制数组*/
        for (j = 0; j<n; j++)
            {
			x0[j] = x1[j];	
        }
        /*迭代计算过程*/
        for (i = 0; i<n; i++)
        {
            double sum = 0;
            double sum_new = 0;
            for (j = 0; j<=i - 1; j++)
            {
                sum += a[i][j] * x1[j];
            }
            for (j = i + 1; j<n; j++)
                sum_new += a[i][j] * x0[j];

            x1[i] = (b[i] - sum - sum_new) / a[i][i];
       
        }

        c = fabs(MAX(x1) - MAX(x0));    /*求范数差*/                            
    
        diff = fabs(c - accuracy);    /*与精度进行比较*/                       
    
        if (diff < accuracy||num >= 10000)
            flag = 0;
        else
            flag = 1;
    } while (flag);                                 

    /*输出结果*/
   cout<<"线性方程组的近似解如下："<<endl;  
 	for(i = 0; i < n; i++)
	 {
	 	cout<< "x" << i + 1 << " = " << x1[i] << endl;
	  } 
}



/*高斯消元法*/
void Gauss_Eliminate(double a[n][n],double b[n])
{
	int i,j,k;
	double x0[n];/*存储初等行变换的系数，进行行相减*/
	double x[n];/*存储解*/ 
	/*判断是否可以使用高斯消元法*/
	for(i = 0;i < n;i++)
	{
		if(a[i][i]==0)
		{
			cout<<"该方程组不能使用高斯消元法"<<endl;
			return;
		}
	}
	
	/*消元过程*/
	for(k = 0;k < n - 1;k++)
	{
		/*求出第k次行变换的系数*/
		for(i = k + 1;i < n;i++)
		{
			x0[i] = a[i][k] / a[k][k];
		}
		
		/*第k次消元*/
		for(i = k + 1;i < n;i++)
		{
			for(j = 0;j < n;j++)
			{
				a[i][j] = a[i][j] - x0[i] * a[k][j];
			}
			b[i] = b[i] - x0[i] * b[k];
		}
	}
	
	x[n - 1] = b[n - 1] / a[n - 1][n - 1];
	for(i = n -2;i >= 0;i--)
	{
		double sum = 0;
		for(j = i + 1;j < n;j++)
		{
			sum = sum + a[i][j] * x[j];
		}
		x[i] = (b[i] - sum) / a[i][i];
	}
	
	cout<<"线性方程组的近似解如下："<<endl;
	for(i = 0;i < n;i++)
	{
		cout<<"x"<<i + 1<<" = "<<x[i]<<endl;
	}
 } 
 
 
 
 /*最终计算函数*/
void linesolve(double a[n][n],double b[n])
{
	int i,j;
	double flag;
	int count = 0;
	for(i=0;i<n;i++)
	{
		flag = 0.0;
		for(j=0;j<n;j++)
		{
			if(i!=j)
			{
				flag = flag + fabs(a[i][j]);
			}
			
		}
		if(flag>=fabs(a[i][i]))
		count++;
	 } 
	 
	if(count==0)
    	Gauss_Seidel(a, b);
    else if(count!=0)
    	Gauss_Eliminate(a,b);
    cout<<endl;
 } 
 
 
 
// int main()
// {
//     double a[n][n] = {7,3,4,6,4,8,3,3,-1,-9,-66.322,1,30,52,-90,20,5,6,9,8,0,1,36,5,-6};
//  	double b[n]= {-5,-6,81,70,99};
//  	
//     linesolve(a,b);
//    
//     return 0;
// }

