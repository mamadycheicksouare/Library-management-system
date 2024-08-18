// MAMADY CHEICK SOUARE 20100011002

#ifndef ODUNC_TESLIM_H
#define ODUNC_TESLIM_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
namespace Ui {
class odunc_teslim;
}

class odunc_teslim : public QDialog
{
    Q_OBJECT

public:
    explicit odunc_teslim(QWidget *parent = nullptr);
    ~odunc_teslim();
    void listele();

private slots:
    void on_tableView_alinan_clicked(const QModelIndex &index);

    void on_oduncver_clicked();

private:
    Ui::odunc_teslim *ui;
    QSqlDatabase teslimdatabase = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery *teslimquery;
    QSqlQueryModel *teslimmodel;
};

#endif // ODUNC_TESLIM_H
