/*
* CS 3505:A7 sprite editor implementation
* This is the source file for our drawing broad, created signals and slots to manipulate drawingbroad’s property.
*
* @author: Robert Li, Wenlin Li, Qingwen Bao, Qimeng Chao, Julian Zhou
* @version: 04/01/22 1.0 implemented the method * @version: 04/04/22 1.1 fixed bug and added extra feature.
*/

#include "drawingbroad.h"
#include <QtWidgets>
#include "iostream"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "previewwindow.h"
#include <QDebug>

//initialize the the drawing borad.
drawingbroad::drawingbroad(QWidget *parent)
    : QWidget{parent}
{
       broadSize = 512;
       broadSizeOffset = broadSize/512.0;
       drawingPattern = 0;
       isPressed = false;
       isDrawing = false;
       penWidth = 5;
       penColor = Qt::black;
       currentPreview = 0;
       currentFrame = 0;
       scaleFactor = 1;
       setBroad(broadSize);
}

//initialize the set size borad.
void drawingbroad::setBroad(int size){
    broadSize = size;
    broadSizeOffset = size/512.0;
    image = QImage(broadSize, broadSize, QImage::Format_RGB32);
    image.fill(qRgb(255, 255, 255));
    frames.append(image);
}

//initialize the set size borad.
void drawingbroad::setBroadSize(int bs){
    std::cout << "size received "<<bs<< std::endl;
    broadSize = bs;
    setBroad(broadSize);
}

//initialize frame area.
void drawingbroad::init(framesarea *_framesArea){
    framesArea = _framesArea;
}

//set drawing pattern(1 is pencil, 2 is earse, 3 is ellipse, 4 is rectangle, 5 is filling out the background color).
void drawingbroad::setDrawingPattern(int i){
    drawingPattern = i;
}

//open the file slot.
bool drawingbroad::openFile(const QString fileName){
        QImage externalImage;
        if (!externalImage.load(fileName)){
            return false;
        }
        QSize Size = externalImage.size().expandedTo(size());
        resizeImage(&externalImage, Size);
        pushFrame(currentFrame);
        setImage(externalImage);
        updateFrameArea(framesArea);
        update();
        return true;
}

//set up the pen color
void drawingbroad::setPenColor(const QColor &newColor)
{
    penColor = newColor;
}

// set up the pencil width.
void drawingbroad::setPenWidth(int newWidth)
{
    penWidth = newWidth;
}
//clear up the current frame.
void drawingbroad::clearImage(){
    image.fill(Qt::white);
    update();
}
//clear up the current frame.
void drawingbroad::clearCurrentFrame(){
    QImage clearFrame = QImage(frames[0].size(), QImage::Format_RGB32);
    clearFrame.fill(Qt::white);
    image = clearFrame;
    pushFrame(currentFrame);
    setImage(clearFrame);
}

//When mouse is pressed, it would active the tool to do something.
void drawingbroad::mousePressEvent(QMouseEvent *event){

        isPressed = true;
        if(event->button() == Qt::LeftButton){  
           startposition.setX(event->pos().rx()*broadSizeOffset);
           startposition.setY(event->pos().ry()*broadSizeOffset);
           position = startposition;
           isDrawing = true;        
        update();
    }
}

//When mouse is moved, it would active the tool to do something.
void drawingbroad::mouseMoveEvent(QMouseEvent *event){
        if ((event->buttons() & Qt::LeftButton) && isDrawing == true){

            position.setX(event->pos().rx()*broadSizeOffset);
            position.setY(event->pos().ry()*broadSizeOffset);
            if(drawingPattern == 1){
                drawLineTo(position);
            }
        }  
        update();
}

//When mouse is release, it would active the tool to do something.
void drawingbroad::mouseReleaseEvent(QMouseEvent *event){
        isPressed = false;
        if(event->button() == Qt::LeftButton && isDrawing == true){
            position.setX(event->pos().rx()*broadSizeOffset);
            position.setY(event->pos().ry()*broadSizeOffset);
            if(drawingPattern == 1){
                drawLineTo(position);
            }
            else if(drawingPattern == 2){
                drawRectangle(position);
            }
            else if(drawingPattern == 3){
                drawEllipse(position);
            }
            else if(drawingPattern == 4){
                drawLineTo(position);
            }else if(drawingPattern == 5){
                 fillBackgroundColor();
            }


            isDrawing = false;
        }
        update();
        pushFrame(currentFrame);
        updateFrameArea(framesArea);

}

