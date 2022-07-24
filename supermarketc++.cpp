#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string.h>

using namespace std;
int flag = 0,e=0;

ifstream fread1,fread2;
ofstream fwrite1,fwrite2;

class Node
{
    public:
            int id,quan,disc;
            char name[25];
            float mrp;
            Node *lchild;
            Node *rchild;

};

class Operations
{
    public:
            void menu(Node *root)
            {
                int choice;
                char username[25],password[25];
                

                while(1)
                {
                    cout<<"\t\t\t\t------------------------------\n";
                    cout<<"\t\t\t\t    SUPERMARKET MAIN MENU      \n";
                    cout<<"\t\t\t\t------------------------------\n";
                    cout<<"\n1 : ADMINISTRATOR\n2 : BUYER\n3 : EXIT\n";
                    cout<<"\nEnter your choice : ";
                    cin>>choice;

                    switch(choice)
                    {
                        case 1 : cout<<"\nEnter the username : ";
                                 cin>>username;
                                 cout<<"\nEnter the password : ";
                                 cin>>password;

                                 if((strcmp(username,"admin")==0 && strcmp(password,"admin@123")==0))
                                        admin(root);
                                 else
                                        cout<<"\nInvalid Login Credentials\n";
                                 break;

                        case 2 : buyer(root);
                                 break;

                        case 3 : fwrite1.open("Inventory.txt",ios :: out);
                                 fwrite1.close();
                                 fwrite2.open("Order list.txt",ios :: out);
                                 fwrite2.close();
                                 inorder(root);
                                 exit(0);

                        default : cout<<"\nPlease enter a valid choice\n";
                    }
                }
            }

            void admin(Node *root)
            {
                int choice,data;

                while(1)
                {
                    cout<<"\n1 : ADD PRODUCT\n2 : MODIFY PRODUCT DETAILS\n3 : DELETE PRODUCT\n4 : DISPLAY\n5 : RETURN BACK TO MAIN MENU\n";
                    cout<<"\nEnter your choice : ";
                    cin>>choice;

                    switch(choice)
                    {
                        case 1 : root = add(root);
                                 break;

                        case 2 : mod(root);
                                 break;

                        case 3 : if(root == NULL)
                                    cout<<"\nNo products in database\n";
                                 else
                                 {  
                                    cout<<"\n\n------------------------------------------------------------------------------------\n";
                                    cout<<"ID\t\tNAME\t\tPRICE\t\tQUANTITY\tDISCOUNT\n";
                                    cout<<"------------------------------------------------------------------------------------\n";
                                    display(root);
                                    
                                    cout<<"\nEnter the id of the product to be deleted : ";
                                    cin>>data;
                            
                                    root = del(root,data);
                                }
                                 break;

                        case 4 : if(root == NULL)
                                    cout<<"\nNo products to display\n";
                                 else
                                 {
                                    cout<<"\n\n------------------------------------------------------------------------------------\n";
                                    cout<<"ID\t\tNAME\t\tPRICE\t\tQUANTITY\tDISCOUNT\n";
                                    cout<<"------------------------------------------------------------------------------------\n";
                                    display(root); 
                                 }
                                  break;

                        case 5 : menu(root);
                                 break;         

                        default : cout<<"\nEnter a valid choice\n";
                    }
                }
            }

            void buyer(Node *root)
            {
                int choice;

                while(1)
                {
                    cout<<"\n1 : BUY A PRODUCT\n2 : RETURN BACK TO MAIN MENU\n";
                    cout<<"\nEnter your choice : ";
                    cin>>choice;

                    switch(choice)
                    {
                        case 1 : bill(root);
                                 break;

                        case 2 : menu(root);
                                 break;

                        default : cout<<"\nEnter a valid choice\n";
                    }
                }
            }

            Node* add(Node *root)
            {
                int id;
                char name[20];
                Node *newnode,*temp,*parent;


                newnode=(Node*)malloc(sizeof(Node));
                newnode->lchild=newnode->rchild=NULL;

                cout<<"\nEnter the product id : ";
                cin>>newnode->id;

                id = newnode->id;

                cout<<"\nEnter the product name : ";
                cin>>newnode->name;

                strcpy(name,newnode->name);

                cout<<"\nEnter the product mrp : ";
                cin>>newnode->mrp;

                cout<<"\nEnter the product quantity : ";
                cin>>newnode->quan;

                cout<<"\nEnter the product discount : ";
                cin>>newnode->disc;


                if(root==NULL)
                    root=newnode;
                else
                {   m:
                        temp=root;

                        while(temp!=NULL)
                        {
                            parent=temp;

                            if(newnode->id > temp->id)
                                temp=temp->rchild;

                            else if(newnode->id < temp->id)
                                temp=temp->lchild;

                            else
                            {
                                if(strcmp(temp->name,name)==0)
                                {
                                    cout<<"\nThe product already exist\nTo modify existing product details please select choice 2\n";
                                    free(newnode);
                                    return root;
                                }
                                else
                                {
                                    cout<<"\nThe given id already exist\nPlease provide a new id : ";
                                    cin>>newnode->id;
                                    
                                    goto m;
                                }
                            }

                        }

                    checker1(root,name);

                    if(flag==0)
                    {
                        if(newnode->id > parent->id)
                            parent->rchild=newnode;

                        else
                            parent->lchild=newnode;
                    }else
                            flag = 0;
                }

                return root;

            }

