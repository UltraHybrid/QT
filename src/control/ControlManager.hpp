#pragma once
#include <unordered_map>

#include "AbstractController.hpp"
#include "PaintPanel.hpp"


class PaintPanel;

class ControlManager {
public:
	explicit ControlManager(PaintPanel* widget);

	void addController(PaintPanel::Regime regime, std::shared_ptr<AbstractController> controller);

	void mouseMoveEvent(PaintPanel::Regime regime, QMouseEvent* event) const;
	void mousePressEvent(PaintPanel::Regime regime, QMouseEvent* event) const;
	void mouseReleaseEvent(PaintPanel::Regime regime, QMouseEvent* event) const;
	void keyPressEvent(PaintPanel::Regime regime, QKeyEvent* event) const;

	void flush();

private:
	std::unordered_map<PaintPanel::Regime, std::shared_ptr<AbstractController>> controllerMap;

	[[nodiscard]] bool canPerform(PaintPanel::Regime regime) const;
};
