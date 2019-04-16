#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define RADIX 10
#include <time.h>
#define CLOCKS_PER_SEC ((clock_t)1000)
#include "../inc/qgsort.h"

int privot_index;  //ȫ�ֱ���������k����ʱ��¼�������
/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : ��������
 *  @param       : ����ָ�� a, ���鳤�� n
 */
void insertSort(int *a,int n){
	int i,j,t,start,finish;  //t��Ϊ����ʱ�洢�������ݵı���

	start=clock();
	for(i=1;i<n;i++){
		t=a[i];
		for(j=i-1;j>=0;j--)  //�Ӵ�����������ǰ����
			if(a[j]>t)
				a[j+1]=a[j];
			else
				break;
			a[j+1]=t;
   	}
   	finish=clock();
}

/**
 *  @name        : void MergeArray(int *a,int begin,int mid,int end,int *temp);
 *  @description : �鲢���򣨺ϲ����飩
 *  @param       : ����ָ��a���������begin�������е�mid�������յ�end����������ָ��temp
 */
void MergeArray(int *a,int begin,int mid,int end,int *temp){
    int i,j,k;
    for(i=begin,j=mid+1,k=begin;i<=mid&&j<=end;k++)
        if(a[i]<=a[j])  //�����������Ԫ�����Ƚϣ�С�����ͷ�ǰ��
            temp[k]=a[i++];
        else
            temp[k]=a[j++];
    while(i<=end)  //��ʣ��Ԫ�ش�������
        temp[k++]=a[i++];
    while(j<=end)
        temp[k++]=a[j++];
    }

/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : �鲢����
 *  @param       : ����ָ��a���������begin�������յ�end����������ָ��temp
 */
void MergeSort(int *a,int begin,int end,int *temp){
    int mid,*t;

    t=(int*)malloc((end-begin+1)*sizeof(int));
    if(begin==end)  //ֻʣһ��Ԫ���򲻵ݹ�
        temp[begin]=a[begin];
    else{
        mid=(begin+end)/2;
        MergeSort(a,begin,mid,t);  //�ݹ�
        MergeSort(a,mid+1,end,t);
        MergeArray(t,begin,mid,end,temp);  //�ϲ�����
    }
}

/**
 *  @name        : QuickSort_Recursion(int *a, int begin, int end);
 *  @description : �������򣨵ݹ�棩
 *  @param       : ����ָ��a���������begin�������յ�end
 */
void QuickSort_Recursion(int *a, int begin, int end){
    int privot;
    if(begin<end){
        privot=Partition(a,begin,end);
        QuickSort_Recursion(a,begin,privot_index-1);  //��ǰ�������,������ֱ��������Ĵ���debug������
        QuickSort_Recursion(a,privot_index+1,end);  //�Ժ�������
    }
}

/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : �������򣨷ǵݹ�棩
 *  @param       : ����ָ��a�����鳤��size
 */
void QuickSort(int *a,int size){
    int stack[MAXSIZE],top=0,bottom=0,i,j;
    int privot;
    stack[top++]=size-1;  //��������β�±��ʼ��ջ
    stack[top++]=0;
    while(top!=bottom){
        i=stack[--top];  //��ջ���޶���������
        j=stack[--top];
        if(i<j){
            privot=Partition(a,i,j);
            if(privot_index>i){  //�ж�����߽��Ƿ��غ�
                stack[top++]=privot_index-1;
                stack[top++]=i;
            }
            if(privot_index<j){  //�ж�����߽��Ƿ��غ�
                stack[top++]=j;
                stack[top++]=privot_index+1;
            }
        }
    }
}


/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : �������������ţ�
 *  @param       : ����ָ��a���������begin�������յ�end
 */
int Partition(int *a, int begin, int end){
    int privot=a[begin];  //ѡȡ��һ��Ԫ��Ϊ��
    while(begin<end){
        while(a[end]>=privot&&begin<end)  //�Ӻ���ǰ������ֱ�����ֱ���С��Ԫ��
            end--;
        if(begin<end)  //������ǰ��
            a[begin++]=a[end];
        while(a[begin]<=privot&&begin<end)  //��ǰ���������ֱ�����ֱ�����Ԫ��
            begin++;
        if(begin<end)
            a[end--]=a[begin];  //���������
    }
    if(end==begin){
        a[begin]=privot;  //���ḳֵ�����Ŀ�λ���������
        privot_index=begin;
    }
    else{
        printf("Error!\n");
        exit(-1);
    }
    return privot;
}


/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : ��������
 *  @param       : ����ָ��a�����鳤��size���������ֵmax
 */
