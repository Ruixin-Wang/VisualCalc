#include "VisualCalc.h"
#include "ui_VisualCalc.h"

double delta = 0.000000001;

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

    QPushButton* numButtons[10];
    for (int i = 0; i < 10; ++i) {
        QString butname = "Button" + QString::number(i);
        numButtons[i] = VisualCalc::findChild<QPushButton*>(butname);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Sub, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Mul, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

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
    if ((displayVal.toDouble() >= -delta || displayVal.toDouble() <= delta))
    {
        ui->Val->setText(butVal);
    }
    else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Val->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void VisualCalc::MathButtonPressed()
{
    divTrig = false;
    mulTrig = false;
    addTrig = false;
    subTrig = false;

    QString displayVal = ui->Val->text();
    calcVal = displayVal.toDouble();

    QPushButton* button = (QPushButton*)sender();
    QString butVal = button->text();

    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0) {
        divTrig = true;
    }
    else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0) {
        mulTrig = true;
    }
    else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0) {
        addTrig = true;
    }
    else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0) {
        subTrig = true;
    }

    ui->Val->setText("");
}

void VisualCalc::EqualButtonPressed() {
    double solution = 0.0;
    QString displayVal = ui->Val->text();
    double dblDisplayVal = displayVal.toDouble();
    if (addTrig || subTrig || mulTrig || divTrig) {
        if (addTrig) {
            solution = calcVal + dblDisplayVal;
        }
        else if (subTrig) {
            solution = calcVal - dblDisplayVal;
        }
        else if (mulTrig) {
            solution = calcVal * dblDisplayVal;
        }
        else if (divTrig) {
            solution = calcVal / dblDisplayVal;
        }
    }
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
