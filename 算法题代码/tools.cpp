#include "tools.h"

int* vectorToArray(QVector<int> vec)//将向量转变为数组
{
    int* array=new int[vec.size()];
    for(int i=0;i<vec.size();i++)
        array[i]=vec.at(i);
    return  array;
}

int direct_insert(QVector<int>initial_num,QVector<int*>&result_list)//直接插入
{
    result_list.append(vectorToArray(initial_num));
    int count=0;
    int *a=vectorToArray(initial_num);
    for(int j=1;j<initial_num.size();j++)
    {
        int key=a[j];
        int i=j-1;
        while(i>=0&&a[i]>key)
        {
            a[i+1]=a[i];
            i--;
        }
        a[i+1]=key;
        int* temp=new int[initial_num.size()];
        memcpy(temp,a,initial_num.size()*sizeof(int));
        result_list.append(temp);
        count++;
    }
    return count;
}

int half_insert(QVector<int>initial_num,QVector<int*>&result_list)//折半插入
{
    result_list.append(vectorToArray(initial_num));
    int count=0;
    int *a=vectorToArray(initial_num);
    int low=0,high=0,mid;
    for(int j=1;j<initial_num.size();j++)
    {
        int key=a[j];
        low=0;
        high=j-1;
        while(low<=high)
        {
            mid=(low+high)/2;
            if(a[mid]>key)
                high=mid-1;
            else
                low=mid+1;
        }
        for(int i=j;i>low;i--)
            a[i]=a[i-1];
        a[low]=key;
        int* temp=new int[initial_num.size()];
        memcpy(temp,a,initial_num.size()*sizeof(int));
        result_list.append(temp);
        count++;
    }
    return count;
}

void ShellInsert(int* arr,int len,int gap){//一趟希尔排序
    for (int i = gap; i < len; ++i)
    {
        if (arr[i]<arr[i-gap])
        {
            int key = arr[i];
            int j;
            for (j = i - gap; j >= 0 && key<arr[j]; j -= gap)
                arr[j + gap] = arr[j];
            arr[j + gap] = key;
        }
    }
}

int shell_sort(QVector<int>initial_num,QVector<int*>&result_list)//执行3轮希尔排序，间隔分别为5，3，1
{
    result_list.append(vectorToArray(initial_num));
    int *a=vectorToArray(initial_num);
    int dlta[3] = { 5,3,1 };
    for(int i=0;i<3;i++)
    {
        ShellInsert(a, initial_num.size(), dlta[i]);
        int* temp=new int[initial_num.size()];
        memcpy(temp,a,initial_num.size()*sizeof(int));
        result_list.append(temp);
    }
    return 3;
}

int bubble_sort(QVector<int>initial_num,QVector<int*>&result_list)//冒泡排序
{
    result_list.append(vectorToArray(initial_num));
    int count=0;
    int *a=vectorToArray(initial_num);
    for(int i=0;i<initial_num.size()-1;i++)
    {
        for (int j = 0; j < initial_num.size() - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                int* temp=new int[initial_num.size()];
                memcpy(temp,a,initial_num.size()*sizeof(int));
                result_list.append(temp);
                count++;
            }
        }
    }
    return count;
}

int quick(int len,int left, int right, int* arr,QVector<int*>&result_list)
{
    if (left >= right)
        return 0;
    int i, j, base, temp;
    i = left, j = right;
    base = arr[left];  //取最左边的数为基准数
    while (i < j)
    {
        while (arr[j] >= base && i < j)
            j--;
        while (arr[i] <= base && i < j)
            i++;
        if (i < j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    //基准数归位
    arr[left] = arr[i];
    arr[i] = base;
    int* tmp=new int[len];
    memcpy(tmp,arr,len*sizeof(int));
    result_list.append(tmp);
    return quick(len,left, i - 1, arr,result_list)+quick(len,i + 1, right, arr,result_list)+1;
}

int quick_sort(QVector<int>initial_num,QVector<int*>&result_list)//快速排序
{
    result_list.append(vectorToArray(initial_num));
    int count=0;
    int *a=vectorToArray(initial_num);
    count=quick(initial_num.size(),0,initial_num.size()-1,a,result_list);
    return count;
}

int Min(int* temp, int i, int len) {
    int min = 99999;
    int result;
    for (int j = i; j < len; j++)
        if (temp[j] < min) {
            result = j;
            min = temp[j];
        }
    return result;
}

int easy_choose(QVector<int>initial_num,QVector<int*>&result_list)//选择排序
{
    result_list.append(vectorToArray(initial_num));
    int count=0;
    int *a=vectorToArray(initial_num);
    for (int i = 0; i < initial_num.size()-1; i++) {
        int j = Min(a, i, initial_num.size());
        if (i != j) {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            int* tmp=new int[initial_num.size()];
            memcpy(tmp,a,initial_num.size()*sizeof(int));
            result_list.append(tmp);
            count++;
        }
    }
    return count;
}
