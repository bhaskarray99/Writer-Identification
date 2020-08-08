#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include "output_search.h"

using namespace std;

#ifndef CONFUSION_MATRIX_H_INCLUDED
#define CONFUSION_MATRIX_H_INCLUDED

void create_cmat()
{
    ifstream ifile;
    string fname,wname;
    int *cnt=0;
    cnt=new int[2];
    int i,j;
    vector<string> v,w;
    ifile.open("E://data//Names.txt");                  //Replace by location of file containing names of authors
    while (!ifile.eof())
    {
        getline(ifile,wname);
        if (!ifile.eof())
        {
            w.push_back(wname);
        }
    }
    ifile.close();
    int cfmat[w.size()][w.size()];
    for (i=0;i<w.size();i++)
    {
        for (j=0;j<w.size();j++)
            cfmat[i][j]=0;
    }
    cin.ignore();
    loop:
    for (i=0;i<w.size();i++)
    {
        system("CLS");
        cout<<"Specify folder for "<<w[i]<<":\t";
        getline(cin,fname);
        cout<<fname<<endl;
        DIR* dirp = opendir(fname.c_str());
        struct dirent * dp;
        if ((dp = readdir(dirp)) == NULL)
        {
            cout<<"Folder not found or folder empty"<<endl;
            Sleep(2000);
            goto loop;
        }
        else
            v.push_back(dp->d_name);
        while ((dp = readdir(dirp)) != NULL) {
            v.push_back(dp->d_name);
        }
        closedir(dirp);
        for(int j=2;j<v.size();j++)
        {
            cout<<v[j]<<"\t \t Processing";
            w_search((fname+"//"+v[j]),cnt);
            cout<<"\b\b\bed "<<endl;
            cfmat[i][cnt[1]]++;
        }
        v.clear();
    }
    ofstream ofile;
    ofile.open("E://data//Confusion_matrix.csv");               //Replace by location of file containing confusion matrix
    ofile<<"OW/CW";
    for (i=0;i<w.size();i++)
        ofile<<","<<w[i];
    ofile<<endl;
    for (i=0;i<w.size();i++)
    {
        ofile<<w[i];
        for (j=0;j<w.size();j++)
            ofile<<","<<cfmat[i][j];
        ofile<<endl;
    }
    ofile.close();
    return;
}


#endif // CONFUSION_MATRIX_H_INCLUDED
