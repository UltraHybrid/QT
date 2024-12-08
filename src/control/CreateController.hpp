#pragma once
#include "AbstractController.hpp"


class ShapeWidget;

class CreateController : public AbstractController {
public:
	explicit CreateController(ControlWidget* widget);

	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
};
