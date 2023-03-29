#include "basic.h"
#include "dock.h"
#include "textdock.h"
#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Dock* dock = new Dock;
	TextDock* tdock = new TextDock(dock);
	dock->show();
	tdock->show();
	return a.exec();
}