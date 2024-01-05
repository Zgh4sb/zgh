#include<stdio.h>
#include<stdlib.h>
#include<assert.h>//Ԥ����ָ����ж��� 
#include<string.h>

void Swap(int *a,int *b)
{
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void InsertSort(int *arr,int n)
{
    assert(arr != NULL);
    for(int i=1;i<n;i++)
    {
        int end=i-1;
        int x=arr[i];
        while(end>=0)
        {
            if(x<arr[end])
            {
                arr[end+1]=arr[end];
                end--;
            }
            else
            {
                break;
            }
        }
        arr[end+1]=x;
    }
}

void ShellSort(int *arr,int n)//ϣ������ 
{
    assert(arr != NULL);
    int gap=n;
    while(gap>1)
    {
        gap=gap/3 + 1;//��һ��ֹ����gap=1 
        for(int i=0;i<gap;i++)
        {
            for(int j=i;j<n-gap;j+=gap)//ͬʱ����j<n-gap��֤����Խ�� 
            {
                int end=j;
                int x=arr[end+gap];
                while(end>=0)
                {
                    if(x<arr[end])
                    {
                        arr[end+gap]=arr[end];
                        end-=gap;
                    }
                    else
                    {
                        break;
                    }
                }
                arr[end+gap]=x;
            }
        }
    }
} 

int Partion3(int *arr,int left,int right)//ǰ��ָ�� 
{
    assert(arr != NULL);
    int key=arr[right];
    int begin=left;
    int end=right-1;
    while(begin < end)
    {
        while(begin < end && arr[begin] <= key)
        {
            begin++;
        }
        while(begin < end && arr[end] >= key)
        {
            end--;
        }
        if(begin < end)
        {
            Swap(&arr[begin],&arr[end]);
        }
    }
    if(arr[begin] >= arr[right])
    {
        Swap(&arr[begin],&arr[right]);
        return begin;
    }
    else
    {
        return right;
    }
}

void _QuickSort3(int *arr,int left,int right)//�ݹ�ʵ�ֿ�������(ǰ��ָ�뷨) 
{
    if(right-left+1 < 10) 
    {
        InsertSort(arr+left,right-left+1);
        return;
    }
    while(left < right)
    {
        int div=Partion3(arr,left,right);
        _QuickSort3(arr,left,div-1);
        left=div+1;
    }
}

void QuickSort(int *arr,int sz)//�������� 
{
    assert(arr != NULL);
    _QuickSort3(arr,0,sz-1);
}

void AdJustDown(int *arr, int sz, int root) // ���µ�����
{
    assert(arr != NULL);

    int parent = root;
    int child = parent * 2 + 1;
    while (child < sz)
    {
        if (child + 1 < sz && arr[child + 1] > arr[child]) 
        {
            child++;
        }
        if (arr[child] > arr[parent])
        {
            Swap(&arr[child], &arr[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}

void HeapSort(int *arr, int sz)//������ 
{
    assert(arr != NULL);
    //���������µ����ɶ�
    for (int i = (sz - 2) / 2; i >= 0; i--)
    {
        AdJustDown(arr, sz, i);
    }
    //ɾ���Ѷ�Ԫ�أ���ʣ��Ԫ�����µ���
    for (int end = sz - 1; end > 0; end--)
    {
        Swap(&arr[0], &arr[end]);
        AdJustDown(arr, end, 0);
    }
}

void _MergeSort(int *arr, int left, int right, int *tmp)//�鲢����ĵݹ�ʵ�� 
{
    if (left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    //������������
    int begin1 = left, end1 = mid;
    int begin2 = mid + 1, end2 = right;
    //��ʹ��������������
    _MergeSort(arr, begin1, end1, tmp);
    _MergeSort(arr, begin2, end2, tmp);
    //������������鲢��tmp����
    int i = left;
    while (begin1 <= end1 && begin2 <= end2)
    {
        if (arr[begin1] < arr[begin2])
        {
            tmp[i++] = arr[begin1++];
        }
        else
        {
            tmp[i++] = arr[begin2++];
        }
    }
    while (begin1 <= end1)
    {
        tmp[i++] = arr[begin1++];
    }
    while (begin2 <= end2)
    {
        tmp[i++] = arr[begin2++];
    }
    //���źõ����ݴ�tmp���鿼��arr
    for (int j = left; j <= right; j++)
    {
        arr[j] = tmp[j];
    }
}

void MergeSort(int *arr, int sz)//�鲢���� 
{
    assert(arr != NULL);
    //�ݹ������������ʹ�ö���ռ�
    int *tmp = (int*)malloc(sizeof(int) * sz);
    if (tmp == NULL)
    {
        perror("MergeSort");
        exit(1);
    }
    _MergeSort(arr, 0, sz - 1, tmp);

    //�ͷŶ���ռ�
    free(tmp);
    tmp = NULL;
}

void CountSort(int *arr, int sz)//�������� 
{
    assert(arr != NULL);
    //ȷ�����ݷ�Χ
    int max = arr[0];
    int min = arr[0];
    for (int i = 0; i < sz; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    int range = max - min + 1;
    int *count = (int*)malloc(sizeof(int)*range);
    if (count == NULL)
    {
        perror("CountSort");
        exit(1);
    }
    memset(count, 0, sizeof(int)*range);
    for (int i = 0; i < sz; i++)
    {
        count[arr[i] - min]++;
    }
    int j = 0;
    for (int i = 0; i < range; i++)//�������� 
    {
        while (count[i]--)
        {
            arr[j++] = i + min;
        }
    }
    free(count);
    count = NULL;
}

int main()
{
    int n=10;
    int a[n]={6, 12, 458, 5, 4, 28, 19, 1230, 9, 47};

    printf("ԭ �� �� Ϊ��");
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");

    printf("ϣ����������");
    ShellSort(a,n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");

    printf("������������");
    QuickSort(a,n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");

    printf("����������");
    HeapSort(a,n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");

    printf("�鲢��������");
    MergeSort(a,n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");

    printf("������������");
    CountSort(a,n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");

    return 0;
}

