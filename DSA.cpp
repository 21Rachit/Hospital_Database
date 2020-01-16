#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<stdlib.h>
#include<conio.h>
#include<process.h>
using namespace std;

fstream f1,f2;
int count_hospital=0;
int cloc=0;
void Check_if_hsptl_exists_and_print();
void Write_To_File();
void sortloc(int);
void hoesnearme(string);
void printlist();
void del();
struct cluster
{
    string name,location;
    float r;
};
struct ll
{
    string n,loc;
    float rat;
    struct ll *link;

}*head=NULL,*temp;

struct node
{
    string hname,hlocation;
    struct node* left;
    struct node* right;
}*root=NULL;
class SignUp
{
	string UserName,Password;

	public:

		SignUp()
		{
			UserName="NULL";
			Password="NULL";
		}

		void assignup(string UName,string Pwd)
		{
			UserName=UName;
			Password=Pwd;
		}

		string Return_UserName()
		{
			return UserName;
		}

		string Return_Password()
		{
			return Password;
		}

		void GetSignUpDetails();

}su;

string HidePassword()
{
	string pwd=" ";
	int ctr;
	char ch;
	    do
		{
			ch=_getch();

				if (ch==13)
					break;

				else if (ch==8 && pwd.size()>=1)
					{
						cout<<"\b \b";
						pwd.erase(pwd.size()-1);
					}

				else
				{
				  cout<<"*";
				  pwd.push_back(ch);
				}

		} while(ch!='\0');

		return pwd;
}
void SignUp_NewEntry(string username,string password)
{
	f1.open("Sign_Up_Details.dat",ios::out|ios::binary|ios::app);
	su.assignup(username,password);
	f1.write((char*)&su,sizeof(su));
	f1.close();
}
bool Check_for_Valid_UserName(string username)
{
	bool found;
	f1.open("Sign_Up_Details.dat",ios::binary|ios::in);

	found=false;

	while(f1.read((char*)&su,sizeof(su)) && found==false)
	{
		if (su.Return_UserName()==username)
			found=true;
	}

	f1.close();
	return found;
}
void SignUp::GetSignUpDetails()
{
	string username,password,rpassword;
	cout<<endl<<"Enter the UserName of your choice:";
	cin>>username;

		if ( Check_for_Valid_UserName(username) )
			cout<<endl<<"UserName Already Exists!";

		else
			{
				cout<<"\nEnter the password: ";
				password=HidePassword();
				cout<<"\nRe-Enter the password: ";
				rpassword=HidePassword();
				if(password==rpassword)
                {
                    SignUp_NewEntry(username,password);
				    cout<<"\nSign-Up Successfull !";
                }
                else
                    cout<<"\nPasswords do not match!!";
			}
}
int Login()
{
	string username,password;
	bool found;

	cout<<"\nEnter UserName:";
	cin>>username;
	cout<<"\nEnter the password:";
	password=HidePassword();

		f1.open("Sign_Up_Details.dat",ios::in|ios::binary);

		found=false;
		while(f1.read((char*)&su,sizeof(su)))
		{
			if (su.Return_UserName()==username && su.Return_Password()==password && found==false)
			{
				cout<<endl<<"Login Successfull !";
				found=true;
				return(1);
			}
		}
		return(0);
		if(found==false)
        cout<<endl<<"UserName and Passwords do not match";
}
int signin()
{
	char ch,opt;

	do
	{   system("cls");
		cout<<"\n1.SignUp\n2.Login\n3.To exit\nEnter your choice:";
		cin>>opt;
			switch(opt)
			{
				case '1' : su.GetSignUpDetails();
							break;

				case '2': {int i=Login();
                          if(i==1)
                            return(1);
							break;}
                case '3': exit(0);
				default: cout<<"\nInvalid Choice :(";
			}

		cout<<"\nEnter (y-Sign):";
		cin>>ch;

	}while(ch=='Y' || ch=='y');
}

class hospital
{
    int hospitalid;
    string hospitalname,phone,location,speciality;
    float rating;
    bool multipurpose;
    public:

        hospital()
        {
            hospitalid=0;
            hospitalname="NOT ASSIGNED";
            phone="NOT ASSIGNED";
            location="NOT ASSIGNED";
            speciality="NOT ASSIGNED";
            rating=0.0;
            multipurpose=false;
        }

        string return_hn()
        {
            return hospitalname;
        }

