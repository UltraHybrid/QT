#include "CreateController.hpp"

#include <qevent.h>

#include "PaintPanel.hpp"
#include "ShapeFactory.hpp"

CreateController::CreateController(PaintPanel* widget)
		: AbstractController(widget)
{
}

void CreateController::mouseMoveEvent(QMouseEvent* event)
{
	const auto pos = event->pos();
	if (activeShape)
	{
		auto w = pos.x() - activeShape->pos().x();
		auto h = pos.y() - activeShape->pos().y();
		activeShape->resize(w, h);
	}
}

void CreateController::mousePressEvent(QMouseEvent* event)
{
	if (!activeShape && event->button() == Qt::LeftButton)
	{
		activeShape = ShapeFactory::createShape(widget, widget->getShapeType(), event->pos(), {1, 1});
		activeShape->show();
	}
	else if (event->button() == Qt::RightButton)
	{
		activeShape->close();
		activeShape = nullptr;
	}
}

void CreateController::mouseReleaseEvent(QMouseEvent* event)
{
	if (activeShape)
	{
		const auto pos = event->pos();
		const auto w = pos.x() - activeShape->pos().x();
		const auto h = pos.y() - activeShape->pos().y();
		if (w > 0 && h > 0)
		{
			widget->addShape(activeShape);
			activeShape = nullptr;
		}
		else
		{
			activeShape->close();
			activeShape = nullptr;
		}
	}
}

void CreateController::keyPressEvent(QKeyEvent* event)
{
	if (activeShape)
	{
		activeShape->close();
		activeShape = nullptr;
	}
}
