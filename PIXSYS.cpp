#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;


typedef struct
{
   unsigned int width;
   unsigned int height;
   unsigned int planes;
   unsigned short bitcount;
   unsigned int size;
} BITMAPINFOHEADER;

typedef struct
{
   unsigned char blue;
   unsigned char green;
   unsigned char red;
}PIXEL;

int grey[1000000];
int maxe=0;

void extract()
{
	FILE *image;
    BITMAPINFOHEADER bih;
    int i=0,b[8],g[8],r[8];
    char path[100];
	char fpath[] = "C:\\";
    cout<<"Enter Name of the File:";
    cin>>path;
    strcat(fpath,path);
    strcat(fpath,".bmp");
    image=fopen(fpath,"rb");

    fseek(image,2,SEEK_SET);
    fread(&bih.size,4,1,image);
    fseek(image,18,SEEK_SET);
    fread(&bih.width,4,1,image);
    fseek(image,22,SEEK_SET);
    fread(&bih.height,4,1,image);
    fseek(image,26,SEEK_SET);
    fread(&bih.planes,2,1,image);
    fseek(image,28,SEEK_SET);
    fread(&bih.bitcount,2,1,image);
    PIXEL pic[bih.width*bih.height*2],p;
    fseek(image,54,SEEK_SET);

    int sum=0;
    maxe=0;
    for(i=0;i<bih.width*bih.height;i++)
    {
        fread(&p.blue,sizeof(p.blue),1,image);
        fread(&p.green,sizeof(p.green),1,image);
        fread(&p.red,sizeof(p.red),1,image);
        pic[i]=p;
        sum=((pic[i].red + pic[i].green + pic[i].blue)/3);
        grey[i]=sum;
    }
    maxe=i;
    fclose(image);
}

int hb[256];
void histogram()
{
	for(int x=0;x<=255;x++)
	{
		hb[x]=0;
	}
	for(int i=0;i<maxe;i++)
	{
		for(int j=0;j<=255;j++)
		{
			if(grey[i]==j)
			{
				hb[j]++;
				break;
			}
		}
    }
}

void display_histo()
{
	for(int i=0;i<256;i++)
	{
		cout<<i<<" intensity : ";
		for(int j=0;j<(hb[i]/40);j++)
		{
			cout<<"|";
		}
		cout<<endl;
	}
}

double cal_1degreemean(int ar[])
{
	double tsum=0;
	double tinten=0;
	double mean;
	for(int i=0;i<maxe;i++)
	{
		double x = grey[i];
		tsum=tsum+x;
		tinten=tinten+(i+1);
	}
	mean=(tsum/(maxe-1));
	return mean;
}

double cal_1degreeDeviation(int ar[],double m)
{
	double tdiff=0;
	double tsq=0;
	double tsqsum=0;
	double tinten=0;
	double tsqrt=0;
	double var=0;

	for(int i=0;i<maxe;i++)
	{
		double x = ar[i];
		tdiff=(x-m);
		tsq=tdiff*tdiff;
		tsqsum=tsqsum+tsq;
		tinten=tinten+(i+1);
	}
	var=(tsqsum/(maxe-1));
	tsqrt=sqrt(var);
	return tsqrt;
}

struct HASH
{
	int key[10];
	char text[100];
}HASH;

struct HASH hashtable[10000];
int checktable[10000]={0};
int t;

int hashfunction(int key)
{
		int tindex=0;
		int dcube=0,dsqr=0,tind=0;
		while(key!=0)
		{
			dcube=((key%10)*(key%10)*(key%10));
			tind=tind+dcube;
			key=key/10;
		}
		while(tind!=0)
		{
			dsqr=((tind%10)*(tind%10));
			tindex=tindex+dsqr;
			tind=tind/10;
			dsqr=((tind%10)*(tind%10)*(tind%10));
			tindex=tindex+dsqr;
			tind=tind/10;
		}
		return tindex;
}

void hashtable_insert(int x)
{
	int index=0;
	char name[100];
	
	

	index=hashfunction(x);
	if(checktable[index]==0)
	{
		hashtable[index].key[1]=x;
		cout<<"Enter the name of the user : ";
		cin>>name;
		int l=strlen(name);
		for(int j=0;j<l;j++)
		{
			hashtable[index].text[j]=name[j];
		}
		checktable[index]=1;
	}
	else if(checktable[index]==1)
	{
		index=index+1;
		hashtable[index].key[1]=x;
		cin>>name;
		int l=strlen(name);
		for(int j=0;j<l;j++)
		{
			hashtable[index].text[j]=name[j];
		}
		checktable[index]=1;
	}
}

int hashtable_search(int key)
{
	 int searchind=hashfunction(key);

	 if(hashtable[searchind].key[1]==key)
	 {
		 return searchind;
	 }
	 else if(hashtable[searchind].key[1]!=key)
	 {
		 for(int i=searchind;i<10000;i++)
		 {
			 if(hashtable[i].key[1]==key)
			 {
				 return i;
				 break;
		     }
		     else
		     {
				 continue;
			 }
		 }
	 }
}



