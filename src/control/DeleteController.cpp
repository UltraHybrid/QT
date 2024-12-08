#include "DeleteController.hpp"

#include <qevent.h>

#include "PaintPanel.hpp"

void DeleteController::mousePressEvent(QMouseEvent* event)
{
	const auto focusShape = widget->getFocusShape();
	if (focusShape && event->button() == Qt::LeftButton)
	{
		PaintPanel::clearShape(focusShape);
		widget->removeShape(focusShape);
	}
}
