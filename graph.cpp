#include "qpainter.h"

#include "graph.h"
#include "ui_graph.h"


Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);

    
}

Graph::~Graph()
{
    delete ui;
}

void Graph::paintEvent(QPaintEvent*, double posX, double posY)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Qt");
}