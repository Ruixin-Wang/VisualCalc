#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QtCharts/QChartView>


using namespace QtCharts;

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();

private:
    Ui::Graph *ui;
    double minX, maxX, minY, maxY;


protected:
    void paintEvent(QPaintEvent*);



};


#endif // GRAPH_H
