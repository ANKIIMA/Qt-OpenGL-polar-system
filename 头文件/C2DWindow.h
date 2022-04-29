#pragma once
#include<qmainwindow.h>
#include<qscrollarea.h>
#include"C2DWidget.h"
class C2DWindow : public QMainWindow
{
	Q_OBJECT
public:
	C2DWindow();
	~C2DWindow();

private:
	C2DWidget* c2dwidget;
	QImage* image;
	QScrollArea* m_SrollArea;

public slots:
	void slotSetDialog();
};