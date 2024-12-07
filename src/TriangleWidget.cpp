#include "TriangleWidget.hpp"

#include <qpainter.h>


TriangleWidget::TriangleWidget(QWidget* parent) : ShapeWidget(parent, ShapeType::TRIANGLE)
{

}

void TriangleWidget::paintEvent(QPaintEvent* event)
{
	auto painter = QPainter{this};
	auto pen = QPen();
	constexpr auto penWidth = 3;
	pen.setWidth(penWidth);
	painter.setPen(pen);
	painter.drawPolygon(
		{
			QPointF{size().width() / 2., penWidth},
			QPointF{size().width() - penWidth * 2., size().height() - penWidth * 2.},
			QPointF{penWidth, size().height() - penWidth * 2.}
		});
	painter.end();
	QWidget::paintEvent(event);
}

QPoint TriangleWidget::getCenter()
{
	auto c = rect().center();
	c.setY(size().height() * 2 / 3);
	return c;
}
