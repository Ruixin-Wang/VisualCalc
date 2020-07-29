#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QMouseEvent>
#include <QPointF>
#include <QDebug>

#include "Node.h"

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    ExprTree& Tree;

    Q_OBJECT

public:
    explicit Graph(QWidget *parent , ExprTree& tree);
    ~Graph();

    void updateArea(double minXn, double minYn, double maxXn, double maxYn)
    {
        minX = minXn;
        minY = minYn;
        maxX = maxXn;
        maxY = maxYn;
    }

private:
    Ui::Graph *ui;

    double minX = -20, minY = -40, maxX = 20, maxY = 40;
    
    QPointF startPos;

    double fx(double x);

private slots:
    void draw(QMouseEvent* event);

signals:
    void mouseMove(QMouseEvent* event);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);



};


#endif // GRAPH_H
