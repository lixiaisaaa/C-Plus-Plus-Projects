/*
* CS 3505:A7 sprite editor implementation
* This is the header file for our main function, created signals and slots to manipulate main’s property. *
* @author: Robert Li, Wenlin Li, Qingwen Bao, Qimeng Chao, Julian Zhou
* @version: 04/01/22 1.0 implemented the method
* @version: 04/04/22 1.1 fixed bug and added extra feature.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "drawingbroad.h"
#include <QMainWindow>
#include "model.h"
#include <QTimer>
#include "sizedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model* m,sizeDialog* sd, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
//    void on_addFrameButton_clicked();

    void addFrame();
    void firstFrame();
    void deleteCurrentFrame();
    void setNextFrame();
    void setLastFrame();
    void clearCurrentFrame();
    void showPreview();
    void setPalette(const QColor &newColor);
    QVector<QImage> getAllFrames();
    void close();

private:
    Ui::MainWindow *ui;
    void penColor();
    QTimer *frameTimer;
    void updateWidgetAndLabel(int);
    void openHelp();



signals:
      void addFrameSingal();
      void addFirstFrameSingal();
      void deleteFrame();
      void setImage(QImage);
      void clearCurrentFrameSignal();
      int getFrameIndexSignal();   
      void updateFrameArea(framesarea *frame);


};
#endif // MAINWINDOW_H
