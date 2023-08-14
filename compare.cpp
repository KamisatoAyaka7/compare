#include<iostream>
#include<fstream>
#include<unistd.h>
#include<thread>

#define once_length 1024

using namespace std;

long long s1=0,s2=0,l1=0;

void show()
{
    while(l1<s1-once_length)
    {
	printf("%lld / ",l1);
	printf("%lld (bytes)\n",s1);
	sleep(1);
    }
}

short compare(char *p1,char *p2)
{
    for(short s1=0;s1<once_length;s1++)
    {
	if(*p1!=*p2)
	{
	    return s1;
	}
    }
    return once_length;
}

int main(int argc,char *argv[])
{
    if(argc==3)
    {
	ifstream f1(argv[1],ios::in|ios::binary);
	ifstream f2(argv[2],ios::in|ios::binary);
	if(!f1)
	{
	    printf("%s doesn't exist.\n",argv[1]);
	    f1.close();
	    f2.close();
	    return 0;
	}
	if(!f2)
	{
	    printf("%s doesn't exist.\n",argv[2]);
	    f1.close();
	    f2.close();
	    return 0;
	}
	f1.seekg(0,ios::end);
	f2.seekg(0,ios::end);
	s1=f1.tellg();
	s2=f2.tellg();
	if(s1!=s2)
	{
	    printf("Their lengths are different.\n");
	    printf("File1: %lld\n",s1-1);
	    printf("File2: %lld\n",s2-1);
	    f1.close();
	    f2.close();
	    return 1;
	}
	else
	{
	    short s3=0;
	    char c1[once_length],c2[once_length];
	    thread th1(show);
	    th1.detach();
	    for(l1=0;l1<s1-once_length;l1+=once_length)
	    {
		f1.seekg(l1,ios::beg);
		f2.seekg(l1,ios::beg);
		f1.read(c1,once_length);
		f2.read(c2,once_length);
		s3=compare(c1,c2);
		if(once_length!=s3)
		{
		    printf("Their contents are different.\n");
		    printf("Address: %lld\n",l1+s3+1);
		    f1.close();
		    f2.close();
		    return 1;
		}
	    }
	    for(;l1<s1;l1++)
	    {
	        f1.seekg(l1,ios::beg);
		f2.seekg(l1,ios::beg);
		f1.read(c1,1);
		f2.read(c2,1);
		if(c1[0]!=c2[0])
		{
	            printf("Their contents are different.\n");
		    printf("Address: %lld\n",l1+1);
		    f1.close();
		    f2.close();
		    return 1;
		}
	    }
	    printf("They are the same.\n");
	    f1.close();
	    f2.close();
	    return 2;
	}
    }
    else if(argc==1)
    {
	printf("compare -file1 -file2\n");
	return 1;
    }
    return 0;
}
