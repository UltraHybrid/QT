#pragma once
#include <qpoint.h>

#include "AbstractController.hpp"


class ShapeWidget;

class MoveController : public AbstractController {
public:
	explicit MoveController(ControlWidget* widget)
		: AbstractController(widget)
	{
	}

	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

private:
	QPoint oldPos;
	QPoint shapePosBeforeMoving;
};
