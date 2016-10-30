#include "editdossier.h"
#include "ui_editdossier.h"
#include "mainwindow.h"
#include <QtCore>
#include <QDebug>
#include <QMessageBox>


EditDossier::EditDossier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDossier)
{
    ui->setupUi(this);
    nbretel_2 = 0;
    nbretel = 0;
    id=-1;
    db=QSqlDatabase::addDatabase("QMYSQL","new");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("gestionecole");
    if(db.open()) {
        // query to get niveau !
        QSqlQuery query;
        QStringList List;
        if(query.exec("SELECT * FROM Niveau")){
         while(query.next()) {
            List.append(query.value(1).toString());

        }
            //ui->niveauComboBox->addItems(List);
        }
        //end query to get niveau !
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

// when editing
EditDossier::EditDossier(int x,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDossier)
{

    ui->setupUi(this);
    id=x;
    nbretel_2 = 0;
    nbretel = 0;
    db=QSqlDatabase::addDatabase("QMYSQL","edit");
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
               ui->nomLeveLineEdit->setText(query.value(0).toString());
               ui->prNomLeveLineEdit->setText(query.value(1).toString());
               //ui->niveauComboBox->set(query.value(2).toString());
               }

           }
              idparent1=0;
              idparent2=0;
           // query to get donnés Parent 1
           query.prepare("SELECT p.id,p.nom,p.prenom,p.profession FROM `Responsabilite` r ,`Parent` p WHERE r.`id_Dossier` = :iddossier AND p.`id` = r.`id_Parent1`");
           query.bindValue(":iddossier",id);
           if(query.exec()){
               while(query.next()){
                   idparent1=query.value(0).toString().toInt();
                   ui->nomPremierResponsableLineEdit->setText(query.value(1).toString());
                   ui->prNomPremierResponsableLineEdit->setText(query.value(2).toString());
                   ui->professionLineEdit->setText(query.value(3).toString());
               }

           }

           query.prepare("SELECT numTel FROM `Tel` WHERE `id_Parent` = :idparent");
           query.bindValue(":idparent",idparent1);

           if(query.exec()){
               int i=0;
               while(query.next()){
                   if(i==0) {
                        ui->lineEdit->setText(query.value(0).toString());
                         i++;
                         nbretel++;

                   }
                   else {
                       tel[nbretel]=new QLineEdit();
                       tel[nbretel]->setText(query.value(0).toString());
                       ui->gridLayout->addWidget( tel[nbretel],i+1,0);
                       nbretel++;
                       i++;

               }
               }

           }
           //get adresse personelle Parent 1:
           query.prepare("SELECT a.adresseLigne1,a.adresseLigne2,a.ville,a.codePostale,a.pays FROM `Adresse` a WHERE a.`id_Parent` = :iddossier AND a.type=1 ");
           query.bindValue(":iddossier",idparent1);
           if(query.exec()){
               while(query.next()){
                   ui->ligneAdresse1LineEdit->setText(query.value(0).toString());
                   ui->ligneAdress2LineEdit->setText(query.value(1).toString());
                   ui->villeLineEdit->setText(query.value(2).toString());
                   ui->codePostaleLineEdit->setText(query.value(3).toString());
                   ui->paysLineEdit->setText(query.value(4).toString());
               }

           }
           //get adresse pro Parent 1:
           query.prepare("SELECT a.adresseLigne1,a.adresseLigne2,a.ville,a.codePostale,a.pays FROM `Adresse` a WHERE a.`id_Parent` = :iddossier AND a.type=0 ");
           query.bindValue(":iddossier",idparent1);
           if(query.exec()){
               while(query.next()){
                   ui->ligneAdresse1LineEdit_5->setText(query.value(0).toString());
                   ui->ligneAdress2LineEdit_5->setText(query.value(1).toString());
                   ui->villeLineEdit_5->setText(query.value(2).toString());
                   ui->codePostaleLineEdit_5->setText(query.value(3).toString());
                   ui->paysLineEdit_5->setText(query.value(4).toString());
               }

           }

           // query to get donnés Parent 2
           query.prepare("SELECT p.id,p.nom,p.prenom,p.profession FROM `Responsabilite` r ,`Parent` p WHERE r.`id_Dossier` = :iddossier AND p.`id` = r.`id_Parent2`");
           query.bindValue(":iddossier",id);
           if(query.exec()){
               while(query.next()){
                   idparent2=query.value(0).toString().toInt();
                   ui->nomPremierResponsableLineEdit_4->setText(query.value(1).toString());
                   ui->prNomPremierResponsableLineEdit_4->setText(query.value(2).toString());
                   ui->professionLineEdit_2->setText(query.value(3).toString());
               }

           }

           query.prepare("SELECT numTel FROM `Tel` WHERE `id_Parent` = :idparent");
           query.bindValue(":idparent",idparent2);

           if(query.exec()){
               int i=0;
               while(query.next()){
                   if(i==0) {
                        ui->lineEdit_4->setText(query.value(0).toString());
                         i++;
                         nbretel_2++;
                   }
                   else {

                       tel_2[nbretel_2]=new QLineEdit();
                       tel_2[nbretel_2]->setText(query.value(0).toString());
                       ui->gridLayout_4->addWidget(tel_2[nbretel_2],i+1,0);
                        i++;
                       nbretel_2++;

               }
               }

           }
           //get adresse perso Parent 2:
           query.prepare("SELECT a.adresseLigne1,a.adresseLigne2,a.ville,a.codePostale,a.pays FROM `Adresse` a WHERE a.`id_Parent` = :iddossier AND a.type=1 ");
           query.bindValue(":iddossier",idparent2);
           if(query.exec()){
               while(query.next()){
                   ui->ligneAdresse1LineEdit_3->setText(query.value(0).toString());
                   ui->ligneAdress2LineEdit_3->setText(query.value(1).toString());
                   ui->villeLineEdit_3->setText(query.value(2).toString());
                   ui->codePostaleLineEdit_3->setText(query.value(3).toString());
                   ui->paysLineEdit_3->setText(query.value(4).toString());
               }

           }
           //adresse pro parent 2
           query.prepare("SELECT a.adresseLigne1,a.adresseLigne2,a.ville,a.codePostale,a.pays FROM `Adresse` a WHERE a.`id_Parent` = :iddossier AND a.`type` = 0 ");
           query.bindValue(":iddossier",idparent2);
           if(query.exec()){
               while(query.next()){
                   ui->ligneAdresse1LineEdit_7->setText(query.value(0).toString());
                   ui->ligneAdress2LineEdit_7->setText(query.value(1).toString());
                   ui->villeLineEdit_7->setText(query.value(2).toString());
                   ui->codePostaleLineEdit_7->setText(query.value(3).toString());
                   ui->paysLineEdit_7->setText(query.value(4).toString());
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

EditDossier::~EditDossier()
{
    delete ui;
}

void EditDossier::on_pushButton_4_clicked()
{

    if(nbretel_2==4) {
        QMessageBox::warning(this, "Nombres Maximum atteint", "Attention, vous avez depasser le nombre de téléphones permis.");
        return;
    }
    qDebug() <<nbretel_2;
    tel_2[nbretel_2]=new QLineEdit();

    ui->gridLayout_4->addWidget(tel_2[nbretel_2],nbretel_2+1,0);
    nbretel_2++;

}

void EditDossier::on_pushButton_clicked()
{
    if(nbretel==4) {
        QMessageBox::warning(this, "Nombres Maximum atteint", "Attention, vous avez depasser le nombre de téléphones permis.");
        return;
    }

    tel[nbretel]=new QLineEdit();

    ui->gridLayout->addWidget(tel[nbretel],nbretel+1,0);
    nbretel++;
}

void EditDossier::on_buttonBox_accepted()
{
    //if update
    if(id>0) {
        QSqlQuery query;
        query.prepare("UPDATE `Dossier` SET `nom` = :nomeleve,`prenom` = :prenleve WHERE `id`=:ideleve;");
        query.bindValue(":nomeleve",ui->nomLeveLineEdit->text());
        query.bindValue(":ideleve",id);
        query.bindValue(":prenleve",ui->prNomLeveLineEdit->text());
        query.exec();

        query.prepare("UPDATE `Parent` SET `nom` = :nomparent,`prenom` = :prenparent,`profession` = :profession WHERE `id`=:idparent;");
        query.bindValue(":nomparent",ui->nomPremierResponsableLineEdit->text());
        query.bindValue(":idparent",idparent1);
        query.bindValue(":prenparent",ui->prNomPremierResponsableLineEdit->text());
        query.bindValue(":profession",ui->professionLineEdit->text());
        query.exec();
        query.bindValue(":nomparent",ui->nomPremierResponsableLineEdit_4->text());
        query.bindValue(":idparent",idparent2);
        query.bindValue(":prenparent",ui->prNomPremierResponsableLineEdit_4->text());
        query.bindValue(":profession",ui->professionLineEdit_2->text());
        query.exec();

        query.prepare("UPDATE `Adresse` SET `adresseLigne1` = :al1,`adresseLigne2` = :al2,`ville` = :ville,`codepostale` = :codepostale,`pays` = :pays WHERE `id_Parent`=:idparent AND `type`=:type;");
        //update addresse perso parent 1
        query.bindValue(":al1",ui->ligneAdresse1LineEdit->text());
        query.bindValue(":al2",ui->ligneAdress2LineEdit->text());
        query.bindValue(":ville",ui->villeLineEdit->text());
        query.bindValue(":codepostale",ui->codePostaleLineEdit->text());
        query.bindValue(":pays",ui->paysLineEdit->text());
        query.bindValue(":idparent",idparent1);
        query.bindValue(":type",1);
        query.exec();
        //update adresse pro parent 1
        query.bindValue(":al1",ui->ligneAdresse1LineEdit_5->text());
        query.bindValue(":al2",ui->ligneAdress2LineEdit_5->text());
        query.bindValue(":ville",ui->villeLineEdit_5->text());
        query.bindValue(":codepostale",ui->codePostaleLineEdit_5->text());
        query.bindValue(":pays",ui->paysLineEdit_5->text());
        query.bindValue(":idparent",idparent1);
        query.bindValue(":type",0);
        query.exec();
        //update adresse perso parent 2
        query.bindValue(":al1",ui->ligneAdresse1LineEdit_3->text());
        query.bindValue(":al2",ui->ligneAdress2LineEdit_3->text());
        query.bindValue(":ville",ui->villeLineEdit_3->text());
        query.bindValue(":codepostale",ui->codePostaleLineEdit_3->text());
        query.bindValue(":pays",ui->paysLineEdit_3->text());
        query.bindValue(":idparent",idparent2);
        query.bindValue(":type",1);
        query.exec();
        //update adresse pro parent 2
        query.bindValue(":al1",ui->ligneAdresse1LineEdit_7->text());
        query.bindValue(":al2",ui->ligneAdress2LineEdit_7->text());
        query.bindValue(":ville",ui->villeLineEdit_7->text());
        query.bindValue(":codepostale",ui->codePostaleLineEdit_7->text());
        query.bindValue(":pays",ui->paysLineEdit_7->text());
        query.bindValue(":idparent",idparent2);
        query.bindValue(":type",0);
        query.exec();


        query.prepare("INSERT INTO `gestionecole`.`Tel` (`numTel` ,`id_Parent`) VALUES(:numtel, :parentid) ON DUPLICATE KEY UPDATE `numTel`=:numtel");
        query.bindValue(":numtel",ui->lineEdit->text());
        query.bindValue(":idparent",idparent1);
        query.exec();
        for(int i=1;i<nbretel;i++) {
            qDebug() << i;
        query.bindValue(":numtel",tel[i]->text());
        query.bindValue(":idparent",idparent1);
        query.exec();
        }

        query.bindValue(":numtel",ui->lineEdit->text());
        query.bindValue(":idparent",idparent2);
        query.exec();
        for(int i=1;i<nbretel_2;i++) {
        query.bindValue(":numtel",tel_2[i]->text());
        query.bindValue(":idparent",idparent2);
        query.exec();
        }
        ((MainWindow*)parentWidget())->fetchDataToModel();
    }
    //if ajout
    else {
        QSqlQuery query;
        query.prepare("INSERT INTO `Dossier` (nom,prenom,id_Niveau) VALUES ( :nomeleve, :prenleve, 1);");
        query.bindValue(":nomeleve",ui->nomLeveLineEdit->text());
        query.bindValue(":prenleve",ui->prNomLeveLineEdit->text());
        query.exec();
        query.prepare("SELECT LAST_INSERT_ID();");
        if(query.exec()) {
            while(query.next())
                id=query.value(0).toString().toInt();
        }

        query.prepare("INSERT INTO `Parent` (`nom`,`prenom`,`profession`) VALUES ( :nomparent, :prenparent,:profession);");
        query.bindValue(":nomparent",ui->nomPremierResponsableLineEdit->text());
        query.bindValue(":prenparent",ui->prNomPremierResponsableLineEdit->text());
        query.bindValue(":profession",ui->professionLineEdit->text());
        query.exec();
        query.prepare("SELECT LAST_INSERT_ID();");
        if(query.exec()) {
            while(query.next())
                idparent1=query.value(0).toString().toInt();
        }
        query.prepare("INSERT INTO `Parent` (`nom`,`prenom`,`profession`) VALUES ( :nomparent, :prenparent,:profession);");
        query.bindValue(":nomparent",ui->nomPremierResponsableLineEdit_4->text());
        query.bindValue(":prenparent",ui->prNomPremierResponsableLineEdit_4->text());
        query.bindValue(":profession",ui->professionLineEdit_2->text());
        query.exec();
        query.prepare("SELECT LAST_INSERT_ID();");
        if(query.exec()) {
            while(query.next())
                idparent2=query.value(0).toString().toInt();
        }
        query.prepare("INSERT INTO `Responsabilite` (`id_Parent1`,`id_Parent2`,`id_Dossier`) VALUES ( :par1, :par2, :iddossier);");
        query.bindValue(":par1",idparent1);
        query.bindValue(":par2",idparent2);
        query.bindValue(":iddossier",id);
        query.exec();

        query.prepare("INSERT INTO `Adresse` (`adresseLigne1`,`adresseLigne2`,`ville`,`codepostale`,`pays`,`type`,`id_Parent`) VALUES ( :al1,:al2,:ville,:codepostale,:pays,:type,:idparent);");
        //update addresse perso parent 1
        query.bindValue(":al1",ui->ligneAdresse1LineEdit->text());
        query.bindValue(":al2",ui->ligneAdress2LineEdit->text());
        query.bindValue(":ville",ui->villeLineEdit->text());
        query.bindValue(":codepostale",ui->codePostaleLineEdit->text());
        query.bindValue(":pays",ui->paysLineEdit->text());
        query.bindValue(":idparent",idparent1);
        query.bindValue(":type",1);
        query.exec();
        //update adresse pro parent 1
        query.bindValue(":al1",ui->ligneAdresse1LineEdit_5->text());
        query.bindValue(":al2",ui->ligneAdress2LineEdit_5->text());
        query.bindValue(":ville",ui->villeLineEdit_5->text());
        query.bindValue(":codepostale",ui->codePostaleLineEdit_5->text());
        query.bindValue(":pays",ui->paysLineEdit_5->text());
        query.bindValue(":idparent",idparent1);
        query.bindValue(":type",0);
        query.exec();
        //update adresse perso parent 2
        query.bindValue(":al1",ui->ligneAdresse1LineEdit_3->text());
        query.bindValue(":al2",ui->ligneAdress2LineEdit_3->text());
        query.bindValue(":ville",ui->villeLineEdit_3->text());
        query.bindValue(":codepostale",ui->codePostaleLineEdit_3->text());
        query.bindValue(":pays",ui->paysLineEdit_3->text());
        query.bindValue(":idparent",idparent2);
        query.bindValue(":type",1);
        query.exec();
        //update adresse pro parent 2
        query.bindValue(":al1",ui->ligneAdresse1LineEdit_7->text());
        query.bindValue(":al2",ui->ligneAdress2LineEdit_7->text());
        query.bindValue(":ville",ui->villeLineEdit_7->text());
        query.bindValue(":codepostale",ui->codePostaleLineEdit_7->text());
        query.bindValue(":pays",ui->paysLineEdit_7->text());
        query.bindValue(":idparent",idparent2);
        query.bindValue(":type",0);
        query.exec();


        query.prepare("INSERT INTO `gestionecole`.`Tel` (`numTel` ,`id_Parent`) VALUES(:numtel, :idparent)");
        query.bindValue(":numtel",ui->lineEdit->text());
        query.bindValue(":idparent",idparent1);
        query.exec();
        query.bindValue(":numtel",ui->lineEdit_4->text());
        query.bindValue(":idparent",idparent2);
        query.exec();
//        for(int i=1;i<nbretel;i++) {
//            qDebug() << i;
//        query.bindValue(":numtel",tel[i]->text());
//        query.bindValue(":idparent",idparent1);
//        query.exec();
//        }

//        query.bindValue(":numtel",ui->lineEdit->text());
//        query.bindValue(":idparent",idparent2);
//        query.exec();
//        for(int i=1;i<nbretel_2;i++) {
//        query.bindValue(":numtel",tel_2[i]->text());
//        query.bindValue(":idparent",idparent2);
//        query.exec();
//        }
        QString connection;
        connection = db.connectionName();
        db.close();
        db = QSqlDatabase();
        db.removeDatabase(connection);
       ((MainWindow*)parentWidget())->fetchDataToModel();

    }
}
