#ifndef DETAILSDOSSIER_H
#define DETAILSDOSSIER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DetailsDossier;
}

class DetailsDossier : public QDialog
{
    Q_OBJECT

public:
    explicit DetailsDossier(QWidget *parent = 0);
    DetailsDossier(int id,QWidget *parent=0);
    ~DetailsDossier();

private:
    QSqlDatabase db;
    Ui::DetailsDossier *ui;
    int id;
};

#endif // DETAILSDOSSIER_H
