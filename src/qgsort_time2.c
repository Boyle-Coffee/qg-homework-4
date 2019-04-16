#include "../inc/qgsort.h"
#include "qgsort.c"
#define SIZE1 10000
#define SIZE2 50000
#define SIZE3 200000

int main(){
    long start,finish;
    int i,j,k,a1[SIZE1],a2[SIZE2],a3[SIZE3]/*,t1[SIZE1],t2[SIZE2],t3[SIZE3]**/;
    int b[]={SIZE1,SIZE2,SIZE3},*ap[3],*at[3];

    ap[0]=a1;
    ap[1]=a2;
    ap[2]=a3;
    printf("h");
    /*at[0]=t1;
    at[1]=t2;
    at[2]=t3;*/
    //测试插入排序
    for(j=0;j<3;j++){
        srand(time(0));
        for(i=0;i<b[j];i++)
            ap[j][i]=rand(); //生成随机数
        start=clock();  //开始计时
        insertSort(ap[j],b[j]);
        finish=clock();//计时结束
        printf("The time of insertSort with %d is %ldms\n",b[j],finish-start);
    }
    printf("\n");
    //测试归并排序
    /*for(j=0;j<3;j++){
        srand(time(0));
        for(i=0;i<b[j];i++)
            ap[j][i]=rand();
        start=clock();
        MergeSort(ap[j],0,b[j]-1,at[j]);
        finish=clock();
        printf("The time of MergeSort with %d is %ldms\n",b[j],finish-start);
    }
    printf("\n");*/
    //测试计数排序
    for(j=0;j<3;j++){
        srand(time(0));
        for(i=0;i<b[j];i++)  //²âÊÔ²åÈëÅÅÐò
            ap[j][i]=rand()%10000;
        start=clock();
        CountSort(ap[j],b[j],10000);
        finish=clock();
        printf("The time of RadixCountSort with %d is %ldms\n",b[j],finish-start);
    }
    printf("\n");

    //测试基数排序
    for(j=0;j<3;j++){
        srand(time(0));
        for(i=0;i<b[j];i++)  //²âÊÔ²åÈëÅÅÐò
            ap[j][i]=rand()%10000;
        start=clock();
        RadixCountSort(ap[j],b[j]);
        finish=clock();
        printf("The time of RadixCountSort with %d is %ldms\n",b[j],finish-start);
    }
    printf("\n");
    //测试快速排序（非递归）
    for(j=0;j<3;j++){
        srand(time(0));
        for(i=0;i<b[j];i++)  //²âÊÔ²åÈëÅÅÐò
            ap[j][i]=rand()%10000;
        start=clock();
        QuickSort(ap[j],b[j]);
        finish=clock();
        printf("The time QuickSort with %d is %ldms\n",b[j],finish-start);
    }
    printf("\n");
    //测试快速排序（递归）
    for(j=0;j<3;j++){
        srand(time(0));
        for(i=0;i<b[j];i++)  //²âÊÔ²åÈëÅÅÐò
            ap[j][i]=rand()%10000;
        start=clock();
        QuickSort_Recursion(ap[j],0,b[j]-1);
        finish=clock();
        printf("The time QuickSort_Recursion with %d is %ldms\n",b[j],finish-start);
    }
    printf("\n");

    return 0;
}

