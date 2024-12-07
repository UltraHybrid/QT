#include "ShapeFactory.hpp"

#include "EllipseWidget.hpp"
#include "RectangleWidget.hpp"
#include "TriangleWidget.hpp"

ShapeWidget* ShapeFactory::createShape(ShapeType type)
{
	switch (type)
	{
		case ShapeType::TRIANGLE:
			return new TriangleWidget;
		case ShapeType::ELLIPSE:
			return new EllipseWidget;
		case ShapeType::RECTANGLE:
			return new RectangleWidget;
	}


}
