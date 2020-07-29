#include "qpainter.h"
#include "graph.h"
#include "ui_graph.h"



Graph::Graph(QWidget *parent, ExprTree& tree) :
    QDialog(parent), Tree(tree), 
    ui(new Ui::Graph)
{
    ui->setupUi(this);

    Graph::setMouseTracking(true);
    connect(this, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(draw(QMouseEvent*)));

    hSlider = ui->HorizontalSlider;
    vSlider = ui->VerticalSlider;
    hSlider->setValue(50);
    vSlider->setValue(50);

    connect(hSlider, SIGNAL(valueChanged(int)), this, SLOT(hSliderSlided(int)));
    connect(vSlider, SIGNAL(valueChanged(int)), this, SLOT(vSliderSlided(int)));
}

Graph::~Graph()
{
    delete ui;
}

double Graph::fx(double x)
{
        return (this->Tree.evaluate((double)x + x));
}

void Graph::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.translate(width() / 2, height() / 2);
    painter.drawLine(QPointF(-width() / 2, 0), QPointF(width() / 2, 0));
    painter.drawLine(QPointF(0, -height() / 2), QPointF(0, height() / 2));

    painter.drawText(QPointF(0, height() / 4), QString::number(0.75 * minY + 0.25 * maxY));
    painter.drawText(QPointF(0, -height() / 4), QString::number(0.25 * minY + 0.75 * maxY));
    painter.drawText(QPointF(-width() / 4, 0), QString::number(0.75 * minX + 0.25 * maxX));
    painter.drawText(QPointF(width() / 4, 0), QString::number(0.25 * minX + 0.75 * maxX));

    painter.translate(width() / 2, 0);
    QPainterPath arr1;
    arr1.lineTo(-18, 7);
    arr1.lineTo(-18, -7);
    arr1.lineTo(0, 0);
    painter.drawPath(arr1);
    painter.fillPath(arr1, Qt::black);

    painter.translate(-width() / 2, -height()/2);
    QPainterPath arr2;
    arr2.lineTo(7, 18);
    arr2.lineTo(-7, 18);
    arr2.lineTo(0, 0);
    painter.drawPath(arr2);
    painter.fillPath(arr2, Qt::black);

    painter.translate(0, height() / 2);
    painter.setPen(Qt::red);

    
    //minX = -20; maxX = 20;
    //minY = -40; maxY = 40;
    for (int i = -width() / 2; i <= width() / 2; i++)
    {
        int j = i - 1;
        QPointF currP = QPointF(i, -(fx(i * (maxX - minX) / width()+0.5*(maxX + minX))-0.5*(maxY+minY)) * height() / (maxY - minY));
        QPointF prevP = QPointF(j, -(fx(j * (maxX - minX) / width() + 0.5 * (maxX + minX)) - 0.5 * (maxY + minY)) * height() / (maxY - minY));
        painter.drawLine(prevP, currP);
    }
}

void Graph::mousePressEvent(QMouseEvent *event){
	if(event->button() == Qt::LeftButton){
		startPos = event->pos();
	}
}
void Graph::mouseMoveEvent(QMouseEvent *event){
    emit mouseMove(event);
	if(event->buttons() & Qt::LeftButton){
		QPointF point = event->pos() - startPos;
		double deltaX = point.x() / width() * (maxX - minX) / 10.0;
		double deltaY = point.y() / height() * (maxY - minY) / 10.0;
        updateArea(minX - 0.5*deltaX, minY + 0.5 * deltaY, maxX - 0.5 * deltaX, maxY + 0.5 * deltaY);
        qDebug() << minX << "," << maxX <<","<<minY<<","<<maxY;
	}
}
void Graph::mouseReleaseEvent(QMouseEvent *event){
}
void Graph::draw(QMouseEvent* event) {
    update(0, 0, width(), height());
    // qDebug() << "update"<< width()<<height();
}

void Graph::vSliderSlided(int tp)
{
    static int or = tp;
    double step = 0.2 * (maxY - minY) * ( tp - or ) * 0.05;
    updateArea(minX, minY - step, maxX, maxY + step);
    update(0, 0, width(), height());

    or = tp;
}

void Graph::hSliderSlided(int tp)
{
    static int or = tp;
    double step = 0.2 * (maxY - minY) * (tp - or ) * 0.5;
    updateArea(minX - step, minY, maxX + step, maxY);
    update(0, 0, width(), height());

    or = tp;
}