#ifndef FRAMESAREA_H
#define FRAMESAREA_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

class framesarea : public QWidget
{
private:
    QVBoxLayout *outlook = nullptr;
    QVector<QLabel*> *labelList = new QVector<QLabel*>();
    int frameIndex;
public:
    explicit framesarea(QWidget *parent = nullptr);
    void updateFrames(QVector<QImage> *frames);
//    void setFrameIndex(int index);
};

#endif // FRAMESAREA_H
