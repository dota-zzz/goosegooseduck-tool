#pragma once

#include <QPushButton>
#include <QPixmap>
#include <QLabel>

class PicBtn :public QPushButton
{
	Q_OBJECT

signals:
	void click_picbtn();

public:
	PicBtn(QPixmap pix_, QWidget* parent = nullptr);
	~PicBtn();
private:
	QPixmap pix;
};