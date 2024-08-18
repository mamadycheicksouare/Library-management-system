// MAMADY CHEICK SOUARE 20100011002

#ifndef ODUNC_ALMA_H
#define ODUNC_ALMA_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
namespace Ui {
class odunc_alma;
}

class odunc_alma : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_alma(QWidget *parent = nullptr);
    ~odunc_alma();
    void listele();

private slots:
    void on_tableView_tumuyeler_clicked(const QModelIndex &index);

    void on_tableView_tumkitaplar_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::odunc_alma *ui;
    QSqlDatabase almadatabase = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery *almaquery;
    QSqlQueryModel *almamodel;
};

#endif // ODUNC_ALMA_H
