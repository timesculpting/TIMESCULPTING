#include<stdio.h>
#include<stdlib.h>
#include<set>
#include<time.h>

#define MODULE 10000000

std::set<int> numbers;
std::set<int>::iterator iter;

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

int compare(const void *x,const void *y)
{
	return *(int *)x-*(int *)y;
}

void sortNumbers()
{
	int startTime=clock();
	int *numbers=new int[MODULE];
	int count=0;
	FILE *inputFile,*outputFile;
	for(int i=0;i<MODULE;++i)
		numbers[i]=-1;
	fopen_s(&inputFile,"numbers.txt","r");
	while(fscanf_s(inputFile,"%d",&numbers[count])!=EOF&&numbers[count]!=-1)
		++count;
	fclose(inputFile);
	qsort(numbers,count,sizeof(int),compare);
	fopen_s(&outputFile,"sortedNumbers.txt","w");
	for(int j=0;j<count;++j)
		fprintf(outputFile,"%d\n",numbers[j]);
	fclose(outputFile);
	delete [] numbers;
	int finishTime=clock();
	double time=(double)(finishTime-startTime)/1000;
	printf("sortNumbers --- %.3f seconds\n",time);
	return;
}

void sortNumbers2()
{
	int startTime=clock();
	FILE *inputFile,*outputFile;
	int number=-1;
	fopen_s(&inputFile,"numbers.txt","r");
	while(fscanf_s(inputFile,"%d",&number)!=EOF&&number!=-1)
	{
		numbers.insert(number);
		number=-1;
	}
	fclose(inputFile);
	fopen_s(&outputFile,"sortedNumbers2.txt","w");
	for(iter=numbers.begin();iter!=numbers.end();++iter)
		fprintf(outputFile,"%d\n",*iter);
	fclose(outputFile);
	int finishTime=clock();
	double time=(double)(finishTime-startTime)/1000;
	printf("sortNumbers2 --- %.3f seconds\n",time);
	return;
}

int main(void)
{
	generateNumbers();
	sortNumbers();
	sortNumbers2();
	system("pause");
	return 0;
}
