#include<fstream>
#include<iostream>
using namespace std;
#include<conio.h>

//DATABASE OF THE BOOKS
struct database
{
       int sno;
       char name[100];
       char company[50];
       int price;
};

//FOR THE HUFFMAN TREE
struct tree
{
       int info;
       tree *left;
       tree *right;
       tree *parent;
};

//FOR THE PRIORITY QUEUE
struct linklist
{
       tree *root;
       linklist *next;
};
                   
/*
CODE TO CHECK PROPER WORKING OF THE PRIORITY QUEUE :
          
void disprootnodes(linklist **first1)
{
     linklist *first=*first1;
     cout<<"rootlist : ";
     while(first!=NULL)
     {
                             cout<<(first->root)->info<<" ";
                             first=first->next;
     }
}*/


//INSERTING INTO THE PRIORITY QUEUE
void pqinsert(linklist **first,tree *t)
{
     linklist *node,*temp=*first;
     node=(linklist *)malloc(sizeof(linklist));
     node->root=t;
     node->next=NULL;
     if(*first==NULL)
                    *first=node;
     else
     {
         linklist *pre=NULL;
         while((temp->root)->info < t->info)
         {
                                   pre=temp;
                                   temp=temp->next;
                                   if(temp==NULL)
                                                 break;
         }
         if(temp==NULL)
                        pre->next=node;
         else
         {
             if(pre==NULL)
             {
                          node->next=temp;
                          *first=node;
             }
             else
             {
                 node->next=pre->next;
                 pre->next=node;
             }
         }
     }
}

//CREATE THE HUFFMAN TREE THAT IS TO BE STORED WHILE DOING PRE-TRAVERSAL
void pretrav(tree *root,tree *position[200],char hufftree[200],int pos)
{
     if(root->left==NULL && root->right==NULL)
     {
                         for(int i=0;i<200;i++)
                         {
                                 if(root==position[i])
                                                      hufftree[pos]=i;
                         }
     }
     else
     {
         if(root->left!=NULL)
         {
                         pos=pos*2;
                         pretrav(root->left,position,hufftree,pos);
                         pos=pos/2;
         }
         if(root->right!=NULL)
         {
                          pos=pos*2+1;
                          pretrav(root->right,position,hufftree,pos);
                          pos=(pos-1)/2;
         }
     }
}
     

