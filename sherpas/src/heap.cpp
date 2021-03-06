/*
 * heap.cpp
 *
 *  Created on: 19 févr. 2019
 *      Author: scholz
 */

#include<iostream>
#include<fstream>
#include<vector>
#include <string>
#include<cmath>
#include "heap.h"

using namespace std;
//basic operation to maintain the result as a heap at each step of the main algorithm, and to extract at any time a "top arcs" from the heap.

Htree::Htree(std::vector<Arc*> res)
{
	m_res=res;
}

void Htree::Hempty()
{
	std::vector<Arc*> res(0);
	m_res=res;
}


Arc* Htree::h(int i)
{
	int s=m_res.size();
	if(i<0 || i>s-1)
	{
		cout << "No element in place " << i << " in the list" << endl;
	}
	return m_res[i];
}

int Htree::hPlace(int i)
{
	int s=m_res.size();
	if(i<0 || i>s-1)
	{
		cout << "No element in place " << i << " in the list" << endl;
	}
	return (*m_res[i]).getPlace();
}

double Htree::hScore(int i)
{
	int s=m_res.size();
	if(i<0 || i>s-1)
	{
		cout << "No element in place " << i << " in the list" << endl;
	}
	return (*m_res[i]).getScore();
}

int Htree::parent(int i)
{
	int r=-1;
	int s=m_res.size();
	if(i>0 && i<s)
	{
		r=(i-1)/2;
	}
	return r;
}

int Htree::left(int i)
{
	int r=2*i+1;
	int s=m_res.size();
	if(r<1 || r>(s-1))
	{
		r=-1;
	}
	return r;
}

int Htree::right(int i)
{
	int r=2*i+2;
	int s=m_res.size();
	if(r<1 || r>(s-1))
	{
		r=-1;
	}
	return r;
}

void Htree::print(int m, std::vector<std::string> ref)
{
	int s=m_res.size();
	if(m>s || m<0)
	{
		m=s;
	}
	for(int i=0; i<m; i++)
	{
		cout << i+1 << ". ";
		(*m_res[i]).printPlace(ref);
		cout << ": " << (*m_res[i]).getScore() << endl;
	}
}

int Htree::size()
{
	return m_res.size();
}

void Htree::swap(int i, int j)
{
	(*m_res[j]).updateCheck(i);
	(*m_res[i]).updateCheck(j);
	Arc* temp=m_res[i];
	m_res[i]=m_res[j];
	m_res[j]=temp;
}

void Htree::push(Arc* a)
{
	int s=m_res.size();
	(*a).updateCheck(s);
	m_res.push_back(a);
	heapUp(s);
}

void Htree::pop(int i)
{
	int s=m_res.size();
	if(i>-1 && i<s)
	{
		swap(i,s-1);
		m_res.pop_back();
		heapUp(i);
		heapDown(i);
	}
}

void Htree::heapDown(int i)
{
	int s=m_res.size();
	int c=0;
	int l=-1;
	int r=-1;
	int largest=i;
	while(c==0)
	{
		c=1;
		if(i>-1 && i< s)
		{
			l = left(i);
			r = right(i);
			if (l > -1 && hScore(l) > hScore(i))
			{
				largest = l;
			}
			if (r>-1 && hScore(r) > hScore(largest))
			{
				largest = r;
			}
			if (largest != i)
			{
				swap(i, largest);
				c=0;
				i=largest;
			}
		}
	}
}

void Htree::heapUp(int i)
{
	int s=m_res.size();
	int c=0;
	int p=-1;
	while(c==0)
	{
		c=1;
		if(i>0 && i< s)
		{
			p=parent(i);
			if(p>-1 && hScore(p)<hScore(i))
			{
				swap(i,p);
				c=0;
				i=p;
			}
		}
	}
}

void Htree::getTop(int m)
{
	std::vector<Arc*> temp(0);
	int s=m_res.size();
	if(m<0||m>s)
	{
		m=s;
	}
	if(m>2)
	{
		for(int i=0;i<m; i++)
		{
			temp.push_back(m_res[0]);
			swap(0,m_res.size()-1);
			m_res.pop_back();
			heapDown(0);
			(*(temp)[i]).updateCheck(i);
		}
		for(int i=m; i<s;i++)
		{
			temp.push_back(m_res[i-m]);
			(*temp[i]).updateCheck(i);
		}
		m_res=temp;
	}
	if(m==2 && (*m_res[1]).getScore()<(*m_res[2]).getScore())
	{
		swap(1,2);
		heapDown(2);
	}
}

double Htree::lRatio(int k)
{
	int s=m_res.size();
	double q=0;
	for(int j=0; j<s;j++)
	{
		q+=(pow(10,((*m_res[j]).getScore()-(*m_res[0]).getScore())/k))*((*m_res[j]).getScore() !=0);
	}
	return 1/q;

}

double Htree::dRatio(int k)
{
	return pow(10,((*m_res[0]).getScore()-(*m_res[1]).getScore())/k);

}

