#pragma once
#include<qdialog.h>
#include<qlineedit.h>
#include<qslider.h>
#include<qdialog.h>
class SetDialog : public QDialog
{
	Q_OBJECT
public:
	SetDialog(float* value);
signals:
public slots:
	void setLineEditValue(int);
	void setSliderValue(QString);
private:
	QLineEdit* lineEdit;
	QSlider* slider;
	float* ptr_value;
};