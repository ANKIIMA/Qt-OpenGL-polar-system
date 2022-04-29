#pragma once
#include<D:\qt\5.14.2\msvc2017\include\QtGui\QPaintEvent>
#include<qpainter.h>
#include<qwidget.h>
#include<D:\qt\5.14.2\msvc2017\include\QtGui\QWheelEvent>

class C2DWidget :public QWidget
{
	Q_OBJECT
public:
	C2DWidget();
	~C2DWidget();
	float m_angle;
private:
	int translationX;
	int translationY;
	int timerld;
	QPoint lastPos;
	qreal scaleX;
	qreal scaleY;
	int m_elapsed;
	float m_radiusSunEarth;
	float m_radiusEarthMoon;

	float m_addTheta;
	QBrush background;
	QPen SunPen;
	QPen EarthPen;
	QPen MoonPen;
	QVector<QVector<float>>m_earthOrbit;
	QVector<QVector<float>>m_moonOrbit;

protected:
	void paintEvent(QPaintEvent* event) override;
	void timerEvent(QTimerEvent* event) override;
	void wheelEvent(QWheelEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
};



