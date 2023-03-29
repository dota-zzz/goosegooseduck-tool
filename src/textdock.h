#pragma once

#include "basic.h"
#include "dock.h"
#include <QWidget>
#include <QGuiApplication>
#include <QScreen>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QPixmap>

class TextDock :public QWidget
{
	Q_OBJECT

public:
	TextDock(Dock* dock, QWidget* parent = nullptr);
	~TextDock();

private:
	int hidden_border;
	int flat_border;
	int widgetX;
	int btnX;
	int btnWidth;
	int btnHeight;
	QPixmap up;
	QPixmap down;
	QPushButton* btn;
	enum Mode {
		HIDDEN,
		FLAT
	};
	Mode mode;
	void change_mode();
};