int main()
{
	system("color 2F");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t                           WELCOME TO PIXSYS");
	
	system ("cls");
	printf("\n\n\n\t\t\t\t\tPIXSYS");
	printf("\n\n\n\n\n\n\n\t\t Developed by  ");
	printf("Hemanth Kollipara");
	
	printf("\n\n\n\n\t\tLoading...\t");
	system("cls");

	int choice=0;
	int choice1=0,choice2=0,choice3=0;
	int ascode=0,top=0;
	double remean[1000]={0};
	double resd[1000]={0};
	double distvect[1000]={0};
	double distvects[1000]={0};
	do
    {
		cout<<endl<<" ********************************************";
		cout<<endl<<"|  1.IMAGE ANALYSIS                          |"<<endl;
		cout<<"|  2.RETRIVE SIMILAR IMAGES FROM DATABASE    |"<<endl;
		cout<<"|  3.FINGERPRINT VERIFICATION                |"<<endl;
		cout<<"|  4.EXIT FROM PIXSYS                        |"<<endl;
		cout<<" ********************************************"<<endl<<endl;
		cout<<"*********************************************"<<endl;
		cout<<"Enter your choice : ";
		cin>>choice;

		if(choice==1)
		{
			extract();
			histogram();
			cout<<endl<<endl<<"HISTOGRAM FOR THE INPUT IMAGE"<<endl;
			display_histo();
			double br = cal_1degreemean(grey);
			double con = cal_1degreeDeviation(grey,br);
			cout<<"\nOVERALL BRIGHTNESS OF THE IMAGE : "<<br<<endl<<endl;
			cout<<"OVERALL CONTRAST OF THE IMAGE : "<<con<<endl<<endl;
	    }
	    
	    
	    
	    
	    
	    else if(choice==2)
		{
			do
			{
				cout<<endl<<"1.UPLOAD IMAGES INTO DATABASE";
				cout<<endl<<"2.RETRIEVE SIMILAR IMAGES FROM THE UPLOADED IMAGES";
				cout<<endl<<"3.BACK INTO PREVIOUS MENU"<<endl;
				cout<<endl<<"Enter you choice : ";
				cin>>choice3;
				if(choice3==1)
				{
					cout<<endl<<endl<<"Enter the file to be uploaded"<<endl;
					extract();
					double b3=cal_1degreemean(grey);
					double c3=cal_1degreeDeviation(grey,b3);
					top=top+1;
					remean[top]=b3;
					resd[top]=c3;
					if(b3&&c3>0)
					{
						cout<<endl<<"Successfully Uploaded !!"<<endl;
					}
					else
					{
						cout<<endl<<"File Not Found !!"<<endl;
					}
				}
				else if(choice3==2)
				{
					cout<<endl<<"Enter the file for which similar images have to be retrived"<<endl;
					extract();
					double b4=cal_1degreemean(grey);
					double c4=cal_1degreeDeviation(grey,b4);
					for(int i=1;i<=top;i++)
					{
						distvect[i]=((b4-remean[i])+(c4-resd[i]));
						distvects[i]=((b4-remean[i])+(c4-resd[i]));
						if(distvect[i]<0)
						{
							distvect[i] = -distvect[i];
							distvects[i] = -distvects[i];
						}
					}
					for(int x=1;x<top;x++)
					{
						for(int y=1;y<top;y++)
						{
							double temp=0;
							if(distvects[y]>distvects[y+1])
							{
								temp=distvects[y];
								distvects[y]=distvects[y+1];
								distvects[y+1]=temp;
							}
						}
					}
					int inda[100];
					int ii=0;
					for(int i=1;i<=top;i++)
					{
						for(int j=1;j<=top;j++)
						{
							if(distvects[i]==distvect[j])
							{
								ii=ii+1;
								inda[i]=j;
							}
						}
					}
					cout<<endl;
					cout<<" *********************************"<<endl;
					cout<<"|  Indexes of similar images are"<<endl;
					for(int i=1;i<=top;i++)
					{
						int x = inda[i];
						if(100-distvect[x]<0)
						{
							distvect[x]=100;
						}
						cout<<"|  "<<inda[i]<<" matched by "<<100-distvect[x]<<"%"<<endl;
					}
				}
			}
			while(choice3!=3);
		}
		
		else if(choice==3)
		{
			do
			{
				cout<<"\n1.UPLOAD FINGERPRINT";
				cout<<"\n2.VERIFY FINGERPRINT";
				cout<<"\n3.BACK TO PREVIOUS MENU\n";
				cout<<"Enter you choice : ";
				cin>>choice2;
				if(choice2==1)
				{
						cout<<"\nEnter the file to be uploaded\n";
						extract();
						double br1 = cal_1degreemean(grey);
						int br1x=br1*1000;
						hashtable_insert(br1x);
						cout<<"\nSuccessfully Uploaded !!"<<endl;
				}
				else if(choice2==2)
				{
					cout<<"\nEnter the file to be verified\n";
					extract();
					double br2 = cal_1degreemean(grey);
					int br2x=br2*1000;
					int index2=hashtable_search(br2x);
					if(index2!=0)
					{
						cout<<"**************"<<endl<<hashtable[index2].text<<" Verified !"<<endl<<"**************";
					}
					else
					{
						cout<<"**************\nNOT Verified !\n**************";
					}
				}
			}
			while(choice2!=3);
		}
		
	 }
	 while(choice!=3);
}	

