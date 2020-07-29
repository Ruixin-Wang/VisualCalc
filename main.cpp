#include "VisualCalc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VisualCalc w;
    w.show();
    return a.exec();
} 
