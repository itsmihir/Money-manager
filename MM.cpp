#include<fstream>
#include<iostream>
#include<stdio.h>
using namespace std;


class dc

{

char spend[20];
int spend_rs;
public:

int get_spend_rs(){return spend_rs;}
void reset()
{
spend_rs=0;
}
void view_opt1()
{
cout<<spend;
}
void get_opt()
{
cout<<"\n ENTER THE NEW EXPENDITURE : ";
cin>>spend;
cout<<"\nENTER THE AMOUNT SPEND     :";
cin>>spend_rs;
}
void view_opt()
{
cout<<spend <<"        	        "<<spend_rs<<"\n";
}

void rm_dec(int m)
{
spend_rs=spend_rs+m;
}

};



class ac
{
public:
int blc;
void print_blc()
{
cout<<"TOTAL BALANCE = "<<blc;
cout<<"\n\n\n";

}

void add_blc(int a)
{
blc=a+blc;
}
};




void check_blc()
{
fstream fout;
ac a;
fout.open("balance.dat",ios::in|ios::binary);
if(!fout)
{
cout<<"error";
}

while(fout.read((char*)&a,sizeof(a)))
{
a.print_blc();

}

fout.close();
}



void add()
{
ac a;
int b;
fstream fout,fin;
fin.open("balance.dat",ios::in|ios::binary);
fout.open("temp.dat",ios::out|ios::binary);
system("clear");
cout<<"\n\n";
cout<<"    ENTER THE VLAUE TO ADD : ";
cin>>b;
while(fin.read((char*)&a,sizeof(a)))
{
a.add_blc(b);
fout.write((char*)&a,sizeof(a));

//b=a.blc;
}

fout.close();
fin.close();
remove("balance.dat");
rename("temp.dat","balance.dat");
cout<<"\n\n\n\n";
int n;
do{
check_blc();
cout<<"\n\n\n PRESS 0 TO GO BACK \n";
cin>>n;

}while(n!=0);
}

void rem_total(int m)
{
fstream fout("balance.dat",ios::in|ios::binary);
fstream fin("temp.dat",ios::out|ios::binary);
ac a;
int k;
fout.read((char*)&a,sizeof(a));
k=a.blc-m;
a.blc=k;
fin.write((char*)&a,sizeof(a));


fout.close();
fin.close();

remove("balance.dat");
rename("temp.dat","balance.dat");
}

void rem_opt(int i,int m)
{
fstream fin,fout;
fin.open("option.dat",ios::in|ios::binary);
fout.open("temp.dat",ios::out|ios::binary);
dc a;
int k=1,p;
while(fin.read((char*)&a,sizeof(a)))
{
if(k==i)
{
a.rm_dec(m);
}
fout.write((char*)&a,sizeof(a));
k++;
}
fin.close();fout.close();

remove("option.dat");
rename("temp.dat","option.dat");

}

void pay()
{
int i=1,j,n,m;
dc a,b;
fstream fin,fout;



do{
fin.open("option.dat",ios::in|ios::binary);
fout.open("option.dat",ios::app|ios::binary);
i=1;
//int n;
system("clear");
while(fin.read((char*)&a,sizeof(a)))
{
cout<<i<<".";
a.view_opt1();
cout<<"\n";
i++;
}

cout<<i<<"."<<"ENTER NEW OPTION\n";

cout<<"0.GO BACK";
cout<<"\n\nWERE YOU SPEND MONEY [select option]: \n";
cin>>n;



if(n==i)
{
b.get_opt();
rem_total(b.get_spend_rs());
fout.write((char*)&b,sizeof(b));
}

if(n>=1&&n<i)
{
cout<<"ENTER THE AMOUNT YOU SEND IN :";
cin>>m;
rem_total(m);
rem_opt(n,m);
}
fin.close();
fout.close();
}while(n!=0);


}

void reset_opt()
{
char m;
cout<<" \n\n DO YOU WANT TO RESET THE BALANCE (Y/N) :";
cin>>m;
if(m=='y'||m=='Y')
{

fstream fin,fout;
fin.open("option.dat",ios::in|ios::binary);
fout.open("temp.dat",ios::out|ios::binary);
dc a;
while(fin.read((char*)&a,sizeof(a)))
{
a.reset();
fout.write((char*)&a,sizeof(a));
}
fin.close();
fout.close();

remove("option.dat");
rename("temp.dat","option.dat");
}
}

void reset_blc()
{
char m;
cout<<" \n\n DO YOU WANT TO RESET THE BALANCE (Y/N) :";
cin>>m;
if(m=='y'||m=='Y')
{
//fstream fin("balance.dat",ios::in|ios::out|ios::binary);
ac a;
fstream fout("temp.dat",ios::out|ios::binary);

a.blc=0;
fout.write((char*)&a,sizeof(a));
fout.close();

remove("balance.dat");
rename("temp.dat", "balance.dat");
}

}

void check_pay()
{
dc a;

fstream fin;
fin.open("option.dat",ios::in|ios::binary);

while(fin.read((char*)&a,sizeof(a)))
{
a.view_opt();
}

fin.close();
}


int main()
{

int i,n,j,flag1=0,flag2=0;
int getch;
do
{
do
{
system("clear");
cout<<"\n\n\n\n\n\n";
cout<<"                               ";
cout<<"1.CHECK BALANCE \n";
cout<<"                               ";
cout<<"2.PAY MONEY \n";
cout<<"                               ";
cout<<"3.ADD BALANCE \n";
cout<<"                               ";
cout<<"4.RESET TOTAL BALANCE\n";
cout<<"                               ";
cout<<"5.RESET PAY DATA\n";
cout<<"                               ";
cout<<"6.EXIT";
cout<<"\n\n";

cin>>n;


}while(n>6||n<1); 
switch(n)
{
case 1:
{
do{
system("clear");
cout<<"\n\n\n";
check_blc();
cout<<"\n\n\n";
cout<<"EXPENDITURES   AMOUNT SPENDED\n";
cout<<"--------------------------------\n";
check_pay();
cout<<"\n\n\n\n\n\n\n PRESS 1 TO GO BACK\n";
cin>>getch;
}while(getch!=1);


}
break;

case 2:
pay();
break;

case 3:
add();
break;

case 4:
system("clear");
reset_blc();
break;

case 5:
system("clear");
reset_opt();
break;

case 6:
flag1=1;
break;

}

}while(flag1==0);
return 0;
}
