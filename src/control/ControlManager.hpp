#pragma once
#include <unordered_map>

#include "AbstractController.hpp"
#include "ControlWidget.hpp"


class ControlWidget;

class ControlManager {
public:
	explicit ControlManager(ControlWidget* widget);

	void addController(ControlWidget::Regime regime, std::shared_ptr<AbstractController> controller);

	void mouseMoveEvent(ControlWidget::Regime regime, QMouseEvent* event) const;
	void mousePressEvent(ControlWidget::Regime regime, QMouseEvent* event) const;
	void mouseReleaseEvent(ControlWidget::Regime regime, QMouseEvent* event) const;
	void keyPressEvent(ControlWidget::Regime regime, QKeyEvent* event) const;

	void flush();

private:
	std::unordered_map<ControlWidget::Regime, std::shared_ptr<AbstractController>> controllerMap;

	[[nodiscard]] bool canPerform(ControlWidget::Regime regime) const;

	void switchController();
};
