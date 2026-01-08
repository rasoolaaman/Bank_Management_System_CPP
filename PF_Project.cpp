#include<iostream>
#include<fstream>
using namespace std;

struct  Account
{
	int id;
	char name[20];
	double amount;
};

void Create();
void Deposit();
void Withdrawal();
void Transfer();
void Update();
void Search();
void Delete();
void ShowAccount();

int main()
{
	cout<<"-------Bank Management System Project--------"<<endl;
	int choice;
	do
	{
		cout<<"\nEnter 1 to Create Account. \n";
		cout<<"Enter 2 to Deposit into your Account. \n";
		cout<<"Enter 3 to Withdrawal from your Account. \n";
		cout<<"Enter 4 to Transfer Money into Another Account. \n";
		cout<<"Enter 5 to Update Account. \n";
		cout<<"Enter 6 to Search Account. \n";
		cout<<"Enter 7 to Delete Account. \n";
		cout<<"Enter 8 to Show Accounts. \n";
		cout<<"Enter 9 to Exit.\n";
		cout<<"Enter your choice : ";
		cin>>choice;
		switch (choice)
		{
			case 1:
					Create();
					break;
			case 2:
					Deposit();
					break;
			case 3:
					Withdrawal();
					break;
			case 4:
					Transfer();
					break;
			case 5:
					Update();
					break;
			case 6:
					Search();
					break;
			case 7:
					Delete();
					break;
			case 8:
					ShowAccount();
					break;
			case 9:
					cout<<"\nExiting.............";
					break;
			default:
					cout<<"\nYou enter a wrong number."<<endl;
					break;
		}
	}while(choice!=9);
	return 0;
}

