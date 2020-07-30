#include "MatrixRes.h"
#include "ui_MatrixRes.h"
#include "NodeforMatrix.h"
#define MAXN 20 

extern MATRIX* MAT;

MatrixRes::MatrixRes(QWidget* parent) : 
    QDialog(parent),
    ui(new Ui::MatrixRes)
{
    ui->setupUi(this); 

    col = MAT->getCol();
    row = MAT->getRow();
    InitRes();
}

MatrixRes::~MatrixRes()
{
    delete ui;
}

void MatrixRes::InitRes()
{
    ui->Mat_Table_Widget->setColumnCount(col);
    ui->Mat_Table_Widget->setRowCount(row);
    ui->Mat_Table_Widget->resizeColumnsToContents();
    ui->Mat_Table_Widget->setAlternatingRowColors(true);

    
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            QTableWidgetItem* cell = new QTableWidgetItem;
            cell->setText(QString::number
                (MAT->data[i * MAT->getCol() + j]));
            
            ui->Mat_Table_Widget->setItem(i, j, cell);
        }
}
