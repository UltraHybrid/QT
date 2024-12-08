#include "RelationController.hpp"

#include <qevent.h>

#include "RelationWidget.hpp"

void RelationController::mouseMoveEvent(QMouseEvent* event)
{
	if (activeRelation)
	{
		activeRelation->setDstPoint(widget->mapFromGlobal(QCursor::pos()));
		widget->repaint();
	}
}

void RelationController::mousePressEvent(QMouseEvent* event)
{
	const auto focusShape = widget->getFocusShape();
	if (!activeRelation && focusShape && event->button() == Qt::LeftButton)
	{
		activeShape = focusShape;
	}
}

void RelationController::mouseReleaseEvent(QMouseEvent* event)
{
	if (const auto shape = widget->getFocusShape(); shape && event->button() == Qt::LeftButton)
	{
		// first
		if (!activeRelation && activeShape == shape)
		{
			activeRelation = PaintPanel::createRelation(widget, shape, nullptr);
			activeRelation->setDstPoint(widget->mapFromGlobal(QCursor::pos()));
			activeRelation->show();
			return;
		}
		// second
		if (activeRelation && activeShape && activeShape != shape)
		{
			PaintPanel::createRelation(widget, activeShape, shape)->show();\
		}
	}

	flush();
}

void RelationController::keyPressEvent(QKeyEvent* event)
{
	if (activeRelation)
	{
		activeRelation->close();
		activeRelation = nullptr;
		activeShape = nullptr;
	}
}
