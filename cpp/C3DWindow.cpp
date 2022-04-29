#include "C3DWindow.h"
#include "SetDialog.h"
#include<qscrollarea.h>
#include<D:\qt\5.14.2\msvc2017\include\QtWidgets\QHBoxLayout>
#include<qaction.h>
#include<qtoolbar.h>
#include<qstatusbar.h>
C3DWindow::C3DWindow()
{
	this->setWindowTitle("3DWindow");
	m_SrollArea = new QScrollArea(this);
	QToolBar* m_tool_bar = new QToolBar();
	addToolBar(Qt::TopToolBarArea, m_tool_bar);


	QAction* setValue = new QAction(QIcon("earth.bmp"), tr("Set rotate speed"), this);
	setValue->setStatusTip(tr("Change point color"));
	connect(setValue, SIGNAL(triggered()), this, SLOT(slotSetDialog()));
	m_tool_bar->addAction(setValue);


	c3dwidget = new C3DWidget();
	m_SrollArea->setWidget(c3dwidget);
	c3dwidget->setFixedSize(1270, 800);
	setCentralWidget(m_SrollArea);
	//this->setCentralWidget(c3dqglwidget);
}

void C3DWindow::slotSetDialog()
{
	SetDialog* setdiaglog = new SetDialog(&(c3dwidget->m_angle));
	setdiaglog->show();
}
C3DWindow::~C3DWindow()
{

}