        string return_hl()
        {
            return location;
        }
        float return_r()
        {
            return rating;
        }
        void gethospitalinfo();
        void showhospitaldetails();

}hos;

void hospital::gethospitalinfo()
{
    char ch;

    cout<<"\nEnter the hospital ID:";
    cin>>hospitalid;
    cout<<"Enter the name of the hospital:";
    cin>>hospitalname;
    cout<<"Enter Phone Number:";
    cin>>phone;
    cout<<"Enter Location:";
    cin>>location;
    cout<<"Enter speciality: ";
    cin>>speciality;
    cout<<"Enter rating: ";
    cin>>rating;
    cout<<"Multi-Speciality ?(y/n):";
    cin>>ch;

        if (ch=='y' || ch=='Y')
            multipurpose=true;
        else
            multipurpose=false;
}

void Write_To_File()
{
    f1.open("hospitaldetails.dat",ios::out|ios::binary|ios::app);
    hos.gethospitalinfo();
    f1.write((char*)&hos,sizeof(hos));
    cout<<endl<<"\nHospital Successfully added to the database :)\n";
    count_hospital++;
    f1.close();
}

void hospital::showhospitaldetails()
{
    cout<<"\nHospital ID:"<<hospitalid;
    cout<<"\nHospital Name:"<<hospitalname;
    cout<<"\nPhone Number:"<<phone;
    cout<<"\nLocation:"<<location;
    cout<<"\nSpeciality:"<<speciality;
    cout<<"\nRating:"<<rating;
    cout<<"\nMulti-Speciality :";
        if (multipurpose==true)
            cout<<"Yes";
        else
            cout<<"No";
}
void check_if_hsptl_exists_and_print()
{
    bool found;
    string t;

    cout<<"\nEnter the Name of the Hospital to be searched:";
    cin>>t;

    f1.open("hospitaldetails.dat",ios::binary|ios::in);
    f1.seekg(0);

    found=false;

    while(f1.read((char*)&hos,sizeof(hos)) && found==false)
    {
        if (hos.return_hn()==t)
        {
            found=true;
            hos.showhospitaldetails();
        }
    }

    f1.close();

    if (found==false)
        cout<<"\nHospital does not exist :(";

}

int create(node *&y,string s1,string s2)
{
if(y==NULL)
{
node *newnode;
newnode=new node;
newnode->hname=s1;
newnode->hlocation=s2;
newnode->left=newnode->right=NULL;
y=newnode;
return(1);
}
else if(s1==y->hname && s2==y->hlocation)
    return(0);
else if(s1<y->hname)
create(y->left,s1,s2);
else
create(y->right,s1,s2);
}
void inorder(node *a)
{
if(a!=NULL)
{
inorder(a->left);
cout<<a->hname<<"\t\t"<<a->hlocation<<"\n";
inorder(a->right);
}
}

void Display_All_Records()
{
    f1.open("hospitaldetails.dat",ios::in|ios::binary);
    f1.seekg(ios::beg);
    string s1,s2;
	cout<<"\nLIST OF Hospitals with LOCATION\n\n";
    cout<<"NAME      |      LOCATION\n---------------------------\n";
    while(f1.read((char*)&hos,sizeof(hos)))
    {
        s1=hos.return_hn();
		s2=hos.return_hl();
		create(root,s1,s2);
    }

    f1.close();

    inorder(root);
}
void sortloc(int x)
{
    struct ll *temp;
    string s1,s2;
    float r;
    temp=head;
    if(temp==NULL)
        cout<<"\nList Of Hospitals Is Empty";
    else
    {
        for(int i=0;i<x-1;i++)
        {

            temp=head;
            for(int j=0;j<x-i-1;j++)
            {
                if( (temp->rat) < (temp->link->rat))
                {
                    s1=temp->n;
                    s2=temp->loc;
                    r=temp->rat;
                    temp->n=temp->link->n;
                    temp->loc=temp->link->loc;
                    temp->rat=temp->link->rat;
                    temp->link->n=s1;
                    temp->link->loc=s2;
                    temp->link->rat=r;
                }
                temp=temp->link;
            }
        }
        printlist();
    }
}

