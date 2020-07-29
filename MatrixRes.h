#pragma once
#include <QDialog>

namespace Ui {
    class MatrixRes;
}

class MatrixRes : public QDialog 
{
    Q_OBJECT

public:
    explicit MatrixRes(QWidget* parent = nullptr);
    ~MatrixRes();
     
private:
    Ui::MatrixRes* ui;
    int col, row;

private slots:
    void InitRes();


};