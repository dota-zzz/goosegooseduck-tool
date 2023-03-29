#include "textdock.h"

TextDock::~TextDock()
{
	delete btn;
}

TextDock::TextDock(Dock* dock, QWidget* parent) {
	up = QPixmap("icon/uparrow.png");
	down = QPixmap("icon/downarrow.png");
	auto screenRect = QGuiApplication::primaryScreen()->geometry();
	int screenWidth = screenRect.width();
	int screenHeight = screenRect.height();
	int widgetwidth = screenWidth * 0.5;
	int widgetheight = screenHeight * 0.5;
	widgetX = screenRect.x() + (screenWidth - widgetwidth) / 2;
	flat_border = screenRect.y() + screenHeight - widgetheight;
	hidden_border = screenRect.y() + screenRect.height() - 0.01 * widgetheight;
	mode = HIDDEN;
	setGeometry(widgetX, hidden_border, widgetwidth, widgetheight);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);


	QVBoxLayout* vlyt = new QVBoxLayout;
	QTextEdit* tedit = new QTextEdit;
	vlyt->addWidget(tedit);
	vlyt->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	setLayout(vlyt);
	btn = new QPushButton;
	btnWidth = 100;
	btnHeight = 40;
	btnX = screenRect.x() + (screenWidth - btnWidth) / 2;
	btn->setGeometry(btnX, hidden_border - btnHeight, btnWidth, btnHeight);
	btn->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	btn->setIcon(QIcon(up));
	btn->setWindowOpacity(0.8);
	btn->show();
	connect(btn, &QPushButton::clicked, [&]() {
		change_mode();
		});
	connect(dock, &Dock::squit, [&]() {
		close();
		delete btn; });
}

void TextDock::change_mode()
{
	switch (mode)
	{
	case TextDock::HIDDEN:
	{
		smooth_move(this, QPoint(widgetX, hidden_border), QPoint(widgetX, flat_border), 300);
		smooth_move(btn, QPoint(btnX, hidden_border - btnHeight), QPoint(btnX, flat_border - btnHeight), 300);
		mode = FLAT;
		btn->setIcon(QIcon(down));
		break;
	}
	case TextDock::FLAT:
	{
		smooth_move(this, QPoint(widgetX, flat_border), QPoint(widgetX, hidden_border), 300);
		smooth_move(btn, QPoint(btnX, flat_border - btnHeight), QPoint(btnX, hidden_border - btnHeight), 300);
		mode = HIDDEN;
		btn->setIcon(QIcon(up));
		break;
	}
	default:
		break;
	}
}