            void checker1(Node *root,char name[])
            {
                if(root==NULL)
                    return;

                checker1(root->lchild,name);

                if((strcmp(name,root->name))==0)
                {   cout<<"\nThe product name "<<name<<" already exist in the database\nTo modify existing product details please select choice 2\n";
                    flag = 1;
                    return;
                }

                checker1(root->rchild,name);
            }

            void mod(Node *root)
            {
                if(root == NULL)
                {
                    cout<<"\nNo products in database\n";
                    return;
                }

                int id;
                Node *temp;

                cout<<"\n\n------------------------------------------------------------------------------------\n";
                cout<<"ID\t\tNAME\t\tPRICE\t\tQUANTITY\tDISCOUNT\n";
                cout<<"------------------------------------------------------------------------------------\n";
                display(root);

                cout<<"\nEnter the id of the product to be modified : ";
                cin>>id;

                temp = search(root,id);

                if(temp == NULL)
                {
                    cout<<"\nNo product exist for the given id\n";
                    return;
                }
                else
                {
                    cout<<"\nEnter the product's new mrp : ";
                    cin>>temp->mrp;

                    cout<<"\nEnter the product's new quantity : ";
                    cin>>temp->quan;

                    cout<<"\nEnter the product's new discount : ";
                    cin>>temp->disc;   
                }

            }

            Node* del(Node *root,int key)
            {
                if(root == NULL)
                {
                    cout<<"\nNo products in the database\n";
                    return root;
                }

    
                Node *cur,*q,*parent,*successor;
                parent=NULL,cur=root;
    
                while(cur!=NULL)
                {
                    if(cur->id==key)
                        break;
                    parent=cur;
        
                    cur = (key<cur->id)?cur->lchild:cur->rchild;
                }

                if(cur==NULL)
                {
                    cout<<"\nNo product exist for the given id\n";
                    return root;
                }

                if(cur->lchild==NULL)
                    q=cur->rchild;

                else if(cur->rchild==NULL)
                    q=cur->lchild;

                else
                {
                    successor = cur->rchild;
        
                    while(successor->lchild != NULL)
                        successor = successor->lchild;
 
                    successor->lchild = cur->lchild;
                    q = cur->rchild;
                }

                if (parent == NULL)
                {
                    cout<<"\nproduct with id "<<key<< "is deleted from database\n";
                    free(cur);
                    
                    return q;
                }

                if(cur == parent->lchild)
                    parent->lchild = q;

                else
                    parent->rchild = q;

                cout<<"\nproduct with id "<<key<< "is deleted from database\n";
                free(cur);
 
                return root;
            }

            void display(Node *root)
            {
                if(root==NULL)
                    return;

                display(root->lchild);

                cout<<root->id<<"\t\t"<<root->name<<"\t\t"<<root->mrp<<"\t\t"<<root->quan<<"\t\t"<<root->disc<<"\n";

                display(root->rchild);
            }

            Node* search(Node *root,int key)
            {
                if(root==NULL || root->id==key)
                    return root;
                if(key < root->id)
                    return(search(root->lchild,key));

                return(search(root->rchild,key));    
            }

            void inorder(Node *root)
            {   
                Node *p;
    
                if(root==NULL)
                    return;

                inorder(root->lchild);

                p = root;
                createfile(p);

                inorder(root->rchild);
            }

            void createfile(Node *p)
            {
                
                fwrite1.open("Inventory.txt",ios :: app);
                fwrite2.open("Order list.txt",ios :: app);

                if(p->quan != 0)
                    fwrite1<<p->id<<"\t\t"<<p->name<<"\t\t"<<p->mrp<<"\t\t"<<p->quan<<"\t\t"<<p->disc<<"\n";
                else
                    fwrite2<<p->id<<"\t\t"<<p->name<<"\t\t"<<p->mrp<<"\t\t"<<p->disc<<"\n";

                fwrite1.close();
                fwrite2.close();
            }

