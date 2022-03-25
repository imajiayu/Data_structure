#include "console.h"
#include "ui_console.h"

Console::Console(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Console)
{
    ui->setupUi(this);
    this->setFixedSize(400,260);
    this->setWindowTitle("Sortor");
    //将显示数据的文本框加入向量，方便操作
    num_list.append(ui->num0);
    num_list.append(ui->num1);
    num_list.append(ui->num2);
    num_list.append(ui->num3);
    num_list.append(ui->num4);
    num_list.append(ui->num5);
    num_list.append(ui->num6);
    num_list.append(ui->num7);
    num_list.append(ui->num8);
    num_list.append(ui->num9);
    num_list.append(ui->num10);
    num_list.append(ui->num11);
    num_list.append(ui->num12);
    for(int i=0;i<num_list.size();i++)
    {
        num_list.at(i)->setEnabled(false);
    }
    //绑定按钮与槽函数
    connect(ui->choose_file,SIGNAL(clicked()),this,SLOT(choose_file_clicked()));

    connect(ui->action_direct_insert,SIGNAL(triggered()), this, SLOT(menu_0_triggered()));
    connect(ui->action_half_insert,SIGNAL(triggered()), this, SLOT(menu_1_triggered()));
    connect(ui->action_shell,SIGNAL(triggered()), this, SLOT(menu_2_triggered()));
    connect(ui->action_bubble,SIGNAL(triggered()), this, SLOT(menu_3_triggered()));
    connect(ui->action_quick,SIGNAL(triggered()), this, SLOT(menu_4_triggered()));
    connect(ui->action_easy_choose,SIGNAL(triggered()), this, SLOT(menu_5_triggered()));

    connect(ui->read_file,SIGNAL(clicked()),this,SLOT(read_file_toggled()));
    connect(ui->manual_input,SIGNAL(clicked()),this,SLOT(manual_input_toggled()));
    ui->choose_file->setEnabled(false);
    ui->file_path->clear();

    connect(ui->execute_sort,SIGNAL(clicked()),this,SLOT(execute_sort_clicked()));
    connect(ui->show_result,SIGNAL(clicked()),this,SLOT(show_result_clicked()));
    connect(ui->next_step,SIGNAL(clicked()),this,SLOT(next_step_clicked()));
    connect(ui->pre_step,SIGNAL(clicked()),this,SLOT(pre_step_clicked()));
    connect(ui->reChoose,SIGNAL(clicked()),this,SLOT(reChoose_clicked()));
    //初始化变量
    mode_chosen=DIRECT_INSERT;
    ui->mode_chosen->setText(QString("直接插入排序"));

    initial_num.clear();
    result_list.clear();
    time_spend=0;
    steps_num=0;
    now_step=0;
    ui->step_num->clear();
    ui->time_spend->clear();
    ui->now_step->clear();

    ui->reChoose->setEnabled(false);
    ui->show_result->setEnabled(false);
    ui->next_step->setEnabled(false);
    ui->pre_step->setEnabled(false);
}

Console::~Console()
{
    delete ui;
}

void Console::menu_0_triggered()//选择直接插入排序模式
{
    mode_chosen=DIRECT_INSERT;
    ui->mode_chosen->setText(QString("直接插入排序"));
    steps_num=0;
    now_step=0;
    result_list.clear();
    for(int i=0;i<initial_num.size();i++)
        num_list.at(i)->setText(QString::number(initial_num.at(i)));
    ui->execute_sort->setEnabled(true);
    ui->show_result->setEnabled(false);
    ui->next_step->setEnabled(false);
    ui->pre_step->setEnabled(false);
    ui->time_spend->setText("");
    ui->step_num->setText("");
    ui->now_step->setText("");
}

void Console::menu_1_triggered()//选择折半插入排序模式
{
    mode_chosen=HALF_INSERT;
    ui->mode_chosen->setText(QString("折半插入排序"));
    steps_num=0;
    now_step=0;
    result_list.clear();
    for(int i=0;i<initial_num.size();i++)
        num_list.at(i)->setText(QString::number(initial_num.at(i)));
    ui->execute_sort->setEnabled(true);
    ui->show_result->setEnabled(false);
    ui->next_step->setEnabled(false);
    ui->pre_step->setEnabled(false);
    ui->time_spend->setText("");
    ui->step_num->setText("");
    ui->now_step->setText("");
}

