#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

void Dialog::fetchDataToModel() {
    if(db.open()) {
        model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT a.id,d.nom,e.nom,p.nom "
                      "FROM `Dossier` d ,`Echeances` e,`Abonnement` a,`Prestation` p "
                      "where a.`id_Dossier` = d.id "
                      "AND a.`id_Echeance` = e.id "
                      "AND d.`id` = :idDossier "
                      "AND a.`id_Prestation` = p.id ");
        query.bindValue(":idDossier",id);
        query.exec();
        model->setQuery(query);
        ui->tableView->setModel(model);

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identificateur"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom éléve"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Echéance"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prestation"));
        ui->tableView->setColumnWidth(2,150);

    }
}
Dialog::Dialog(int x,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    selectedrow=-1;
    id=x;
    ui->setupUi(this);
    db=QSqlDatabase::addDatabase("QMYSQL","GestionPresa");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("gestionecole");
    this->fetchDataToModel();
    ui->label_2->setText(ui->label_2->text()+QString::number(id));
    QSqlQuery query;
    QStringList List;
    if(query.exec("SELECT * FROM Echeances")){
     while(query.next()) {
        List.append(query.value(1).toString());

    }
        ui->echAnceComboBox->addItems(List);
    }
    List.clear();
    if(query.exec("SELECT * FROM Prestation")){
     while(query.next()) {
        List.append(query.value(1).toString());

    }
        ui->prestationComboBox->addItems(List);
    }
}

Dialog::~Dialog()
{
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO `Abonnement` (`id_Dossier`,`id_Echeance`,`id_Prestation`) VALUES ( :idDossier, :idEch, :idPres);");
    query.bindValue(":idPres",ui->prestationComboBox->currentIndex()+1);
    query.bindValue(":idEch",ui->echAnceComboBox->currentIndex()+1);
    query.bindValue(":idDossier",id);
    query.exec();
    this->fetchDataToModel();
}


void Dialog::on_pushButton_2_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM `Abonnement` WHERE `id` = ?");
    query.addBindValue(ui->tableView->model()->data(ui->tableView->model()->index(selectedrow,0)).toString().toInt());
    query.exec();
    this->fetchDataToModel();
}

void Dialog::on_tableView_pressed(const QModelIndex &index)
{
    selectedrow=index.row();

}
