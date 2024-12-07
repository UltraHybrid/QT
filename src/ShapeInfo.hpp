#pragma once
#include <QVector>
#include <qpoint.h>


struct ShapeInfo
{
	qint32 type;
	QPoint pos;
	QPoint size;
	QVector<qint32> relationIds{};
};

QDataStream& operator<<(QDataStream& out, const ShapeInfo& st);

QDataStream& operator>>(QDataStream& in, ShapeInfo& st);