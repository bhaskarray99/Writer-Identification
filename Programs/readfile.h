#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <conio.h>

using namespace std;

#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

double *getarray(int n)
{
    double *A=0;
    A=new double[n];
    for (int i=0;i<n;i++)
        A[i]=0;
    return A;
}

void nlize (double *arr)
{
    int i;
    double norm_vec=0;
    for (i=0;i<676;i++)
        norm_vec+=(arr[i]*arr[i]);
    norm_vec=sqrt(norm_vec);
    norm_vec/=100;
    for (i=0;i<676;i++)
        arr[i]/=norm_vec;
}

void readf (string filename, double *marr, double *varr)
{
    int i,j,k;
    char c1,c2;
    double *arr=getarray(676);
    ifstream myfile;
    myfile.open(filename.c_str());
    if (myfile.is_open())
    {
        myfile>>c1;
        while (!myfile.eof())
        {
            while (int(c1)<65 || int(c1)>90)
            {
                if (int(c1)<97 || int(c1)>122)
                {
                    if (!myfile.eof())
                        myfile>>c1;
                    else
                        break;
                }
                else
                    break;
            }
            myfile>>c2;
            if (myfile.eof())
            {
                break;
            }
            if (int(c2)<=122 && int(c2)>=65)
            {
                if (int(c2)<=90 || int(c2)>=97)
                {
                    arr[(((int(c1)-65)%32)*26)+((int(c2)-65)%32)]++;
                }
            }
            c1=c2;
        }
    }
    myfile.close();
    nlize(arr);
    for (i=1;i<677;i++)
        marr[i]+=arr[i-1];
    k=0;
    for (i=0;i<676;i++)
    {
        for (j=0;j<676-i;j++)
        {
            varr[k]+=arr[j]*arr[j+i];
            k++;
        }
    }

    marr[0]++;
}

#endif // READFILE_H_INCLUDED
