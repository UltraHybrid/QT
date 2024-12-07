#include "ControlWidget.hpp"

#include <iostream>
#include <qevent.h>

#include "RelationWidget.hpp"
#include "ShapeWidget.hpp"


ControlWidget::ControlWidget(QWidget* parent) : QWidget(parent)
{
}

void ControlWidget::mouseMoveEvent(QMouseEvent* event)
{
	// QWidget::mouseMoveEvent(event);
	if (regime == Regime::CREATE)
	{
		const auto pos = event->pos();
		if (activeShape)
		{
			auto w = pos.x() - activeShape->pos().x();
			auto h = pos.y() - activeShape->pos().y();
			activeShape->resize(w, h);
		}
	}
	else if (regime == Regime::RELATION)
	{
		if (activeRelation)
		{
			activeRelation->setDstPoint(mapFromGlobal(QCursor::pos()));
			repaint();
		}
	}
	else if (regime == Regime::MOVE && event->buttons().testFlag(Qt::LeftButton) && activeShape)
	{
		activeShape->move(activeShape->pos() + mapFromGlobal(QCursor::pos()) - oldPos);
		oldPos = mapFromGlobal(QCursor::pos());

		repaint();
	}
}

void ControlWidget::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);
	const auto focusShape = getFocusShape();
	switch (regime)
	{
		case Regime::CREATE:
			if (!activeShape && event->button() == Qt::LeftButton && creator)
			{
				const auto pos = event->pos();
				activeShape = creator();
				activeShape->setParent(this);
				activeShape->move(pos.x(), pos.y());
				activeShape->resize(1, 1);
				activeShape->show();
			}
			else if (event->button() == Qt::RightButton)
			{
				resetCreatedShape();
			}
			break;
		case Regime::DELETE:
			//TODO relations
			if (focusShape && event->button() == Qt::LeftButton)
			{
				for (const auto r : focusShape->getRelations())
				{
					r->getFirst()->removeRelation(r);
					r->getSecond()->removeRelation(r);
					r->close();
				}
				shapes.erase(focusShape);
				focusShape->close();
			}
			break;

		case Regime::RELATION:
			if (!activeRelation && focusShape && event->button() == Qt::LeftButton)
			{
				activeShape = focusShape;
			}
			break;
		case Regime::MOVE:
			if (focusShape && event->button() == Qt::LeftButton)
			{
				activeShape = focusShape;
				setCursor(QCursor(Qt::ClosedHandCursor));
				oldPos = mapFromGlobal(QCursor::pos());
			}
			break;
		default: ;
	}
}

void ControlWidget::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mouseReleaseEvent(event);
	switch (regime)
	{
		case Regime::CREATE:
			if (activeShape)
			{
				const auto pos = event->pos();
				const auto w = pos.x() - activeShape->pos().x();
				const auto h = pos.y() - activeShape->pos().y();
				if (w > 0 && h > 0)
				{
					shapes.emplace(activeShape);
					activeShape = nullptr;
				}
				else
				{
					resetCreatedShape();
				}
			}
		case Regime::MOVE:
			setCursor(QCursor(Qt::ArrowCursor));
		activeShape = nullptr;
		break;
		case Regime::RELATION:
			if (const auto shape = getFocusShape(); shape && event->button() == Qt::LeftButton)
			{
				// first
				if (!activeRelation && activeShape == shape)
				{
					activeRelation = new RelationWidget{};
					activeRelation->setParent(this);
					activeRelation->setFirst(shape);
					activeRelation->setDstPoint(mapFromGlobal(QCursor::pos()));
					activeRelation->show();
				}
				// second
				else if (activeRelation && activeShape != shape)
				{
					activeRelation->setSecond(shape);
					activeRelation->getFirst()->addRelation(activeRelation);
					activeRelation->getSecond()->addRelation(activeRelation);
					activeRelation = nullptr;
					activeShape = nullptr;
				}
			}
			else
			{
				resetCreatedRelation();
			}
		break;
	}
}

void ControlWidget::keyPressEvent(QKeyEvent* event)
{
	QWidget::keyPressEvent(event);
	if (event->key() == Qt::Key_Escape)
	{
		if (regime == Regime::CREATE)
		{
			resetCreatedShape();
		}
		if (regime == Regime::RELATION)
		{
			resetCreatedRelation();
			activeShape = nullptr;
		}
	}
}

void ControlWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
}

void ControlWidget::setRegime(Regime regime)
{
	this->regime = regime;
}

void ControlWidget::setShapeCreator(std::function<ShapeWidget*()>&& cr)
{
	creator = cr;
}

void ControlWidget::resetCreatedShape()
{
	if (activeShape)
	{
		activeShape->close();
		activeShape = nullptr;
	}
}

void ControlWidget::resetCreatedRelation()
{
	if (activeRelation)
	{
		activeRelation->close();
		activeRelation = nullptr;
	}
}

ShapeWidget* ControlWidget::getFocusShape()
{
	auto shape = std::ranges::find_if(shapes, [this](const ShapeWidget* sw)
	{
		return sw->rect().contains(mapFromGlobal(QCursor::pos()) - sw->pos());
	});
	if (shape != shapes.end())
	{
		return *shape;
	}
	return nullptr;
}
