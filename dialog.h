#ifndef DIALOG_H
#define DIALOG_H
#include <QtSql>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(int x,QWidget *parent = 0);
    ~Dialog();
    void fetchDataToModel();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_pressed(const QModelIndex &index);

private:
    int id;
    Ui::Dialog *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    int selectedrow;
};

#endif // DIALOG_H
