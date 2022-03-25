#ifndef CONSOLE_H
#define CONSOLE_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include "lnode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Console; }
QT_END_NAMESPACE

class Console : public QMainWindow
{
    Q_OBJECT

public:
    Console(QWidget *parent = nullptr);
    ~Console();

    int node_num;//人数
    int rand_num;//随机数
    int out_num;
    QTimer *timer;//计时器
    QVector<QPushButton*> node_but_list;//按钮列表
    QVector<QLabel*> out_list;//出列标签列表

    LNode* first_node;//首个节点

private slots:
    void num_confirm_clicked();//确认人数
    void num_reset_clicked();//重置
    void gen_rand_clicked();//摇骰子
    void num_but_clicked();//点击按钮选择开始人
    void update_time();//按照计时器进行游戏

private:
    Ui::Console *ui;
};
#endif // CONSOLE_H
