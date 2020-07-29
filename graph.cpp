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
        QPointF currP = QPointF(i, -fx(i * (maxX - minX) / width()) * height() / (maxY - minY));
        QPointF prevP = QPointF(j, -fx(j * (maxX - minX) / width()) * height() / (maxY - minY));
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
		double deltaX = point.x() / width() * (maxX - minX);
		double deltaY = point.y() / height() * (maxY - minY);
		// minX -= deltaX, maxX -= deltaX, minY += deltaY, maxY += deltaY;
        updateArea(minX + 0.5*deltaX, minY + 0.5 * deltaY, maxX - 0.5 * deltaX, maxY - 0.5 * deltaY);
        qDebug() << minX << "," << maxX <<","<<minY<<","<<maxY;
	}
}
void Graph::mouseReleaseEvent(QMouseEvent *event){
}
void Graph::draw(QMouseEvent* event) {
    update(0, 0, width(), height());
    // qDebug() << "update"<< width()<<height();
}