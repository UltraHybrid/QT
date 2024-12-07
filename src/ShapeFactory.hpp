#pragma once
#include "ShapeType.hpp"


class ShapeWidget;

class ShapeFactory {
public:
	static ShapeWidget* createShape(ShapeType type);
};
