#pragma once


class RelationWidget;
class ShapeWidget;
class ControlWidget;
class QKeyEvent;
class QMouseEvent;

class AbstractController {
public:
	virtual ~AbstractController() = default;
	explicit AbstractController(ControlWidget* widget);

	virtual void mouseMoveEvent(QMouseEvent* event) {}
	virtual void mousePressEvent(QMouseEvent* event) {}
	virtual void mouseReleaseEvent(QMouseEvent* event) {}
	virtual void keyPressEvent(QKeyEvent* event) {}
	virtual void flush();

protected:
	ControlWidget* widget;
	ShapeWidget* activeShape{nullptr};
	RelationWidget* activeRelation{nullptr};
};
