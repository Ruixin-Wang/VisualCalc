#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QMouseEvent>
#include <QPointF>
#include <QDebug>

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

    double minX = -20, minY = -40, maxX = 20, maxY = 40;
    
    QPointF startPos;


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
