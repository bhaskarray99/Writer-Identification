#include <fstream>
#include <iostream>
#include "readfile.h"
#include <math.h>

using namespace std;

#ifndef PROCESS_DATA_H_INCLUDED
#define PROCESS_DATA_H_INCLUDED

#define tol 0.1

void red_sto_mat(double *vmarr,double *mvarr)
{
    int i,j,k,s;
    vector<int> sel;
    for (i=0;i<676;i++)
    {
        if (abs(vmarr[i])>tol)
            sel.push_back(i);
    }
    s=sel.size();
    k=0;
    ofstream fw;
    fw.open("E://data//Var_mean.txt",ios::out|ios::trunc);      //Replace by location of file containing inter-author var-cov matrix
    for (i=0;i<s;i++)
    {
        for (j=0;j<s;j++)
        {
            if (j<i)
                fw<<vmarr[((sel[i]-sel[j])*(1353-sel[i]+sel[j])/2)+sel[j]]<<"\t";
            else
                fw<<vmarr[((sel[j]-sel[i])*(1353-sel[j]+sel[i])/2)+sel[i]]<<"\t";
        }
        fw<<endl;
    }
    fw.close();
    fw.open("E://Mean_var.txt",ios::out|ios::trunc);        //Replace by location of file containing mean intra-author var-cov matrix
    for (i=0;i<s;i++)
    {
        for (j=0;j<s;j++)
        {
            if (j<i)
                fw<<mvarr[((sel[i]-sel[j])*(1353-sel[i]+sel[j])/2)+sel[j]]<<"\t";
            else
                fw<<mvarr[((sel[j]-sel[i])*(1353-sel[j]+sel[i])/2)+sel[i]]<<"\t";
        }
        fw<<endl;
    }
    fw.close();
    fw.open("E://data//PC.txt",ios::out|ios::trunc);        //Replace by location of file containing principal component values
    for (i=0;i<s;i++)
        fw<<sel[i]<<"\t";
    fw.close();

}

void tot_var()
{
    int i,j,k;
    char ch;
    double *marr=getarray(677);
    double *mmarr=getarray(677);
    double *varr=getarray(228826);
    double *vmarr=getarray(228826);
    double *mvarr=getarray(228826);
    ifstream infile;
    infile.open("E://data//Means.txt",ios::in|ios::binary);             //Replace by location of file containing means of individual authors
    while (!infile.eof())
    {
        for (i=0;i<677;i++)
        {
            infile>>marr[i];
        }
        if (!infile.eof())
        {
            k=0;
            for (i=0;i<676;i++)
            {
                mmarr[i+1]+=marr[i+1];
                for (j=0;j<676-i;j++)
                {
                    vmarr[k]+=marr[j+1]*marr[j+i+1];
                    k++;
                }
            }
            mmarr[0]++;
        }
    }
    infile.close();
    k=0;
    for (i=0;i<676;i++)
    {
        mmarr[i+1]/=mmarr[0];
        for (j=0;j<676-i;j++)
        {
            vmarr[k]=(vmarr[k]/mmarr[0])-(mmarr[j+1]*mmarr[j+i+1]);
            k++;
        }
    }
    infile.open("E://data//Variance-covariance matrices.txt");          //Replace by location of file containing var-cov matrices of individual authors
    if (!infile.is_open())
        cout<<"Error opening file"<<endl;
    while (!infile.eof())
    {
        for (i=0;i<228826;i++)
            infile>>varr[i];
        infile.read(&ch,1);
        if (!infile.eof())
        {
            for (i=0;i<228826;i++)
                mvarr[i]+=varr[i];
        }
    }
    infile.close();
    for (i=0;i<228826;i++)
        mvarr[i]/=mmarr[0];
    red_sto_mat(vmarr,mvarr);
}
#endif // PROCESS_DATA_H_INCLUDED
