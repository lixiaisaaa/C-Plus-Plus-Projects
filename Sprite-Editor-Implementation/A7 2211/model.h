#ifndef MODEL_H
#define MODEL_H
#include <QObject>
#include <QImage>
#include <QColor>
#include "QColorDialog"
#include "QFileDialog"
#include <fstream>
#include <iostream>
#include "drawingbroad.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
using namespace std;

class Model : public QObject {
    Q_OBJECT

private:
    int tool;
    bool isEraserOn;
    QColor currentColor;

public:
    explicit Model(QObject* parent = 0);

protected:


signals:

    void setDrawingPattern(int);

    void setPenColor(const QColor &newColor);

    void setPalette(const QColor &newColor);

    void setEraserOn();

    void clearImage();

    void setPenWidth(int);

    bool openFileSignal(const QString);
    bool saveFileSignal(const QString);

    void deleteFromFrames();

    void addFrames();

    void setFrameSignal(QVector<QImage>);

    void frameUpdate();

    QVector<QImage> requestFrames();


public slots:

    void turnOnPencil();

    void turnOnEraser();

    void turnOnEllipseTool();

    void turnOnLineTool();

    void clear();

    void PenWidth(int);

    void openFile();

    void openSSP();

    void saveFile();

    void turnOnRecTool();

    void penColor();

    void fillBackgroundColor();

};

#endif // MODEL_H
