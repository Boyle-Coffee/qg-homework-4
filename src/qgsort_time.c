#include "../inc/qgsort.h"
#include "qgsort.c"
/***
程序功能：测试各排序函数在100*100k时的时间
***/
int main(){
    long start,finish;
    int i,j,**a4;

    a4=(int**)malloc(sizeof(int*)*100000);  //申请100000*int指针的空间（100000太大无法直接用数组声明）
    for(i=0;i<100000;i++)
        a4[i]=(int*)malloc(sizeof(int)*100);
    srand(time(0));  //随机数种子
    for(j=0;j<100000;j++)
        for(i=0;i<100;i++)
           a4[j][i]=rand()%200;  //生成两百以内的随机数
    start=clock();  //计时开始
    for(j=0;j<100000;j++)
        insertSort(a4[j],100);  //调用函数
    finish=clock();  //计时结束
    printf("The time insertSort with 100*100k is %ldms\n",finish-start);
    printf("\n");

    srand(time(0));
    for(j=0;j<100000;j++)
        for(i=0;i<100;i++)
           a4[j][i]=rand()%200;  //生成两百以内的随机数
    start=clock();  //计时开始
    for(j=0;j<100000;j++)
        QuickSort_Recursion(a4[j],0,99); //调用函数
    finish=clock();  //计时结束
    printf("The time QuickSort_Recursiont with 100*100k is %ldms\n",finish-start);
    printf("\n");

    srand(time(0));
    for(j=0;j<100000;j++)
        for(i=0;i<100;i++)
           a4[j][i]=rand()%200;  //生成两百以内的随机数
    start=clock();  //计时开始
    for(j=0;j<100000;j++)
        QuickSort(a4[j],100); //调用函数
    finish=clock();  //计时结束
    printf("The time QuickSort with 100*100k is %ldms\n",finish-start);
    printf("\n");

    srand(time(0));
    for(j=0;j<100000;j++)
        for(i=0;i<100;i++)
           a4[j][i]=rand()%200;  //生成两百以内的随机数
    start=clock();  //计时开始
    for(j=0;j<100000;j++)
        CountSort(a4[j],100,200); //调用函数
    finish=clock();  //计时结束
    printf("The time CountSort with 100*100k is %ldms\n",finish-start);
    printf("\n");

    srand(time(0));
    for(j=0;j<100000;j++)
        for(i=0;i<100;i++)
           a4[j][i]=rand()%200;  //生成两百以内的随机数
    start=clock(); //计时开始
    for(j=0;j<100000;j++)
        RadixCountSort(a4[j],100); //调用函数
    finish=clock();  //计时结束
    printf("The time RadixCountSort with 100*100k is %ldms\n",finish-start);
    printf("\n");
    getchar();

    return 0;
}
