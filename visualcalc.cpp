#include "VisualCalc.h"
#include "ui_VisualCalc.h"

#include "ExprTree.h"

double calcVal = 0.0;
bool divTrig = false;
bool mulTrig = false;
bool addTrig = false;
bool subTrig = false;

VisualCalc::VisualCalc(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::VisualCalc)
{
    ui->setupUi(this);
    ui->Val->setText(QString::number(calcVal));

    QPushButton* numButtons[23];
    for (int i = 0; i < 10; ++i) {
        QString butname = "Button" + QString::number(i);
        numButtons[i] = VisualCalc::findChild<QPushButton*>(butname);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Dot, SIGNAL(released()), this, SLOT(NumPressed()));
    for (int i = 1; i <= 22; i++) {
        QString butname = "Opr" + QString::number(i);
        numButtons[i] = VisualCalc::findChild<QPushButton*>(butname);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(MathButtonPressed()));
    }

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));


    Tree = new ExprTree;
}

VisualCalc::~VisualCalc()
{
    delete ui;
}

void VisualCalc::NumPressed()
{
    QPushButton* button = (QPushButton*)sender();
    QString butVal = button->text();
    QString displayVal = ui->Val->text();
    if ((displayVal.toDouble() == 0.0))
    {
        if (!butVal.compare(".")) 
        {
            ui->Val->setText("0.");
        }
        else if (!ui->Val->text().compare("0."))
        {
            QString newVal = displayVal + butVal;
            double dblNewVal = newVal.toDouble();
            ui->Val->setText(newVal);
        } else 
        ui->Val->setText(butVal);
    }
    else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Val->setText(newVal);
    }
}


void VisualCalc::MathButtonPressed()
{
    QString displayVal = ui->Val->text();
    if (!displayVal.isEmpty() && !(this->Tree->getSizeofQ() == 0 && displayVal.toDouble() == 0))
    {
        struct Node* N = new struct Node;
        N->Element = displayVal;
        N->type = Const;
        N->LChild = N->RChild = NULL;
        this->Tree->enQueue(N);
        ui->Expr->setText(this->Tree->renewExpr());
    }

    struct Node* N1 = new struct Node;
    QPushButton* button = (QPushButton*)sender();
    QString butVal = button->whatsThis();
    N1->Element = butVal;
    N1->type = Operator;
    N1->LChild = N1->RChild = NULL;
    this->Tree->enQueue(N1);
    ui->Expr->setText(this->Tree->renewExpr());

    
    ui->Val->setText("");
}

void VisualCalc::EqualButtonPressed() {
    double solution = 0.0;
    QString displayVal = ui->Val->text();
    struct Node* N = new struct Node;
    N->Element = displayVal;
    N->type = Const;
    N->LChild = N->RChild = NULL;
    this->Tree->enQueue(N);
    ui->Expr->setText(this->Tree->renewExpr());

    
    // Evaluation 
    this->Tree->buildTree();
    solution = this->Tree->evaluate();


    ui->Val->setText(QString::number(solution));
}

void VisualCalc::ChangeNumberSign()
{
    QString displayVal = ui->Val->text();
    QRegExp reg("[-+]?[0-9.]*");
    if (reg.exactMatch(displayVal))
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Val->setText(QString::number(dblDisplayValSign));
    }
}


void VisualCalc::on_Generate_clicked()
{
    new_graph = new Graph;
    new_graph->show();
}
