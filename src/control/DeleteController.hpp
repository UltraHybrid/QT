#pragma once
#include "AbstractController.hpp"


class DeleteController final : public AbstractController
{
public:
	explicit DeleteController(ControlWidget* widget)
		: AbstractController(widget)
	{
	}

	void mousePressEvent(QMouseEvent* event) override;
};
