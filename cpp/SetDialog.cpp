#include"SetDialog.h"
#include<qlineedit.h>
#include<qslider.h>
#include<D:\qt\5.14.2\msvc2017\include\QtWidgets\QHBoxLayout>
#include<qdialog.h>
SetDialog::SetDialog(float* value)
{
	ptr_value = value;

	slider = new QSlider(Qt::Horizontal);
	slider->setMinimum(0);
	slider->setMaximum(100);

	int curValue = (*ptr_value) * 10000;
	lineEdit = new QLineEdit(QString("%1").arg(curValue));

	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setLineEditValue(int)));
	connect(lineEdit, SIGNAL(textEdited(QString)), this, SLOT(setSliderValue(QString)));
	slider->setValue(curValue);

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(lineEdit);
	layout->addWidget(slider);

	this->setLayout(layout);
	this->resize(300, 50);
	this->setWindowTitle("Set Rotate Speed");
}

void SetDialog::setSliderValue(QString)
{
	int value = lineEdit->text().toInt();
	(*ptr_value) = float(value) / 10000;
	slider->setValue(value);

}

void SetDialog::setLineEditValue(int)
{
	int  value = slider->value();
	(*ptr_value) = float(value) / 10000;
	QString str = QString("%1").arg(value);
	lineEdit->setText(str);
}