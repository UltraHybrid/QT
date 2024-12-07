#include "ControlWidget.hpp"

#include <iostream>
#include <qevent.h>

#include "ShapeFactory.hpp"
#include "ShapeWidget.hpp"
#include "RelationWidget.hpp"


QDataStream& operator<<(QDataStream& out, const ShapeInfo& st)
{
	out << st.type;
	out << st.pos;
	out << st.size;
	out << st.relationIds;
	return out;
}

QDataStream& operator>>(QDataStream& in, ShapeInfo& st)
{
	in >> st.type;
	in >> st.pos;
	in >> st.size;
	in >> st.relationIds;
	return in;
}

ControlWidget::ControlWidget(QWidget* parent) : QWidget(parent)
{
}

void ControlWidget::mouseMoveEvent(QMouseEvent* event)
{
	// QWidget::mouseMoveEvent(event);
	if (regime == Regime::CREATE)
	{
		const auto pos = event->pos();
		if (activeShape)
		{
			auto w = pos.x() - activeShape->pos().x();
			auto h = pos.y() - activeShape->pos().y();
			activeShape->resize(w, h);
		}
	}
	else if (regime == Regime::RELATION)
	{
		if (activeRelation)
		{
			activeRelation->setDstPoint(mapFromGlobal(QCursor::pos()));
			repaint();
		}
	}
	else if (regime == Regime::MOVE && event->buttons().testFlag(Qt::LeftButton) && activeShape)
	{
		activeShape->move(activeShape->pos() + mapFromGlobal(QCursor::pos()) - oldPos);
		oldPos = mapFromGlobal(QCursor::pos());

		repaint();
	}
}

void ControlWidget::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);
	const auto focusShape = getFocusShape();
	switch (regime)
	{
		case Regime::CREATE:
			if (!activeShape && event->button() == Qt::LeftButton)
			{
				activeShape = ShapeFactory::createShape(this, createShapeType, event->pos(), {1, 1});
				activeShape->show();
			}
			else if (event->button() == Qt::RightButton)
			{
				resetCreatedShape();
			}
			break;
		case Regime::DELETE:
			//TODO relations
			if (focusShape && event->button() == Qt::LeftButton)
			{
				clearShape(focusShape);
				shapes.erase(focusShape);
			}
			break;

		case Regime::RELATION:
			if (!activeRelation && focusShape && event->button() == Qt::LeftButton)
			{
				activeShape = focusShape;
			}
			break;
		case Regime::MOVE:
			if (focusShape && event->button() == Qt::LeftButton)
			{
				activeShape = focusShape;
				setCursor(QCursor(Qt::ClosedHandCursor));
				oldPos = mapFromGlobal(QCursor::pos());
				shapePosBeforeMoving = activeShape->pos();
			}
			break;
		default: ;
	}
}

void ControlWidget::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mouseReleaseEvent(event);
	switch (regime)
	{
		case Regime::CREATE:
			if (activeShape)
			{
				const auto pos = event->pos();
				const auto w = pos.x() - activeShape->pos().x();
				const auto h = pos.y() - activeShape->pos().y();
				if (w > 0 && h > 0)
				{
					shapes.emplace(activeShape);
					activeShape = nullptr;
				}
				else
				{
					resetCreatedShape();
				}
			}
		case Regime::MOVE:
			if (event->button() == Qt::LeftButton)
			{
				setCursor(QCursor(Qt::ArrowCursor));
			}
			if (event->button() == Qt::RightButton)
			{
				setCursor(QCursor(Qt::ArrowCursor));
				activeShape->move(shapePosBeforeMoving);
				repaint();
			}
			activeShape = nullptr;
		break;
		case Regime::RELATION:
			if (const auto shape = getFocusShape(); shape && event->button() == Qt::LeftButton)
			{
				// first
				if (!activeRelation && activeShape == shape)
				{
					activeRelation = createRelation(this, shape, nullptr);
					activeRelation->setDstPoint(mapFromGlobal(QCursor::pos()));
					activeRelation->show();
				}
				// second
				else if (activeRelation && activeShape != shape)
				{
					activeRelation->close();
					activeRelation = createRelation(this, activeShape, shape);
					activeRelation->show();
					activeRelation = nullptr;
					activeShape = nullptr;
				}
			}
			else
			{
				resetCreatedRelation();
			}
		break;
	}
}

void ControlWidget::keyPressEvent(QKeyEvent* event)
{
	QWidget::keyPressEvent(event);
	if (event->key() == Qt::Key_Escape)
	{
		if (regime == Regime::CREATE && activeShape)
		{
			resetCreatedShape();
		}
		if (regime == Regime::RELATION && activeRelation)
		{
			resetCreatedRelation();
			activeShape = nullptr;
		}
		if (regime == Regime::MOVE && activeShape)
		{
			setCursor(QCursor(Qt::ArrowCursor));
			activeShape->move(shapePosBeforeMoving);
			repaint();
			activeShape = nullptr;
		}
	}
}

void ControlWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
}

void ControlWidget::setRegime(Regime regime)
{
	this->regime = regime;
}

void ControlWidget::setShapeType(ShapeType type)
{
	createShapeType = type;
}

void ControlWidget::resetCreatedShape()
{
	if (activeShape)
	{
		activeShape->close();
		activeShape = nullptr;
	}
}

void ControlWidget::resetCreatedRelation()
{
	if (activeRelation)
	{
		activeRelation->close();
		activeRelation = nullptr;
	}
}

ShapeWidget* ControlWidget::getFocusShape()
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

bool ControlWidget::isShapesConnect(ShapeWidget* sw1, ShapeWidget* sw2)
{
	return std::ranges::any_of(sw1->getRelations(), [sw2](const RelationWidget* rw)
	{
		return rw->getFirst() == sw2 || rw->getSecond() == sw2;
	});
}

RelationWidget* ControlWidget::createRelation(QWidget* parent, ShapeWidget* sw1, ShapeWidget* sw2)
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

void ControlWidget::clearShape(ShapeWidget* sw)
{
	for (const auto r : sw->getRelations())
	{
		r->getFirst()->removeRelation(r);
		r->getSecond()->removeRelation(r);
		r->close();
	}
	sw->close();
}

void ControlWidget::removeAllShapes()
{
	std::ranges::for_each(shapes, [](ShapeWidget* s){ clearShape(s);});
	shapes.clear();
}

void ControlWidget::saveTo(QDataStream& stream)
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

		std::ranges::transform(sw->getRelations(), std::back_inserter(info.relationIds), [shapesV, sw](RelationWidget* rw)
		{
			const auto relateShape = rw->getFirst() == sw ? rw->getSecond() : rw->getFirst();
			return std::ranges::find(shapesV, relateShape) - shapesV.begin();
		});

		res.emplace_back(info);
	}

	stream << res;
}

void ControlWidget::loadFrom(QDataStream& stream)
{
	activeShape = nullptr;
	activeRelation = nullptr;
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
