#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QMouseEvent>
#include <QPointF>

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

    double minX, minY, maxX, maxY;
    
    QPointF startPos;
    bool isMoving;

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);



};


#endif // GRAPH_H
