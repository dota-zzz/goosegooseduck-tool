#pragma once
#include <QLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPropertyAnimation>
#include <time.h>
#include <sstream>
#include <QString>
#include <QScreen>
#include <QGuiApplication>
#include <QWindow>
#include <iostream>
#include <QPixmap>
#include <windows.h>

static void clear_layout(QLayout* layout) {
	while (QLayoutItem* item = layout->takeAt(0)) {
		if (QWidget* widget = item->widget())
			widget->deleteLater();

		if (QLayout* childLayout = item->layout())
			clear_layout(childLayout);

		if (QSpacerItem* spaerItem = item->spacerItem())
			layout->removeItem(spaerItem);

		delete item;
	}
}

template <typename LayoutType, typename... Args> static QWidget* make_widgetlist(Args... args) {
	auto layout_ = new LayoutType;
	(layout_->addWidget(args), ...);
	layout_->setContentsMargins(0, 0, 0, 0);
	auto widget_ = new QWidget;
	widget_->setLayout(layout_);
	return widget_;
}

template <typename T> static void set_fixed_size(T* widget, int x, int y) {
	widget->setMinimumSize(QSize(x, y));
	widget->setMaximumSize(QSize(x, y));
}


template <typename T>
static void smooth_move(T* widget, QPoint p1, QPoint p2, int time)
{
	QPropertyAnimation* animation = new QPropertyAnimation(widget, "pos");
	animation->setDuration(time); // 动画持续时间（毫秒）
	animation->setStartValue(p1);
	animation->setEndValue(p2);
	animation->start(QAbstractAnimation::DeleteWhenStopped);
}

static QString get_time()
{
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	std::stringstream ss;
	ss << tm_t->tm_hour << ":" << tm_t->tm_min << ":" << tm_t->tm_sec;
	QString handle_str(QString::fromStdString(ss.str()));
	return handle_str;
}

static QPixmap capture_window()
{
	// 获取屏幕对象
	QScreen* screen = QGuiApplication::primaryScreen();
	QPixmap screenshot = QGuiApplication::primaryScreen()->grabWindow(0);
	return screenshot;
}