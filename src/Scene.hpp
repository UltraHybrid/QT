#pragma once
#include <qgraphicsscene.h>


class TriangleWidget;

class Scene : public QGraphicsScene {
	Q_OBJECT
private:
	QGraphicsProxyWidget* createdShape{nullptr};
	std::vector<QGraphicsProxyWidget*> shapes;
	QGraphicsProxyWidget* getSelectShape(const QPointF& point);

public:
	explicit Scene(QObject* parent);

	void resetCreatedShape();


protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
};
