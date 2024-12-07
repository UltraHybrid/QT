#pragma once
#include <ui_MainWnd.h>
#include <unordered_set>


class RelationWidget;
class ShapeWidget;


class ControlWidget : public QWidget {
public:
	enum class Regime
	{
		CREATE,
		DELETE,
		MOVE,
		RELATION,
		NONE
	};

	explicit ControlWidget(QWidget* parent);

	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

	void setRegime(Regime regime);
	void setShapeCreator(std::function<ShapeWidget*()>&& cr);

private:
	ShapeWidget* activeShape{nullptr};
	RelationWidget* activeRelation{nullptr};
	std::pmr::unordered_set<ShapeWidget*> shapes{};
	Regime regime{Regime::NONE};

	std::function<ShapeWidget*()> creator = nullptr;
	QPoint oldPos;

	void resetCreatedShape();
	void resetCreatedRelation();
	ShapeWidget* getFocusShape();
};