void ins(hospital &h)
{
    struct ll *newnode;
    newnode=new ll;
    newnode->n=h.return_hn();
    newnode->loc=h.return_hl();
    newnode->rat=h.return_r();
    newnode->link=NULL;
    if(head==NULL)
    {
        head=newnode;
        temp=head;
    }
    else
    {
        temp->link=newnode;
        temp=newnode;
    }

}
int searchhos(hospital h)
{
    struct ll *t;
    t=head;
    if(t==NULL)
        return(1);
        else{
        while(t!=NULL)
        {
            if(t->n==h.return_hn() && t->loc==h.return_hl())
                return(0);
            t=t->link;
        }
        return(1);}
}
void hoesnearme(string l)
{

    f2.open("hospitaldetails.dat",ios::in|ios::binary);
    f2.seekg(0);
    cloc=0;
    while(f2.read((char*)&hos,sizeof(hos)))
    {
        if(l==hos.return_hl())
            {   if(searchhos(hos)==1)
                    {ins(hos);
                    cloc++;}

            }
    }
    f2.close();
    sortloc(cloc);
}
void printlist()
{
    struct ll *temp;
    temp=head;
    if(temp==NULL)
        cout<<"\nNo hospital available";
    else
    {
        cout<<"Name\t\tLocation\t\tRating\n";
        while(temp!=NULL)
        {
            cout<<temp->n<<"\t\t"<<temp->loc<<"\t\t"<<temp->rat<<endl;
            temp=temp->link;
        }
    }
 del();
}
void del()
{
    struct ll *t;
    t=head;
    while(head!=NULL)
    {
        head=t->link;
        delete(t);
        t=head;
    }
}
void kmean(int n)
{
    float t[n];
    int i[n];
    int q=0;
    cluster km[n][count_hospital];
    cluster a[count_hospital];

    f1.open("hospitaldetails.dat",ios::in|ios::binary);

    while(f1.read((char*)&hos,sizeof(hos)))
          {
            a[q].name=hos.return_hn();
            a[q].location=hos.return_hl();
            a[q].r=hos.return_r();
            q++;
          }
    f1.close();

    int min,x,f=0;

    //initial means
    float m[n];

    for(int i=0;i<n;i++)
    {
      cout<<"Enter the "<<i+1<<" mean ";
      cin>>m[i];
    }

    float om[n];    //old means

    do
    {
    //saving old mean
    for(int i=0;i<n;i++)
    om[i]=m[i];

    //creating clusters
    for(int j=0;j<n;j++)
    i[j]=0;
    for(int j=0;j<count_hospital;j++)
    {
      for(int k=0;k<n;k++)
      {
        t[k]=a[j].r-m[k];
        if(t[k]<0)
        t[k]=-t[k];
      }
      min=0;
      for(int j=0;j<n;j++)
      if(t[j]<t[min])
      min=j;
      km[min][i[min]++]=a[j];
    }
    for(int j=0;j<n;j++)
    {
      x=0;
      for(int k=0;k<i[j];k++)
      x+=km[j][k].r;
      m[j]=x/i[j];
    }
    for(int j=0;j<n;j++)
    if(m[j]==om[j])
    f=1;
    }while(f==0);
    for(int j=0;j<n;j++)
    {
      cout<<"Cluster "<<j+1<<":"<<endl;;
      for(int k=0;k<i[j];k++)
      {
          cout<<km[j][k].name<<" "<<km[j][k].location<<" "<<km[j][k].r<<endl;
      }
      cout<<"Mean "<<j+1<<": "<<m[j];
      cout<<"\n";
    }
}
int main()
{
    char ch,opt;
    string s;
    int nom;
    rr:
    signin();
    do
    {
        system("cls");
        cout<<"\n\t\t\t\t\tMENU\n";
    cout<<"--------------------------------------------------------------------------------";
        cout<<"\n1) Add New Hospital\n\n2) View Hospital Details\n\n3) Display All Records\n\n4) Hospitals near me\n\n5)Cluster by rating\n\nEnter your choice:";
        cin>>opt;

            switch(opt)
            {
                case '1' : Write_To_File();
                            break;

                case '2' : check_if_hsptl_exists_and_print();
                            break;

                case '3' : Display_All_Records();
                            break;
                case '4' : cout<<"\nEnter your location: ";
                           cin>>s;
                           hoesnearme(s);
                            break;
                case '5' : cout<<"\nEnter the number of means : ";
                           cin>>nom;
                           kmean(nom);
                            break;

                default : cout<<"Invalid Choice:";
            }
             cout<<"\n\nPress (y-Main Menu) and (n-Logout):";
             cin>>ch;
    }while(ch=='y' || ch=='Y');
    goto rr;
}


