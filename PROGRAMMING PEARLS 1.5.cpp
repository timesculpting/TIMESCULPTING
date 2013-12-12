#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MODULE 10000000
#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F

void generateNumbers()
{
	int startTime=clock();
	bool *numbers=new bool[MODULE];
	FILE *outputFile;
	int randomNumber;
	fopen_s(&outputFile,"numbers.txt","w");
	srand((unsigned int)time(NULL));
	for(int i=0;i<MODULE;++i)
	{
		printf("%d\n",i);
		randomNumber=(32768*rand()+rand())%MODULE;
		if(numbers[randomNumber]!=1)
		{
			numbers[randomNumber]=1;
			fprintf(outputFile,"%d\n",randomNumber);
		}
	}
	fclose(outputFile);
	int finishTime=clock();
	double time=(double)(finishTime-startTime)/1000;
	printf("generateNumbers --- %.3f seconds\n",time);
	return;
}

void setBit(int *numbers,int number)
{
	numbers[number>>SHIFT]|=(1<<(number&MASK));
	return;
}

void unsetBit(int *numbers,int number)
{
	numbers[number>>SHIFT]&=~(1<<(number&MASK));
	return;
}

bool checkBit(int *numbers,int number)
{
	return numbers[number>>SHIFT]&(1<<(number&MASK));
}

void sortNumbers()
{
	int startTime=clock();
	int *numbers=new int[1+(MODULE/2)/BITSPERWORD];
	FILE *inputFile,*outputFile,*tempFile;
	memset(numbers,0,(1+(MODULE/2)/BITSPERWORD)*sizeof(int));
	int number=-1;
	fopen_s(&inputFile,"numbers.txt","r");
	fopen_s(&tempFile,"temp.txt","w");
	while(fscanf_s(inputFile,"%d",&number)!=EOF&&number!=-1)
	{
		if(number<5000000)
			setBit(numbers,number);
		else
			fprintf(tempFile,"%d\n",number-5000000);
		number=-1;
	}
	fclose(inputFile);
	fclose(tempFile);
	fopen_s(&outputFile,"sortedNumbers.txt","w");
	for(int i=0;i<MODULE/2;++i)
		if(checkBit(numbers,i))
			fprintf(outputFile,"%d\n",i);
	memset(numbers,0,(1+(MODULE/2)/BITSPERWORD)*sizeof(int));
	fopen_s(&tempFile,"temp.txt","r");
	while(fscanf_s(tempFile,"%d",&number)!=EOF&&number!=-1)
	{
		setBit(numbers,number);
		number=-1;
	}
	fclose(tempFile);
	for(int i=0;i<MODULE/2;++i)
		if(checkBit(numbers,i))
			fprintf(outputFile,"%d\n",i+5000000);
	fclose(outputFile);
	int finishTime=clock();
	double time=(double)(finishTime-startTime)/1000;
	printf("sortNumbers --- %.3f seconds\n",time);
	return;
}

int main(void)
{
	generateNumbers();
	sortNumbers();
	system("pause");
	return 0;
}
