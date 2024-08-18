// MAMADY CHEICK SOUARE 20100011002

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_uye_clicked();

    void on_pushButton_kitap_clicked();

    void on_pushButton_alinan_clicked();

    void on_pushButton_teslim_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
};
#endif // MAINWINDOW_H
