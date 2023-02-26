#include "previewwindow.h"
#include "ui_previewwindow.h"
#include "QTimer"
#include <iostream>

PreviewWindow::PreviewWindow(QVector<QImage> frames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviewWindow)
{
    ui->setupUi(this);
    ui->label->setScaledContents(true);
    ui->spinBox->setRange(0, 30);
    ui->spinBox->setSingleStep(1);
    ui->slider->setTickInterval(5);
    ui->slider->setRange(0, 30);
    this->frames = frames;
    currentFrame = 0;
    showFrame(frames.at(currentFrame));
    frametimer = new QTimer(this);
    connect(frametimer, SIGNAL(timeout()), this, SLOT(changeFrame()));
    frametimer->start(0);
    on_spinBox_valueChanged(0);
    on_slider_valueChanged(0);
    ui->slider->setValue(0);
    ui->spinBox->setValue(0);
    this->show();
}

PreviewWindow::~PreviewWindow()
{
    delete ui;
}

void PreviewWindow::on_closeButton_pressed()
{
    this->close();
}

void PreviewWindow::showFrame(QImage frame)
{
    ui->label->setPixmap(QPixmap::fromImage(frame).scaled(ui->label->height(), ui->label->width(), Qt::IgnoreAspectRatio));
    ui->label->show();
}

void PreviewWindow::changeFrame()
{
    currentFrame = (currentFrame+1) % frames.size();
    showFrame(frames.at(currentFrame));

}

void PreviewWindow::on_spinBox_valueChanged(int value)
{
    if (value == 0)
        frametimer->stop();
    else if (frames.size() > 0){
        if (!frametimer->isActive()){
            frametimer->start();
        }
        frametimer->setInterval(1000/value);
    }
    ui->slider->setValue(value);
}

void PreviewWindow::on_slider_valueChanged(int value)
{
    if (value == 0)
        frametimer->stop();
    else if (frames.size() > 0){
        if (!frametimer->isActive()){
            frametimer->start();
        }
        frametimer->setInterval(1000/value);
    }
    ui->spinBox->setValue(value);
}


void PreviewWindow::on_rSize_clicked()
{
    showFrame(frames.at(currentFrame));
    ui->label->setFixedHeight(frames.at(currentFrame).width());
    ui->label->setFixedWidth(frames.at(currentFrame).width());
}


void PreviewWindow::on_pwSize_clicked()
{
    showFrame(frames.at(currentFrame));
    ui->label->setFixedHeight(200);
    ui->label->setFixedWidth(200);
}

