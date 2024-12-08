#pragma once


class RelationWidget;
class ShapeWidget;
class PaintPanel;
class QKeyEvent;
class QMouseEvent;

class AbstractController {
public:
	virtual ~AbstractController() = default;
	explicit AbstractController(PaintPanel* widget);

	virtual void mouseMoveEvent(QMouseEvent* event) {}
	virtual void mousePressEvent(QMouseEvent* event) {}
	virtual void mouseReleaseEvent(QMouseEvent* event) {}
	virtual void keyPressEvent(QKeyEvent* event) {}
	virtual void flush();

protected:
	PaintPanel* widget;
	ShapeWidget* activeShape{nullptr};
	RelationWidget* activeRelation{nullptr};
};
