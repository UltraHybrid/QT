#include "ShapeInfo.hpp"
#include <QDataStream>
#include <QVector>


QDataStream& operator<<(QDataStream& out, const ShapeInfo& st)
{
	out << st.type;
	out << st.pos;
	out << st.size;
	out << st.relationIds;
	return out;
}

QDataStream& operator>>(QDataStream& in, ShapeInfo& st)
{
	in >> st.type;
	in >> st.pos;
	in >> st.size;
	in >> st.relationIds;
	return in;
}