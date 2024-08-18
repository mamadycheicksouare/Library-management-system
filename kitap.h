// MAMADY CHEICK SOUARE 20100011002

#ifndef KITAP_H
#define KITAP_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
namespace Ui {
class kitap;
}

class kitap : public QDialog
{
    Q_OBJECT

public:
    explicit kitap(QWidget *parent = nullptr);
    ~kitap();
    void listele();

private slots:
    void on_tableView_tumkitap_clicked(const QModelIndex &index);

    void on_pushButton_kayit_clicked();

    void on_pushButton_guncelle_clicked();

    void on_pushButton_sil_clicked();

private:
    Ui::kitap *ui;
    QSqlDatabase kitapdatabase = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery *kitapquery;
    QSqlQueryModel *kitapmodel;
};

#endif // KITAP_H
