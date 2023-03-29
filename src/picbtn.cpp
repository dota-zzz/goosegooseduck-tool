#include "picbtn.h"

PicBtn::~PicBtn()
{

}

PicBtn::PicBtn(QPixmap pix_, QWidget* parent) :pix(pix_)
{
	setAttribute(Qt::WA_DeleteOnClose);
	connect(this, &QPushButton::clicked, [&]() {
		QLabel* label = new QLabel;
		label->setPixmap(pix);
		label->setFixedSize(pix.size());
		label->show();
		label->setAttribute(Qt::WA_DeleteOnClose);
		emit click_picbtn();
		});
}