#pragma once

#include <QGraphicsView>
#include <QWidget>
#include <QWheelEvent>


class GraView :public QGraphicsView
{
public:
	GraView(QWidget* parent = nullptr) : QGraphicsView(parent)
	{
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏水平条
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖条
		setDragMode(QGraphicsView::ScrollHandDrag);
		setRenderHint(QPainter::Antialiasing);
		setRenderHint(QPainter::SmoothPixmapTransform);
		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		setResizeAnchor(QGraphicsView::AnchorUnderMouse);
		setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
		setAttribute(Qt::WA_DeleteOnClose);
		setWindowFlags(Qt::Tool);
	}
	~GraView();

protected:
	void wheelEvent(QWheelEvent* event) override {

		if (event->angleDelta().y() < 0) {
			// 滚轮向上，缩小图片
			scale(0.8, 0.8);
		}
		else {
			// 滚轮向下，放大图片
			scale(1.2, 1.2);
		}

	}
};