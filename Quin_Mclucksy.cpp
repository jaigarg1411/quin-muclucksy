#include <iostream>
#include <list>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include <cstring>
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

struct Implicant{
  int* array;
  int size;

  Implicant(int _size)
  {
    size = _size;
    array = new int[size];
  }

  Implicant(int _size, Implicant i1, Implicant i2)
  {
		size = _size;
		Implicant e(size);
		array = new int[size];
		int n1 = size/2;
		int i,j;
		for(i=0;i<n1;i++)
		{
			array[i] = i1.array[i];
		}
		for(j=n1;j<size;j++)
		{
			array[j] = i2.array[j-n1];
		}

		sort(array,array+size);
  }
};

struct Bucket{
  list<Implicant> implicants;
};

struct BucketStore{
  stack<Bucket*> store;
};

int largest_minterm(list<int> minterms)
{
  list<int> :: iterator it;
  int max = *minterms.begin();
  for(it = minterms.begin(); it != minterms.end(); ++it)
  {
    if(*it > max)
    {
      max = *it;
    }
  }

  return max;
}

int number_of_1(int m)
{
  bitset <no_bits> bin = dec2bin(m);
  int i,count = 0;
  for(i=0;i<32;i++)
  {
    if(bin[i] == 1)
    {
      count++;
    }
  }
  return count;
}

bool check(int m, int n)
{
  int k = m-n;
  int l = log2(k);
  int p = pow(2,l);

  if(p == k)
  return true;
  else
  return false;
}

