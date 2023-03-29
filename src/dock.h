#pragma once

#include <QWidget>
#include <QGuiApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QEvent>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <thread>
#include <QTimer>
#include "basic.h"
#include "picbtn.h"

#include <iostream>
#include <windows.h>

class Dock :public QWidget
{
	Q_OBJECT

signals:
	void squit();

public:
	Dock(QWidget* parent = nullptr);
	~Dock();
private:
	int widgetwidth;
	int widgetheight;
	int widgetY;
	int btnY;
	int btnwidth;
	QPushButton* btn;
	QRect screenRect;
	enum Mode {
		HIDDEN,
		FLAT
	};
	Mode mode;
	int hidden_border;
	int flat_border;
	QVBoxLayout* scrarea_lyt = nullptr;
	QPixmap left;
	QPixmap right;

	void change_mode();
	QScrollArea* create_scrollarea();
};