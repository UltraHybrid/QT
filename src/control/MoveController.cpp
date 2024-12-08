#include "MoveController.hpp"

#include <qevent.h>

#include "ShapeWidget.hpp"

void MoveController::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons().testFlag(Qt::LeftButton) && activeShape)
	{
		activeShape->move(activeShape->pos() + widget->mapFromGlobal(QCursor::pos()) - oldPos);
		oldPos = widget->mapFromGlobal(QCursor::pos());

		widget->repaint();
	}
}

void MoveController::mousePressEvent(QMouseEvent* event)
{
	if (const auto focusShape = widget->getFocusShape(); focusShape && event->button() == Qt::LeftButton)
	{
		activeShape = focusShape;
		widget->setCursor(QCursor(Qt::ClosedHandCursor));
		oldPos = widget->mapFromGlobal(QCursor::pos());
		shapePosBeforeMoving = activeShape->pos();
	}
}

void MoveController::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		widget->setCursor(QCursor(Qt::ArrowCursor));
	}
	if (activeShape && event->button() == Qt::RightButton)
	{
		widget->setCursor(QCursor(Qt::ArrowCursor));
		activeShape->move(shapePosBeforeMoving);
		widget->repaint();
	}
	activeShape = nullptr;
}

void MoveController::keyPressEvent(QKeyEvent* event)
{
	if (activeShape)
	{
		widget->setCursor(QCursor(Qt::ArrowCursor));
		activeShape->move(shapePosBeforeMoving);
		widget->repaint();
		activeShape = nullptr;
	}
}
