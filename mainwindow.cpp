// MAMADY CHEICK SOUARE 20100011002

/*

                   NOT : Veri taban adi Odev2.db olarak belirlenmistir
            uye, kitap, odunc_alinan, odunc_teslim_edilen ise tablolarin adi

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <uye.h>
#include <kitap.h>
#include <odunc_alma.h>
#include <odunc_teslim.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database.setDatabaseName("odev2.db");

    if(!database.open())
    {
        ui->statusbar->showMessage("Not Connected to the database!");
        return;
    }

    else {
        ui->statusbar->showMessage("Connected to the database!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_uye_clicked()
{
    uye *uyepencere = new uye();
    uyepencere->show();

}


void MainWindow::on_pushButton_kitap_clicked()
{
    kitap *kitappencere = new kitap();
    kitappencere->show();
}


void MainWindow::on_pushButton_alinan_clicked()
{
    odunc_alma *odunc_almapencere = new odunc_alma();
    odunc_almapencere->show();
}


void MainWindow::on_pushButton_teslim_clicked()
{
    odunc_teslim *odunc_teslimpencere = new odunc_teslim();
    odunc_teslimpencere->show();
}

