#include "sizedialog.h"
#include "ui_sizedialog.h"

sizeDialog::sizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sizeDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

}

sizeDialog::~sizeDialog()
{
    delete ui;
}

void sizeDialog::on_sizeButton8_clicked()
{
    ui->spinBox->setValue(8);
}


void sizeDialog::on_sizeButton32_clicked()
{
    ui->spinBox->setValue(32);
}


void sizeDialog::on_sizeButton128_clicked()
{
    ui->spinBox->setValue(128);
}


void sizeDialog::on_sizeButton64_clicked()
{
    ui->spinBox->setValue(64);
}


void sizeDialog::on_sizeButton512_clicked()
{
    ui->spinBox->setValue(512);
}


void sizeDialog::on_sizeButton256_clicked()
{
    ui->spinBox->setValue(256);
}

void sizeDialog::on_applyButton_clicked()
{
    emit setSize(ui->spinBox->value());
    this->destroy();
}