            void bill(Node *root)
            {
                int code[100],quan[100],c=0,d,id;
                char choice;
                float amt = 0,dis=0,total=0;
                Node *temp;

                checker3(root);

                if(root==NULL || e == 0)
                {
                    printf("\nNo products to buy\n");
                    return;
                }    

                else
                {   fwrite1.open("Sales report.txt",ios :: app);
                    cout<<"\n\t\t\t\tRECIEPT\n";
                    cout<<"\n\n------------------------------------------------------------------------------------\n";
                    cout<<"ID\t\tNAME\t\tPRICE\t\tQUANTITY\tDISCOUNT\n";
                    cout<<"------------------------------------------------------------------------------------\n";
                    display1(root);

                    cout<<"\t\t\t\t------------------------------\n";
                    cout<<"\t\t\t\t    PLEASE PLACE AN ORDER      \n";
                    cout<<"\t\t\t\t------------------------------\n";

                    do
                    {   m:
                            cout<<"\nEnter Product code : ";
                            cin>>code[c];

                            temp = search(root,code[c]);

                            while(temp==NULL)
                            {
                                cout<<"\nNo product exist for the "<<code[c]<<" id\n";
                                cout<<"\nEnter new product code : ";
                                cin>>code[c];
                      
                                temp = search(root,code[c]);
                            }

                            if(temp->quan ==0)
                            {
                                cout<<"\nSorry , The stock of this product is not available\nplease provide another id\n";
                                goto m;
                            }  

                            cout<<"\nEnter the product quantity : ";
                            cin>>quan[c];

                            for(int j = 0;j<c;j++)
                            {
                                if(code[c]==code[j])
                                {
                                    cout<<"\nrepetation of product code , enter a new code\n";
                                    goto m;
                                }
                            }c++;e--;

                            if(e != 0) 
                            {
                                cout<<"\nDo you want to buy an another product ? if yes then press y else n : ";
                                fflush(stdin);
                                cin>>choice;
                            }else
                                {
                                    e = 0;
                                    choice = 'n';
                                }
                    }while(choice == 'y');

                    cout<<"\n\n\t\t\t--------------------------------RECIEPT-------------------------------------\n";
                    cout<<"\nPRODUCT NO\t\tPRODUCT NAME\t\tPRODUCT MRP\t\tPRODUCT QUANTITY\tAMOUNT\t\tAMOUNT WITH DISCOUNT\n";
                    e = 0;

                    for(int j=0;j<c;j++)
                    {
                        temp = search(root,code[j]);
                        d = checker2(quan[j],temp->quan);

                        if(d==0)
                            quan[j] = temp->quan;
                        temp->quan = d;

                        amt = temp->mrp * quan[j];
                        dis = amt - (amt*temp->disc/100);
                        total = total + dis;
                  
                        if(quan[j] != 0)
                            fwrite1<<temp->id<<"\t\t"<<temp->name<<"\t\t"<<temp->mrp<<"\t\t"<<quan[j]<<"\t\t"<<dis<<"\n";
                                          
                        cout<<"\n"<<temp->id<<"\t\t\t"<<temp->name<<"\t\t\t"<<temp->mrp<<"\t\t\t"<<quan[j]<<"\t\t\t"<<amt<<"\t\t"<<dis<<"\n";
                    
                    }fwrite1.close();
                }

                cout<<"----------------------------------------------------------------------------------------------------------------------------------\n";
                cout<<"\nTotal amount : "<<total<<" \n";
            }

            void display1(Node *root)
            {
                if(root==NULL)
                    return;

                display1(root->lchild);

                if(root->quan != 0)
                    cout<<root->id<<"\t\t"<<root->name<<"\t\t"<<root->mrp<<"\t\t"<<root->quan<<"\t\t"<<root->disc<<"\n";

                display1(root->rchild);
            }

            int checker2(int a,int b)
            {
                if(a > b)
                    return 0;
                else if(a<b)
                    return b-a;
                else
                    return 0;
            }

            void checker3(Node *root)
            {
                if(root==NULL)
                return;

                checker3(root->lchild);

                if(root->quan != 0)
                    e++;

                checker3(root->rchild);

            }

            Node* createroot(Node *root)
            {   
                FILE *fp,*fp1;
                Node *newnode;
                newnode=(Node*)malloc(sizeof(Node));
                newnode->lchild=newnode->rchild=NULL;

                fp = fopen("Inventory.txt","r");
                fp1 = fopen("Order list.txt","r");
    
                while((fscanf(fp,"%d%s%f%d%d",&newnode->id,newnode->name,&newnode->mrp,&newnode->quan,&newnode->disc))!= EOF)
                    root = add2(root,newnode->id,newnode->name,newnode->mrp,newnode->quan,newnode->disc);

                fclose(fp);

                while((fscanf(fp1,"%d%s%f%d",&newnode->id,newnode->name,&newnode->mrp,&newnode->disc))!= EOF)
                    root = add2(root,newnode->id,newnode->name,newnode->mrp,0,newnode->disc);   

                fclose(fp1);

                return root;
            }

            Node* add2(Node *root,int id,char name[],float mrp,int quan,int disc)
            {

                Node *newnode,*temp,*parent;

                newnode=(Node*)malloc(sizeof(Node));
                newnode->lchild=newnode->rchild=NULL;

                newnode->id=id;
                strcpy(newnode->name,name);
                newnode->mrp=mrp;
                newnode->quan=quan;
                newnode->disc=disc;

                if(root==NULL)
                    root=newnode;

                else
                {   
                    temp=root;

                    while(temp!=NULL)
                    {
                        parent=temp;

                        if(newnode->id > temp->id)
                            temp=temp->rchild;
                        else
                            temp=temp->lchild;
                    }

                    if(newnode->id > parent->id)
                        parent->rchild=newnode;

                    else
                        parent->lchild=newnode;
        
                }

                return root;
            }
            

};

int main()
{   
    Node *root = NULL;

    Operations s1;

    root = s1.createroot(root);

    s1.menu(root);

    return 0;
}