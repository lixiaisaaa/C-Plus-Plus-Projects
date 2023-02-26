#include "framesarea.h"
#include <QScrollArea>
#include <QtGui>
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QVector>


//initialization the frame area.
framesarea::framesarea(QWidget *parent) : QWidget(parent)
{
    //

    this->setFixedSize(150, 300);
    this->setContentsMargins(0,0,0,0);
    this->setStyleSheet("background-color: black");
    //
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(150, 300);
    scrollArea->setContentsMargins(0,0,0,0);

    QWidget *widget = new QWidget();
    scrollArea->setWidget(widget);

    //
    outlook = new QVBoxLayout();
    outlook->setAlignment(Qt::AlignTop);
    outlook->setContentsMargins(0,0,0,0);

    widget->setLayout(outlook);
    this->show();
}

//update the current frame.
void framesarea::updateFrames(QVector<QImage> *frames){
    for (int i = 0; i < labelList->length(); i++){
        delete labelList->at(i);
    }
    labelList->clear();

    //Real-time update frame.
    for(int i = 0; i < frames->length(); i++) {
        QImage img = frames->at(i);
        QLabel *label = new QLabel(QString::number(i+1));
        label->setAutoFillBackground(true);
        label->setContentsMargins(0,0,0,0);
        label->setFixedSize(100, 100);
        label->setPixmap(QPixmap::fromImage(img).scaled(100, 100, Qt::IgnoreAspectRatio));
        labelList->append(label);
        outlook->addWidget(label);
    }   
}