//It is to control the pain tool.
void drawingbroad::paintEvent(QPaintEvent *) {
       QPainter painter(this);
       QPixmap pm;
       pm.convertFromImage(image);
       QRect testRcet = QRect(0,0,512,512);
       pm = pm.scaled((QSize(512,512)));
       //
       painter.drawImage(testRcet, pm.toImage(), testRcet);
       painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
       if (isPressed){
           if(drawingPattern == 2){
               painter.drawRect(startposition.x()/broadSizeOffset, startposition.y()/broadSizeOffset, (position.x()-startposition.x())/broadSizeOffset, (position.y()-startposition.y())/broadSizeOffset);
           }
           if (drawingPattern == 3){
               painter.drawEllipse(startposition.x()/broadSizeOffset, startposition.y()/broadSizeOffset, (position.x()-startposition.x())/broadSizeOffset, (position.y()-startposition.y())/broadSizeOffset);
           }
           if (drawingPattern == 4){
               painter.drawLine(startposition.x()/broadSizeOffset, startposition.y()/broadSizeOffset, (position.x()-startposition.x())/broadSizeOffset, (position.y()-startposition.y())/broadSizeOffset);
           }
           if (drawingPattern == 5){
               fillBackgroundColor();
           }

       }
}
//when it is actived, the line will be drawn.
void drawingbroad::drawLineTo(const QPoint &endPosition) {
        QPainter painter(&image);
        painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        painter.drawLine(startposition, endPosition);
        int rad = (penWidth / 2) + 2;
        update(QRect(startposition, endPosition).normalized().adjusted(-rad, -rad, +rad, +rad));
        startposition = endPosition;
}

//when it is actived, the rectangle will be drawn.
void drawingbroad::drawRectangle(const QPoint &endPosition) {
        QPainter painter(&image);
        painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        painter.drawRect(startposition.x(), startposition.y(), endPosition.x()-startposition.x(), endPosition.y()-startposition.y());

        int rad = (penWidth / 2) + 2;
        update(QRect(startposition, endPosition).normalized().adjusted(-rad, -rad, +rad, +rad));
        position = startposition;
}

//when it is actived, the ellipse will be drawn.
void drawingbroad::drawEllipse(const QPoint &endPosition) {
        QPainter painter(&image);
        painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        painter.drawEllipse(startposition.x(), startposition.y(), endPosition.x()-startposition.x(), endPosition.y()-startposition.y());

        int rad = (penWidth / 2) + 2;
        update(QRect(startposition, endPosition).normalized().adjusted(-rad, -rad, +rad, +rad));

}

//resize the current image.
void drawingbroad::resizeImage(QImage *image, const QSize &newSize){
           if (image->size() != newSize){
               QImage newImage(newSize, QImage::Format_RGB32);
               newImage.fill(Qt::white);
               QPainter painter(&newImage);
               painter.drawImage(QPoint(0, 0), *image);
               *image = newImage;
           }
}


int drawingbroad::getFrameIndex(){
    return currentFrame;
}

void drawingbroad::addFrame() {
    pushFrame(currentFrame);
    QImage temp;
    if (frames.length() > 0) {
        temp = frames[frames.length() - 1];
    }
    frames.append(temp);
    currentFrame = frames.length()-1;
}

void drawingbroad::addFirstFrame(){
    pushFrame(0);
}

void drawingbroad::deleteFrame() {
    if (frames.length() == 1){
        clearCurrentFrame();
        return;
    }
    if (currentFrame >= 0 && currentFrame < frames.size()) {
        frames.remove(currentFrame);
        if (currentFrame == frames.length()){
            currentFrame = frames.length() - 1;
        }
    }
   setImage(frames[currentFrame]);
}

QImage drawingbroad::nextFrames(framesarea *frame){
    pushFrame(currentFrame);
    currentFrame = (currentFrame + 1) % frames.length();
    frame->updateFrames(&frames);
    return frames[currentFrame];
}

QImage drawingbroad::lastFrame(framesarea *frame){
    pushFrame(currentFrame);
    currentFrame = currentFrame - 1;
    if (currentFrame < 0) currentFrame = frames.length() - 1;
    frame->updateFrames(&frames);
    return frames[currentFrame];
}

void drawingbroad::updateFrameArea(framesarea *frame)
{
    frame->updateFrames(&frames);
}

void drawingbroad::pushFrame(int frameIndex) {
    if (frameIndex < frames.size())
        frames[frameIndex] = image;
    else
        frames.push_back(image);
}

void drawingbroad::setImage(QImage newImage)
{
    image = newImage;
    update();
}

QVector<QImage> drawingbroad::getFrames(){
    return frames;
}

void drawingbroad::setFrames(QVector<QImage> f){
     frames = f;
}

void drawingbroad::fillBackgroundColor(){
    image.fill(penColor);
}
