// MAMADY CHEICK SOUARE 20100011002

#ifndef UYE_H
#define UYE_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
namespace Ui {
class uye;
}

class uye : public QDialog
{
    Q_OBJECT

public:
    explicit uye(QWidget *parent = nullptr);
    ~uye();
    void listele();



private slots:
    void on_pushButton_kayt_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_guncelle_clicked();

    void on_pushButton_sil_clicked();

private:
    Ui::uye *ui;

    QSqlDatabase uyedatabase = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery *uyequery;
    QSqlQueryModel *uyemodel;
};

#endif // UYE_H
