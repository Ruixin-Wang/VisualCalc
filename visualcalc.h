#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisualCalc.h"
#include "visualcalc.h"
#include "Node.h"
#include "graph.h"

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

private slots:
    void on_Generate_clicked();

private:
    Ui::VisualCalc *ui;
    ExprTree *Tree;


private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void DeleteButtonPressed();
    void ClearButtonPressed();
};