void Console::menu_2_triggered()//选择希尔排序模式
{
    mode_chosen=SHELL;
    ui->mode_chosen->setText(QString("希尔排序(5、3、1)"));
    steps_num=0;
    now_step=0;
    result_list.clear();
    for(int i=0;i<initial_num.size();i++)
        num_list.at(i)->setText(QString::number(initial_num.at(i)));
    ui->execute_sort->setEnabled(true);
    ui->show_result->setEnabled(false);
    ui->next_step->setEnabled(false);
    ui->pre_step->setEnabled(false);
    ui->time_spend->setText("");
    ui->step_num->setText("");
    ui->now_step->setText("");
}

void Console::menu_3_triggered()//选择冒泡排序模式
{
    mode_chosen=BUBBLE;
    ui->mode_chosen->setText(QString("冒泡排序"));
    steps_num=0;
    now_step=0;
    result_list.clear();
    for(int i=0;i<initial_num.size();i++)
        num_list.at(i)->setText(QString::number(initial_num.at(i)));
    ui->execute_sort->setEnabled(true);
    ui->show_result->setEnabled(false);
    ui->next_step->setEnabled(false);
    ui->pre_step->setEnabled(false);
    ui->time_spend->setText("");
    ui->step_num->setText("");
    ui->now_step->setText("");
}

void Console::menu_4_triggered()//选择快速排序模式
{
    mode_chosen=QUICK;
    ui->mode_chosen->setText(QString("快速排序"));
    steps_num=0;
    now_step=0;
    result_list.clear();
    for(int i=0;i<initial_num.size();i++)
        num_list.at(i)->setText(QString::number(initial_num.at(i)));
    ui->execute_sort->setEnabled(true);
    ui->show_result->setEnabled(false);
    ui->next_step->setEnabled(false);
    ui->pre_step->setEnabled(false);
    ui->time_spend->setText("");
    ui->step_num->setText("");
    ui->now_step->setText("");
}

void Console::menu_5_triggered()//选择简单排序模式
{
    mode_chosen=EASY_CHOOSE;
    ui->mode_chosen->setText(QString("简单选择排序"));
    steps_num=0;
    now_step=0;
    result_list.clear();
    for(int i=0;i<initial_num.size();i++)
        num_list.at(i)->setText(QString::number(initial_num.at(i)));
    ui->execute_sort->setEnabled(true);
    ui->show_result->setEnabled(false);
    ui->next_step->setEnabled(false);
    ui->pre_step->setEnabled(false);
    ui->time_spend->setText("");
    ui->step_num->setText("");
    ui->now_step->setText("");
}

void Console::read_file_toggled()//选择读取文件
{
    ui->choose_file->setEnabled(true);
    for(int i=0;i<num_list.size();i++)
    {
        num_list.at(i)->setEnabled(false);
    }
}

void Console::manual_input_toggled()//选择手动输入
{
    ui->choose_file->setEnabled(false);
    file_path.clear();
    ui->file_path->clear();
    for(int i=0;i<num_list.size();i++)
    {
        num_list.at(i)->setEnabled(true);
    }
}

void Console::choose_file_clicked()//选择文件，并将数据读入
{
    file_path.clear();
    ui->file_path->setText("");

    initial_num.clear();
    for(int i=0;i<13;i++)
    {
        num_list.at(i)->setText("");
    }

    file_path = QFileDialog::getOpenFileName(this,"选择数据文件","./*.txt");//打开选择文件对话框，选择txt文件
    ui->file_path->setText(file_path);

    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString line = in.readLine();
    QStringList list=line.split(" ");//数据以空格分隔
    for(int j=0;j<13;j++)
    {
        if(j<list.size())
        {
            initial_num.append(list.at(j).toInt());
            num_list.at(j)->setText(QString::number(initial_num.at(j)));//读入数字并显示
        }
        else
            num_list.at(j)->setText("");
        num_list.at(j)->setEnabled(false);
    }
}

