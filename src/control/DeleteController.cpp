#include "DeleteController.hpp"

#include <qevent.h>

#include "ControlWidget.hpp"

void DeleteController::mousePressEvent(QMouseEvent* event)
{
	const auto focusShape = widget->getFocusShape();
	if (focusShape && event->button() == Qt::LeftButton)
	{
		ControlWidget::clearShape(focusShape);
		widget->removeShape(focusShape);
	}
}
