// MAMADY CHEICK SOUARE 20100011002

#include "odunc_teslim.h"
#include "ui_odunc_teslim.h"

QString alma_tarihi;
odunc_teslim::odunc_teslim(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::odunc_teslim)
{
    ui->setupUi(this);
    teslimdatabase.setDatabaseName("odev2.db");
    teslimquery = new QSqlQuery(teslimdatabase);
    listele();
}

void odunc_teslim::listele(){

    if(teslimdatabase.open())
    {
        teslimquery = new QSqlQuery(teslimdatabase);
        teslimquery->prepare("select * from odunc_alinan");
        teslimquery->exec();
        teslimmodel = new QSqlQueryModel();
        teslimmodel->setQuery(*teslimquery);
        ui->tableView_alinan->setModel(teslimmodel);

        teslimquery->prepare("select * from odunc_teslim_edilen");
        teslimquery->exec();
        teslimmodel = new QSqlQueryModel();
        teslimmodel->setQuery(*teslimquery);
        ui->tableView_teslim->setModel(teslimmodel);


    }
}

odunc_teslim::~odunc_teslim()
{   if (teslimdatabase.isOpen())
    {
        teslimdatabase.close();
    }
    delete ui;
}

void odunc_teslim::on_tableView_alinan_clicked(const QModelIndex &index)
{
        teslimquery = new QSqlQuery(teslimdatabase);
        teslimquery->prepare("select * from odunc_alinan");
        teslimquery->exec();
        teslimmodel = new QSqlQueryModel();
        teslimmodel->setQuery(*teslimquery);
    QString uyeno = teslimmodel->index(index.row(),0).data().toString();
    QString kitapno = teslimmodel->index(index.row(),1).data().toString();
    alma_tarihi = teslimmodel->index(index.row(),2).data().toString();

    ui->lineEdit_uyeno->setText(uyeno);
    ui->lineEdit_kitapno->setText(kitapno);


}


void odunc_teslim::on_oduncver_clicked()
{
    if(ui->lineEdit_kitapno->text() =="" || ui->lineEdit_uyeno->text() =="" || ui->dateEdit->text() =="")
    {
        QMessageBox::critical(this,"Missing info", "fill the required fields","ok");

    }

    else {
         int uyeno =ui->lineEdit_uyeno->text().toInt();
         int kitapno = ui->lineEdit_kitapno->text().toInt();
         int stok;
         int borc =0;
         QString tarih = ui->dateEdit->text();

         teslimquery = new QSqlQuery(teslimdatabase);
         teslimquery->prepare("insert into odunc_teslim_edilen(uye_no,kitap_no,alma_tarihi,verme_tarihi,borc) values(?,?,?,?,?)");
         teslimquery->addBindValue(uyeno);
         teslimquery->addBindValue(kitapno);
         teslimquery->addBindValue(alma_tarihi);
         teslimquery->addBindValue(tarih);

         QDate date1 = QDate::fromString(alma_tarihi, "dd/MM/yyyy");
         QDate date2 = QDate::fromString(tarih, "dd/MM/yyyy");

         int gunsayisi = date1.daysTo(date2);

         if(gunsayisi > 15)
         {
             borc = 2 * (gunsayisi-15);
         }

         teslimquery->addBindValue(borc);
         teslimquery->exec();

         teslimquery->prepare("DELETE from odunc_alinan WHERE kitap_no = ? and uye_no =?");
         teslimquery->addBindValue(kitapno);
         teslimquery->addBindValue(uyeno);
         teslimquery->exec();

         teslimquery->prepare("select kitap_sayisi from kitap WHERE kitap_no = ?");
         teslimquery->addBindValue(kitapno);
         teslimquery->exec();

         if(teslimquery->next())
         {
             stok = teslimquery->value(0).toInt();
         }

         teslimquery->prepare("UPDATE kitap SET kitap_sayisi =? WHERE kitap_no = ?");
         teslimquery->addBindValue(stok+1);
         teslimquery->addBindValue(kitapno);
         teslimquery->exec();

         listele();



         QMessageBox::information(this,"bilgi", "Odunc teslim etme islemi basariyla tamamlandi!","ok");
    }
}

