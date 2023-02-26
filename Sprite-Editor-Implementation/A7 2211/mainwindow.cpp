/*
* CS 3505:A7 sprite editor implementation
* This is the sources file for our main function, created signals and slots to manipulate main’s property.
*
* @author: Robert Li, Wenlin Li, Qingwen Bao, Qimeng Chao, Julian Zhou
* @version: 04/01/22 1.0 implemented the method
* @version: 04/04/22 1.1 fixed bug and added extra feature.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingbroad.h"
#include "iostream"
#include "previewwindow.h"
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(Model* m, sizeDialog* sd,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    sd ->show();
    firstFrame();
    ui->penWidth->setValue(5);
    ui->addFrameButton->setStyleSheet("QPushButton {background-color: white; color: color;}");
    ui->deleteFrameButton->setStyleSheet("QPushButton {background-color: white; color: color;}");
    ui->showSpriteButton->setStyleSheet("QPushButton {background-color: white; color: color;}");
    ui->indexLabel->setStyleSheet("QLabel {color : black;}");
    ui->label_2->setStyleSheet("QLabel {color : black;}");
    ui->penColor->setStyleSheet("QPushButton {background-color: black; color: color;}");
    setWindowTitle(tr("Sprite Editor"));
    ui->drawingBoard->init(ui->showFramesWidget);
    connect(sd,SIGNAL(setSize(int)),ui->drawingBoard,SLOT(setBroadSize(int)));
    connect(ui->penColor, &QPushButton::clicked, m, &Model::penColor);
    connect(ui->eraserButton, &QPushButton::clicked, m, &Model::turnOnEraser);
    connect(ui->pencilButton, &QPushButton::clicked, m, &Model::turnOnPencil);
    connect(m, &Model::setDrawingPattern, ui->drawingBoard, &drawingbroad::setDrawingPattern);
    connect(m, &Model::setPenColor, ui->drawingBoard, &drawingbroad::setPenColor);
    connect(m, &Model::setPalette, this, &MainWindow::setPalette);

    connect(ui->recToolButton, &QPushButton::clicked, m, &Model::turnOnRecTool);
    connect(ui->ellipseButton, &QPushButton::clicked, m, &Model::turnOnEllipseTool);
    connect(ui->lineButton, &QPushButton::clicked, m, &Model::turnOnLineTool);
    connect(ui->fillColorButton, &QPushButton::clicked,m,&Model::fillBackgroundColor);


    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearCurrentFrame);
    connect(this, &MainWindow::clearCurrentFrameSignal, ui->drawingBoard, &drawingbroad::clearCurrentFrame);
    connect(ui->penWidth, &QSpinBox::valueChanged, m, &Model::PenWidth);
    connect(m, &Model::setPenWidth, ui->drawingBoard, &drawingbroad::setPenWidth);

    connect(ui->actionOpen_Image, &QAction::triggered,m,&Model::openFile);
    connect(m,&Model::openFileSignal, ui->drawingBoard, &drawingbroad::openFile);
    connect(ui->actionOpen_SSP, &QAction::triggered,m,&Model::openSSP);
    connect(ui->actionSave, &QAction::triggered,m,&Model::saveFile);
    connect(m,&Model::setFrameSignal, ui->drawingBoard, &drawingbroad::setFrames);
    connect(ui->actionhelp,&QAction::triggered, this,  &MainWindow::openHelp);

    connect(this,&MainWindow::getFrameIndexSignal, ui->drawingBoard, &drawingbroad::getFrameIndex);
    connect(this, &MainWindow::addFirstFrameSingal,ui->drawingBoard, &drawingbroad::addFirstFrame);
    connect(ui->addFrameButton, &QPushButton::pressed, this, &MainWindow::addFrame);
    connect(this, &MainWindow::addFrameSingal,ui->drawingBoard, &drawingbroad::addFrame);
    connect(this, &MainWindow::updateFrameArea,ui->drawingBoard, &drawingbroad::updateFrameArea);
    connect(ui->deleteFrameButton, &QPushButton::pressed, this, &MainWindow::deleteCurrentFrame);
    connect(this, &MainWindow::deleteFrame, ui->drawingBoard, &drawingbroad::deleteFrame);
    connect(ui->nextFrameButton, &QPushButton::pressed, this, &MainWindow::setNextFrame);
    connect(this, &MainWindow::setImage,ui->drawingBoard, &drawingbroad::setImage);
    connect(ui->lastFrameButton, &QPushButton::pressed, this, &MainWindow::setLastFrame);
    connect(ui->showSpriteButton, &QPushButton::pressed, this, &MainWindow::showPreview);
    connect(this, &MainWindow::getAllFrames, ui->drawingBoard, &drawingbroad::getFrames);
    connect(ui->actionClose,&QAction::triggered,this, &MainWindow::close);

    connect(m,SIGNAL(requestFrames()),this,SLOT(getAllFrames()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<QImage> MainWindow::getAllFrames(){
    QVector<QImage> r = ui->drawingBoard->getFrames();
    std::cout << "received "<<r.size()<< std::endl;
    return r;
}

void MainWindow::setPalette(const QColor &newColor){
    QColor col = newColor;
    if(col.isValid()) {
       QString qss = QString("background-color: %1").arg(col.name());
       ui->penColor->setStyleSheet(qss);
    }
}

void MainWindow::addFrame() {
    emit addFrameSingal();
    emit updateFrameArea(ui->showFramesWidget);
    updateWidgetAndLabel(1);
}


void MainWindow::updateWidgetAndLabel(int mode){
    if(mode == 1){

    int currentFrame = emit getFrameIndexSignal();
//    ui->showFramesWidget->setFrameIndex(currentFrame);
    ui->indexLabel->setText(QString::number(currentFrame + 1));
    }
    else if(mode == 2){
      int currentFrame = emit getFrameIndexSignal();
      ui->indexLabel->setText(QString::number(currentFrame + 1));
    }
    else if(mode == 3){
        int currentFrame = emit getFrameIndexSignal();
        ui->indexLabel->setText(QString::number(currentFrame));
    }
}

void MainWindow::firstFrame(){
    emit addFirstFrameSingal();
    emit updateFrameArea(ui->showFramesWidget);
}

void MainWindow::deleteCurrentFrame() {
    emit deleteFrame();
    emit updateFrameArea(ui->showFramesWidget);
    updateWidgetAndLabel(1);
}


void MainWindow::setNextFrame()
{
    QImage newImage = ui->drawingBoard->nextFrames(ui->showFramesWidget);
    emit setImage(newImage);
    updateWidgetAndLabel(2);
}

void MainWindow::setLastFrame()
{
    QImage newImage = ui->drawingBoard->nextFrames(ui->showFramesWidget);
    emit setImage(newImage);
    updateWidgetAndLabel(2);
}

void MainWindow::clearCurrentFrame(){
    emit clearCurrentFrameSignal();
    emit updateFrameArea(ui->showFramesWidget);
    updateWidgetAndLabel(3);
}

void MainWindow::showPreview()
{
    QVector<QImage> FrameList = emit getAllFrames();
    new PreviewWindow(FrameList);
}
void MainWindow::openHelp(){
    QMessageBox::about(this, tr("About sprite editor"),
               tr("<p>The <b>Scribble</b> Group Name:反情報工学研究总会</p><p>"

                  "Group Members:Robert Li, Wenlin Li, Qingwen Bao, Julian Zhou and Qimeng Chao.</p><p>"

                  "Data uploaded: 04/05/2022</p><p>"

                  "Brief instrction: This is a Qt-based sprite editor. Our sprites editor have animation cycles associated with them, the sequence of images might show the sprite walking, or exploding, or powering-up, and so on. Our sprite editor usually includes a zoomed-in view of the image pixels and the ability to manipulate the pixels using simple tools. This project has a sense of an array of images to handle to the sequence of frames. A useful feature in an editor is a preview, which animates the sequence of images at adjustable rates.</p><p>"

                  "Design decisions: By considering carefully, we desicide to devide into 7 main classes which included all the code we need to meet the assignment requirments, this way we can maintain and manage our code better and clear, and add extra features as needed."

                  "How to use: See the video we have post for tutorial.</p><p>"

                  "The challenges: we had hard time on managing the drawing broad layers, at first, we use filled with white method to clear the image, it will never clear right if we have only one layer left, in this case, we have used some time to figure out that, we need to clear the frame on this broad as well.</p><p>"

                  "The preview part is also a hard part for us, we have lost in manage the signal and slots. After some TAs help, we eventually figuered this problem, and made the connect clear and nice.</p><p>"

                  "The extra features: Open Image: We can input the image from local device to the drawing board. Paint Bucket: The user can fill out the background color which from the color palette..</p>"));
}

void MainWindow::close(){
    this->close();
}
