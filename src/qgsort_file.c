#include "../inc/qgsort.h"
#include "qgsort.c"
#include <stdio.h>

int main(){
    long start,finish;
    int i,a[10000],b[10000];
    FILE *fp1;

    srand(time(0));
    for(i=0;i<10000;i++)
        a[i]=rand()%200; //���������
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",a[i]);  //��ӡ�����
    }
    fp1=fopen("test.txt","wb+");  //���ļ�
    fwrite(a,sizeof(int),10000,fp1);  //д�������
    fclose(fp1);

    fp1=fopen("test.txt","rb");  //���ļ�
    fread(b,sizeof(int),10000,fp1);  //��ȡ�����
    start=clock(); //��ʱ��ʼ
    insertSort(b,10000);  //���ú�������
    finish=clock();  //��ʱ����
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",b[i]);  //��ӡ�����������
    }
    fclose(fp1);
    printf("\nThe time insertSort with 10000 is %ldms\n",finish-start);
    printf("Done!\n");
    getchar();

    fp1=fopen("test.txt","rb");
    fread(b,sizeof(int),10000,fp1);
    start=clock();
    CountSort(b,10000,200);  //���ú�������
    finish=clock();
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",b[i]);  //��ӡ�����������
    }
    fclose(fp1);
    printf("\nThe time CountSort with 10000 is %ldms\n",finish-start);
    printf("Done!\n");
    getchar();

    fp1=fopen("test.txt","rb");
    fread(b,sizeof(int),10000,fp1);
    start=clock();
    QuickSort(b,10000);  //���ú�������
    finish=clock();
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",b[i]);  //��ӡ�����������
    }
    fclose(fp1);
    printf("\nThe time QuickSort with 10000 is %ldms\n",finish-start);
    printf("Done!\n");
    getchar();

    fp1=fopen("test.txt","rb");
    fread(b,sizeof(int),10000,fp1);
    start=clock();
    QuickSort_Recursion(b,0,10000-1);  //���ú�������
    finish=clock();
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",b[i]);  //��ӡ�����������
    }
    fclose(fp1);
    printf("\nThe time QuickSort_Recursion with 10000 is %ldms\n",finish-start);
    printf("Done!\n");
    getchar();

    fp1=fopen("test.txt","rb");
    fread(b,sizeof(int),10000,fp1);
    start=clock();
    RadixCountSort(b,10000);  //���ú�������
    finish=clock();
    for(i=0;i<10000;i++){
        if((i+1)%10==0)
            printf("\n");
        printf("%d\t",b[i]);  //��ӡ�����������
    }
    fclose(fp1);
    printf("\nThe time RadixCountSort with 10000 is %ldms\n",finish-start);
    printf("Done!\n");
    getchar();

    return 0;
}
