#pragma once
#include <QDialog>

namespace Ui {
    class MatrixView;
}

class MatrixView : public QDialog
{
    Q_OBJECT

public:
    explicit MatrixView(QWidget* parent = nullptr);
    ~MatrixView();
     
private:
    Ui::MatrixView* ui;
    int col, row;

private slots:
    void rowadd();
    void rowdec();
    void coladd();
    void coldec();
    void renew();
    void InitTable();


};