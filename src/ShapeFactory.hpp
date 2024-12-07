#pragma once
#include <qpoint.h>

#include "ShapeType.hpp"


class QWidget;
class ShapeWidget;

class ShapeFactory {
public:
	static ShapeWidget* createShape(QWidget* parent, ShapeType type, QPoint pos, QPoint size);
};