void Create()
{
	bool flag;
	ofstream ofs;
	ofs.open("data.txt", ios::app);
	Account b;
	do
	{
		flag=false;
		cout<<"\nEnter Account ID : ";
		cin>>b.id;
		ifstream ifs;
		ifs.open("data.txt");
		Account a;
		ifs>>a.id;
		ifs>>a.name;
		ifs>>a.amount;
		while(!ifs.eof())
		{
			if(a.id==b.id)
			{
				flag=true;
				cout<<"\nAccount id already taken."<<endl;
				cout<<"Please! Change your Account ID. "<<endl;
			}
			ifs>>a.id;
			ifs>>a.name;
			ifs>>a.amount;
		}
		ifs.close();
	}while(flag);
	cout<<"Enter Account Name : ";
	cin>>b.name;
	cout<<"Enter Account Balance : ";
	cin>>b.amount;
	
	cout<<"\nAccount Created Successfully."<<endl;
	ofs<<b.id<<"\t"<<b.name<<"\t"<<b.amount<<endl;
	ofs.close();
}
void Deposit()
{
	ifstream ifs;
	ifs.open("data.txt");
	ofstream ofd;
	ofd.open("temp.txt");
	int no;
	double bal;
	cout<<"\nEnter Account ID for Deposit Money: ";
	cin>>no;
	Account a;
	ifs>>a.id;
	ifs>>a.name;
	ifs>>a.amount;
	while(!ifs.eof())
	{
		if(no==a.id)
		{
			do
			{
				cout<<"Enter Amount for Deposit:";
				cin>>bal;
				if(bal<0)
				{
					cout<<"\nEnter Positive Amount."<<endl;
				}
			}while(bal<0);
			no=0;
			a.amount =a.amount +bal;
			ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;	
		}
		else
		{
			ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;	
		}
		ifs>>a.id;
		ifs>>a.name;
		ifs>>a.amount;
	}
	if(no)
	{
		cout<<"\nAccount not Found."<<endl;
	}
	else
	{
		cout<<"\nDeposit Successfully."<<endl;
	}
	ifs.close();
	ofd.close();
	remove("data.txt");
	rename("temp.txt", "data.txt");
}
void Withdrawal()
{
	ifstream ifs;
	ifs.open("data.txt");
	ofstream ofd;
	ofd.open("temp.txt");
	int no;
	double bal;
	cout<<"\nEnter Account ID for Withdrawal Money: ";
	cin>>no;
	Account a;
	ifs>>a.id;
	ifs>>a.name;
	ifs>>a.amount;
	while(!ifs.eof())
	{
		if(no==a.id)
		{
			do
			{
				cout<<"Enter Amount for Withdrawal:";
				cin>>bal;
				if(bal<0)
				{
					cout<<"\nEnter Positive Amount."<<endl;
				}
			}while(bal<0);
			if(a.amount-bal>=0)
			{
				no=0;
				a.amount =a.amount -bal;
				ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;
				cout<<"\nWithdrawal Successfully."<<endl;
			}
			else
			{
				no=0;
				ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;
				cout<<"\nYou have Insufficient Balnace."<<endl;
			}
		}
		else
		{
				ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;	
		}
		ifs>>a.id;
		ifs>>a.name;
		ifs>>a.amount;
	}
	if(no)
	{
		cout<<"\nAccount not Found!"<<endl;
	}
	ifs.close();
	ofd.close();
	remove("data.txt");
	rename("temp.txt", "data.txt");
	
}
void Update()
{
	ifstream ifs;
	ifs.open("data.txt");
	ofstream ofd;
	ofd.open("temp.txt");
	int no;
	bool flag=true;
	cout<<"\nEnter Account ID to Change Account Detail: ";
	cin>>no;
	Account a;
	ifs>>a.id;
	ifs>>a.name;
	ifs>>a.amount;
	while(!ifs.eof())
	{
		if(no==a.id)
		{
			flag=false;
			cout<<"Enter New Account Name : ";
			cin>>a.name;
			cout<<"\nAccount ID:"<<a.id<<"\nAccount Name:"<<a.name<<"\nAccount Balance:"<<a.amount<<endl;
			ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;
		}
		else
		{
			ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;	
		}
		ifs>>a.id;
		ifs>>a.name;
		ifs>>a.amount;
	}
	if(flag)
	{
		cout<<"\nAccount not found!"<<endl;
	}
	ifs.close();
	ofd.close();
	remove("data.txt");
	rename("temp.txt", "data.txt");
}
void Transfer()
{
	ifstream ifs;
	ifs.open("data.txt");
	int acc1,acc2,count=0;
	double bal;
	bool flag=true,amo=false;
	do
	{
		cout<<"\nEnter Amount to Transfer: ";
		cin>>bal;
		if(bal<0)
		{
			cout<<"\nEnter Positive Amount"<<endl;
		}
	}while(bal<0);
	cout<<"Enter Account ID of Sender Account to Transfer Money: ";
	cin>>acc1;
	cout<<"Enter Account ID of Reciever Account to Transfer Money: ";
	cin>>acc2;
	Account a;
	ifs>>a.id;
	ifs>>a.name;
	ifs>>a.amount;
	while(!ifs.eof())
	{
		if(acc1==a.id||acc2==a.id)
		{
			count++;
			if(acc1==a.id)
			{
				flag=false;
				if(a.amount-bal<0)
				{
					count--;
					amo=true;
				}
			}
		}
		ifs>>a.id;
		ifs>>a.name;
		ifs>>a.amount;
	}
	ifs.close();
	if(count==0)
	{
		cout<<"\nBoth Accounts not Found!"<<endl;
	}
	else if(amo)
	{
		cout<<"\nSender have in Sufficient Balance."<<endl;
	}
	else if(count==2)
	{
		ifs.open("data.txt");
		ofstream ofd;
		ofd.open("temp.txt");
		ifs>>a.id;
		ifs>>a.name;
		ifs>>a.amount;
		while(!ifs.eof())
		{
			if(acc1==a.id||acc2==a.id)
			{
				if(acc1==a.id)
				{
					if(a.amount-bal>=0)
					{
						a.amount =a.amount -bal;
						ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;
						cout<<"\nTrnasfer Successfully"<<endl;
					}
				}
				else
				{
					a.amount =a.amount +bal;
					ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;
				}
			}
			else
			{
					ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;	
			}
			ifs>>a.id;
			ifs>>a.name;
			ifs>>a.amount;
		}
		ifs.close();
		ofd.close();
		remove("data.txt");
		rename("temp.txt", "data.txt");
	}
	else if(flag)
	{
		cout<<"\nSender Account not Found!"<<endl;
	}
	else
	{
		cout<<"\nReceiver Account not Found!"<<endl;
	}
}
void Search()
{
	ifstream ifs;
	ifs.open("data.txt");
	Account a;
	int flag=0;
	int no;
	cout<<"\nEnter Account ID to show your Account:";
	cin>>no;
	ifs>>a.id;
	ifs>>a.name;
	ifs>>a.amount;
	while(!ifs.eof())
	{
		if(no==a.id)
		{
			flag=1;
			break;
			
		}	
		ifs>>a.id;
		ifs>>a.name;
		ifs>>a.amount;
	}
	if(flag)
	{
		cout<<"\nAccount Details:\n";
		cout<<"Account ID:"<<a.id<<"\nAccount Name:"<<a.name<<"\nAccount Balance:"<<a.amount<<endl;
	}
	else
	{
		cout<<"\nAccount not found!\n";
	}
	ifs.close();
}
void Delete()
{
	ifstream ifs;
	ifs.open("data.txt");
	ofstream ofd;
	ofd.open("temp.txt");
	int no;
	bool flag=true;
	cout<<"\nEnter Account id to Delete Account : ";
	cin>>no;
	Account a;
	ifs>>a.id;
	ifs>>a.name;
	ifs>>a.amount;
	while(!ifs.eof())
	{
		if(no==a.id)
		{
			cout<<"\nAccount Successfully deleted!\n";
			flag=false;
			
		}
		else
		{
				ofd<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;	
		}
	
		ifs>>a.id;
		ifs>>a.name;
		ifs>>a.amount;
	}
	ifs.close();
	ofd.close();
	remove("data.txt");
	rename("temp.txt", "data.txt");
	if(flag)
	{
		cout<<"\nAccount not Found!"<<endl;
	}
	else
	{
		ShowAccount();
	}
}
void ShowAccount()
{
	ifstream ifs;
	ifs.open("data.txt");
	Account a;
	ifs>>a.id;
	ifs>>a.name;
	ifs>>a.amount;
	while(!ifs.eof())
	{
		cout<<"\n"<<a.id<<"\t"<<a.name<<"\t"<<a.amount<<endl;
		ifs>>a.id;
		ifs>>a.name;
		ifs>>a.amount;
	}
	ifs.close();
}
