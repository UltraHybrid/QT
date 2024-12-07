#include <QApplication>

#include "MainWnd.hpp"


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWnd mw{};
	mw.show();
	return QApplication::exec();
}
