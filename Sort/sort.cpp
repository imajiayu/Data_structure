#include <iostream>
#include <algorithm>
using namespace std;

void InsertSort() {//²åÈëÅÅÐò
	int len;
	cin >> len;
	int* temp = (int*)malloc((len + 1) * sizeof(int));
	for (int i = 1; i <= len; i++)
		cin >> temp[i];
	for(int i=2;i<=len;i++)
		if (temp[i] < temp[i - 1]) {
			temp[0] = temp[i];
			temp[i] = temp[i - 1];
			int j;
			for (j = i - 2; temp[0] < temp[j]; j--)
				temp[j + 1] = temp[j];
			temp[j + 1] = temp[0];
		}
	cout << "²åÈëÅÅÐò:" << endl;
	for (int i = 1; i <= len; i++)
		cout << temp[i] << ' ';
	cout << endl;
}


void merge(int* data, int start, int end, int* result)
{
	int left_length = (end - start + 1) / 2 + 1;
	int left_index = start;
	int right_index = start + left_length;
	int result_index = start;
	while (left_index < start + left_length && right_index < end + 1)  //store data into new array
	{
		if (data[left_index] <= data[right_index])
			result[result_index++] = data[left_index++];
		else
			result[result_index++] = data[right_index++];
	}
	while (left_index < start + left_length)
		result[result_index++] = data[left_index++];
	while (right_index < end + 1)
		result[result_index++] = data[right_index++];
}

void Msort(int* data, int start, int end, int* result)
{
	if (1 == end - start)
	{
		if (data[start] > data[end])
		{
			int temp = data[start];
			data[start] = data[end];
			data[end] = temp;
		}
		return;
	}
	else if (end == start)
		return;
	else {
		Msort(data, start, (end - start + 1) / 2 + start, result);
		Msort(data, (end - start + 1) / 2 + start + 1, end, result);
		merge(data, start, end, result);
		for (int i = start; i <= end; ++i)
		{
			data[i] = result[i];
		}
	}
}


void MergeSort() {//¹é²¢ÅÅÐò
	int len;
	cin >> len;
	int* temp = (int*)malloc((len) * sizeof(int));
	int* result = (int*)malloc((len) * sizeof(int));
	for (int i = 0; i < len; i++)
		cin >> temp[i];
	Msort(temp,0,len-1,result);
	cout << "¹é²¢ÅÅÐò:" << endl;
	for (int i = 0; i < len; i++)
		cout << result[i]<<' ';
	cout << endl;
}

int Min(int* temp, int i, int len) {
	int min = 99999;
	int result;
	for (int j = i; j <= len; j++)
		if (temp[j] < min) {
			result = j;
			min = temp[j];
		}
	return result;
}

void SelectSort() {//Ñ¡ÔñÅÅÐò
	int len;
	cin >> len;
	int* temp = (int*)malloc((len + 1) * sizeof(int));
	for (int i = 1; i <= len; i++)
		cin >> temp[i];
	for (int i = 1; i < len; i++) {
		int j = Min(temp, i, len);
		if (i != j) {
			int t = temp[i];
			temp[i] = temp[j];
			temp[j] = t;
		}
	}
	cout << "Ñ¡ÔñÅÅÐò:" << endl;
	for (int i = 1; i <= len; i++)
		cout << temp[i] << ' ';
	cout << endl;
}

void quick(int left, int right, int* arr) {
	if (left >= right)
		return;
	int i, j, base, temp;
	i = left, j = right;
	base = arr[left];  //È¡×î×ó±ßµÄÊýÎª»ù×¼Êý
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
	//»ù×¼Êý¹éÎ»
	arr[left] = arr[i];
	arr[i] = base;
	quick(left, i - 1, arr);//µÝ¹é×ó±ß
	quick(i + 1, right, arr);//µÝ¹éÓÒ±ß
}

void QuickSort() {//¿ìËÙÅÅÐò
	int len;
	cin >> len;
	int* temp = (int*)malloc((len) * sizeof(int));
	for (int i = 0; i < len; i++)
		cin >> temp[i];
	quick(0, len - 1, temp);
	cout << "¿ìËÙÅÅÐò:" << endl;
	for (int i = 0; i < len; i++)
		cout << temp[i] << ' ';
	cout << endl;
}

void BubbleSort() {//½»»»ÅÅÐò
	int len;
	cin >> len;
	int* temp = (int*)malloc((len) * sizeof(int));
	for (int i = 0; i < len; i++)
		cin >> temp[i];
	for(int i=0;i<len-1;i++){
		for (int j = 0; j < len - i - 1; j++) {
			if (temp[j] > temp[j + 1]) {
				int t = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = t;
			}
		}
	}
	cout << "½»»»ÅÅÐò:" << endl;
	for (int i = 0; i < len; i++)
		cout << temp[i] << ' ';
	cout << endl;
}

void HeapAdjust(int* arr, int len, int index){
	int left = 2 * index + 1; // indexµÄ×ó×Ó½Úµã
	int right = 2 * index + 2;// indexµÄÓÒ×Ó½Úµã

	int maxIdx = index;
	if (left<len && arr[left] > arr[maxIdx])
		maxIdx = left;
	if (right<len && arr[right] > arr[maxIdx])
		maxIdx = right;

	if (maxIdx != index){
		swap(arr[maxIdx], arr[index]);
		HeapAdjust(arr, len, maxIdx);
	}
}

void heap(int* arr, int len) {
	for (int i = len / 2 - 1; i >= 0; i--)
		HeapAdjust(arr, len, i);
	
	for (int i = len - 1; i >= 1; i--){
		swap(arr[0], arr[i]);           
		HeapAdjust(arr, i, 0);
	}
}

void HeapSort() {
	int len;
	cin >> len;
	int* temp = (int*)malloc((len) * sizeof(int));
	for (int i = 0; i < len; i++)
		cin >> temp[i];
	heap(temp, len);
//	cout << "¶ÑÅÅÐò:" << endl;
	for (int i = 0; i < len; i++)
		cout << temp[i] << ' ';
	cout << endl;
}

void ShellInsert(int* arr,int len,int gap){//Ò»ÌËÏ£¶ûÅÅÐò
	for (int i = gap + 1; i <= len; ++i){
		if (arr[i]<arr[i-gap]){
			arr[0] = arr[i];
			int j;
			for (j = i - gap; j > 0 && arr[0]<arr[j]; j -= gap)
				arr[j + gap] = arr[j];
			arr[j + gap] = arr[0];
		}
	}
}

void ShellSort() {
	int len;
	cin >> len;
	int* temp = (int*)malloc((len + 1) * sizeof(int));
	for (int i = 1; i <= len; i++)
		cin >> temp[i];
	int dlta[3] = { 5,3,1 };
	for(int i=0;i<3;i++)
		ShellInsert(temp, len, dlta[i]);
	cout << "Ï£¶ûÅÅÐò:" << endl;
	for (int i = 1; i <= len; i++)
		cout << temp[i] << ' ';
	cout << endl;
}

int main() {
	HeapSort();

	//sort(temp, temp + cnt);

	
}
