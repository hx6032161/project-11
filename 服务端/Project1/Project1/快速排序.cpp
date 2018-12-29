#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace::std;

int quicksort1(int * arr, int first, int last)
{
	if (first > last)
	{
		return 0;
	}
	int i, j, mid;
	mid = arr[first];
	i = first + 1;
	j = last;
	while (i <= j)
	{
		while (j >= i)
		{
			if (arr[j] >= mid)
			{
				j--;
			}
			else
			{
				while (i <= j)
				{
					if (arr[i] < mid)
					{
						i++;
					}
					else
					{
						int temp = arr[i];
						arr[i] = arr[j];
						arr[j] = temp;
						break;
					}
				}
			}
		}
	}
	if (j != first)
	{
		//num����λ
		arr[first] = arr[j];
		arr[j] = mid;
	}
	
	//�ݹ�������������
	quicksort1(arr, first, j - 1);
	quicksort1(arr, j + 1, last);
	return 0;
}

int printfArr(int * arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << "	";
	}
	cout << endl;
	return 0;
}

int main()
{
	//int arr[10] = { 6, 1, 3, 2, 8, 4, 10, 7, 5, 9 };
	int arr[] = { 12, 14, 2, 122, 43, 23, 22, 123, 4, 5, 8, 4, 1, 1922 };
	//int arr[] = { 12, 14, 2, 122,  22, 123, 4,5, 8, 4, 1, 1922 };
	//int arr[] = { 5,4,7,6,2,1};
	//int arr[] = { 5, 4, 7, 6,7, 2, 1, 88, 6, 11};
	int len = sizeof(arr) / sizeof(arr[0]);
	printfArr(arr, len);
	quicksort1(arr, 0, len - 1);
	printfArr(arr, len);
	system("pause");
	return 0;
}


int a[101], n;//����ȫ�ֱ�����������������Ҫ���Ӻ�����ʹ��
void quicksort(int left, int right) {
	int i, j, t, temp;
	if (left > right)
		return;
	temp = a[left]; //temp�д�ľ��ǻ�׼��
	i = left;
	j = right;
	while (i != j) { //˳�����Ҫ��Ҫ�ȴ��ұ߿�ʼ��
		while (a[j] >= temp && i < j)
			j--;
		while (a[i] <= temp && i < j)//�����ұߵ�
			i++;
		if (i < j)//�����������������е�λ��
		{
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	//���ս���׼����λ
	a[left] = a[i];
	a[i] = temp;
	quicksort(left, i - 1);//����������ߵģ�������һ���ݹ�Ĺ���
	quicksort(i + 1, right);//���������ұߵ� ��������һ���ݹ�Ĺ���
}
int main11() {
	int i;
	//��������
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	quicksort(1, n); //�����������
	//��������Ľ��
	for (i = 1; i < n; i++)
		printf("%d ", a[i]);
	printf("%d\n", a[n]);
	return 0;
}