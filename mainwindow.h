#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QWidgetAction>
#include <qsortfilterproxymodelmorethanrow.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fetchDataToModel();

private slots:
    void on_actionAjout_Dossier_triggered();

    void on_actionA_propos_triggered();

    void searchSlot();

    void on_actionSupprimer_triggered();

    void on_actionDetails_triggered();

    void on_actionEditer_triggered();

    void on_actionQuitter_triggered();

    void on_actionGestion_Prestation_triggered();

    void on_tableView_pressed(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    QWidgetAction *searchAction;
    int rowSelected;
    QLineEdit *search;
    QString findName;
    QAbstractItemModel *modl;
    QSortFilterProxyModelMoreThanRow proxy;
    QModelIndex matchingIndex;
     QItemSelectionModel *sm;
     int selection;

};

#endif // MAINWINDOW_H
