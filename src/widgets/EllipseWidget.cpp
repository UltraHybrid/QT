#include "EllipseWidget.hpp"

#include <qpainter.h>


EllipseWidget::EllipseWidget(QWidget* parent): ShapeWidget(parent, ShapeType::ELLIPSE)
{
}

void EllipseWidget::paintEvent(QPaintEvent* event)
{
	ShapeWidget::paintEvent(event);
	auto painter = QPainter{this};
	auto pen = QPen();
	constexpr auto penWidth = 3;
	pen.setWidth(penWidth);
	painter.setPen(pen);
	painter.drawEllipse(penWidth, penWidth, size().width() - penWidth * 2, size().height() - penWidth * 2);
	painter.end();
}

QPoint EllipseWidget::getCenter()
{
	return rect().center();
}
