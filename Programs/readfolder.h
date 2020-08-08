#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <windows.h>
#include "readfile.h"

using namespace std;

#ifndef READFOLDER_H_INCLUDED
#define READFOLDER_H_INCLUDED

void read_directory(string name, string wname)
{
    system("CLS");
    int i,j,k;
    vector<string> v;
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    if ((dp = readdir(dirp)) == NULL)
    {
        cout<<"Folder not found or folder empty"<<endl;
        Sleep(2000);
        return;
    }
    else
        v.push_back(dp->d_name);
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
    double *marr=getarray(677);
    double *varr=getarray(228826);
    for(int i=2;i<v.size();i++)
    {
        cout<<v[i]<<"\t \t Reading";
        readf(name+"//"+v[i],marr,varr);
        cout<<"\b\b\b   "<<endl;
    }
    cout<<"Writing data to file"<<endl;
    for (i=1;i<677;i++)
        marr[i]/=marr[0];
    for (i=0;i<228826;i++)
        varr[i]/=marr[0];
    k=0;
    for (i=0;i<676;i++)
    {
        for (j=0;j<676-i;j++)
        {
            varr[k]-=marr[j+1]*marr[j+i+1];
            k++;
        }
    }
    k=marr[0];
    marr[0]=0;
    nlize(marr);
    marr[0]=k;
    ofstream idfile;
    idfile.open("E://data//Means.txt",ios::app);              //Replace by location of file containing means of individual authors
    for (i=0;i<677;i++)
        idfile<<marr[i]<<"\t";
    idfile.close();
    idfile.open("E://data//Variance-covariance matrices.txt",ios::app);             //Replace by location of file containing var-cov matrices of individual writer
    for (i=0;i<228826;i++)
        idfile<<varr[i]<<"\t";
    idfile.close();
    idfile.open("E://data//Names.txt",ios::app);            //Replace by location of file containing names of authors
    idfile<<wname<<endl;
    idfile.close();
}


#endif // READFOLDER_H_INCLUDED
