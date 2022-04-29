#include "C3DWidget.h"
#include<QMouseEvent>
#include<QWheelEvent>
#include<math.h>
#include<Windows.h>
#include<gl/glut.h>
#include<gl/GLU.h>

C3DWidget::C3DWidget()//构造函数，顺带存入轨道线点
{
	corner = 0;
	m_addTheta = 0.0;
	m_addAlpha = 2 * m_addTheta;
	startTimer(5);
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	m_radiusSunEarth = 0.5f;
	m_radiusEarthMoon = 0.15f;
	translationX = translationY = 0;
	m_angle = 0.02f;
	rotationX = 0;
	rotationY = 0;

	float addTheta = 0.0f;
	while (addTheta < 360)
	{
		QVector<float>tmp;
		tmp.push_back(m_radiusSunEarth * cos(addTheta));
		tmp.push_back(0.0f);
		tmp.push_back(m_radiusSunEarth * sin(addTheta));
		m_earthOrbit.push_back(tmp);
		tmp.clear();
		addTheta += 0.02f;
	}
}

C3DWidget::~C3DWidget()//析构函数
{

}

void C3DWidget::initializeGL()//初始化GL
{
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	
	//m_newSunPic.load(":/new/prefix1/sun.bmp");
	m_newSunPic.load("sun.bmp");
	m_newSunPic = m_newSunPic.convertToFormat(QImage::Format_RGBA8888, Qt::AutoColor);
	
	m_newEarthPic.load("earth.bmp");
	m_newEarthPic = m_newEarthPic.convertToFormat(QImage::Format_RGBA8888, Qt::AutoColor);

	m_newMoonPic.load("moon.bmp");
	m_newMoonPic = m_newMoonPic.convertToFormat(QImage::Format_RGBA8888, Qt::AutoColor);
	//m_newSunPic = QGLWidget::convertToGLFormat(m_sunpic);
}

void C3DWidget::resizeGL(int width, int height)//调整窗口画布大小
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLint)width, (GLint)height);//视口
	glMatrixMode(GL_PROJECTION);//投影变换
	glLoadIdentity();//加载标准化坐标系
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.01, 100);//透视设定
	glMatrixMode(GL_MODELVIEW);//模型和视图变换
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f);//设置摄像机的参数

}

void C3DWidget::paintGL()//画图
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色为黑色，清除深度缓存为小于设定深度
	glLoadIdentity();
	gluLookAt(0.5f, 2.0f, 1.50f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);//总摄像机设定

	glScalef(scaleX, scaleY, scaleZ);
	glTranslatef(translationX,translationY,0);
	glRotatef(rotationX, 1, 0, 0);
	glRotatef(rotationY, 0, 1, 0);
	drawSun();

	glPushAttrib(GL_ALL_ATTRIB_BITS);//搭配pop使用，属性组保存进堆栈

	glBegin(GL_LINES);
	glColor3f(0.31f, 0.78f, 0.69f);//画出轨道
	for (int i = 0; i < m_earthOrbit.size(); i++)
	{
		glVertex3f(m_earthOrbit[i][0], m_earthOrbit[i][1], m_earthOrbit[i][2]);
	}
	glEnd();
	glPopAttrib();
	


	glPushMatrix();//地球自转并画出
	glTranslatef(m_radiusSunEarth * cos(m_addTheta), 0.0f, m_radiusSunEarth * sin(m_addTheta));//将坐标轴向某个方向平移到地球的位置
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(66.3f, 0.0f, 0.0f, 1.0f);
	glRotatef(-corner, 0.0, -0.261, 0.595);
	drawEarth();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();//月球自转并画出
	glTranslatef(m_radiusSunEarth * cos(m_addTheta) + m_radiusEarthMoon * cos(m_addAlpha),0.0f,
		+m_radiusSunEarth * sin(m_addTheta) + m_radiusEarthMoon * sin(m_addAlpha));

	//glTranslatef(-m_radiusEarthMoon*cos(m_addTheta), 0.0f, -m_radiusEarthMoon * sin(m_addTheta));//将坐标轴向某个方向平移到地球的位置
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(66.3f, 0.0f, 0.0f, 1.0f);
	glRotatef(-corner, 0.0, -0.261, 0.595);
	drawMoon();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void C3DWidget::drawSun()//画太阳
{
	GLUquadricObj* qobj;//创建立体球
	qobj = gluNewQuadric();//创建二次曲面
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_newSunPic.width(), m_newSunPic.height(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, m_newSunPic.bits());//指定纹理

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//纹理过滤
	glEnable(GL_TEXTURE_2D);//启用二维纹理
	gluQuadricTexture(qobj, GL_TRUE);//对物体生成纹理坐标
	gluSphere(qobj, 0.2, 60, 60);//画出球体
	glDisable(GL_TEXTURE_2D);//对活动单元进行二位贴图
}

void C3DWidget::drawEarth()//画地球，参考上部分
{
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_newEarthPic.width(), m_newEarthPic.height(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, m_newEarthPic.bits());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(qobj, GL_TRUE);
	gluSphere(qobj, 0.08, 60, 60);
	glDisable(GL_TEXTURE_2D);
}

void C3DWidget::drawMoon()
{
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_newMoonPic.width(), m_newMoonPic.height(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, m_newMoonPic.bits());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(qobj, GL_TRUE);
	gluSphere(qobj, 0.03, 60, 60);
	glDisable(GL_TEXTURE_2D);
}

void C3DWidget::timerEvent(QTimerEvent* event)//更新函数
{
	m_addTheta += m_angle;
	m_addAlpha += m_angle*2;
	corner = m_addTheta * 360;
	if (m_addTheta > 360 )
	{
		m_addTheta -= 360;
	}
	if (m_addTheta > 360)
	{
		m_addTheta -= 360;
	}
	update();//触发paintGL重绘
}

void C3DWidget::wheelEvent(QWheelEvent* event)//缩放重写
{
	if (event->delta() > 0)
	{
		scaleX += 0.1;
		scaleY += 0.1;
		scaleZ += 0.1;
	}
	else
	{
		if (scaleX > 0.2 )
		{
			scaleX -= 0.1;
			scaleY -= 0.1;
			scaleZ -= 0.1;
		}
	}
	event->accept();
	update();
}

void C3DWidget::mouseMoveEvent(QMouseEvent* event)//未完成
{
	int dx = (event->x() - lastpos.x());
	int dy = (event->y() - lastpos.y());

	if (event->buttons() & Qt::LeftButton)
	{
		if (QApplication::keyboardModifiers() == Qt::ControlModifier)
		{
			translationX += dx * 0.002;
			translationY += dy * 0.002;
			update();
		}
		else
		{
			rotationX += dx;
			rotationY += dy;
		}
	}
	lastpos = event->pos();
}


