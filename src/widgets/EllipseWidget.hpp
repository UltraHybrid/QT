#pragma once
#include "ShapeWidget.hpp"


class EllipseWidget final : public ShapeWidget {
public:
	explicit EllipseWidget(QWidget* parent = nullptr);

	void paintEvent(QPaintEvent* event) override;
	QPoint getCenter() override;
};
