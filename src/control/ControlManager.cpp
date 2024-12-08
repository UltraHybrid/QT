#include "ControlManager.hpp"

ControlManager::ControlManager(ControlWidget* widget)
{
}

void ControlManager::addController(ControlWidget::Regime regime, std::shared_ptr<AbstractController> controller)
{
	controllerMap.emplace(regime, controller);
}

void ControlManager::mouseMoveEvent(const ControlWidget::Regime regime, QMouseEvent* event) const
{
	if (!canPerform(regime)) return;
	controllerMap.at(regime)->mouseMoveEvent(event);
}

void ControlManager::mousePressEvent(const ControlWidget::Regime regime, QMouseEvent* event) const
{
	if (!canPerform(regime)) return;
	controllerMap.at(regime)->mousePressEvent(event);
}

void ControlManager::mouseReleaseEvent(const ControlWidget::Regime regime, QMouseEvent* event) const
{
	if (!canPerform(regime)) return;
	controllerMap.at(regime)->mouseReleaseEvent(event);
}

void ControlManager::keyPressEvent(const ControlWidget::Regime regime, QKeyEvent* event) const
{
	if (!canPerform(regime)) return;
	controllerMap.at(regime)->keyPressEvent(event);
}

void ControlManager::flush()
{
	std::ranges::for_each(controllerMap, [](const auto& e){e.second->flush();});
}

bool ControlManager::canPerform(ControlWidget::Regime regime) const
{

	return regime != ControlWidget::Regime::NONE && controllerMap.contains(regime);
}

void ControlManager::switchController()
{

}
