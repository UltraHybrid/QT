#pragma once
#include "AbstractController.hpp"


class RelationController : public AbstractController {
public:
	explicit RelationController(PaintPanel* widget)
		: AbstractController(widget)
	{
	}

	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
};
