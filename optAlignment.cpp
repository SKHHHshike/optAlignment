// optAlignment.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "malloc.h"
#include "time.h"
#include <vector>
#include <stdlib.h>
#include <fstream>

//��m>=n���������orz
#define size1 8
#define size2 5

using namespace std;



vector <char>a;
vector <char>b;
int m;
int n;




int optCost1(int i,int j);
int optCost2(int i,int j);
int min(int a,int b,int c);
void getRandomString1();
void getRandomString2();
struct position
{
	int i;
	int j;
	int value;
	position *previous;
};

int main()
{

	//��ʼ��һ����ʼ������������� 
	//����ʱע�͵���ʼ����
	srand((unsigned)time(0));
	m=size1;
	n=size2;
	getRandomString1();
	getRandomString2();
	//��ʼ��һ����

	//��ʼ�������Զ�������� 
	//����ʱע�͵���ʼ��һ�������ļ�a.txt��b.txt��д���ƥ������
	/*fstream File;
    char c;  
	//��ȡa
    File.open("a.txt",ios::in);  
    while(!File.eof() )  
    {  
        File>>c;  
		a.push_back(c); 
    }  
    File.close();  
	a.pop_back();
	//��ȡb
	File.open("b.txt",ios::in);  
    while(!File.eof() )  
    {  
        File>>c;  
		b.push_back(c); 
    }  
    File.close();  
	b.pop_back();

	//����m��n
	m=a.size();
	n=b.size();
	*/
	//��ʼ��������

	//���ԭ����
	printf("a:");
	for(int y = 0; y < m; y++)
		printf("%c",a[y]);
	printf("\n");

	printf("b:");
	for(int y = 0; y < n; y++)
		printf("%c",b[y]);

	//��������ʱ��
	double start, finish;
	int cost;

	//����2����Ϊ����1����ʱ��̫�����������к���2��
	start=clock();
	cost=optCost2(0,0);
	printf("\noptimal cost: %d\n",cost);
	finish=clock();
	printf( "����2����ʱ�䣺%f seconds\n",(finish - start) / CLOCKS_PER_SEC);

	//����1
	start=clock();
	printf("\n����1��������...");
	cost=optCost1(0,0);
	printf("\noptimal cost: %d\n",cost);
	finish=clock();
	printf( "����1����ʱ�䣺%f seconds\n",(finish - start) / CLOCKS_PER_SEC);

	printf("���н���\n");
	getchar();
	return 0;
}

//����1
int optCost1(int i,int j)
{
	if(i==m)
		return 2*(n-j);
	else if(j==n)
		return 2*(m-i);
	else
	{
		int penalty;
		if(a[i]==b[j])
			penalty=0;
		else
			penalty=1;
		return min(optCost1(i+1,j+1)+penalty,optCost1(i+1,j)+2, optCost1(i,j+1)+2);

	}
}

//����2
int optCost2(int i,int j)
{
	//��������M
	position **M;
	M=(position **)malloc(sizeof(position*)*(m+1));
	for(int t=0;t<m+1;t++)
		M[t]=(position *)malloc(sizeof(position)*(n+1));


	for(int x=0;x<m+1;x++)
	{
		for(int y=0;y<n+1;y++)
		{
			M[x][y].i=x;
			M[x][y].j=y;
		}
	}


	for(int x=m;x>=0;x--)
	{
		for(int y=n;y>=0;y--)
		{
			if(x==m){
				M[x][y].value= 2*(n-y);
				M[x][y].previous=NULL;
			}
			else if(y==n){
				M[x][y].value=2*(m-x);
				M[x][y].previous=NULL;
			}
			else
			{
			int penalty;
			if(a[x]==b[y])
				penalty=0;
			else
				penalty=1;
			M[x][y].value= min(M[x+1][y+1].value+penalty,M[x+1][y].value+2, M[x][y+1].value+2);
			if(M[x][y].value==M[x+1][y+1].value+penalty)
				M[x][y].previous=&(M[x+1][y+1]);
			else if(M[x][y].value==M[x+1][y].value+2)
				M[x][y].previous=&(M[x+1][y]);
			else
				M[x][y].previous=&(M[x][y+1]);
			}
		}
	}

	//�����ά����
	printf("\nM���飺\n");
		for(int x=0;x<m+1;x++)
	{
		for(int y=0;y<n+1;y++)
			printf("%d\t",M[x][y].value);
		printf("\n");
	}


	//��ʼ����
	
	//����һ���������洢����·��
	int l=max(m,n);
	int **array;
	array=(int **)malloc(sizeof(int*)*(l+1));
	for(int t=0;t<l+1 ;t++)
		array[t]=(int *)malloc(sizeof(int)*(2));

	for(int x=0;x<l+1;x++)
	{
		array[x][0]=-1;
		array[x][1]=-1;
	}

	int e=0;
	int f=0;
	for(int t=0;t<l+1 && M[e][f].previous!=NULL;t++)
	{
		array[t][0]=e;
		array[t][1]=f;
		position temp =*(M[e][f].previous);
		e=temp.i;
		f=temp.j;
	}

	printf("����·�ߣ�\n");
	for(int x=0;x<l+1 && array[x][0]!=-1;x++)
	{
		printf("(%d,%d)\t",array[x][0],array[x][1]);
	}



	//������ƥ��
	//���������ƥ��õ����ж���Ϊa1,b1
	vector <char>a1;
	vector <char>b1;
	for(int e=0;e<m;e++)
	{
		a1.push_back(a[e]);
	}
	for(int e=0;e<n;e++)
	{
		b1.push_back(b[e]);
	}
	char gap='_';

	for(int x=0;x<m+1 && array[x][0]!=-1;x++)
	{
		if(array[x][0]==array[x+1][0])
			a1.insert(a1.begin()+x,gap);
		else if(array[x][1]==array[x+1][1])
			b1.insert(b1.begin()+x,gap);
	}

	//���
	printf("\n���ƥ�䣺\n");
	for(int y = 0; y < a1.size(); y++)
		printf("%c",a1[y]);
	printf("\n");
	for(int y = 0; y < b1.size(); y++)
		printf("%c",b1[y]);

	return M[0][0].value;//����cost

}
int min(int a,int b,int c)
{
	if(a<b)
	{
		if(a<c)
			return a;
		else
			return c;
	}
	else
	{
		if(b<c)
			return b;
		else
			return c;
	}
}

//����õ�������a
void getRandomString1()
{
	for(int i=0;i<m;i++)
	{
		int temp=rand()%4+1;
		char tempc;
		switch (temp)
		{
		case 1:
			tempc='A';
			break;
		case 2:
			tempc='G';
			break;
		case 3:
			tempc='T';
			break;
		case 4:
			tempc='C';
			break;
		}
		a.push_back(tempc);
	}
}

//����õ�������2
void getRandomString2()
{
	for(int i=0;i<n;i++)
	{
		int temp=rand()%4+1;
		char tempc;
		switch (temp)
		{
		case 1:
			tempc='A';
			break;
		case 2:
			tempc='G';
			break;
		case 3:
			tempc='T';
			break;
		case 4:
			tempc='C';
			break;
		}
		b.push_back(tempc);
	}
}

