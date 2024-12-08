#include "ShapeWidget.hpp"


ShapeWidget::ShapeWidget(QWidget* parent, const ShapeType type) : QWidget(parent), type(type)
{
	setAttribute(Qt::WA_NoSystemBackground);
	setFocusPolicy(Qt::NoFocus);
	setAttribute( Qt::WA_TransparentForMouseEvents );
	setMouseTracking(false);
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
