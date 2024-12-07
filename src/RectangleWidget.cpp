#include "RectangleWidget.hpp"

#include <qpainter.h>

RectangleWidget::RectangleWidget(QWidget* parent) : ShapeWidget(parent, ShapeType::RECTANGLE)
{
}

void RectangleWidget::paintEvent(QPaintEvent* event)
{
	ShapeWidget::paintEvent(event);
	auto painter = QPainter{this};
	auto pen = QPen();
	constexpr auto penWidth = 3;
	pen.setWidth(penWidth);
	painter.setPen(pen);
	painter.drawRect(penWidth, penWidth, size().width() - penWidth * 2, size().height() - penWidth * 2);
	painter.end();
}

QPoint RectangleWidget::getCenter()
{
	return rect().center();
}
