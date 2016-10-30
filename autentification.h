#ifndef AUTENTIFICATION_H
#define AUTENTIFICATION_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class Autentification;
}

class Autentification : public QDialog
{
    Q_OBJECT

public:
    explicit Autentification(QWidget *parent = 0);
    ~Autentification();

private slots:

    void on_afficherMotDePasseCheckBox_clicked(bool checked);

    void on_pushButton_2_clicked();

private:
    Ui::Autentification *ui;
};

#endif // AUTENTIFICATION_H
