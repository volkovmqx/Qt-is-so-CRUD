#ifndef EDITDOSSIER_H
#define EDITDOSSIER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class EditDossier;
}

class EditDossier : public QDialog
{
    Q_OBJECT

public:
    explicit EditDossier(QWidget *parent = 0);
    EditDossier(int id,QWidget *parent = 0);
    ~EditDossier();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_buttonBox_accepted();

private:
    int idparent1;
    int idparent2;
    Ui::EditDossier *ui;
    QSqlDatabase db;
    int nbretel;
    int nbretel_2;
    QLineEdit *tel[4];
    QLineEdit *tel_2[4];
    int id;

};

#endif // EDITDOSSIER_H
