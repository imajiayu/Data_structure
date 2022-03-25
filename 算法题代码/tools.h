#ifndef TOOLS_H
#define TOOLS_H
#include <QVector>
//分别为不同排序方法的实现函数，返回值为花费步数，每一步结果保存在result_list中
int direct_insert(QVector<int>initial_num,QVector<int*>&result_list);
int half_insert(QVector<int>initial_num,QVector<int*>&result_list);
int shell_sort(QVector<int>initial_num,QVector<int*>&result_list);
int bubble_sort(QVector<int>initial_num,QVector<int*>&result_list);
int quick_sort(QVector<int>initial_num,QVector<int*>&result_list);
int easy_choose(QVector<int>initial_num,QVector<int*>&result_list);
#endif // TOOLS_H
