#include "../inc/qgsort.h"
#include "qgsort.c"
#include <stdio.h>

int main(){
    long start,finish;
    int i,a[10000],b[10000];
    FILE *fp1;

    srand(time(0));
    for(i=0;i<10000;i++)
        a[i]=rand()%200; //生成随机数
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",a[i]);  //打印随机数
    }
    fp1=fopen("test.txt","wb+");  //打开文件
    fwrite(a,sizeof(int),10000,fp1);  //写入随机数
    fclose(fp1);

    fp1=fopen("test.txt","rb");  //打开文件
    fread(b,sizeof(int),10000,fp1);  //读取随机数
    start=clock(); //计时开始
    insertSort(b,10000);  //调用函数排序
    finish=clock();  //计时结束
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",b[i]);  //打印排序后的随机数
    }
    fclose(fp1);
    printf("\nThe time insertSort with 10000 is %ldms\n",finish-start);
    printf("Done!\n");
    getchar();

    fp1=fopen("test.txt","rb");
    fread(b,sizeof(int),10000,fp1);
    start=clock();
    CountSort(b,10000,200);  //调用函数排序
    finish=clock();
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",b[i]);  //打印排序后的随机数
    }
    fclose(fp1);
    printf("\nThe time CountSort with 10000 is %ldms\n",finish-start);
    printf("Done!\n");
    getchar();

    fp1=fopen("test.txt","rb");
    fread(b,sizeof(int),10000,fp1);
    start=clock();
    QuickSort(b,10000);  //调用函数排序
    finish=clock();
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",b[i]);  //打印排序后的随机数
    }
    fclose(fp1);
    printf("\nThe time QuickSort with 10000 is %ldms\n",finish-start);
    printf("Done!\n");
    getchar();

    fp1=fopen("test.txt","rb");
    fread(b,sizeof(int),10000,fp1);
    start=clock();
    QuickSort_Recursion(b,0,10000-1);  //调用函数排序
    finish=clock();
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",b[i]);  //打印排序后的随机数
    }
    fclose(fp1);
    printf("\nThe time QuickSort_Recursion with 10000 is %ldms\n",finish-start);
    printf("Done!\n");
    getchar();

    fp1=fopen("test.txt","rb");
    fread(b,sizeof(int),10000,fp1);
    start=clock();
    RadixCountSort(b,10000);  //调用函数排序
    finish=clock();
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",b[i]);  //打印排序后的随机数
    }
    fclose(fp1);
    printf("\nThe time RadixCountSort with 10000 is %ldms\n",finish-start);
    printf("Done!\n");
    getchar();

    return 0;
}
