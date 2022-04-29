#pragma once
#include<qmainwindow.h>
#include<qscrollarea.h>
#include"C3DWidget.h"
class C3DWindow : public QMainWindow
{
	Q_OBJECT;
public:
	C3DWindow();
	~C3DWindow();
	
private:
	C3DWidget* c3dwidget;
	QImage* image;
	QScrollArea* m_SrollArea;

public slots:
	void slotSetDialog();
};