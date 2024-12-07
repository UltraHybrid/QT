#pragma once

#include "ShapeWidget.hpp"


class TriangleWidget final : public ShapeWidget {
public:
	explicit TriangleWidget(QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* event) override;
	QPoint getCenter() override;
};