void CountSort(int *a, int size,int max){
    int *count,i,j,k,*b;

    count=(int*)malloc((max+1)*sizeof(int));
    b=(int*)malloc(size*sizeof(int));
    for(i=0;i<=max;i++)  //��ʼ��������
        count[i]=0;
    for(i=0;i<size;i++){  //��ÿ������Ԫ�ؽ��м���
        b[i]=a[i];
    }
    for(j=0;j<size;j++)  //���ֱ�����С�����ͼ�����һ
        for(k=0;k<max+1;k++)
            if(a[j]<=k)
                count[k]++;
    for(i=0;i<size;i++)  //ͨ���������ҵ�����λ��
        a[--count[a[i]]]=b[i];  //�������ݺ������һ
}


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : ������������
 *  @param       : ����ָ��a�����鳤��size
 */
void RadixCountSort(int *a,int size){
    /*int ta,tb,tc,td[15];debugʱ�ӵĲ�������*/
    int count[RADIX],i,j,k=1,*b,loop=1;

    b=(int*)malloc(size*sizeof(int));
    while(loop){
        for(i=0;i<RADIX;i++)
            count[i]=0; //�����������ʼ��Ϊ��
        for(i=0;i<size;i++){
            b[i]=a[i];
            /*td[i]=b[i]; debug���ӵ�����*/
        }
        for(i=0;i<RADIX;i++)
            for(j=0;j<size;j++){
                if((a[j]%(k*10)/k)<=i)  //�Ƚϵ�kλ�����ֵ�kλ������С�����ͼ�����һ��debug N�η��ּ�����ʽ�д���һ��λ����μ�����
                    count[i]++;
            }
            for(i=size-1;i>=0;i--)  //ͨ���������ҵ�����λ��
                a[--count[(b[i]%(k*10)/k)]]=b[i];

        k=k*RADIX;  //k����������
        loop=0;
        for(i=0;i<size;i++)  //k��������Ԫ�ص�λ����ֹͣѭ��
            if(a[i]/k)
                loop=1;
    }
}


/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : ��ɫ����
 *  @param       : ����ָ��a��ֻ��0��1��2Ԫ�أ������鳤��size
 */
void ColorSort(int *a,int size){
    int *p0,*p1,*p2,t;

    p1=p0=a;  //��ʼ��ָ��
    p2=&a[size-1];
    while(p1!=p2){
        if(*p1==1&&p1!=p2)
            p1++;
        if(*p2!=2&&*p1==2&&p1!=p2){  //�����м�ָ��ָ��2�ͺͲ�ָ��2��p2����
            t=*p2;
            *p2=*p1;
            *p1=t;
        }
        if(*p2==2&&p1!=p2)
            p2--;
        if(*p0!=0&&*p1==0){  //�����м�ָ��ָ��0�ͺͲ�ָ��0��p0����
            t=*p0;
            *p0=*p1;
            *p1=t;
        }
        if(*p0==0)
            p0++;
    }
}


/**
 *  @name        : ����
 *  @description : ��һ�������������ҵ���K��/С����
 *  @param       : ����ָ��a�����鳤��size
 */

int find_k_min(int a[],int k,int size){
    if(k<=0||k>size){  //���k�Ƿ�Խ��
        puts("the params of find_k_min is Error!");
        exit(-1);
    }
    int stack[MAXSIZE],top=0,bottom=0,i,j,in;
    int privot;
    stack[top++]=size-1;  //��������β�±��ʼ��ջ
    stack[top++]=0;
    while(top!=bottom){
        i=stack[--top];  //��ջ���޶���������
        j=stack[--top];
        if(i<=j){
            privot=Partition(a,i,j);
            in=privot_index;
            if(k==privot_index+1)
                return privot;
                if(privot_index>i&&k<privot_index+1){  //�ж�k�ڲ��ڻ����������棬�ھͷֽ�����
                    stack[top++]=privot_index-1;
                    stack[top++]=i;
                }
                if(privot_index<j&&k>privot_index+1){  //�ж�k�ڲ��ڻ����������棬�ھͷֽ�����
                    stack[top++]=j;
                    stack[top++]=privot_index+1;
                }
            if(k==privot_index+1)
                return privot;
        }
    }
}

int find_k_max(int a[],int k,int size){
    if(k<=0||k>size){  //���k�Ƿ�Խ��
        puts("the params of find_k_max is Error!");
        exit(-1);
    }
    k=size-k+1;  //�������������ĳ������һ����������һ����ͬ
    return find_k_min(a,k,size);
}
