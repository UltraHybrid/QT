#include "ShapeFactory.hpp"

#include "EllipseWidget.hpp"
#include "RectangleWidget.hpp"
#include "TriangleWidget.hpp"


ShapeWidget* ShapeFactory::createShape(QWidget* parent, const ShapeType type, QPoint pos, QPoint size)
{
	ShapeWidget* res{nullptr};
	switch (type)
	{
		case ShapeType::TRIANGLE:
			res = new TriangleWidget;
		break;
		case ShapeType::ELLIPSE:
			res = new EllipseWidget;
		break;
		case ShapeType::RECTANGLE:
			res = new RectangleWidget;
		break;
	}

	if (!res)
	{
		throw std::exception{"Undefined shape type"};
	}

	res->setParent(parent);
	res->resize(size.x(), size.y());
	res->move(pos);

	return res;
}
