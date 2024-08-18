// MAMADY CHEICK SOUARE 20100011002

#include "odunc_alma.h"
#include "ui_odunc_alma.h"

odunc_alma::odunc_alma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::odunc_alma)
{
    ui->setupUi(this);
    almadatabase.setDatabaseName("odev2.db");
    almaquery = new QSqlQuery(almadatabase);
    listele();
}

void odunc_alma::listele()
{
    if(almadatabase.open())
    {
        almaquery = new QSqlQuery(almadatabase);
        almaquery->prepare("select * from kitap");
        almaquery->exec();
        almamodel = new QSqlQueryModel();
        almamodel->setQuery(*almaquery);
        ui->tableView_tumkitaplar->setModel(almamodel);

        almaquery->prepare("select * from uye");
        almaquery->exec();
        almamodel = new QSqlQueryModel();
        almamodel->setQuery(*almaquery);
        ui->tableView_tumuyeler->setModel(almamodel);

        almaquery->prepare("select * from odunc_alinan");
        almaquery->exec();
        almamodel = new QSqlQueryModel();
        almamodel->setQuery(*almaquery);
        ui->tableView_odunclistesi->setModel(almamodel);




    }
}

odunc_alma::~odunc_alma()
{
    if (almadatabase.isOpen())
        {
            almadatabase.close();
        }
    delete ui;
}

void odunc_alma::on_tableView_tumuyeler_clicked(const QModelIndex &index)
{   almaquery = new QSqlQuery(almadatabase);
    almaquery->prepare("select * from uye");
    almaquery->exec();
    almamodel = new QSqlQueryModel();
    almamodel->setQuery(*almaquery);
QString no = almamodel->index(index.row(),0).data().toString();


ui->lineEdit_uyeno->setText(no);



}


void odunc_alma::on_tableView_tumkitaplar_clicked(const QModelIndex &index)
{
    almaquery = new QSqlQuery(almadatabase);
    almaquery->prepare("select * from kitap");
    almaquery->exec();
    almamodel = new QSqlQueryModel();
    almamodel->setQuery(*almaquery);
    QString kno = almamodel->index(index.row(),0).data().toString();

    ui->lineEdit_kitapno->setText(kno);

}


void odunc_alma::on_pushButton_clicked()
{
    if(ui->lineEdit_kitapno->text() =="" || ui->lineEdit_uyeno->text() =="" || ui->dateEdit->text() =="")
    {
        QMessageBox::critical(this," Missing info", "fill the required fields","ok");

    }

    else {
        int uyeno = ui->lineEdit_uyeno->text().toInt();
        int kitapno = ui->lineEdit_kitapno->text().toInt();
        QString tarih = ui->dateEdit->text();
        int stok=0;
        int count;

        almaquery = new QSqlQuery(almadatabase);
        almaquery->prepare("select kitap_sayisi from kitap WHERE kitap_no = ?");
        almaquery->addBindValue(kitapno);
        almaquery->exec();

        if(almaquery->next())
        {
            stok = almaquery->value(0).toInt();
        }

        if(stok < 1)
        {
            QMessageBox::critical(this,"bilgi", "Bu kitap mevcut degildir","ok");
        }

        else {
            almaquery = new QSqlQuery(almadatabase);
            almaquery->prepare("select COUNT(*) from odunc_alinan WHERE kitap_no = ? and uye_no =?");
            almaquery->addBindValue(kitapno);
            almaquery->addBindValue(uyeno);
            almaquery->exec();

            if(almaquery->next())
            {
                count = almaquery->value(0).toInt();
            }

            if (count > 0)
            {
                QMessageBox::critical(this,"bilgi", "Bu uyeye bu kitap oduncu var zaten bir daha alamaz!","ok");
            }

            else {
                almaquery = new QSqlQuery(almadatabase);
                almaquery->prepare("insert into odunc_alinan(uye_no,kitap_no,odunc_alma_tarihi) values(?,?,?)");
                almaquery->addBindValue(uyeno);
                almaquery->addBindValue(kitapno);
                almaquery->addBindValue(tarih);
                almaquery->exec();

                almaquery->prepare("UPDATE kitap SET kitap_sayisi =? WHERE kitap_no = ?");
                almaquery->addBindValue(stok-1);
                almaquery->addBindValue(kitapno);
                almaquery->exec();

                listele();



                QMessageBox::information(this,"bilgi", "Odunc alma islemi basariyla tamamlandi!","ok");
            }
        }



    }
}

