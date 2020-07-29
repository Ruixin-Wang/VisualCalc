#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisualCalc.h"
#include "visualcalc.h"
#include "Node.h"
#include "NodeforMatrix.h"
#include "graph.h"
#include "stat.h"
#include "calculus.h"
#include "MatrixView.h"

QT_BEGIN_NAMESPACE 
namespace Ui { class VisualCalc; }
QT_END_NAMESPACE

class VisualCalc : public QMainWindow
{
    Q_OBJECT

public:
    explicit VisualCalc(QWidget *parent = Q_NULLPTR);
    ~VisualCalc();

    Graph* new_graph;
    Stat* new_stat;
    MatrixView* new_Mat;

    void initTable(); 
    void initEQN();

private slots:
    void on_Generate_clicked();

private:
    Ui::VisualCalc *ui;
    ExprTree *Tree;
    ExprTreeForMatrix* MTree;



private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ConstButtonPressed();
    void VarButtonPressed();


    void ChangeNumberSign();
    void DeleteButtonPressed();
    void ClearButtonPressed();

    void MatrixButtonPressed();

    void EQNAddVar();
    void EQNDecVar();
    void EQNSolve();

private slots:
    void StatAddData();
    void StatDelData();
    void StatAnalysis();
private slots:
    void IntegrationEqualButtonPressed();
    void DerivateEqualButtonPressed();

    void AddMatrix();
    void EditMatrix();
    void DeleteMatrix();
    void InsertMatrix();
    void MatEval();
};


