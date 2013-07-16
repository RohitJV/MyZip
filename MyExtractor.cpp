#include<iostream>
#include<fstream>
using namespace std;
#include<conio.h>

struct database
{
       int sno;
       char name[100];
       char company[50];
       int price;
};

int main()
{
    char inputfile[50],treefile[50],codefile[50],tempname[50];
    char ch,code,out1[100];
    database s[5],out[100];
    ifstream fin;
    fin.open("F:/Programs/MyZip/book.txt");
    for(int i=0;i<5;i++)
    {
            fin>>s[i].sno;
            fin.get(ch);
            fin.get(s[i].name,100);
            fin.get(ch);
            fin.get(s[i].company,50);
            fin.get(ch);
            fin>>s[i].price;
            fin.get(ch);
            cout<<s[i].sno<<" "<<s[i].name<<" "<<s[i].company<<" "<<s[i].price<<"\n";
    }   
    fin.close();
    
    ifstream fin1;
    cout<<"Enter the name of a valid code file : ";
    cin>>inputfile;
    
    cout<<inputfile<<"\n";
    strcpy(tempname,"F:/Programs/MyZip_files/");
    strcat(tempname,inputfile);
    cout<<tempname;
    strcpy(codefile,tempname);
    strcat(codefile,"_1.txt");
    cout<<"\n"<<codefile<<"\n";
    fin1.open(codefile);
    
    ifstream fin2;
    strcpy(treefile,tempname);
    strcat(treefile,"_2.txt");
    fin2.open(treefile);
    char tree[200];
    fin2>>tree;
    
    cout<<"\n\n*************************************\n\n";
    getch();
    int i=1;
    int pos=0;
    while(1)
    {
                             fin1>>code;
                             if(code=='a')
                             {
                                          out1[pos++]=char(tree[i]+48);
                                          cout<<char(tree[i]+48);
                                          break;
                             }
                             else
                             {
                                 if(code=='0')
                                 {            
                                              if(tree[i]!='`')
                                              {
                                                              cout<<char(tree[i]+48);
                                                              out1[pos++]=char(tree[i]+48);
                                                              fin2.close();
                                                              fin2.open(treefile);
                                                              i=2;
                                              }
                                              else
                                                  i=i*2;
                                 }
                                 else
                                 {
                                     if(tree[i]!='`')
                                     {
                                                              cout<<char(tree[i]+48);
                                                              out1[pos++]=char(tree[i]+48);         
                                                              fin2.close();
                                                              fin2.open(treefile);
                                                              i=3;
                                     }
                                     else
                                              i=i*2+1;         
                                 }
                             }
    }                                                                                      
    getch();
    cout<<"\n\n";     
    ofstream fout2;
    char outfile[30];
    cout<<"Enter the name of the outputfile file : ";
    cin>>outfile;
    strcpy(tempname,"F:/Programs/MyZip_files/");
    strcat(tempname,outfile);
    strcat(tempname,".txt");
    fout2.open(tempname);  
    for(int j=0;j<pos;j++)
    {
                      cout<<s[out1[j]-1-48].sno<<" "<<s[out1[j]-1-48].name<<" "<<s[out1[j]-1-48].company<<" "<<s[out1[j]-1-48].price<<"\n";
                      fout2<<s[out1[j]-1-48].sno<<" "<<s[out1[j]-1-48].name<<" "<<s[out1[j]-1-48].company<<" "<<s[out1[j]-1-48].price<<"\n";
    }                
    getch();
}
