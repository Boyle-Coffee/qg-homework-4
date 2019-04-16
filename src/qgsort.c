#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define RADIX 10
#include <time.h>
#define CLOCKS_PER_SEC ((clock_t)1000)
#include "../inc/qgsort.h"

int privot_index;  //全局变量，用于k排序时记录轴的坐标
/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : 插入排序
 *  @param       : 数组指针 a, 数组长度 n
 */
void insertSort(int *a,int n){
	int i,j,t,start,finish;  //t作为排序时存储插入数据的变量

	start=clock();
	for(i=1;i<n;i++){
		t=a[i];
		for(j=i-1;j>=0;j--)  //从待插入数据向前遍历
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
 *  @description : 归并排序（合并数组）
 *  @param       : 数组指针a，数组起点begin，数组中点mid，数组终点end，承载数组指针temp
 */
void MergeArray(int *a,int begin,int mid,int end,int *temp){
    int i,j,k;
    for(i=begin,j=mid+1,k=begin;i<=mid&&j<=end;k++)
        if(a[i]<=a[j])  //两个数组遍历元素作比较，小的数就放前面
            temp[k]=a[i++];
        else
            temp[k]=a[j++];
    while(i<=end)  //将剩余元素存入数组
        temp[k++]=a[i++];
    while(j<=end)
        temp[k++]=a[j++];
    }

/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : 归并排序
 *  @param       : 数组指针a，数组起点begin，数组终点end，承载数组指针temp
 */
void MergeSort(int *a,int begin,int end,int *temp){
    int mid,*t;

    t=(int*)malloc((end-begin+1)*sizeof(int));
    if(begin==end)  //只剩一个元素则不递归
        temp[begin]=a[begin];
    else{
        mid=(begin+end)/2;
        MergeSort(a,begin,mid,t);  //递归
        MergeSort(a,mid+1,end,t);
        MergeArray(t,begin,mid,end,temp);  //合并数组
    }
}

/**
 *  @name        : QuickSort_Recursion(int *a, int begin, int end);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void QuickSort_Recursion(int *a, int begin, int end){
    int privot;
    if(begin<end){
        privot=Partition(a,begin,end);
        QuickSort_Recursion(a,begin,privot_index-1);  //对前半段排序,这里出现变量混淆的错误，debug检查出来
        QuickSort_Recursion(a,privot_index+1,end);  //对后半段排序
    }
}

/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : 快速排序（非递归版）
 *  @param       : 数组指针a，数组长度size
 */
void QuickSort(int *a,int size){
    int stack[MAXSIZE],top=0,bottom=0,i,j;
    int privot;
    stack[top++]=size-1;  //用数组首尾下标初始化栈
    stack[top++]=0;
    while(top!=bottom){
        i=stack[--top];  //出栈，限定划分区域
        j=stack[--top];
        if(i<j){
            privot=Partition(a,i,j);
            if(privot_index>i){  //判断轴与边界是否重合
                stack[top++]=privot_index-1;
                stack[top++]=i;
            }
            if(privot_index<j){  //判断轴与边界是否重合
                stack[top++]=j;
                stack[top++]=privot_index+1;
            }
        }
    }
}


/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : 快速排序（枢轴存放）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
int Partition(int *a, int begin, int end){
    int privot=a[begin];  //选取第一个元素为轴
    while(begin<end){
        while(a[end]>=privot&&begin<end)  //从后向前遍历，直到发现比轴小的元素
            end--;
        if(begin<end)  //换到轴前面
            a[begin++]=a[end];
        while(a[begin]<=privot&&begin<end)  //从前往后遍历，直到发现比轴大的元素
            begin++;
        if(begin<end)
            a[end--]=a[begin];  //换到轴后面
    }
    if(end==begin){
        a[begin]=privot;  //将轴赋值给最后的空位，排序完毕
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
 *  @description : 计数排序
 *  @param       : 数组指针a，数组长度size，数组最大值max
 */
void CountSort(int *a, int size,int max){
    int *count,i,j,k,*b;

    count=(int*)malloc((max+1)*sizeof(int));
    b=(int*)malloc(size*sizeof(int));
    for(i=0;i<=max;i++)  //初始化计数器
        count[i]=0;
    for(i=0;i<size;i++){  //对每个数组元素进行计数
        b[i]=a[i];
    }
    for(j=0;j<size;j++)  //发现比数据小的数就计数加一
        for(k=0;k<max+1;k++)
            if(a[j]<=k)
                count[k]++;
    for(i=0;i<size;i++)  //通过计数来找到数据位置
        a[--count[a[i]]]=b[i];  //插入数据后计数减一
}


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : 基数计数排序
 *  @param       : 数组指针a，数组长度size
 */
void RadixCountSort(int *a,int size){
    /*int ta,tb,tc,td[15];debug时加的测试数据*/
    int count[RADIX],i,j,k=1,*b,loop=1;

    b=(int*)malloc(size*sizeof(int));
    while(loop){
        for(i=0;i<RADIX;i++)
            count[i]=0; //将计数数组初始化为零
        for(i=0;i<size;i++){
            b[i]=a[i];
            /*td[i]=b[i]; debug所加的数据*/
        }
        for(i=0;i<RADIX;i++)
            for(j=0;j<size;j++){
                if((a[j]%(k*10)/k)<=i)  //比较第k位，发现第k位比数据小的数就计数加一（debug N次发现计数方式有错导致一个位数多次计数）
                    count[i]++;
            }
            for(i=size-1;i>=0;i--)  //通过计数来找到数据位置
                a[--count[(b[i]%(k*10)/k)]]=b[i];

        k=k*RADIX;  //k按基数增加
        loop=0;
        for(i=0;i<size;i++)  //k超过所有元素的位数就停止循环
            if(a[i]/k)
                loop=1;
    }
}


/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : 颜色排序
 *  @param       : 数组指针a（只含0，1，2元素），数组长度size
 */
void ColorSort(int *a,int size){
    int *p0,*p1,*p2,t;

    p1=p0=a;  //初始化指针
    p2=&a[size-1];
    while(p1!=p2){
        if(*p1==1&&p1!=p2)
            p1++;
        if(*p2!=2&&*p1==2&&p1!=p2){  //发现中间指针指向2就和不指向2的p2交换
            t=*p2;
            *p2=*p1;
            *p1=t;
        }
        if(*p2==2&&p1!=p2)
            p2--;
        if(*p0!=0&&*p1==0){  //发现中间指针指向0就和不指向0的p0交换
            t=*p0;
            *p0=*p1;
            *p1=t;
        }
        if(*p0==0)
            p0++;
    }
}


/**
 *  @name        : 自拟
 *  @description : 在一个无序序列中找到第K大/小的数
 *  @param       : 数组指针a，数组长度size
 */

int find_k_min(int a[],int k,int size){
    if(k<=0||k>size){  //检查k是否越界
        puts("the params of find_k_min is Error!");
        exit(-1);
    }
    int stack[MAXSIZE],top=0,bottom=0,i,j,in;
    int privot;
    stack[top++]=size-1;  //用数组首尾下标初始化栈
    stack[top++]=0;
    while(top!=bottom){
        i=stack[--top];  //出栈，限定划分区域
        j=stack[--top];
        if(i<=j){
            privot=Partition(a,i,j);
            in=privot_index;
            if(k==privot_index+1)
                return privot;
                if(privot_index>i&&k<privot_index+1){  //判断k在不在划分区域里面，在就分解区域
                    stack[top++]=privot_index-1;
                    stack[top++]=i;
                }
                if(privot_index<j&&k>privot_index+1){  //判断k在不在划分区域里面，在就分解区域
                    stack[top++]=j;
                    stack[top++]=privot_index+1;
                }
            if(k==privot_index+1)
                return privot;
        }
    }
}

int find_k_max(int a[],int k,int size){
    if(k<=0||k>size){  //检查k是否越界
        puts("the params of find_k_max is Error!");
        exit(-1);
    }
    k=size-k+1;  //这个程序与上面的程序道理一样，仅仅这一步不同
    return find_k_min(a,k,size);
}
