#pragma once
//#include<qopenglwidget.h>
#include<D:\qt\5.14.2\msvc2017\include\QtWidgets\QOpenGLWidget>
#include<D:\qt\5.14.2\msvc2017\include\QtOpenGL\QtOpenGL>
#include<D:\qt\5.14.2\msvc2017\include\QtCore\QTimerEvent>

class C3DWidget : public QOpenGLWidget
{
	Q_OBJECT;
public:
	C3DWidget();
	~C3DWidget();
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void timerEvent(QTimerEvent* event);

	void drawEarth();
	void drawSun();
	void drawMoon();
public:
	float m_angle;

private:
	GLfloat m_radiusSunEarth;
	GLfloat m_radiusEarthMoon;
	GLfloat m_addTheta;
	GLfloat corner;
	QImage m_sunpic;
	QImage m_newSunPic;
	QImage m_newEarthPic;
	QImage m_newMoonPic;
	QVector<QVector<float>> m_earthOrbit;
	qreal scaleX,scaleY,scaleZ;
	QPoint lastpos;
	qreal translationX;
	qreal translationY;
	qreal rotationX;
	qreal rotationY;
	qreal m_addAlpha;
protected:
	void wheelEvent(QWheelEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

};

