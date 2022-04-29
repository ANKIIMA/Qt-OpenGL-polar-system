#include"C2DWidget.h"
#include<math.h>
#include<qpainter.h>
#include<qtimer.h>
#include<qvector.h>
#include<D:\qt\5.14.2\msvc2017\include\QtGui\QWheelEvent>
#include<qapplication.h>
#include<qevent.h>
C2DWidget::C2DWidget()
{
	translationX = 0;
	translationY = 0;
	scaleX = 1;
	scaleY = 1;

	timerld = startTimer(10);
	m_angle = 0.002f;
	m_addTheta = 0;

	m_radiusSunEarth = 200;
	m_radiusEarthMoon = -100;

	background = QBrush(QColor(13, 45, 45));

	SunPen = QPen(Qt::red);
	SunPen.setWidth(1);

	EarthPen = QPen(Qt::blue);
	EarthPen.setWidth(1);

	MoonPen = QPen(Qt::white);
	MoonPen.setWidth(1);

	float addTheta = 0.0f;
	while (addTheta < 360)
	{
		QVector<float> tmp;
		tmp.push_back(m_radiusSunEarth * cos(addTheta));
		tmp.push_back(m_radiusSunEarth * sin(addTheta));
		m_earthOrbit.push_back(tmp);
		tmp.clear();
		addTheta += 0.2f;
	}
}

void C2DWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	QPixmap backGround("background.bmp");
	QPixmap Suntex("sun.bmp");
	QPixmap Earthtex("earth.bmp");
	QPixmap Moontex("moon.bmp");

	painter.begin(this);

	painter.fillRect(event->rect(), background);
	painter.drawPixmap(backGround.rect(), backGround);
	

	painter.scale(scaleX, scaleY);
	painter.translate(translationX, translationY);
	
	painter.translate(500, 350);
	painter.setPen(SunPen);
	painter.setBrush(Suntex);
	painter.drawEllipse(QPoint(0, 0), 60, 60);//画出太阳

	
	for (int i = 0; i < m_earthOrbit.size() - 1; i++)//绘制红色轨道
	{
		painter.drawLine(m_earthOrbit[i][0], m_earthOrbit[i][1],
			m_earthOrbit[i + 1][0], m_earthOrbit[i + 1][1]);
	}

	painter.translate(m_radiusSunEarth * cos(m_addTheta), -m_radiusSunEarth * sin(m_addTheta));//平移坐标系，前面x轴，后面y轴
	painter.rotate(360 * m_addTheta); //自转时旋转坐标系
	painter.setPen(EarthPen);		
	painter.setBrush(Earthtex);
	painter.drawEllipse(QPoint(0, 0), 40, 40);//画出地球

	painter.translate(m_radiusSunEarth * cos(m_addTheta) + m_radiusEarthMoon * cos(m_addTheta),
		-m_radiusSunEarth * sin(m_addTheta) - m_radiusEarthMoon * sin(m_addTheta));
	painter.rotate(360 * m_addTheta);
	painter.setPen(MoonPen);
	painter.setBrush(Moontex);
	painter.drawEllipse(QPoint(0, 0), 20, 20);//画出月球


	painter.end();
}

void C2DWidget::timerEvent(QTimerEvent* event)
{
	m_addTheta += m_angle;
	if (m_addTheta > 360)
	{
		m_addTheta -= 360;
	}
	update();
}
void C2DWidget::wheelEvent(QWheelEvent* event)
{
	if (event->delta() > 0)
	{
		scaleX += 0.1;
		scaleY += 0.1;
	}
	else
	{
		if (scaleX > 0.2 && scaleY > 0.2)
		{
			scaleX -= 0.1;
			scaleY -= 0.1;
		}
	}
	event->accept();
	update();
}

void C2DWidget::mousePressEvent(QMouseEvent* event)
{
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		if (timerld > 0)
		{
			killTimer(timerld);
			timerld = 0;
		}
		else timerld = startTimer(10);
	}
	lastPos = event->pos();
}
void C2DWidget::mouseMoveEvent(QMouseEvent* event)
{
	int dx = (event->x() - lastPos.x()) / scaleX;
	int dy = (event->y() - lastPos.y()) / scaleY;
	if (event->buttons() & Qt::LeftButton)
	{
		translationX += dx;
		translationY += dy;
		update();
	}
	lastPos = event->pos();
}

C2DWidget::~C2DWidget()
{

}



