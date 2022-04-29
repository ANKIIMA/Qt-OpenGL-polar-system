#include "C3DWidget.h"
#include<QMouseEvent>
#include<QWheelEvent>
#include<math.h>
#include<Windows.h>
#include<gl/glut.h>
#include<gl/GLU.h>

C3DWidget::C3DWidget()//���캯����˳���������ߵ�
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

C3DWidget::~C3DWidget()//��������
{

}

void C3DWidget::initializeGL()//��ʼ��GL
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

void C3DWidget::resizeGL(int width, int height)//�������ڻ�����С
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLint)width, (GLint)height);//�ӿ�
	glMatrixMode(GL_PROJECTION);//ͶӰ�任
	glLoadIdentity();//���ر�׼������ϵ
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.01, 100);//͸���趨
	glMatrixMode(GL_MODELVIEW);//ģ�ͺ���ͼ�任
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f);//����������Ĳ���

}

void C3DWidget::paintGL()//��ͼ
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫΪ��ɫ�������Ȼ���ΪС���趨���
	glLoadIdentity();
	gluLookAt(0.5f, 2.0f, 1.50f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);//��������趨

	glScalef(scaleX, scaleY, scaleZ);
	glTranslatef(translationX,translationY,0);
	glRotatef(rotationX, 1, 0, 0);
	glRotatef(rotationY, 0, 1, 0);
	drawSun();

	glPushAttrib(GL_ALL_ATTRIB_BITS);//����popʹ�ã������鱣�����ջ

	glBegin(GL_LINES);
	glColor3f(0.31f, 0.78f, 0.69f);//�������
	for (int i = 0; i < m_earthOrbit.size(); i++)
	{
		glVertex3f(m_earthOrbit[i][0], m_earthOrbit[i][1], m_earthOrbit[i][2]);
	}
	glEnd();
	glPopAttrib();
	


	glPushMatrix();//������ת������
	glTranslatef(m_radiusSunEarth * cos(m_addTheta), 0.0f, m_radiusSunEarth * sin(m_addTheta));//����������ĳ������ƽ�Ƶ������λ��
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(66.3f, 0.0f, 0.0f, 1.0f);
	glRotatef(-corner, 0.0, -0.261, 0.595);
	drawEarth();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();//������ת������
	glTranslatef(m_radiusSunEarth * cos(m_addTheta) + m_radiusEarthMoon * cos(m_addAlpha),0.0f,
		+m_radiusSunEarth * sin(m_addTheta) + m_radiusEarthMoon * sin(m_addAlpha));

	//glTranslatef(-m_radiusEarthMoon*cos(m_addTheta), 0.0f, -m_radiusEarthMoon * sin(m_addTheta));//����������ĳ������ƽ�Ƶ������λ��
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(66.3f, 0.0f, 0.0f, 1.0f);
	glRotatef(-corner, 0.0, -0.261, 0.595);
	drawMoon();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void C3DWidget::drawSun()//��̫��
{
	GLUquadricObj* qobj;//����������
	qobj = gluNewQuadric();//������������
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_newSunPic.width(), m_newSunPic.height(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, m_newSunPic.bits());//ָ������

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//�������
	glEnable(GL_TEXTURE_2D);//���ö�ά����
	gluQuadricTexture(qobj, GL_TRUE);//������������������
	gluSphere(qobj, 0.2, 60, 60);//��������
	glDisable(GL_TEXTURE_2D);//�Ի��Ԫ���ж�λ��ͼ
}

void C3DWidget::drawEarth()//�����򣬲ο��ϲ���
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

void C3DWidget::timerEvent(QTimerEvent* event)//���º���
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
	update();//����paintGL�ػ�
}

void C3DWidget::wheelEvent(QWheelEvent* event)//������д
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

void C3DWidget::mouseMoveEvent(QMouseEvent* event)//δ���
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


