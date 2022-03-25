#ifndef CONSOLE_H
#define CONSOLE_H

#include <QMainWindow>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "parameters.h"
#include "tools.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Console; }
QT_END_NAMESPACE

class Console : public QMainWindow
{
    Q_OBJECT

public:
    Console(QWidget *parent = nullptr);
    ~Console();

    QString file_path;//文件路径
    int mode_chosen;//当前排序模式
    QVector<QLineEdit*> num_list;//文本框列表
    QVector<int> initial_num;//未排序数据
    QVector<int*> result_list;//每一步结果列表
    long time_spend;//耗费时间
    int steps_num;//步骤数
    int now_step;//当前步骤

private slots://槽函数
    void menu_0_triggered();//直接插入
    void menu_1_triggered();//折半插入
    void menu_2_triggered();//希尔
    void menu_3_triggered();//冒泡
    void menu_4_triggered();//快速
    void menu_5_triggered();//简单选择

    void read_file_toggled();//选择文件模式
    void manual_input_toggled();//手动输入模式

    void choose_file_clicked();//选择文件路径

    void execute_sort_clicked();//执行排序
    void show_result_clicked();//最终结果
    void next_step_clicked();//下一步
    void pre_step_clicked();//上一步
    void reChoose_clicked();//重新输入数据

private:
    Ui::Console *ui;
};
#endif // CONSOLE_H
