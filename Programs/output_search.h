#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <conio.h>
#include "readfile.h"

using namespace std;

#ifndef OUTPUT_SEARCH_H_INCLUDED
#define OUTPUT_SEARCH_H_INCLUDED

void w_search (string filename,int *cnt)
{
    double *arr=getarray(676);
    double *carr=getarray(677);
    int i,j,k;
    cnt[0]=0;
    cnt[1]=0;
    char c1,c2;
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open())
    {
        cout<<"Error opening file";
        getch();
        return;
    }
    else
    {
        infile>>c1;
        while (!infile.eof())
        {
            while (int(c1)<65 || int(c1)>90)
            {
                if (int(c1)<97 || int(c1)>122)
                {
                    if (!infile.eof())
                        infile>>c1;
                    else
                        break;
                }
                else
                    break;
            }
            infile>>c2;
            if (infile.eof())
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
    infile.close();
    nlize(arr);
    infile.open("E://data//PC.txt",ios::in);                //Replace by location of file containing the principal component
    infile>>k;
    int sel[k];
    double *pc=getarray(k);
    for (i=0;i<k;i++)
        infile>>sel[i];
    for (i=0;i<k;i++)
        infile>>pc[i];
    infile.close();
    double mini=700,dist;
    infile.open("E://data//Means.txt",ios::in);             //Replace by location of file containing means of individual authors
    char ch;
    while (!infile.eof())
    {
        for (i=0;i<677;i++)
        {
            infile>>carr[i];
        }
        if (!infile.eof())
        {
            dist=0;
            for (i=0;i<k;i++)
                dist+=abs((arr[sel[i]]-carr[sel[i]+1])*pc[i]);
            if (dist<mini)
            {
                mini=dist;
                cnt[1]=cnt[0];
            }
            cnt[0]++;
        }
    }
    infile.close();
    return;
}

#endif // OUTPUT_SEARCH_H_INCLUDED
