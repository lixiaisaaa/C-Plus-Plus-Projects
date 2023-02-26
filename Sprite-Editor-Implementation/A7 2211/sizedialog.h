/**
* CS 3505:A7 sprite editor implementation
* This is the header file for our sizedialog, created signals and slots to manipulate dialog’s property.
* * @author: Robert Li, Wenlin Li, Qingwen Bao, Qimeng Chao, Julian Zhou
* @version: 04/01/22 1.0 implemented the method
* @version: 04/04/22 1.1 fixed bug and added extra feature.
*/

#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>
namespace Ui {
class sizeDialog;
}

class sizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sizeDialog(QWidget *parent = nullptr);
    ~sizeDialog();

signals:
    void setSize(int size);

private slots:
    void on_sizeButton8_clicked();

    void on_sizeButton32_clicked();

    void on_sizeButton128_clicked();

    void on_sizeButton64_clicked();

    void on_sizeButton512_clicked();

    void on_sizeButton256_clicked();

    void on_applyButton_clicked();

private:
    Ui::sizeDialog *ui;
    sizeDialog* sd;
};

#endif // SIZEDIALOG_H
