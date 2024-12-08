#include "AbstractController.hpp"

#include "RelationWidget.hpp"

AbstractController::AbstractController(ControlWidget* widget) : widget(widget)
{
}

void AbstractController::flush()
{
	if (activeRelation)
	{
		activeRelation->close();
		activeRelation = nullptr;
		activeShape = nullptr;
	}
	if (activeShape)
	{
		activeShape->close();
		activeShape = nullptr;
	}
}