void Console::execute_sort_clicked()//执行排序
{
    if(!ui->read_file->isChecked()&&!ui->manual_input->isChecked())
    {
        QMessageBox::information(NULL, QString("提示"), QString("请选择输入数据方式"), QMessageBox::Yes);
        return;
    }
    if(ui->read_file->isChecked()&&this->file_path=="")
    {
        QMessageBox::information(NULL, QString("提示"), QString("尚未选择文件"), QMessageBox::Yes);
        return;
    }
    if(ui->manual_input->isChecked())
    {
        for(int i=0;i<13;i++)
        {
            if(num_list.at(i)->text()!="")
                initial_num.append(num_list.at(i)->text().toInt());
        }
        if(initial_num.size()==0)
        {
            QMessageBox::information(NULL, QString("提示"), QString("尚未输入数据"), QMessageBox::Yes);
            return;
        }
        for(int j=0;j<13;j++)
        {
            if(j<initial_num.size())
                num_list.at(j)->setText(QString::number(initial_num.at(j)));
            else
                num_list.at(j)->setText("");
            num_list.at(j)->setEnabled(false);
        }
    }

    ui->read_file->setEnabled(false);
    ui->manual_input->setEnabled(false);
    ui->execute_sort->setEnabled(false);

    timespec start_time,end_time;
    clock_gettime(CLOCK_REALTIME, &start_time);//开始计时
    switch (mode_chosen)//根据选择的模式进行排序
    {
        case 0:
            steps_num=direct_insert(initial_num,result_list);
            break;
        case 1:
            steps_num=half_insert(initial_num,result_list);
            break;
        case 2:
            steps_num=shell_sort(initial_num,result_list);
            break;
        case 3:
            steps_num=bubble_sort(initial_num,result_list);
            break;
        case 4:
            steps_num=quick_sort(initial_num,result_list);
            break;
        case 5:
            steps_num=easy_choose(initial_num,result_list);
            break;
    }

    clock_gettime(CLOCK_REALTIME, &end_time);
    time_spend=end_time.tv_nsec-start_time.tv_nsec;//结束计时

    ui->time_spend->setText(QString::number(time_spend,10));
    ui->step_num->setText(QString::number(steps_num));
    ui->now_step->setText(QString::number(now_step));

    ui->reChoose->setEnabled(true);
    ui->show_result->setEnabled(true);
    ui->next_step->setEnabled(true);
    ui->pre_step->setEnabled(false);

    if(now_step==steps_num)
    {
        ui->show_result->setEnabled(false);
        ui->next_step->setEnabled(false);
        ui->pre_step->setEnabled(false);
    }
}

void Console::show_result_clicked()//直接展示最终结果
{
    ui->pre_step->setEnabled(true);
    for(int i=0;i<initial_num.size();i++)
    {
        num_list.at(i)->setText(QString::number(result_list.at(steps_num)[i]));
    }
    now_step=steps_num;
    ui->now_step->setText(QString::number(now_step));
    ui->show_result->setEnabled(false);
    ui->next_step->setEnabled(false);
}

void Console::next_step_clicked()//下一步
{
    ui->pre_step->setEnabled(true);
    now_step++;
    if(now_step==steps_num)
    {
        ui->show_result->setEnabled(false);
        ui->next_step->setEnabled(false);
    }
    ui->now_step->setText(QString::number(now_step));

    for(int i=0;i<initial_num.size();i++)
    {
        num_list.at(i)->setText(QString::number(result_list.at(now_step)[i]));
    }
}

void Console::pre_step_clicked()//上一步
{
    ui->next_step->setEnabled(true);
    ui->show_result->setEnabled(true);
    now_step--;
    if(now_step==0)
    {
        ui->pre_step->setEnabled(false);
    }
    ui->now_step->setText(QString::number(now_step));

    for(int i=0;i<initial_num.size();i++)
    {
        num_list.at(i)->setText(QString::number(result_list.at(now_step)[i]));
    }
}

void Console::reChoose_clicked()//初始化，重新选择
{
    ui->read_file->setEnabled(true);
    ui->manual_input->setEnabled(true);

    ui->execute_sort->setEnabled(true);
    ui->reChoose->setEnabled(false);
    ui->show_result->setEnabled(false);
    ui->next_step->setEnabled(false);
    ui->pre_step->setEnabled(false);

    initial_num.clear();
    result_list.clear();
    time_spend=0;
    steps_num=0;
    now_step=0;
    this->file_path.clear();
    ui->file_path->clear();
    ui->step_num->clear();
    ui->time_spend->clear();
    ui->now_step->clear();

    for(int i=0;i<13;i++)
    {
        num_list.at(i)->setText("");
        if(ui->manual_input->isChecked())
            num_list.at(i)->setEnabled(true);
    }
}
