#pragma once
#include "ShapeWidget.hpp"


class RectangleWidget final  : public ShapeWidget  {
public:
	explicit RectangleWidget(QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* event) override;
	QPoint getCenter() override;
};
