#pragma once
#include <QWidget>
#include <unordered_set>

#include "ShapeType.hpp"
#include "ShapeWidget.hpp"


class ControlManager;
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

	void setRegime(Regime regime);
	Regime getRegime();
	void saveTo(QDataStream &stream);
	void loadFrom(QDataStream &stream);
	void setShapeType(ShapeType type);
	ShapeType getShapeType() const;
	void addShape(ShapeWidget* shape);
	void removeShape(ShapeWidget* shape);

private:
	std::unordered_set<ShapeWidget*> shapes{};
	Regime regime{Regime::NONE};
	ShapeType createShapeType;
	std::shared_ptr<ControlManager> controller;

public:
	ShapeWidget* getFocusShape();

	static bool isShapesConnect(ShapeWidget* sw1, ShapeWidget* sw2);

	static RelationWidget* createRelation(QWidget* parent, ShapeWidget* sw1, ShapeWidget* sw2);

	static void clearShape(ShapeWidget* sw);
	void removeAllShapes();
};
