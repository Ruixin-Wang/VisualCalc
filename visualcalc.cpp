#include "VisualCalc.h"
#include "ui_VisualCalc.h"

#include "Node.h"

double calcVal = 0.0;
bool divTrig = false;
bool mulTrig = false;
bool addTrig = false;
bool subTrig = false;

std::map<std::string, int> variables;

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
    connect(ui->DEL, SIGNAL(released()), this, SLOT(DeleteButtonPressed()));
    connect(ui->AC, SIGNAL(released()), this, SLOT(ClearButtonPressed()));

    // used to build Tree
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
    // construct Const node
    if (!displayVal.isEmpty() && !(this->Tree->getSizeofQ() == 0 && displayVal.toDouble() == 0))
    {
        Node* N = new ConstNode(displayVal.toDouble());
        this->Tree->enQueue(N);
        ui->Expr->setText(this->Tree->renewExpr());
    }

    
    QPushButton* button = (QPushButton*)sender();
    QString butVal = button->whatsThis();
    // TODO: complete, and what to compare
    if (butVal == QString::fromStdString("+")) 
    {
        Node* N1 = new AddNode(nullptr, nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("*"))
    {
        Node* N1 = new MutliplyNode(nullptr, nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("sin"))
    {
        Node* N1 = new SinNode(nullptr);
        this->Tree->enQueue(N1);
    }
    else if (butVal == QString::fromStdString("cos"))
    {
        Node* N1 = new CosNode(nullptr);
        this->Tree->enQueue(N1);
    }
    ui->Expr->setText(this->Tree->renewExpr());

    
    ui->Val->setText("");
}

void VisualCalc::EqualButtonPressed() {
    double solution = 0.0;
    QString displayVal = ui->Val->text();
    Node* N = new ConstNode(displayVal.toDouble());
    this->Tree->enQueue(N);
    ui->Expr->setText(this->Tree->renewExpr());

    
    // Evaluation 
    this->Tree->buildTree();
    // TODO: evaluate equation with variables
    // when x=0?
    solution = this->Tree->evaluate();


    ui->Val->setText(QString::number(solution));
    this->Tree->clear();
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

void VisualCalc::DeleteButtonPressed()
{
    QString displayVal = ui->Val->text();
    if (displayVal.compare(""))
    {
        displayVal.chop(1);
        ui->Val->setText(displayVal);
    }
    else
    {
        this->Tree->del();
        ui->Expr->setText(this->Tree->renewExpr());
    }

}

void VisualCalc::ClearButtonPressed()
{
    this->Tree->clear();
    ui->Val->setText("0");
    ui->Expr->setText(this->Tree->renewExpr());
}

void VisualCalc::on_Generate_clicked()
{
    new_graph = new Graph;
    new_graph->show();
}
