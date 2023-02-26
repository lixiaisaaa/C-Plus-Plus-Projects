#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class PreviewWindow;
}

class PreviewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewWindow(QVector<QImage> frames, QWidget *parent = nullptr);
    ~PreviewWindow();
    void init(QTimer* frameTimer);

private slots:
    void on_closeButton_pressed();
    void on_spinBox_valueChanged(int arg1);
    void on_slider_valueChanged(int value);
    void changeFrame();

    void on_rSize_clicked();

    void on_pwSize_clicked();

private:
    Ui::PreviewWindow *ui;
    int currentFrame;
    QVector<QImage> frames;
    QTimer *frametimer;
    void showFrame(QImage frame);
};

#endif // PREVIEWWINDOW_H