int main()
{
    char inputfile[30],codefile[30],treefile[30],tempname[30];
    
    //INITIALIZE THE HUFFMAN TREE WITH '`'
    char hufftree[200];
    for(int i=0;i<200;i++)
            hufftree[i]='`';

    int inputorder[200],count=0;
    char code[200][10];
    linklist *rootnodes=NULL;
    tree *position[200];
    int frequency[200];
    database s[200];
    int n,i,x;

    //ITEMS AVAILABLE
    cout<<"\nItems Available : ";
    cout<<"\n1.Murder of Roger Ackroyd by Agatha Christie";
    cout<<"\n2.Introduction to Algortihms By CLRS";
    cout<<"\n3.Data Structures Using C by Tenenbaum";
    cout<<"\n4.Harry Potter Ang the Deathly Hallows by JKRowling";
    cout<<"\n5.Elephants Can Remember by Agatha Christie";
    cout<<"\n\nEnter the number of items : ";
    
    cin>>n;
    ofstream fout;
    cout<<"Enter the name of your input file : ";
    cin>>tempname;

    //CREATE THE PATH FOR THE INPUT FILE
    strcpy(inputfile,"F:/Programs/MyZip_files/");
    strcat(inputfile,tempname);
    strcat(inputfile,".txt");
    cout<<inputfile<<"\n";
    fout.open(inputfile);
    for(i=0;i<n;i++)
    {
                    cout<<"Enter the Item Serial No : ";
                    cin>>x;
                    inputorder[count++]=x;
                    if(x==1)
                    {
                            s[i].sno=1;
                            strcpy(s[i].name,"Murder of Roger Ackroyd by Agatha Christie");
                            strcpy(s[i].company,"Harper Collins");
                            s[i].price=100;
                            fout<<s[i].sno<<"\n"<<s[i].name<<"\n"<<s[i].company<<"\n"<<s[i].price<<"\n";
                    }
                    else if(x==2)
                    {
                         s[i].sno=2;
                         strcpy(s[i].name,"Introduction to Algortihms By CLRS");
                         strcpy(s[i].company,"PHI Learning");
                         s[i].price=400;
                         fout<<s[i].sno<<"\n"<<s[i].name<<"\n"<<s[i].company<<"\n"<<s[i].price<<"\n";
                    }
                    else if(x==3)
                    {
                         s[i].sno=3;
                         strcpy(s[i].name,"Data Structures Using C by Tenenbaum");
                         strcpy(s[i].company,"Pearson Education");
                         s[i].price=300;
                          fout<<s[i].sno<<"\n"<<s[i].name<<"\n"<<s[i].company<<"\n"<<s[i].price<<"\n";
                    }
                    else if(x==4)
                    {
                         s[i].sno=4;
                         strcpy(s[i].name,"Harry Potter Ang the Deathly Hallows by JKRowling");
                         strcpy(s[i].company,"Bloomsburg");
                         s[i].price=600;
                          fout<<s[i].sno<<"\n"<<s[i].name<<"\n"<<s[i].company<<"\n"<<s[i].price<<"\n";
                    }
                    else
                    {
                         s[i].sno=5;
                         strcpy(s[i].name,"Elephants Can Remember by Agatha Christie");
                         strcpy(s[i].company,"Harper Collins");
                         s[i].price=100;
                         fout<<s[i].sno<<"\n"<<s[i].name<<"\n"<<s[i].company<<"\n"<<s[i].price<<"\n";
                    }
    }
    fout.close();
    

    //CREATE THE HUFFMAN TREE AND CODE
    ifstream fin;
    fin.open(inputfile);
    for(i=0;i<200;i++)
                    frequency[i]=0;
    for(i=0;i<n;i++)
    {
                    char ch;
                    int temp1;
                    char temp2[100];
                    char temp3[50];
                    int temp4;
                    fin>>temp1;
                    fin.get(ch);
                    fin.get(temp2,100);
                    fin.get(ch);
                    fin.get(temp3,50);
                    fin.get(ch);
                    fin>>temp4;
                    frequency[temp1]++;
                    fin.get(ch);
    }
    fin.close();
    
    for(i=0;i<200;i++)
    {
                     if(frequency[i]!=0)
                     {
                                        tree *temp;
                                        temp=(tree *)malloc(sizeof(tree));
                                        temp->info=frequency[i];
                                        temp->left=NULL;
                                        temp->right=NULL;
                                        temp->parent=NULL;
                                        position[i]=temp;
                                        pqinsert(&rootnodes,temp);
                     }
                     else 
                     position[i]=NULL;
    }                
    
    while(rootnodes->next!=NULL)
    {
                                tree *p1=rootnodes->root;
                                rootnodes=rootnodes->next;
                                tree *p2=rootnodes->root;
                                rootnodes=rootnodes->next;
                                tree *p;
                                p=(tree*)malloc(sizeof(tree));
                                p->info=p1->info + p2->info;
                                p->left=p1;
                                p->right=p2;
                                p1->parent=p;
                                p2->parent=p;
                                pqinsert(&rootnodes,p);                            
    }
    
    tree *mainroot=rootnodes->root;
    for(i=0;i<200;i++)
    {
           int j=0;
           if(frequency[i]!=0)
           {
                    tree *p=position[i];
    
                    while(p!=mainroot)
                    {
                             if(p==(p->parent)->left)
                                                     code[i][j++]='0';
                             else
                                                     code[i][j++]='1';
                             p=p->parent;
                    }
                    code[i][j]='\0';
                    strrev(code[i]);
                    cout<<code[i]<<"\n";
            }
    }
    
    //STORE THE HUFFMAN CODE INTO A FILE
    char temp1[30];
    char huffcode[200];
    strcpy(huffcode,"");
    ofstream fout1;
    cout<<"Enter the name of your code file : ";
    cin>>temp1;
    strcpy(tempname,"F:/Programs/MyZip_files/");
    strcat(tempname,temp1);
    strcpy(codefile,tempname);
    strcat(codefile,"_1.txt");
    cout<<"Codefile : "<<codefile<<"\n";
    fout1.open(codefile);
    for(i=0;i<n;i++)
    {
                     strcat(huffcode,code[inputorder[i]]);
    }
    strcat(huffcode,"a");
    cout<<"code : "<<huffcode<<"\n";
    fout1.write((char*)&huffcode,sizeof(char)*200);
    fout1.close();
    
    pretrav(rootnodes->root,position,hufftree,1);
    //cout<<hufftree;
    
    //STORE THE HUFFMAN TREE INTO A FILE
    ofstream fout2;
    char tempname1[30];
    strcpy(tempname1,"F:/Programs/MyZip_files/");
    strcat(tempname1,temp1);
    strcpy(treefile,tempname1);
    strcat(treefile,"_2.txt");
    cout<<"Treefile : "<<treefile<<"\n";
    fout2.open(treefile,ios::binary);
    fout2.write((char*)&hufftree,sizeof(char)*200);
    fout2.close();
    getch();
}

