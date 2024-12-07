#include "RelationWidget.hpp"

#include <iostream>
#include <qpainter.h>

#include "ShapeWidget.hpp"

RelationWidget::RelationWidget(QWidget* parent) : QWidget(parent)
{
}

void RelationWidget::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPoint p1, p2;
	if (first)
	{
		p1 = first->pos() + first->getCenter();
	}
	else return;

	if (second)
	{
		p2 = second->pos() + second->getCenter();
	}
	else
	{
		p2 = dst;
	}
	QPainter painter{this};
	auto pen = QPen{};
 	pen.setWidth(3);
	painter.setPen(pen);
	painter.drawLine(p1, p2);
	auto pMax = QPoint{std::max(p1.x(), p2.x()), std::max(p1.y(), p2.y())};
	if (size().height() < pMax.y() || size().width() < pMax.x())
		resize(pMax.x(), pMax.y());
	painter.end();
}

void RelationWidget::setFirst(ShapeWidget* shape)
{
	first = shape;
}

ShapeWidget* RelationWidget::getFirst() const
{
	return first;
}

void RelationWidget::setSecond(ShapeWidget* shape)
{
	second = shape;
	repaint();
}

ShapeWidget* RelationWidget::getSecond() const
{
	return second;
}

void RelationWidget::setDstPoint(QPoint p)
{
	dst = p;
	repaint();
}
