#include "ControlManager.hpp"

ControlManager::ControlManager(PaintPanel* widget)
{
}

void ControlManager::addController(PaintPanel::Regime regime, std::shared_ptr<AbstractController> controller)
{
	controllerMap.emplace(regime, controller);
}

void ControlManager::mouseMoveEvent(const PaintPanel::Regime regime, QMouseEvent* event) const
{
	if (!canPerform(regime)) return;
	controllerMap.at(regime)->mouseMoveEvent(event);
}

void ControlManager::mousePressEvent(const PaintPanel::Regime regime, QMouseEvent* event) const
{
	if (!canPerform(regime)) return;
	controllerMap.at(regime)->mousePressEvent(event);
}

void ControlManager::mouseReleaseEvent(const PaintPanel::Regime regime, QMouseEvent* event) const
{
	if (!canPerform(regime)) return;
	controllerMap.at(regime)->mouseReleaseEvent(event);
}

void ControlManager::keyPressEvent(const PaintPanel::Regime regime, QKeyEvent* event) const
{
	if (!canPerform(regime)) return;
	controllerMap.at(regime)->keyPressEvent(event);
}

void ControlManager::flush()
{
	std::ranges::for_each(controllerMap, [](const auto& e){e.second->flush();});
}

bool ControlManager::canPerform(PaintPanel::Regime regime) const
{
	return regime != PaintPanel::Regime::NONE && controllerMap.contains(regime);
}
