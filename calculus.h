#pragma once
#include"Node.h"

double NumIntegrationSimpson(ExprTree* T, double low_bound, double up_bound);
double NumIntegrationRomberg(ExprTree* T, double low_bound, double up_bound);
double NumDiff( ExprTree* T, double point);
double ExprDiff(ExprTree* T, double point);
void DiffString(ExprTree* T); 