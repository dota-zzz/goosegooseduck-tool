#include "picbtn.h"
#include "gravw.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGuiApplication>

PicBtn::~PicBtn()
{

}

PicBtn::PicBtn(QPixmap pix_, QWidget* parent) :pix(pix_)
{
	setAttribute(Qt::WA_DeleteOnClose);
	connect(this, &QPushButton::clicked, [&]() {
		auto view = new GraView;
		auto scene = new QGraphicsScene(view);
		scene->addPixmap(pix);
		view->setScene(scene);
		auto screenRect = QGuiApplication::primaryScreen()->geometry();
		int screenWidth = screenRect.width();
		int screenHeight = screenRect.height();
		int viewwid = screenWidth * 0.8;
		int viewhei = screenHeight * 0.8;
		view->setGeometry(screenRect.x() + screenWidth * 0.1, screenRect.y() + screenHeight * 0.1, viewwid, viewhei);
		view->show();
		emit click_picbtn();
		});
}