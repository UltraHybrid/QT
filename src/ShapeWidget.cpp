#include "ShapeWidget.hpp"

ShapeWidget::ShapeWidget(QWidget* parent = nullptr) : QWidget(parent)
{
	setAttribute(Qt::WA_NoSystemBackground);
}

void ShapeWidget::addRelation(RelationWidget* relation)
{
	relations.emplace(relation);
}

void ShapeWidget::removeRelation(RelationWidget* relation)
{
	relations.erase(relation);
}

std::unordered_set<RelationWidget*> ShapeWidget::getRelations()
{
	return relations;
}
