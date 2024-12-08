#pragma once
#include "PaintPanel.hpp"
#include "ShapeType.hpp"


class RelationWidget;


class ShapeWidget : public QWidget {
public:
	explicit ShapeWidget(QWidget* parent, ShapeType type);

	virtual QPoint getCenter() = 0;
	virtual ShapeType getType(){ return type; }

	void addRelation(RelationWidget* relation);
	void removeRelation(RelationWidget* relation);

	std::unordered_set<RelationWidget*> getRelations();

protected:
	std::unordered_set<RelationWidget*> relations{};

private:
	ShapeType type;
};
