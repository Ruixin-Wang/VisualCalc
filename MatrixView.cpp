#include "MatrixView.h"
#include "ui_MatrixView.h"
#include "NodeforMatrix.h"
#define MAXN 20 

extern std::map<std::string, MATRIX*> variablesforMatrix;
extern std::string CurrentMat;

MatrixView::MatrixView(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::MatrixView)
{
    ui->setupUi(this); 

    MATRIX* MAT = variablesforMatrix[CurrentMat];
    col = (MAT != NULL) ? MAT->getCol() : 0;
    row = (MAT != NULL) ? MAT->getRow() : 0;
    InitTable();
    

    
    connect(ui->RowAdd, SIGNAL(released()), this, SLOT(rowadd()));
    connect(ui->RowDec, SIGNAL(released()), this, SLOT(rowdec()));
    connect(ui->ColAdd, SIGNAL(released()), this, SLOT(coladd()));
    connect(ui->ColDec, SIGNAL(released()), this, SLOT(coldec()));
    connect(ui->Finish, SIGNAL(released()), this, SLOT(renew()));

}

MatrixView::~MatrixView()
{
    delete ui;
}

void MatrixView::InitTable()
{
    ui->Mat_Table_Widget->setColumnCount(col);
    ui->Mat_Table_Widget->setRowCount(row);
    ui->Mat_Table_Widget->resizeColumnsToContents();
    ui->Mat_Table_Widget->setAlternatingRowColors(true);

    
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            QTableWidgetItem* cell = new QTableWidgetItem;
            if (variablesforMatrix[CurrentMat]!=NULL &&
                i < variablesforMatrix[CurrentMat]->getRow() &&
                j < variablesforMatrix[CurrentMat]->getCol())
            cell->setText(QString::number
                (variablesforMatrix[CurrentMat]->data[i * variablesforMatrix[CurrentMat]->getCol() + j]));
            
            ui->Mat_Table_Widget->setItem(i, j, cell);
        }
}

void MatrixView::rowadd()
{
    if (row < MAXN)
    row++;
    InitTable();
}

void MatrixView::rowdec()
{
    if (row > 0)
    row--;
    InitTable();
}

void MatrixView::coladd()
{
    if (col < MAXN)
    col++;
    InitTable();
}

void MatrixView::coldec()
{
    if (col > 0)
    col--;
    InitTable();
}

void MatrixView::renew()
{
    double data[400];
    QTableWidgetItem* cellItem;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            cellItem = ui->Mat_Table_Widget->item(i, j);
            data[i * col + j] = cellItem->text().toDouble();
        }
    MATRIX* MAT = new MATRIX(row, col, data);
    variablesforMatrix[CurrentMat] = MAT;
    this->close();
}