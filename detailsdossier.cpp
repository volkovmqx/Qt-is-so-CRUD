#include "detailsdossier.h"
#include "ui_detailsdossier.h"
#include <QDebug>

DetailsDossier::DetailsDossier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailsDossier)
{
    ui->setupUi(this);
    id=-1;

}
DetailsDossier::DetailsDossier(int x,QWidget *parent):
    QDialog(parent),
    ui(new Ui::DetailsDossier)
{
    ui->setupUi(this);
    id=x;
    qDebug() << id;

    //database connection :
    db=QSqlDatabase::addDatabase("QMYSQL","details");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("gestionecole");

    if(db.open()) {
        // query to get donnés eleve
        QSqlQuery query;
        query.prepare("SELECT d.nom,d.prenom,n.niveau  FROM `Dossier` d ,`Niveau` n WHERE d.`id` = :iddossier AND n.`id` = d.`id_Niveau`");
        query.bindValue(":iddossier",id);
        if(query.exec()){
            while(query.next()){
            ui->label_2->setText(query.value(0).toString());
            ui->label_3->setText(query.value(1).toString());
            ui->label_5->setText(query.value(2).toString());
            }

        }
           int idparent1=0;
           int idparent2=0;
        // query to get donnés Parent 1
        query.prepare("SELECT p.id,p.nom,p.prenom,p.profession FROM `Responsabilite` r ,`Parent` p WHERE r.`id_Dossier` = :iddossier AND p.`id` = r.`id_Parent1`");
        query.bindValue(":iddossier",id);
        if(query.exec()){
            while(query.next()){
                idparent1=query.value(0).toString().toInt();
                ui->label_6->setText(query.value(1).toString());
                ui->label_7->setText(query.value(2).toString());
                ui->label_32->setText(query.value(3).toString());
            }

        }
        query.prepare("SELECT numTel FROM `Tel` WHERE `id_Parent` = :idparent");
        query.bindValue(":idparent",idparent1);

        if(query.exec()){
            int i=0;
            while(query.next()){
                if(i==0) {
                     ui->label_13->setText(query.value(0).toString());
                      i++;
                }
                else {

                    ui->gridLayout->addWidget(new QLabel(query.value(0).toString()),i+1,0);
                     i++;

            }
            }

        }
        //get adresse personelle Parent 1:
        query.prepare("SELECT a.adresseLigne1,a.adresseLigne2,a.ville,a.codePostale,a.pays FROM `Adresse` a WHERE a.`id_Parent` = :iddossier AND a.type=1 ");
        query.bindValue(":iddossier",idparent1);
        if(query.exec()){
            while(query.next()){
                ui->label_8->setText(query.value(0).toString());
                ui->label_9->setText(query.value(1).toString());
                ui->label_10->setText(query.value(2).toString());
                ui->label_11->setText(query.value(3).toString());
                ui->label_12->setText(query.value(4).toString());
            }

        }
        //get adresse pro Parent 1:
        query.prepare("SELECT a.adresseLigne1,a.adresseLigne2,a.ville,a.codePostale,a.pays FROM `Adresse` a WHERE a.`id_Parent` = :iddossier AND a.type=0 ");
        query.bindValue(":iddossier",idparent1);
        if(query.exec()){
            while(query.next()){
                ui->label_14->setText(query.value(0).toString());
                ui->label_15->setText(query.value(1).toString());
                ui->label_16->setText(query.value(2).toString());
                ui->label_17->setText(query.value(3).toString());
                ui->label_18->setText(query.value(4).toString());
            }

        }

        // query to get donnés Parent 2
        query.prepare("SELECT p.id,p.nom,p.prenom,p.profession FROM `Responsabilite` r ,`Parent` p WHERE r.`id_Dossier` = :iddossier AND p.`id` = r.`id_Parent2`");
        query.bindValue(":iddossier",id);
        if(query.exec()){
            while(query.next()){
                idparent2=query.value(0).toString().toInt();
                ui->label_19->setText(query.value(1).toString());
                ui->label_20->setText(query.value(2).toString());
                ui->label_33->setText(query.value(3).toString());
            }

        }

        query.prepare("SELECT numTel FROM `Tel` WHERE `id_Parent` = :idparent");
        query.bindValue(":idparent",idparent2);

        if(query.exec()){
            int i=0;
            while(query.next()){
                if(i==0) {
                     ui->label_26->setText(query.value(0).toString());
                      i++;
                }
                else {

                    ui->gridLayout_4->addWidget(new QLabel(query.value(0).toString()),i+1,0);
                     i++;

            }
            }

        }
        //get adresse perso Parent 2:
        query.prepare("SELECT a.adresseLigne1,a.adresseLigne2,a.ville,a.codePostale,a.pays FROM `Adresse` a WHERE a.`id_Parent` = :iddossier AND a.type=1 ");
        query.bindValue(":iddossier",idparent2);
        if(query.exec()){
            while(query.next()){
                ui->label_27->setText(query.value(0).toString());
                ui->label_28->setText(query.value(1).toString());
                ui->label_29->setText(query.value(2).toString());
                ui->label_30->setText(query.value(3).toString());
                ui->label_31->setText(query.value(4).toString());
            }

        }
        //adresse pro parent 2
        query.prepare("SELECT a.adresseLigne1,a.adresseLigne2,a.ville,a.codePostale,a.pays FROM `Adresse` a WHERE a.`id_Parent` = :iddossier AND a.`type` = 0 ");
        query.bindValue(":iddossier",idparent2);
        if(query.exec()){
            while(query.next()){
                ui->label_21->setText(query.value(0).toString());
                ui->label_22->setText(query.value(1).toString());
                ui->label_23->setText(query.value(2).toString());
                ui->label_24->setText(query.value(3).toString());
                ui->label_25->setText(query.value(4).toString());
            }

        }
        //end query
    }
    else {
        qDebug() << "Error = " << db.lastError().text();
    }

    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);



}

DetailsDossier::~DetailsDossier()
{
    delete ui;
}
