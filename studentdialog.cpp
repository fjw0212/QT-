#include "studentdialog.h"
#include "ui_studentdialog.h"
#include<QMessageBox>
studentDialog::studentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::studentDialog)
{
    ui->setupUi(this);
    createQsqldata();
    createQsquery();//创建表
    ui->comboBoxvalue->addItem("id");
    ui->comboBoxvalue->addItem("name");
    ui->comboBoxvalue->addItem("score");
    ui->comboBox_con->addItem("up");
    ui->comboBox_con->addItem("down");
}

studentDialog::~studentDialog()
{
    delete ui;
    sqdbs.close();
}
void  studentDialog::createQsqldata()
{
    sqdbs= QSqlDatabase::addDatabase("QSQLITE");//数据库创建
    sqdbs.setDatabaseName("studentmis.db");//设置数据库名称
    if(sqdbs.open()==true)
    {
    QMessageBox::information(0," success "," open success!!",QMessageBox::Ok);
    }
    else{
    QMessageBox::critical(0," failed "," open failed!!",QMessageBox::Ok);
    }

}
void  studentDialog::createQsquery()
{
    QSqlQuery tempquery;
    QString qstr=QString("CREATE TABLE IF NOT EXISTS student (id INT PRIMARY KEY, name TEXT not null, score INT )");
    if(tempquery.exec(qstr)==true)
    {
        QMessageBox::information(0,"  query success "," query success!!",QMessageBox::Ok);
    }
    else{
         QMessageBox::critical(0," query failed "," query failed!!",QMessageBox::Ok);
    }

}
void  studentDialog::chaxunquery()
{

}

void studentDialog::on_pushButton_clicked()
{
    //排序
    // 准备 SELECT 查询，按照 "name" 列升序排序
       QSqlQuery query;

       // 绑定参数
       QString val = ui->comboBoxvalue->currentText();
       QString con=  ui->comboBox_con->currentText();//选择升序 (ASC) 或降序 (DESC) 排序

       if(con=='up')
       {
           con="ASC";
       }else{con="DESC";}

        query.prepare(QString("SELECT * FROM student ORDER BY %1 %2").arg(val).arg(con));
       // 执行查询
       if (query.exec()) {
           QMessageBox::information(0,"  query  order success "," query success!!",QMessageBox::Ok);
           // 执行查询
            QSqlQueryModel *model = new QSqlQueryModel;//模型-视图体系结构
            model->setQuery("SELECT * FROM student");//查询结果集中的数据会被 QSqlQueryModel 存储起来，查询结果集中的数据会被 QSqlQueryModel 存储起来，
           model->clear();
           model->setQuery(query);
            // 创建表视图并设置模型

            ui->tableView->setModel(model);

            // 显示表视图
            ui->tableView->show();
       } else {
           QMessageBox::critical(0," query order failed "," query  order failed!!",QMessageBox::Ok);
       }

}


void studentDialog::on_pushButton_find_clicked()
{
    // 准备 SELECT 查询
        QSqlQuery query;
        query.prepare("SELECT * FROM student WHERE id = :mid OR name = :mname ");

        // 绑定参数
        int mid = ui->lineEdit_id->text().toInt();
        QString mname=  ui->lineEdit_name->text();
        query.bindValue(":mid", mid);
        query.bindValue(":mname", mname);

        // 执行查询
        if (query.exec()) {
            // 遍历查询结果
            while (query.next())//循环遍历结果
            {
                // 获取当前行的数据
                int id = query.value("id").toInt();

                ui->lineEdit_id->setText(QString::number(id));
                QString name = query.value("name").toString();
                ui->lineEdit_name->setText(name);

                int score = query.value("score").toInt();
                ui->lineEdit_score->setText(QString::number(score));

                           }
        } else {
             QMessageBox::critical(0," query  find failed "," query find failed!!",QMessageBox::Ok);
        }
}


void studentDialog::on_pushButton_delete_clicked()
{
    //
    // 准备 DELETE 查询
        QSqlQuery query;
        query.prepare("DELETE FROM student WHERE id = :id OR name = :mname");

        // 绑定参数
        int mid = ui->lineEdit_id->text().toInt();
        QString mname=  ui->lineEdit_name->text();
        query.bindValue(":mid", mid);
        query.bindValue(":mname", mname);

        // 执行查询
        if (query.exec()) {
            QMessageBox::information(0,"  query delete success "," query delete success!!",QMessageBox::Ok);
        } else {
           QMessageBox::critical(0," query  delete failed "," query delete failed!!",QMessageBox::Ok);
        }
}


void studentDialog::on_pushButton_insert_clicked()
{
//获取id  name score 信息
    int currid=ui->lineEdit_id->text().toInt();
    QString currname=ui->lineEdit_name->text();
    double currscore=ui->lineEdit_score->text().toDouble();
    //加入到数据表中去
    QSqlQuery tempquery;
    QString qstr=QString("insert into student (id , name , score )values(%1,'%2',%3)").arg(currid).arg(currname).arg(currscore);
    //执行操作
    if(tempquery.exec(qstr)==true)
    {
        QMessageBox::information(0,"  query insert success "," query insert success!!",QMessageBox::Ok);
    }
    else{
         QMessageBox::critical(0," query  insert failed "," query insert failed!!",QMessageBox::Ok);
    }
}


void studentDialog::on_pushButton_update_clicked()
{
       // 执行查询
        QSqlQueryModel *model = new QSqlQueryModel;//模型-视图体系结构
        model->setQuery("SELECT * FROM student");//查询结果集中的数据会被 QSqlQueryModel 存储起来，查询结果集中的数据会被 QSqlQueryModel 存储起来，

        // 创建表视图并设置模型

        ui->tableView->setModel(model);

        // 显示表视图
        ui->tableView->show();
}

