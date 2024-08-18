// MAMADY CHEICK SOUARE 20100011002

#include "kitap.h"
#include "ui_kitap.h"

kitap::kitap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kitap)
{
    ui->setupUi(this);
    kitapdatabase.setDatabaseName("odev2.db");
    kitapquery = new QSqlQuery(kitapdatabase);
    listele();
}

kitap::~kitap()
{
    if (kitapdatabase.isOpen())
        {
            kitapdatabase.close();
        }
    delete ui;
}

void kitap::listele()
{


    if(kitapdatabase.open())
    {
        kitapquery = new QSqlQuery(kitapdatabase);
        kitapquery->prepare("select * from kitap");
        kitapquery->exec();
        kitapmodel = new QSqlQueryModel();
        kitapmodel->setQuery(*kitapquery);
        ui->tableView_tumkitap->setModel(kitapmodel);

    }
}


void kitap::on_tableView_tumkitap_clicked(const QModelIndex &index)
{
    kitapquery = new QSqlQuery(kitapdatabase);
               kitapquery->prepare("select * from kitap");
               kitapquery->exec();
               kitapmodel = new QSqlQueryModel();
               kitapmodel->setQuery(*kitapquery);
        QString no = kitapmodel->index(index.row(),0).data().toString();
        QString ad = kitapmodel->index(index.row(),1).data().toString();
        QString stok = kitapmodel->index(index.row(),2).data().toString();

        ui->lineEdit_no->setText(no);
        ui->lineEdit_ad->setText(ad);
        ui->lineEdit_stok->setText(stok);


        int kitap_no = ui->lineEdit_no->text().toInt();

        kitapquery->prepare("select * from odunc_alinan WHERE kitap_no = ?");
        kitapquery->addBindValue(kitap_no);
        kitapquery->exec();
        kitapmodel = new QSqlQueryModel();
        kitapmodel->setQuery(*kitapquery);
        ui->tableView_alinma->setModel(kitapmodel);


        kitapquery->prepare("select * from odunc_teslim_edilen WHERE kitap_no = ?");
        kitapquery->addBindValue(kitap_no);
        kitapquery->exec();
        kitapmodel = new QSqlQueryModel();
        kitapmodel->setQuery(*kitapquery);
        ui->tableView_oncealinma->setModel(kitapmodel);
}


void kitap::on_pushButton_kayit_clicked()
{
    if(ui->lineEdit_ad->text() == "" || ui->lineEdit_stok->text() == "")
    {
        QMessageBox::critical(this,"Missing info", "fill the required fields","ok");

    }

    else {
        QString ad;
        ad = ui->lineEdit_ad->text();
        int stok = ui->lineEdit_stok->text().toInt();
        kitapquery = new QSqlQuery(kitapdatabase);
        kitapquery->prepare("insert into kitap(kitap_ad,kitap_sayisi) values(?,?)");
        kitapquery->addBindValue(ad);
        kitapquery->addBindValue(stok);
        kitapquery->exec();

        listele();

        QMessageBox::information(this,"info","Kitap basariyla eklendi!","ok");
    }

    listele();
}


void kitap::on_pushButton_guncelle_clicked()
{
    if(ui->lineEdit_ad->text() == "" || ui->lineEdit_stok->text() == "" || ui->lineEdit_no->text() == "")
    {
        QMessageBox::critical(this,"Eksik bilgi", "Gerekli alanlari doldurunuz","ok");

    }

    else {
        kitapquery = new QSqlQuery(kitapdatabase);
        QString ad;

        int no = ui->lineEdit_no->text().toInt();

        ad = ui->lineEdit_ad->text();
        int stok  = ui->lineEdit_stok->text().toInt();
        kitapquery->prepare("UPDATE kitap SET kitap_ad =?,kitap_sayisi =? WHERE kitap_no = ?");
        kitapquery->addBindValue(ad);
        kitapquery->addBindValue(stok);
        kitapquery->addBindValue(no);
        kitapquery->exec();

        listele();

        QMessageBox::information(this,"info","Kitabin bilgileri basariyla guncellendi!","ok");
    }
}


void kitap::on_pushButton_sil_clicked()
{
    if(ui->lineEdit_ad->text() == "" || ui->lineEdit_stok->text() == "" || ui->lineEdit_no->text() == "")
    {
        QMessageBox::critical(this,"Eksik bilgi", "Gerekli alanlari doldurunuz","ok");

    }

    else {
        int no = ui->lineEdit_no->text().toInt();
         int count =0;

        kitapquery->prepare("SELECT COUNT(*) from odunc_alinan WHERE kitap_no = ?");
        kitapquery->addBindValue(no);
        kitapquery->exec();

        if(kitapquery->next())
        {
            count = kitapquery->value(0).toInt();

        }

        if(count > 0)
        {
            QMessageBox::information(this,"info","Bu kitap silinemez odunc verilmistir!","ok");
        }

        else {
            kitapquery->prepare("DELETE from kitap WHERE kitap_no = ?");
            kitapquery->addBindValue(no);
            kitapquery->exec();
            QMessageBox::information(this,"info","Kitap basariyla silindi!","ok");
        }
        listele();

        ui->lineEdit_ad->clear();
        ui->lineEdit_no->clear();
        ui->lineEdit_stok->clear();



    }
}

