#include "../inc/qgsort.h"
#include "qgsort.c"
/***
�����ܣ����Ը���������100*100kʱ��ʱ��
***/
int main(){
    long start,finish;
    int i,j,**a4;

    a4=(int**)malloc(sizeof(int*)*100000);  //����100000*intָ��Ŀռ䣨100000̫���޷�ֱ��������������
    for(i=0;i<100000;i++)
        a4[i]=(int*)malloc(sizeof(int)*100);
    srand(time(0));  //���������
    for(j=0;j<100000;j++)
        for(i=0;i<100;i++)
           a4[j][i]=rand()%200;  //�����������ڵ������
    start=clock();  //��ʱ��ʼ
    for(j=0;j<100000;j++)
        insertSort(a4[j],100);  //���ú���
    finish=clock();  //��ʱ����
    printf("The time insertSort with 100*100k is %ldms\n",finish-start);
    printf("\n");

    srand(time(0));
    for(j=0;j<100000;j++)
        for(i=0;i<100;i++)
           a4[j][i]=rand()%200;  //�����������ڵ������
    start=clock();  //��ʱ��ʼ
    for(j=0;j<100000;j++)
        QuickSort_Recursion(a4[j],0,99); //���ú���
    finish=clock();  //��ʱ����
    printf("The time QuickSort_Recursiont with 100*100k is %ldms\n",finish-start);
    printf("\n");

    srand(time(0));
    for(j=0;j<100000;j++)
        for(i=0;i<100;i++)
           a4[j][i]=rand()%200;  //�����������ڵ������
    start=clock();  //��ʱ��ʼ
    for(j=0;j<100000;j++)
        QuickSort(a4[j],100); //���ú���
    finish=clock();  //��ʱ����
    printf("The time QuickSort with 100*100k is %ldms\n",finish-start);
    printf("\n");

    srand(time(0));
    for(j=0;j<100000;j++)
        for(i=0;i<100;i++)
           a4[j][i]=rand()%200;  //�����������ڵ������
    start=clock();  //��ʱ��ʼ
    for(j=0;j<100000;j++)
        CountSort(a4[j],100,200); //���ú���
    finish=clock();  //��ʱ����
    printf("The time CountSort with 100*100k is %ldms\n",finish-start);
    printf("\n");

    srand(time(0));
    for(j=0;j<100000;j++)
        for(i=0;i<100;i++)
           a4[j][i]=rand()%200;  //�����������ڵ������
    start=clock(); //��ʱ��ʼ
    for(j=0;j<100000;j++)
        RadixCountSort(a4[j],100); //���ú���
    finish=clock();  //��ʱ����
    printf("The time RadixCountSort with 100*100k is %ldms\n",finish-start);
    printf("\n");
    getchar();

    return 0;
}
