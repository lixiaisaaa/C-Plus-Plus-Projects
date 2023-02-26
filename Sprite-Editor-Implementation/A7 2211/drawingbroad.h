/*
 * CS 3505:A7 sprite editor implementation *
 * This is the header file for our drawing broad, created signals
 * and slots to manipulate drawingbroad’s property.
 * @author: Robert Li, Wenlin Li, Qingwen Bao, Qimeng Chao, Julian Zhou
 * @version: 04/01/22 1.0 implemented the method
 * @version: 04/04/22 1.1 fixed bug and added extra feature.
 */

#ifndef DRAWINGBROAD_H
#define DRAWINGBROAD_H

#include <QWidget>
#include <QObject>
#include <QImage>
#include <QtGlobal>
#include "framesarea.h"
#include "sizedialog.h"

class drawingbroad : public QWidget
{
    Q_OBJECT
public:
    explicit drawingbroad(QWidget *parent = nullptr);
    QColor getColor() const { return penColor; }
    int getPenWidth() const { return penWidth; }
    int broadSize;

    void pushFrame(int frameIndex);
    void setImage(QImage newImage);
    void init(framesarea *_framesArea);
    QImage nextFrames(framesarea *frame);
    QImage lastFrame(framesarea *frame);

private:
     //void paintEvent(QPaintEvent *);
     void drawLineTo(const QPoint &endPosition);
     void drawRectangle(const QPoint &endPosition);
     void drawEllipse(const QPoint &endPosition);
     void resizeImage(QImage *image, const QSize &newSize);
     void setBroad(int size);
     void fillBackgroundColor();
     bool isPressed;
     bool isDrawing;
     QImage image;
     QPoint startposition;
     QPoint position;
     QColor penColor;
     int penWidth = 1;
     double broadSizeOffset;
     int drawingPattern;
     QVector<QImage> frames;
     int currentPreview;
     qreal scaleFactor;
     QImage tempImage;
     int currentFrame;
     int framerate;
     framesarea *framesArea;


protected:
     void mousePressEvent(QMouseEvent *event) override;
     void mouseMoveEvent(QMouseEvent *event) override;
     void mouseReleaseEvent(QMouseEvent *event) override;
     void paintEvent(QPaintEvent *event) override;
signals:

public slots:
    void setDrawingPattern(int i);
    void setPenColor(const QColor &newColor);
    void clearImage();
    void setPenWidth(int newWidth);
    bool openFile(const QString);

    //
    void addFrame();
    void addFirstFrame();
    void deleteFrame();
    int getFrameIndex();
    QVector<QImage> getFrames();
    void setFrames(QVector<QImage> f);
    void setBroadSize(int size);
    void clearCurrentFrame();
    void updateFrameArea(framesarea *frame);

};

#endif // DRAWINGBROAD_H
