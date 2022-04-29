#include"C2DWindow.h"
#include"SetDialog.h"
#include<qscrollarea.h>
#include<D:\qt\5.14.2\msvc2017\include\QtWidgets\QHBoxLayout>
#include<qaction.h>
#include<qtoolbar.h>
#include<qstatusbar.h>
C2DWindow::C2DWindow()
{
	this->setWindowTitle("SunEarthMoon");
	m_SrollArea = new QScrollArea(this);
	QToolBar* m_tool_bar = new QToolBar();
	addToolBar(Qt::TopToolBarArea, m_tool_bar);

	
	QAction* setValue = new QAction(QIcon("earth.bmp"), tr("Set rotate speed"), this);
	setValue->setStatusTip(tr("Change point color"));
	connect(setValue, SIGNAL(triggered()), this, SLOT(slotSetDialog()));
	m_tool_bar->addAction(setValue);

	//this->setGeometry(400, 100, 1000, 800);

	c2dwidget = new C2DWidget();
	m_SrollArea->setWidget(c2dwidget);
	c2dwidget->setFixedSize(1270, 800);
	setCentralWidget(m_SrollArea);
	//this->setCentralWidget(c2dwidget);
	 

}
void C2DWindow::slotSetDialog()
{
	SetDialog* setdiaglog = new SetDialog(&(c2dwidget->m_angle));
	setdiaglog->show();
}
C2DWindow::~C2DWindow()
{

}