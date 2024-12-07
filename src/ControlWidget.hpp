#pragma once
#include <ui_MainWnd.h>
#include <unordered_set>

#include "ShapeType.hpp"
#include "ShapeWidget.hpp"


class RelationWidget;
class ShapeWidget;


struct ShapeInfo
{
	qint32 type;
	QPoint pos;
	QPoint size;
	QVector<qint32> relationIds{};


};

QDataStream& operator<<(QDataStream& out, const ShapeInfo& st);

QDataStream& operator>>(QDataStream& in, const ShapeInfo& st);




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
	void saveTo(QDataStream &stream);
	void loadFrom(QDataStream &stream);

private:
	ShapeWidget* activeShape{nullptr};
	RelationWidget* activeRelation{nullptr};
	std::unordered_set<ShapeWidget*> shapes{};
	Regime regime{Regime::NONE};

	std::function<ShapeWidget*()> creator = nullptr;
	QPoint oldPos;
	QPoint shapePosBeforeMoving;

	void resetCreatedShape();
	void resetCreatedRelation();
	ShapeWidget* getFocusShape();

	static bool isShapesConnect(ShapeWidget* sw1, ShapeWidget* sw2);
};
