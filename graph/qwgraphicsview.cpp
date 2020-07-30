#include "qwgraphicsview.h"

void QWGraphicsView::mouseMoveEvent(QMouseEvent* event) {
	emit mouseMove(event);
	if (event->buttons() & Qt::LeftButton) {
		QPointF point = event->pos() - startPos;
		double deltaX = point.x() / width() * (maxX - minX);
		double deltaY = point.y() / height() * (maxY - minY);
		minX -= deltaX, maxX -= deltaX, minY += deltaY, maxY += deltaY;
		qDebug() << minX << "," << maxX << "," << minY << "," << maxY;
	}
}