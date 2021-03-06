#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM 500000 // primes upto
#define NP 50000// number of primes to store
#define TEST(d) printf("TEST %d\n", d)
int nums[NUM];
int primes[NP];
int np = 0;
//#define S
struct triplet
{
	int a;
	int b;
	int c;
};

void printNums()
{
	for(int i=0;i<NUM;i++)
	{
		if(nums[i]==0)
		{
			printf("%d\n",i);
		}
	}
}

void init()
{
	for(int i =0; i<NUM;i++)
	{
		nums[i]=0;
	}
}
void genPrimes()
{
	nums[0]=1;
	nums[1]=1;
	nums[2]=0;
	{

		for(int i = 2;i<NUM;i++)
		{
			int itrn=NUM/i;
			if(nums[i]==0)
			{
				if(i>1000)
				{
					primes[np]=i;
					np++;
				}
				for(int j=2;j<=itrn;j++)
				{
					nums[i*j]=1;
				}
			}
		}

	}
}

void addToSet(int *set,int i)
{
	if(i>=0&& i<10)
		set[i]++;
}

void reSet(int *set)
{
	for(int i=0;i<10;i++)
		set[i]=0;
}

int inset(int *set,int k)
{
	//TEST(k);
	if(set[k]==0)
		return 0;
	else return 1;
}
void splitToSet(int *set,int n)
{
	while(n)
	{
		addToSet(set,n%10);
		n/=10;
	}
}

int compareSet(int*set1,int*set2)
{
	for(int i=0;i<10;i++)
	{
		if(set1[i]!=set2[i])
			return 0;
	}
	return 1;
}
#ifdef S
int main()
{
	clock_t begin = clock();
	init();
	genPrimes();
	int *set1=malloc(sizeof(int)*10);
	int *set2=malloc(sizeof(int)*10);
	int *set3=malloc(sizeof(int)*10);

 	for(int i=0;i<np-2;i++)
	{	reSet(set1);
		splitToSet(set1,primes[i]);
		/*printf("%d:",primes[i]);
		for(int asd=0;asd<10;asd++)
		{
			printf("%d ",set[asd]);
		}
		printf("\n");*/

		for(int j=i+1;j<np;j++)
		{
			//TEST(1);

			int diff = primes[j]-primes[i];
			int p2 = primes[j]+diff;


			if(p2<NUM && nums[p2]==0)
			{
				reSet(set2);
				splitToSet(set2,primes[j]);
				if(compareSet(set1,set2))
				{
					reSet(set3);
					splitToSet(set3,p2);
					if(compareSet(set2,set3))
						printf("ans:%d,%d,%d\n",primes[i],primes[j],p2);
				}

			}
		}
	}
 	clock_t end = clock();
 	long elapsed=end-begin;
	printf("%ld\n\n",elapsed);
	return 0;
}
#endif

#ifndef  S
int main()
{
	clock_t begin = clock();
	init();
	genPrimes();

	#pragma omp parallel
	{
		int *set1=malloc(sizeof(int)*10);
		int *set2=malloc(sizeof(int)*10);
		int *set3=malloc(sizeof(int)*10);
		#pragma omp for schedule(dynamic)
		for(int i=0;i<np-2;i++)
		{	reSet(set1);
			splitToSet(set1,primes[i]);
			/*printf("%d:",primes[i]);
			for(int asd=0;asd<10;asd++)
			{
				printf("%d ",set[asd]);
			}
			printf("\n");*/

			for(int j=i+1;j<np;j++)
			{
				//TEST(1);

				int diff = primes[j]-primes[i];
				int p2 = primes[j]+diff;


				if(p2<NUM && nums[p2]==0)
				{
					reSet(set2);
					splitToSet(set2,primes[j]);
					if(compareSet(set1,set2))
					{
						reSet(set3);
						splitToSet(set3,p2);
						if(compareSet(set2,set3))
							printf("ans:%d,%d,%d\n",primes[i],primes[j],p2);
					}

				}
			}
		}
	}
 	clock_t end = clock();
 	long elapsed=end-begin;
	printf("%ld\n\n",elapsed);
	return 0;
}
#endif
