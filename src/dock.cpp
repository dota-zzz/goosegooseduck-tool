#include "dock.h"


Dock::~Dock()
{
	delete btn;
}

Dock::Dock(QWidget* parent)
{
	left = QPixmap("icon/leftarrow.png");
	right = QPixmap("icon/rightarrow.png");
	screenRect = QGuiApplication::primaryScreen()->geometry();
	int screenWidth = screenRect.width();
	int screenHeight = screenRect.height();
	widgetwidth = screenWidth * 0.2;
	widgetheight = screenHeight;
	flat_border = screenRect.x() + screenWidth - widgetwidth;
	hidden_border = screenRect.x() + screenRect.width() - 0.01 * widgetwidth;
	widgetY = screenRect.y() + (screenHeight - widgetheight) / 2;


	//初始设置
	setGeometry(hidden_border, widgetY, widgetwidth, widgetheight);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	mode = HIDDEN;

	btn = new QPushButton;
	btnwidth = 40;
	int btnheight = 100;
	btnY = screenRect.y() + ((screenHeight - btnheight) / 2) * 0.9;
	btn->setGeometry(hidden_border - btnwidth, btnY, btnwidth, btnheight);
	connect(btn, &QPushButton::clicked, [&]() {
		change_mode();
		});
	btn->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
	btn->setIcon(QIcon(left));
	btn->setWindowOpacity(0.8);
	btn->show();
	//设置ui
	QVBoxLayout* mainly = new QVBoxLayout;
	QHBoxLayout* hly = new QHBoxLayout;
	QPushButton* btn_ = new QPushButton;
	QPushButton* btn1_ = new QPushButton;
	btn_->setText("清空");
	btn1_->setText("退出");

	btn_->setFixedSize(100, 50);
	btn1_->setFixedSize(100, 50);
	connect(btn_, &QPushButton::clicked, [&]() {
		clear_layout(scrarea_lyt);
		});
	connect(btn1_, &QPushButton::clicked, [&]() {
		close();
		delete btn;
		emit squit();
		});
	hly->addStretch(1);
	hly->addWidget(btn_);
	hly->addWidget(btn1_);
	mainly->addWidget(create_scrollarea());
	mainly->addLayout(hly);
	setLayout(mainly);
}

void Dock::change_mode()
{
	switch (mode)
	{
	case Dock::HIDDEN:
	{
		smooth_move(this, QPoint(hidden_border, 0), QPoint(flat_border, 0), 300);
		smooth_move(btn, QPoint(hidden_border - btnwidth, btnY), QPoint(flat_border - btnwidth, btnY), 300);
		mode = FLAT;
		btn->setIcon(QIcon(right));
		break;
	}
	case Dock::FLAT:
	{
		smooth_move(this, QPoint(flat_border, 0), QPoint(hidden_border, 0), 300);
		smooth_move(btn, QPoint(flat_border - btnwidth, btnY), QPoint(hidden_border - btnwidth, btnY), 300);
		mode = HIDDEN;
		btn->setIcon(QIcon(left));
		break;
	}
	default:
		break;
	}
}

QScrollArea* Dock::create_scrollarea()
{
	QScrollArea* scrollArea = new QScrollArea;
	QWidget* widget = new QWidget;
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(widget);
	scrarea_lyt = new QVBoxLayout(widget);
	widget->setLayout(scrarea_lyt);
	scrarea_lyt->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

	QTimer* timer = new QTimer(this);
	timer->callOnTimeout([&]() {
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState('D') & 0x8000)
		{
			while (GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState('D') & 0x8000) {
				Sleep(1);
			}
			auto pix = capture_window();
			PicBtn* newButton = new PicBtn(pix);
			newButton->setMinimumSize(QSize(200, 200));
			newButton->setMaximumSize(QSize(200, 200));
			newButton->setIconSize(QSize(200, 200));
			newButton->setIcon(QIcon(pix)); // 设置QPushButton的背景图片
			if (scrarea_lyt) {
				auto hlist = make_widgetlist<QVBoxLayout>(new QLabel(get_time()), newButton);
				scrarea_lyt->addWidget(hlist);
			}
			connect(newButton, &PicBtn::click_picbtn, [&]() {
				change_mode();
				});
		}
		});
	timer->start(1);

	return scrollArea;
}