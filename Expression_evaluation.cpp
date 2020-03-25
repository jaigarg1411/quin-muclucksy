#include <iostream>
#include <string>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;
#define no_bits 32

bitset <no_bits> dec2bin(unsigned int deci)
{
	bitset <no_bits> bin;
	int i=0;
	while(deci!=0)
	{
		bin[i] = deci%2;
		deci /= 2;
		i++;
	}
	return bin;
}

int min_term(int in,char inp1[100],int tru[100],char str[2000])
{
  int m=0,n=1;
	int k=0,i=0;
  while(str[k] != ' ')
  {
    k++;
  }
  k++;
	// Calculating min terms for SOP --------------------------------------------
	if(str[k] != '(')
	{
	  while(1)
	  {
			if(str[k] == '\n')
			{
				break;
			}

			else if((str[k] == ' '))
			{
				k = k + 3;
			}
			else
			{
				int p=1;
		    while(1)
				{
					if((str[k] == '\n') || (str[k] == ' '))
					{
						break;
					}
					else
					{
						int index;
						for(i=0;i<in;i++)
						{
							if(str[k] == inp1[i])
							{
								index = i;
								break;
							}
						}
			      if(((str[k+1] >= 'a') && (str[k+1] <= 'z')) || (str[k+1] == ' ') || (str[k+1] == '\n'))
			      {
			        p = p * tru[index];
			      }
			      else
			      {
			        if(tru[index] == 1)
			        {
			          p = p*0;
			        }
			        else
			        {
			          p = p*1;
			        }
							k++;
			      }
						k++;
					}
				}
				m = m+p;
	  	}
		}
		return m;
	}
	// Calculating min terms for POS -------------------------------------------
	else
	{
		while(1)
		{
			if(str[k] == '\n')
			{
				break;
			}
			else if(str[k] == ')')
			{
				if(str[k+1] == '\n')
				{
					k++;
				}
				else
				{
					k = k + 2;
				}
			}
			else if(str[k] == '(')
			{
				k++;
			}
			else
			{
				int p = 0;
				while(1)
				{
					if((str[k] == ')') || (str[k] == '\n'))
					{
						break;
					}
					else if(str[k] == ' ')
					{
						k = k + 3;
					}
					else if(str[k] == '+')
					{
						k = k + 2;
					}
					else
					{
						int index;
						for(i=0;i<in;i++)
						{
							if(str[k] == inp1[i])
							{
								index = i;
								break;
							}
						}
						if((str[k+1] == ' ') || (str[k+1] == ')'))
						{
							p = p + tru[index];
						}
						else
						{
							if(tru[index] == 0)
							{
								p = p + 1;
							}
							else
							{
								p = p + 0;
							}
							k++;
						}
						k++;
					}
				}
				n = n * p;
			}
		}
		return n;
	}
}

int main()
{
  FILE* fp;
  fp = fopen("input.txt","r");
	FILE* fp1;
	fp1 = fopen("output.txt","w");
	char a[2000][2000];
	char inp[2000];
	int i=0,j=0;
  if((fp == NULL) || (fp1 == NULL))
  {
    cout << "Error opening the input file!" << endl;
  }
  else
	{
    while((fgets(a[i],2000,fp)))
    {
      i++;
    }
	}
	fclose(fp);
    i=0;
    int in=0,out=0;
    int k = 0;
    while(a[0][k] != ' ')
    {
      k++;
    }
    k++;
    while(a[0][k] != '\n')
    {
      if((a[0][k] >= 'a') && (a[0][k] <= 'z'))
      {
        inp[i] = a[0][k];
        i++;
        in++;
      }
      k++;
    }
    k=0;
    while(a[1][k] != ' ')
    {
      k++;
    }
    k++;
    while(a[1][k] != '\n')
    {
      if((a[1][k] == ' '))
      {
        k++;
      }
      else
			{
				out++;
				k++;
			}
    }
		int n = pow(2,in);
    int truth[n][in];
    for(i=0;i<n;i++)
    {
      bitset <no_bits> bin;
      bin = dec2bin(i);
      for(j=0;j<in;j++)
      {
        truth[i][in-j-1] = bin[j];
      }
    }
		char inp1[in];
		for(k=0;k<in;k++)
		{
			inp1[k] = inp[in-k-1];
		}
    fprintf(fp1,"%s",a[0]);
    for(i=0;i<out;i++)
    {
			fprintf(fp1,".%c = m(",a[i+2][1]);
      for(j=0;j<n;j++)
      {
        int m;
				m = min_term(in,inp,truth[j],a[i+2]);
        if(m > 0)
        {
          fprintf(fp1,"%d,",j);
        }
      }
      fprintf(fp1,")\n");
    }
}
