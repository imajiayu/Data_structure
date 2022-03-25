#include "console.h"
#include "ui_console.h"

const int but_layout[15][16]={
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
    {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0},
    {1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0},
    {1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0},
    {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
    {1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1},
    {1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};//当选择人数不同时，按钮的排布方式

Console::Console(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Console)
{
    ui->setupUi(this);
    this->setFixedSize(380,340);
    this->setWindowTitle(QString("Joseph Ring"));
    //绑定每个人按钮，并且放入vector中
    for(int i=0;i<16;i++)
    {
        QString temp="node_"+QString::number(i);
        node_but_list.append(this->findChild<QPushButton*>(temp));
        node_but_list.at(i)->setVisible(false);
        node_but_list.at(i)->setText("");
        connect(node_but_list.at(i),SIGNAL(clicked()),this,SLOT(num_but_clicked()));
        temp="out_"+QString::number(i);
        out_list.append(this->findChild<QLabel*>(temp));
        out_list.at(i)->setText("");
    }
    //绑定按钮与槽函数
    connect(ui->num_confirm,SIGNAL(clicked()),this,SLOT(num_confirm_clicked()));
    connect(ui->num_reset,SIGNAL(clicked()),this,SLOT(num_reset_clicked()));
    connect(ui->gen_rand,SIGNAL(clicked()),this,SLOT(gen_rand_clicked()));
    //初始化变量
    timer=new QTimer;
    qsrand(QTime::currentTime().msec());
    connect(timer,SIGNAL(timeout()),this,SLOT(update_time()));

    ui->gen_rand->setVisible(false);
    ui->rand_num->setVisible(false);
    ui->rand_num->setText("");
    ui->out->setVisible(false);
    ui->num_reset->setEnabled(false);
    ui->tip->setVisible(false);

    node_num=0;
    rand_num=0;
    out_num=0;
    first_node=NULL;
}

Console::~Console()
{
    delete ui;
}

void Console::num_confirm_clicked()
{
    int temp=ui->node_num->text().toInt();
    if(temp<=1||temp>=17)
    {
        QMessageBox::information(NULL, QString("提示"), QString("请输入[2,16]中的数字"), QMessageBox::Yes);
        return;
    }

    node_num=temp;
    ui->tip->setVisible(true);
    ui->num_confirm->setEnabled(false);
    ui->num_reset->setEnabled(true);
    ui->out->setVisible(true);
    ui->node_num->setEnabled(false);

    for(int i=0,t=1;i<16;i++)
    {
        if(but_layout[node_num-2][i]==1)
        {
            node_but_list.at(i)->setVisible(true);
            node_but_list.at(i)->setText(QString::number(t++));
        }
    }
    //按照人数显示按钮
    //将每个节点按照链表方式连接起来
    LNode* temp_node;
    LNode* pre_node;
    for(int i=0,t=node_num;i<16&&t>0;i++)
    {
        if(but_layout[node_num-2][i]==1)
        {
            temp_node=new LNode;
            if(t==node_num)
            {
                first_node=temp_node;
                temp_node->but=node_but_list.at(i);
                pre_node=temp_node;
                t--;
            }
            else if(t>1)
            {
                pre_node->next=temp_node;
                temp_node->but=node_but_list.at(i);
                pre_node=temp_node;
                t--;
            }
            else
            {
                pre_node->next=temp_node;
                temp_node->but=node_but_list.at(i);
                temp_node->next=first_node;
                t--;
            }
        }
    }
}

void Console::num_reset_clicked()//重置人数
{
    node_num=0;
    out_num=0;
    first_node=NULL;

    ui->tip->setVisible(false);
    ui->num_confirm->setEnabled(true);
    ui->num_reset->setEnabled(false);
    ui->gen_rand->setEnabled(false);
    ui->out->setVisible(false);
    ui->node_num->setEnabled(true);
    ui->node_num->setText("");

    for(int i=0;i<16;i++)
    {
        node_but_list.at(i)->setVisible(false);
        node_but_list.at(i)->setEnabled(true);
        node_but_list.at(i)->setStyleSheet("background: rgb(255,255,255)");
        out_list.at(i)->setText("");
    }
}

void Console::gen_rand_clicked()//产生随机数，开始转圈
{
    rand_num=qrand()%6+1;
    ui->rand_num->setText(QString::number(rand_num));
    ui->gen_rand->setEnabled(false);
    timer->start(1000);//开始计时器
}

void Console::update_time()//核心函数
{
    if(rand_num>1)//游戏正在进行
    {
        first_node->but->setStyleSheet("background: rgb(255,255,255)");
        first_node=first_node->next;
        first_node->but->setStyleSheet("background: rgb(255,0,0)");
        rand_num--;
    }
    else if(rand_num>0)//指到应当出列的人
    {
        first_node->but->setStyleSheet("background: rgb(255,255,255)");
        first_node->next->but->setStyleSheet("background: rgb(255,0,0)");
        rand_num--;
    }
    else//该轮游戏结束
    {
        timer->stop();
        first_node->next->but->setVisible(false);
        out_list.at(out_num++)->setText(first_node->next->but->text());
        first_node->next=first_node->next->next;
        first_node->next->but->setStyleSheet("background: rgb(255,0,0)");
        first_node=first_node->next;
        ui->rand_num->setText("");
        ui->gen_rand->setEnabled(true);

        if(first_node->next==first_node)//所有玩家均出列
        {
            ui->gen_rand->setVisible(false);
            out_list.at(out_num)->setText(first_node->but->text());
            ui->num_reset->setEnabled(true);
        }
    }
}

void Console::num_but_clicked()//点击按钮选择开始人
{
    QPushButton* pushed_but=dynamic_cast<QPushButton*>(sender());
    for(int i=0;i<node_num;i++)
    {
        if(pushed_but==first_node->but)
            break;
        else
            first_node=first_node->next;
    }

    LNode* temp=first_node;
    for(int i=0;i<node_num;i++)
    {
        temp->but->setEnabled(false);
        temp=temp->next;
    }

    first_node->but->setStyleSheet("background: rgb(255,0,0)");
    ui->tip->setVisible(false);

    ui->gen_rand->setVisible(true);
    ui->gen_rand->setEnabled(true);
    ui->rand_num->setVisible(true);
    ui->num_reset->setEnabled(false);
}
