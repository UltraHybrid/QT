#include "Scene.hpp"

#include <iostream>

#include "QGraphicsSceneEvent"
#include "TriangleWidget.hpp"
#include "QGraphicsProxyWidget"

QGraphicsProxyWidget* Scene::getSelectShape(const QPointF& point)
{
	auto fi = focusItem();
	auto pred = [&point](QGraphicsProxyWidget* s)
	{
		return s->contains(point - s->pos());
	};
	const auto shape = std::ranges::find_if(shapes, pred);
	if (shape != shapes.end())
	{
		return *shape;
	}
	return nullptr;
}

Scene::Scene(QObject* parent) : QGraphicsScene(parent)
{
	setBackgroundBrush(QColor(10, 100, 10));
}

void Scene::resetCreatedShape()
{
	if (createdShape)
	{
		createdShape->close();
		createdShape = nullptr;
	}
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsScene::mouseMoveEvent(event);
	const auto pos = event->scenePos();
	if (createdShape)
	{
		auto w = pos.x() - createdShape->pos().x();
		auto h = pos.y() - createdShape->pos().y();
		createdShape->resize(w, h);
	}
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsScene::mousePressEvent(event);
	if (!createdShape && event->button() == Qt::LeftButton)
	{
		const auto pos = event->scenePos();
		// const auto widget = new TriangleWidget{};
		widget->move(pos.x(), pos.y());
		createdShape = addWidget(widget);
		createdShape->resize(1, 1);
	}
	else if (event->button() == Qt::RightButton)
	{
		resetCreatedShape();
	}

	auto selectShape = getSelectShape(event->scenePos());
	if (selectShape)
	{
		std::cout << "найдена фигура" << std::endl;
	}
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsScene::mouseReleaseEvent(event);
	if (createdShape)
	{
		const auto pos = event->scenePos();
		auto psdfos = createdShape->pos();
		const auto w = pos.x() - createdShape->pos().x();
		const auto h = pos.y() - createdShape->pos().y();
		auto iio = createdShape->rect();
		if (w > 0 && h > 0)
		{
			shapes.emplace_back(createdShape);
			createdShape = nullptr;
		}
		else
		{
			resetCreatedShape();
		}

	}
}

void Scene::keyPressEvent(QKeyEvent* event)
{
	QGraphicsScene::keyPressEvent(event);
	if (event->key() == Qt::Key_Escape)
	{
		resetCreatedShape();
	}
}
