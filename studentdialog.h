#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlError>
QT_BEGIN_NAMESPACE
namespace Ui { class studentDialog; }
QT_END_NAMESPACE

class studentDialog : public QDialog
{
    Q_OBJECT

public:
    studentDialog(QWidget *parent = nullptr);
    ~studentDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_find_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_update_clicked();

private:
    Ui::studentDialog *ui;
    QSqlDatabase sqdbs;//创建数据库原理，提供了一个接口，使得应用程序能够连接到各种不同类型的数据库
    QSqlQuery myquery;
    void  createQsqldata();
    void  createQsquery();
    void  chaxunquery();
};
#endif // STUDENTDIALOG_H
