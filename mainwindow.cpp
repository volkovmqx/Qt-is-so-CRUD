#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <limits>
#include <QDebug>
#include <editdossier.h>
#include <detailsdossier.h>
#include <QMessageBox>
#include <QLineEdit>

void MainWindow::fetchDataToModel() {
    if(db.open()) {
        model = new QSqlQueryModel();
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Prénom Deuxiéme Responsable"));
        model->setQuery("SELECT  DISTINCT d.id,d.nom,d.prenom,n.niveau,p1.nom,p1.prenom,p2.nom,p2.prenom "
                            "FROM `Dossier` d ,`Niveau` n,`Responsabilite` r,`Parent` p1, `Parent` p2 "
                            "where r.`id_Parent1` = p1.id "
                            "AND r.`id_Parent2` = p2.id "
                            "AND r.`id_Dossier` = d.id "
                            "AND n.`id` = d.`id_Niveau` "
                            );
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identificateur"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom éléve"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom éléve"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Niveau"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom Premier Responsable"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prénom Premier Responsable"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Nom Deuxiéme Responsable"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Prénom Deuxiéme Responsable"));
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0,100);
        ui->tableView->setColumnWidth(1,120);
        ui->tableView->setColumnWidth(2,120);
        this->searchSlot();
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    search=new QLineEdit(this);
    search->setFixedWidth(250);
    search->setClearButtonEnabled(true);
    search->setPlaceholderText("Recherche ...");
    search->setText("");
    searchAction = new QWidgetAction(this);
    searchAction->setDefaultWidget(search);

    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->toolBar_2->addWidget(empty);
    ui->toolBar_2->addAction(searchAction);
    ui->toolBar_2->addAction(ui->actionRecherche);
    connect(search, SIGNAL(textChanged(const QString &)), this, SLOT(searchSlot()));


    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("gestionecole");
    this->fetchDataToModel();

}


MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::searchSlot() {
    ui->actionDetails->setEnabled(false);
    ui->actionEditer->setEnabled(false);
    ui->actionSupprimer->setEnabled(false);
     ui->actionGestion_Prestation->setEnabled(false);


    ui->tableView->setModel(model);
    findName = search->text().trimmed();
    modl = ui->tableView->model();
    proxy.setSourceModel(modl);
    proxy.setFilterRegExp(QRegExp(findName, Qt::CaseInsensitive,QRegExp::FixedString));
    proxy.setFilterFixedString(findName);
    //ui->tableView->setModel(proxy);
    // now the proxy only contains rows that match the name
    // let's take the first one and map it to the original model

    matchingIndex = proxy.mapToSource(proxy.index(0,0));
    if(matchingIndex.isValid()){

            ui->tableView->setModel(& proxy);
            ui->tableView->scrollTo(matchingIndex,QAbstractItemView::EnsureVisible);
        } else {
            QMessageBox::information(this,"Recherche", "Pas trouvé !");
        }
}


void MainWindow::on_actionAjout_Dossier_triggered()
{
    EditDossier * ed=new EditDossier(this);
    ed->show();
}

void MainWindow::on_actionA_propos_triggered()
{
    QMessageBox::information(this, "à propos", "Application de Gestion d'école <br>créer et conçu par <b>Lotfi Messaudi</b>.");

}


void MainWindow::on_actionSupprimer_triggered()
{
    QString id=ui->tableView->model()->data(ui->tableView->model()->index(rowSelected,0)).toString();
    int reponse = QMessageBox::question(this, "Confirmation de suppression", "êtes vous sur de supprimer le dossier N°"+id, QMessageBox ::Yes | QMessageBox::No);

      if (reponse == QMessageBox::Yes)
      {
          QSqlQuery query;
          query.prepare("DELETE FROM `Dossier` WHERE `id` = ?");
          query.addBindValue(id);
          query.exec();
          this->fetchDataToModel();
      }
}


void MainWindow::on_actionDetails_triggered()
{
    DetailsDossier * dd=new DetailsDossier(ui->tableView->model()->data(ui->tableView->model()->index(rowSelected,0)).toString().toInt()
,this);
    dd->show();
}

void MainWindow::on_actionEditer_triggered()
{
    EditDossier * ed=new EditDossier(ui->tableView->model()->data(ui->tableView->model()->index(rowSelected,0)).toString().toInt()
,this);
    ed->show();
}


void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

void MainWindow::on_actionGestion_Prestation_triggered()
{
    Dialog *d=new Dialog(ui->tableView->model()->data(ui->tableView->model()->index(rowSelected,0)).toString().toInt()
                         ,this);
    d->show();
}

void MainWindow::on_tableView_pressed(const QModelIndex &index)
{
    rowSelected=index.row();
    ui->actionDetails->setEnabled(true);
    ui->actionEditer->setEnabled(true);
    ui->actionSupprimer->setEnabled(true);
    ui->actionGestion_Prestation->setEnabled(true);
}
