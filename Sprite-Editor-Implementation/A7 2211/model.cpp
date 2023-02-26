#include "model.h"
Model::Model(QObject *parent): QObject{parent} {
    tool = 0;
    isEraserOn = false;
    currentColor = Qt::black;
}
void Model::turnOnPencil(){
      tool = 1;
      isEraserOn = false;
      emit setDrawingPattern(tool);
      emit setPenColor(currentColor);
}


void Model::turnOnEraser(){
    isEraserOn = true;
    tool = 1;
    emit setDrawingPattern(tool);
    emit setPenColor(Qt::white);
}

void Model::clear(){
    emit clearImage();
}

void Model::PenWidth(int newWidth){
    emit setPenWidth(newWidth);
}

void Model::openFile(){
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isEmpty()){
        emit openFileSignal(fileName);
    }

}

void Model::openSSP(){
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty()){
        qWarning("fileName error");
        return;
    }
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning("open error");
        return;
    }
    QTextStream in(&fileName);
    QByteArray sspFile= file.readAll();
    QString qs = file.readAll();
    QJsonDocument jd(QJsonDocument::fromJson(sspFile));
    file.close();
    QJsonObject jo= jd.object();

    int height = jo["height"].toInt();
    int width = jo["width"].toInt();
    int numberOfFrames = jo["numberOfFrames"].toInt();

    QVector<QImage> frames;
    int framesCount = 0;
    for(int i = 0; i < numberOfFrames; i++){
        QImage tempImage = QImage(width, height, QImage::Format_ARGB32);
        for (int r=0; r<height; r++){
            for(int c=0; c<width; c++){
                QString frameIndex = "frame"+QString::number(framesCount);
                int red =jo["frames"][frameIndex][r][c][0].toInt();
                int green =jo["frames"][frameIndex][r][c][1].toInt();
                int blue =jo["frames"][frameIndex][r][c][2].toInt();
                int alpha =jo["frames"][frameIndex][r][c][3].toInt();
                tempImage.setPixelColor(r,c, QColor(red,green,blue,alpha));
            }
        }
        frames.append(tempImage);
        framesCount++;
    }
    emit setFrameSignal(frames);
}


void Model::saveFile(){

    QVector<QImage> frames =  emit requestFrames();
    if(frames.isEmpty()){
        return;
    }else{
        if(frames[0].isNull())
            return;
    }
    QString fileName = QFileDialog::getSaveFileName();
    QFile jsonFile(fileName);
    QJsonObject spriteObject;
    if(!jsonFile.open(QIODevice::WriteOnly)){
        qWarning("save error");
        return;
    }
    int frameWidth = frames[0].width();
    int frameHeight = frames[0].height();
    int frameNum = frames.size();
    spriteObject.insert("height",QJsonValue::fromVariant(frameHeight));
    spriteObject.insert("width",QJsonValue::fromVariant(frameWidth));
    spriteObject.insert("numberOfFrames",QJsonValue::fromVariant(frameNum));
    QJsonObject allFrames;

     int index = 0;
     for (QImage temp : frames){
         QJsonArray JFrame;
         JFrame.empty();
          for (int row = 0; row < frameHeight; row++ ){
              QJsonArray Jrows;
              Jrows.empty();
              for( int col = 0; col < frameWidth; col++){
                  QJsonArray pix;
                  pix.empty();
                  QColor currentPixel(temp.pixel(row,col));
                  pix.append(currentPixel.red());
                  pix.append(currentPixel.green());
                  pix.append(currentPixel.blue());
                  pix.append(currentPixel.alpha());
                  Jrows.append(pix);
              }
              JFrame.append(Jrows);
          }
          QString s = "frame"+QString::number(index);
          allFrames.insert(s,JFrame);
          index++;
     }
    spriteObject.insert("frames",allFrames);
    QJsonDocument doc(spriteObject);
    doc.setObject(spriteObject);
    jsonFile.write(doc.toJson());
    jsonFile.close();
}
void Model::turnOnRecTool(){
    isEraserOn = false;
    tool = 2;
    emit setPenColor(currentColor);
    emit setDrawingPattern(tool);
}
void Model::turnOnEllipseTool(){
    isEraserOn = false;
    tool = 3;
    emit setPenColor(currentColor);
    emit setDrawingPattern(tool);
}
void Model::turnOnLineTool(){
    isEraserOn = false;
    tool = 4;
    emit setPenColor(currentColor);
    emit setDrawingPattern(tool);
}
void Model::penColor(){
    if(isEraserOn == false){
    emit setDrawingPattern(tool);
    currentColor = QColorDialog::getColor();
    emit setPenColor(currentColor);
    emit setPalette(currentColor);
    }
    else{
    currentColor = QColorDialog::getColor();
    emit setPalette(currentColor);
    }
}

void Model::fillBackgroundColor(){
    isEraserOn = false;
    tool = 5;
    emit setPenColor(currentColor);
    emit setDrawingPattern(tool);
}


