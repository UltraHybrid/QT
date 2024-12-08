#include "PaintPanel.hpp"

#include <iostream>
#include <qevent.h>

#include "ShapeInfo.hpp"
#include "ShapeFactory.hpp"
#include "ShapeWidget.hpp"
#include "RelationWidget.hpp"
#include "ControlManager.hpp"
#include "CreateController.hpp"
#include "DeleteController.hpp"
#include "MoveController.hpp"
#include "RelationController.hpp"


PaintPanel::PaintPanel(QWidget* parent) : QWidget(parent)
{
	controller = std::make_shared<ControlManager>(this);
	controller->addController(Regime::MOVE, std::make_shared<MoveController>(this));
	controller->addController(Regime::DELETE, std::make_shared<DeleteController>(this));
	controller->addController(Regime::CREATE, std::make_shared<CreateController>(this));
	controller->addController(Regime::RELATION, std::make_shared<RelationController>(this));
}

void PaintPanel::mouseMoveEvent(QMouseEvent* event)
{
	QWidget::mouseMoveEvent(event);
	controller->mouseMoveEvent(regime, event);
}

void PaintPanel::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);
	controller->mousePressEvent(regime, event);
}

void PaintPanel::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mouseReleaseEvent(event);
	controller->mouseReleaseEvent(regime, event);
}

void PaintPanel::keyPressEvent(QKeyEvent* event)
{
	QWidget::keyPressEvent(event);
	controller->keyPressEvent(regime, event);
}

void PaintPanel::setRegime(const Regime regime)
{
	controller->flush();
	this->regime = regime;
}

PaintPanel::Regime PaintPanel::getRegime() const
{
	return regime;
}

ShapeType PaintPanel::getShapeType() const
{
	return createShapeType;
}

void PaintPanel::addShape(ShapeWidget* shape)
{
	shapes.emplace(shape);
}

void PaintPanel::removeShape(ShapeWidget* shape)
{
	shapes.erase(shape);
}

void PaintPanel::setShapeType(const ShapeType type)
{
	createShapeType = type;
}

ShapeWidget* PaintPanel::getFocusShape()
{
	const auto shape = std::ranges::find_if(shapes, [this](const ShapeWidget* sw)
	{
		return sw->rect().contains(mapFromGlobal(QCursor::pos()) - sw->pos());
	});
	if (shape != shapes.end())
	{
		return *shape;
	}
	return nullptr;
}

bool PaintPanel::isShapesConnect(ShapeWidget* sw1, ShapeWidget* sw2)
{
	return std::ranges::any_of(sw1->getRelations(), [sw2](const RelationWidget* rw)
	{
		return rw->getFirst() == sw2 || rw->getSecond() == sw2;
	});
}

RelationWidget* PaintPanel::createRelation(QWidget* parent, ShapeWidget* sw1, ShapeWidget* sw2)
{
	const auto rel = new RelationWidget;
	rel->setParent(parent);
	rel->setFirst(sw1);
	rel->setSecond(sw2);

	if (sw1 && sw2)
	{
		sw1->addRelation(rel);
		sw2->addRelation(rel);
	}

	return rel;
}

void PaintPanel::clearShape(ShapeWidget* sw)
{
	for (const auto r : sw->getRelations())
	{
		r->getFirst()->removeRelation(r);
		r->getSecond()->removeRelation(r);
		r->close();
	}
	sw->close();
}

void PaintPanel::removeAllShapes()
{
	std::ranges::for_each(shapes, [](ShapeWidget* s){ clearShape(s);});
	shapes.clear();
}

void PaintPanel::saveTo(QDataStream& stream)
{
	const auto shapesV = std::vector<ShapeWidget*>{shapes.begin(), shapes.end()};
	auto res = QVector<ShapeInfo>{};
	for (const auto sw : shapesV)
	{
		ShapeInfo info;
		info.type = static_cast<int>(sw->getType());
		info.pos = sw->pos();
		info.size = {sw->width(), sw->height()};
		info.relationIds.reserve(sw->getRelations().size());

		std::ranges::transform(sw->getRelations(), std::back_inserter(info.relationIds),
			[shapesV, sw](const RelationWidget* rw)
			{
				const auto relateShape = rw->getFirst() == sw ? rw->getSecond() : rw->getFirst();
				return std::ranges::find(shapesV, relateShape) - shapesV.begin();
			});

		res.emplace_back(info);
	}

	stream << res;
}

void PaintPanel::loadFrom(QDataStream& stream)
{
	removeAllShapes();

	auto in = QVector<ShapeInfo>{};

	stream >> in;

	auto inShapes = QVector<ShapeWidget*>{};

	for (const auto& e: in)
	{
		const auto shape = ShapeFactory::createShape(this, static_cast<ShapeType>(e.type), e.pos, e.size);
		shape->show();
		inShapes.push_back(shape);
	}

	for (auto i = 0; i < in.size(); ++i)
	{
		auto& shapeInfo = in.at(i);
		for (const auto j : shapeInfo.relationIds)
		{
			if (isShapesConnect(inShapes.at(i), inShapes.at(j))) continue;
			const auto relation = createRelation(this, inShapes.at(i), inShapes.at(j));
			relation->show();
		}
	}

	shapes = std::unordered_set<ShapeWidget*>{inShapes.begin(), inShapes.end()};
}