bool check_array(Implicant i1,Implicant i2)
{
	int i,temp=0;
	bool n;
	n = check(i1.array[0],i2.array[0]);
	if(n == false)
	{
		return false;
	}
	else
	{
		for(i=1;i<i1.size;i++)
		{
			if((check(i1.array[i],i2.array[i]) == false) || ((i1.array[i] - i2.array[i]) != (i1.array[0] - i2.array[0])))
			{
				temp = 1;
			}
		}

		if(temp == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool isSuperset(Implicant recent,Implicant old)
{
	int n1 = old.size;
	int n2 = recent.size;
	int o[n1],r[n2];
	int i,j;
	for(i=0;i<n1;i++)
	{
		o[i] = old.array[i];
	}
	for(i=0;i<n2;i++)
	{
		r[i] = recent.array[i];
	}
	int temp=0;
	for(i=0;i<n2;i++)
	{
		for(j=0;j<n1;j++)
		{
			if(r[i] == o[j])
			break;
		}
		if(j == n1)
		{
			temp = 1;
			break;
		}
	}

	if(temp == 0)
	return true;
	else
	return false;
}

bool present(int q,Implicant ii)
{
	int l;
	int s = ii.size;
	bool temp = false;
	for(l=0;l<s;l++)
	{
		if(q == ii.array[l])
		{
			temp = true;
			break;
		}
	}
	return temp;
}

bool check_implicant(Implicant i1,Implicant i2)
{
	int n1 = i1.size;
	int n2 = i2.size;
	if(n1 != n2)
	return false;
	else
	{
		int i,temp=0;
		for(i=0;i<n1;i++)
		{
			if(i1.array[i] != i2.array[i])
			{
				temp=1;
				break;
			}
		}
		if(temp == 0)
		return true;
		else
		return false;
	}
}

void printlist(list<Implicant> l)
{
  list<Implicant> :: iterator i;
  for(i = l.begin(); i != l.end() ;i++)
  cout << i->array[0] << " "  << i->array[1] << " "  << i->array[2] << " "  << i->array[3] << "    ";
}

void print(list<int> l)
{
	list<int> :: iterator iii = l.begin();
	while(iii != l.end())
	{
		cout << *iii << "  ";
		iii++;
	}
}

int main()
{
	FILE* fp;
	fp = fopen("output.txt","r");
	char aa[2000][2000];
	int s=0,i;
  if(fp == NULL)
  {
    cout << "Error opening the input file!" << endl;
  }
  else
	{
    while((fgets(aa[s],2000,fp)))
    {
      s++;
    }
	}
	fclose(fp);
	cout << "Please wait while minimised expressions are calculated:-\n";
	cout << "Minimised Expressions are:-\n";
	for(int row = 1;row < s;row++)
	{
		list<int> minterms;
		i=7;
		char pl[20];
		for(int z=0;z<20;z++)
		{
			pl[z] = '\0';
		}
		int h=0;
		while(aa[row][i] != ')')
		{
			if(aa[row][i] == ',')
			{
				int n = 0;
				while(pl[n] != '\0')
				n++;
				int x=0,y=0;
				for(x=0;x<n;x++)
				{
					y = y*10 + (pl[x] - '0');
				}
				i++;
				h=0;
				minterms.push_back(y);
			}
			else if(aa[row][i]!=',')
			{
				pl[h] = aa[row][i];
				i++;
				h++;
			}
		}
		minterms.sort();
		i=0;

	  int size_of_bucket;
		int tbits;
	  size_of_bucket = ceil(log2(largest_minterm(minterms))) + 1;
		tbits = size_of_bucket;
	  Bucket* pBucket[size_of_bucket];
	  for(i=0;i<size_of_bucket;i++)
	  {
	    pBucket[i] = new Bucket;
	  }

	  BucketStore Bstore;

	  list<int> :: iterator it;
	  for(it = minterms.begin(); it != minterms.end(); ++it)
	  {
	    Implicant e(1);
	    e.array[0] = *it;
	    pBucket[number_of_1(e.array[0])]->implicants.push_back(e);
	  }

	  for(i=0;i<size_of_bucket;i++)
	  {
	    if(!pBucket[i]->implicants.empty())
	    Bstore.store.push(pBucket[i]);
	  }
		int count=0;
		int size_of_nbucket;
		while(1)
		{
			count = 0;
			size_of_nbucket = size_of_bucket - 1;
			Bucket* nBucket[size_of_nbucket];
		  for(i=0;i<size_of_nbucket;i++)
		  {
		    nBucket[i] = new Bucket;
		  }
			for(i=0;i<size_of_nbucket;i++)
			{
				list<Implicant> :: iterator it1;
				list<Implicant> :: iterator it2;
				for(it1 = pBucket[i]->implicants.begin();it1 != pBucket[i]->implicants.end();it1++)
				{
					for(it2 = pBucket[i+1]->implicants.begin();it2 != pBucket[i+1]->implicants.end();it2++)
					{
						bool temp1;
						temp1 = check_array(*it2,*it1);
						if(temp1)
						{
							Implicant i3(2*((*it1).size),*it1,*it2);
							nBucket[i]->implicants.push_back(i3);
							count++;
						}
					}
				}
			}
			for(i=0;i<size_of_nbucket;i++)
		  {
		    if(!nBucket[i]->implicants.empty())
		    Bstore.store.push(nBucket[i]);
		  }
			for(i=0;i<size_of_nbucket;i++)
			{
				pBucket[i] = nBucket[i];
			}
			size_of_bucket = size_of_nbucket;

			if((count == 0) || (count == 1))
			{
				break;
			}
		}

		Bucket prime_implicants;
		list<Implicant> :: iterator it1;
		it1 = Bstore.store.top()->implicants.begin();
		(prime_implicants).implicants.push_back(*it1);

		list<Implicant> :: iterator it2;
		it2 = prime_implicants.implicants.begin();
		while(!Bstore.store.empty())
		{
			for(it1 = Bstore.store.top()->implicants.begin();it1 != Bstore.store.top()->implicants.end();it1++)
			{
				bool temp2 = false;
				for(it2 = prime_implicants.implicants.begin();it2 != prime_implicants.implicants.end();it2++)
				{
					temp2 = isSuperset(*it1,*it2);
					if(temp2)
					{
						break;
					}
				}
				if(!temp2)
				{
					(prime_implicants).implicants.push_back(*it1);
				}
			}
			Bstore.store.pop();
		}

		Bucket ess_prime_implicants;

		list<int> :: iterator it3;
		list<Implicant> :: iterator it4;
		while(!minterms.empty())
		{
			it3 = minterms.begin();
			while(it3 != minterms.end())
			{
				int count = 0;
				int start = 0,ss;
				for(it4=prime_implicants.implicants.begin();it4 != prime_implicants.implicants.end();it4++)
				{
					bool temp3;
					temp3 = present(*it3,*it4);
					if(temp3)
					{
						ss = start;
						count++;
					}
					start++;
				}
				if(count==1)
				{
					list<Implicant> :: iterator tt;

					tt = prime_implicants.implicants.begin();
					start = 0;
					while(start != ss)
					{
						tt++;
						start++;
					}

					bool temp4 = false;
					for(it2 = ess_prime_implicants.implicants.begin();it2 != ess_prime_implicants.implicants.end();it2++)
					{
						temp4 = isSuperset(*tt,*it2);
						if(temp4)
						{
							break;
						}
					}
					if(!temp4)
					{
						(ess_prime_implicants).implicants.push_back(*tt);
					}
					}
					it3++;

			}

			list<Implicant> :: iterator m1;
			list<Implicant> :: iterator m2;
			list<int> :: iterator m3 = minterms.begin();

			while(m3 != minterms.end())
			{
				int t=0;
				for(m1 = ess_prime_implicants.implicants.begin();m1 != ess_prime_implicants.implicants.end();m1++)
				{
					if(present(*m3,*m1))
					{
						minterms.remove(*m3);
						m3 = minterms.begin();
						t=1;
						break;
					}
				}
				if(t==0)
				m3++;
			}

			m2 = prime_implicants.implicants.begin();
			while(m2 != prime_implicants.implicants.end())
			{
				int t1=0;
				for(m1 = ess_prime_implicants.implicants.begin();m1 != ess_prime_implicants.implicants.end();m1++)
				{
					if(check_implicant(*m1,*m2))
					{
						prime_implicants.implicants.erase(m2);
						m2 = prime_implicants.implicants.begin();
						t1=1;
						break;
					}
				}
				if(t1==0)
				m2++;
			}

			int a[prime_implicants.implicants.size()];
			for(i=0;i<prime_implicants.implicants.size();i++)
			{
				a[i] = 0;
			}

			list<Implicant> :: iterator it7;
			list<int> :: iterator it8;
			int count1 = 0;
			int p=0;
			for(it7 = prime_implicants.implicants.begin();it7 != prime_implicants.implicants.end();it7++)
			{
				count1 = 0;
				for(it8 = minterms.begin();it8 != minterms.end();it8++)
				{
					for(i=0;i<it7->size;i++)
					{
						if(it7->array[i] == *it8)
						{
							count1++;
							break;
						}
					}
				}
				a[p] = count1;
				p++;
			}
			int max = a[0],in=0;
			for(i=0;i<prime_implicants.implicants.size();i++)
			{
				if(a[i] > max)
				{
					max = a[i];
					in = i;
				}
			}
			if(!prime_implicants.implicants.empty())
			{
				it7 = prime_implicants.implicants.begin();
				for(i=0;i<in;i++)
				{
					it7++;
				}
				(ess_prime_implicants).implicants.push_back(*it7);


				if(!minterms.empty())
				m3 = minterms.begin();
				while(m3 != minterms.end())
				{
					int t=0;
					if(present(*m3,*it7))
					{
						minterms.remove(*m3);
						m3 = minterms.begin();
						t=1;
						break;
					}
					if(t==0)
					m3++;
				}

				m2 = prime_implicants.implicants.begin();
				while(m2 != prime_implicants.implicants.end())
				{
					int t1=0;
					if(check_implicant(*it7,*m2))
					{
						prime_implicants.implicants.erase(m2);
						m2 = prime_implicants.implicants.begin();
						t1=1;
						break;
					}
					if(t1==0)
					m2++;
				}
			}

		}

		list<Implicant> :: iterator i9;
		char ch[26];
		int j=7,i=0;
		while(aa[0][j] != '\n')
		{
			ch[i] = aa[0][j];
			i++;
			if(aa[0][j+1] != '\n')
			{
				j = j + 2;
			}
			else
			j++;
		}


		int jj=1;
		i9 = ess_prime_implicants.implicants.begin();
		cout << aa[row][0] << aa[row][1] << " = ";
		for(i9 = ess_prime_implicants.implicants.begin();i9!=ess_prime_implicants.implicants.end();i9++)
		{
			int size_ = ess_prime_implicants.implicants.size();
			int n3 = i9->size,j;
			int bits = tbits-1;
			int bi[n3][bits];
			for(i=0;i<n3;i++)
			{
				bitset<no_bits> binn;
				binn = dec2bin(i9->array[i]);
				for(j=0;j<bits;j++)
				{
					bi[i][bits-j-1] = binn[j];
				}
			}

			for(i=0;i<bits;i++)
			{
				int temp4=0,bit = bi[0][i];
				for(j=0;j<n3-1;j++)
				{
					if(bi[j][i] != bi[j+1][i])
					{
						temp4 = 1;
						break;
					}
				}
				if(temp4 == 0)
				{
					if(bit == 1)
					{
						cout << ch[i];
					}
					else
					{
						cout << ch[i] << "'";
					}
				}
			}

			if(jj != size_)
			cout << " + ";
			jj++;
		}
		printf("\b\n");
	}
}
