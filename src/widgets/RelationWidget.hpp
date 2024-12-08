#pragma once
#include "PaintPanel.hpp"

class ShapeWidget;

class RelationWidget : public QWidget {
public:
	explicit RelationWidget(QWidget* parent = nullptr);

	void paintEvent(QPaintEvent* event) override;

	void setFirst(ShapeWidget* shape);
	ShapeWidget* getFirst() const;
	void setSecond(ShapeWidget* shape);
	ShapeWidget* getSecond() const;

	void setDstPoint(QPoint p);

private:
	ShapeWidget* first{nullptr};
	ShapeWidget* second{nullptr};
	QPoint dst{};
};
