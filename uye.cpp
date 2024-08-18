// MAMADY CHEICK SOUARE 20100011002

#include "uye.h"
#include "ui_uye.h"

uye::uye(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uye)
{
    ui->setupUi(this);
uyedatabase.setDatabaseName("odev2.db");
    listele();
}


uye::~uye()
{
    if (uyedatabase.isOpen())
        {
            uyedatabase.close();
        }
    delete ui;
}
void uye::listele()
{


    if(uyedatabase.open())
    {
        uyequery = new QSqlQuery(uyedatabase);
        uyequery->prepare("select * from uye");
        uyequery->exec();
        uyemodel = new QSqlQueryModel();
        uyemodel->setQuery(*uyequery);
        ui->tableView->setModel(uyemodel);
    }
}


void uye::on_pushButton_kayt_clicked()
{
    if(ui->lineEdit_ad->text() == "" || ui->lineEdit_soyad->text() == "" )
    {
        QMessageBox::critical(this,"Missing info", "fill the required fields","ok");

    }

    else {
        QString ad,soyad;
        ad = ui->lineEdit_ad->text();
        soyad = ui->lineEdit_soyad->text();
        uyequery->prepare("insert into uye(uye_ad,uye_soyad) values(?,?)");
        uyequery->addBindValue(ad);
        uyequery->addBindValue(soyad);
        uyequery->exec();

        listele();

        QMessageBox::information(this,"info","Uye basariyla eklendi!","ok");
    }

}


void uye::on_tableView_clicked(const QModelIndex &index)
{          uyequery = new QSqlQuery(uyedatabase);
           uyequery->prepare("select * from uye");
           uyequery->exec();
           uyemodel = new QSqlQueryModel();
           uyemodel->setQuery(*uyequery);
    QString no = uyemodel->index(index.row(),0).data().toString();
    QString ad = uyemodel->index(index.row(),1).data().toString();
    QString soyad = uyemodel->index(index.row(),2).data().toString();

    ui->lineEdit_no->setText(no);
    ui->lineEdit_ad->setText(ad);
    ui->lineEdit_soyad->setText(soyad);
}


void uye::on_pushButton_guncelle_clicked()
{
    if(ui->lineEdit_ad->text() == "" || ui->lineEdit_soyad->text() == "" || ui->lineEdit_no->text() == "")
    {
        QMessageBox::critical(this,"Eksik bilgi", "Gerekli alanlari doldurunuz","ok");

    }

    else {
        QString ad,soyad;

        int no = ui->lineEdit_no->text().toInt();

        ad = ui->lineEdit_ad->text();
        soyad = ui->lineEdit_soyad->text();
        uyequery->prepare("UPDATE uye SET uye_ad =?,uye_soyad =? WHERE uye_no = ?");
        uyequery->addBindValue(ad);
        uyequery->addBindValue(soyad);
        uyequery->addBindValue(no);
        uyequery->exec();

        listele();

        QMessageBox::information(this,"info","Uyenin bilgileri basariyla guncellendi!","ok");
    }
}


void uye::on_pushButton_sil_clicked()
{
    if(ui->lineEdit_ad->text() == "" || ui->lineEdit_soyad->text() == "" || ui->lineEdit_no->text() == "")
    {
        QMessageBox::critical(this,"Eksik bilgi", "Gerekli alanlari doldurunuz","ok");

    }

    else {
        int no = ui->lineEdit_no->text().toInt();
         int count =0;

        uyequery->prepare("SELECT COUNT(*) from odunc_alinan WHERE uye_no = ?");
        uyequery->addBindValue(no);
        uyequery->exec();

        if(uyequery->next())
        {
            count = uyequery->value(0).toInt();

        }

        if(count > 0)
        {
            QMessageBox::information(this,"info","Bu uye silinemez teslim etmedigi kitaplar var!","ok");
        }

        else {
            uyequery->prepare("DELETE from uye WHERE uye_no = ?");
            uyequery->addBindValue(no);
            uyequery->exec();
            QMessageBox::information(this,"info","This User was deleted!","ok");
        }
        listele();

        ui->lineEdit_ad->clear();
        ui->lineEdit_no->clear();
        ui->lineEdit_soyad->clear();



    }

}

