#pragma once
#include <QDialog>

class QWGraphicsView : public QWGraphicsView
{
	Q_OBJECT

private:
	double minX = -20, minY = -40, maxX = 20, maxY = 40;

	QPointF startPos;

protected:
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
public:
	QWGraphicsView(QWidget* parent = nullptr);
signals:
	void mouseMove(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
};