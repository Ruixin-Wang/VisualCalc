#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

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

protected:
    void paintEvent(QPaintEvent*, double posX, double posY);



};


#endif // GRAPH_H
