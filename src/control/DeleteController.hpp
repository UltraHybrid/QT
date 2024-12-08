#pragma once
#include "AbstractController.hpp"


class DeleteController final : public AbstractController
{
public:
	explicit DeleteController(PaintPanel* widget)
		: AbstractController(widget)
	{
	}

	void mousePressEvent(QMouseEvent* event) override;
};
