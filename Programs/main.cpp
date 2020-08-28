#include <iostream>
#include <fstream>
#include <malloc.h>
#include <vector>
#include <bits/stdc++.h>
#include <conio.h>
#include <string>
#include <iomanip>
#include <windows.h>
#include <sys/types.h>
#include <dirent.h>
#include "readfolder.h"
#include "readfile.h"
#include "output_search.h"
#include "process_data.h"
#include "confusion_matrix.h"

using namespace std;

void input()
{
    ifstream ifile;
    string wname,filename;
    cout<<"Data for the following authors are already present. Please select someone except them"<<endl;
    ifile.open("E://data//Names.txt");      //Replace by location of file containing names of authors
    while (!ifile.eof())
    {
        getline(ifile,wname);
        if (!ifile.eof())
            cout<<wname<<endl;
    }
    ifile.close();
    cout<<endl<<endl;
    cout<<"Enter writer name:\t";
    cin.ignore();
    getline(cin,wname);
    cout<<"Enter folder location for the author:\t";
    getline(cin,filename);
    read_directory(filename,wname);
}

int main()
{
    int choose=0;
    string filename;
        while (choose!=5)
        {
            system("CLS");
            cout<<"1.\t Input documents"<<endl<<"2.\t Perform processing"<<endl<<"3.\t Verify writer for document"<<endl<<"4.\t Create confusion matrix"<<endl<<"5.\t Exit application"<<endl<<"Choose option:\t";
            cin>>choose;
            while (choose<1 || choose>5)
            {
                cout<<"Error in value. Enter again:\t";
                cin>>choose;
            }
            system("CLS");
            switch (choose)
            {
            case 1:
                input();
                    break;
            case 2:
                tot_var();
                break;
            case 3:
                {int *cnt=0;
                cnt=new int[2];
                ifstream infile;
                cout<<"Enter location of file containing the required text:\t";
                cin.ignore();
                getline(cin,filename);
                w_search(filename,cnt);
                if (cnt[0])
                {
                    string wname[cnt[0]];
                    infile.open("E://data//Names.txt");             //Replace by location of file containing names of authors
                    for (int i=0;i<cnt[0];i++)
                    {
                        getline(infile,wname[i]);
                    }
                    infile.close();
                    cout<<"The probable writer is:\t"<<wname[cnt[1]]<<endl<<endl<<endl<<"Press any key to return to main menu";
                    getch();
                }
                break;
                }
            case 4:
                create_cmat();
                break;
            case 5:
                exit(0);
                break;
            default:
                return 0;
            }
        }
    return 0;
}
