#pragma once
#include "ControlWidget.hpp"


class ShapeWidget : public QWidget {
public:
	explicit ShapeWidget(QWidget* parent);

	virtual QPoint getCenter() = 0;

	void addRelation(RelationWidget* relation);
	void removeRelation(RelationWidget* relation);

	std::unordered_set<RelationWidget*> getRelations();

protected:
	std::unordered_set<RelationWidget*> relations{};
};
