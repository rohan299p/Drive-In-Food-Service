
#include<iostream>
#include<string.h>
#include<conio.h>
#include<math.h>
#include<fstream>           // i/o operations on files
#include<stdlib.h>
#include<iomanip>
using namespace std;
ifstream fin;                   // input operations on files
ofstream fout;                  // output operations on files
fstream fio,fio1;

class food
{
        int menu_number;
        float price;
        string menu_name;
        int availability;
    public:
        friend class menu;
}food_obj;

string user_name;
string user_mob_no;

class menu//: public food
{
        int menu_number1;
        float price1;
        string menu_name1;
        //int availability;


        int quantity;
        float total_cost;
        static float sum;
    public:
        menu()
        {
            fout.open("menu_bill.dat",ios::binary|ios::trunc);
            fout.close();
        }
        void get_user_info();
        void buy_food();
        void get_menu_data();
        void update_menu_getdata(int);
        void add_menu();
        void display_menu_();
        void display_menu();

        void update_menu();
        int search_menu(int);
        int search_duplicate(int);

        int avl_check(int);
        void display_bill();
        void display_bill_();
        void generate_bill(int);

        void removefromcart();
        void remove_menu();

        void menu_main_function();
        void call_cust_section();
        void call_admin_section();

}menu_obj;
float menu :: sum=0;

void menu::get_user_info()
{
    cout<<"\n\n"<<setfill(' ')<<setw(22)<<' '<<"Enter Your Name: ";
    cin>>user_name;
    cout<<"\n"<<setfill(' ')<<setw(22)<<' '<<"Enter Your Mobile Number: ";
    cin>>user_mob_no;
}

void menu::get_menu_data()
{
    int rcd;
    cout<<"\n\n"<<setfill(' ')<<setw(10)<<' '<<"----------------------------------------------------------------"<<endl;
    no:
    cout<<"\n\n"<<setfill(' ')<<setw(22)<<' '<<" Enter Menu Identity number: ";
	cin>>rcd;
	while(cin.fail())                                   /////////new addition
    {
        cin.clear();
        cin.ignore();
        cout<<"\n\n"<<setfill(' ')<<setw(25)<<' '<<"Error Occured...Enter Valid Input!!"<<endl;
        Sleep(1500);
        goto no;
    }
	if(rcd<=0)
    {
        cout<<"\n\n"<<setfill(' ')<<setw(15)<<' '<<" Enter Valid Menu Identity number greater than '0'! "<<endl;
        goto no;
    }
    else if(rcd>0)
    {
        if(search_duplicate(rcd)==1)
        {
            display_menu();
            cout<<"\n\t\t Identity Number already exist.\n\t\t Enter Non_existing Number ... "<<endl;
            goto no;
        }
        else
        {
            food_obj.menu_number=rcd;
            goto continu;
        }
    }
    continu:
	cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<" Enter the name of menu: ";
    cin>>food_obj.menu_name;

	cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<" Enter price: ";
    cin>>food_obj.price;

	cout<<"\n"<<setfill(' ')<<setw(15)<<' '<<" Enter Availability: "<<"\n"<<setfill(' ')<<setw(25)<<' '<<" (Enter 1 for AVAILABLE, 0 for UNAVAILABLE ): ";
	cin>>food_obj.availability;
	cout<<"\n\n"<<setfill(' ')<<setw(10)<<' '<<"----------------------------------------------------------------"<<endl;
}

void menu::update_menu_getdata(int update_no)
{
    int rcd;
    cout<<"\n\n"<<setfill(' ')<<setw(10)<<' '<<"----------------------------------------------------------------"<<endl;
    no:
    cout<<"\n\n"<<setfill(' ')<<setw(22)<<' '<<" Enter Menu Identity number: ";
	cin>>rcd;
	while(cin.fail())                                   /////////new addition
    {
        cin.clear();
        cin.ignore();
        cout<<"\n\n"<<setfill(' ')<<setw(25)<<' '<<"Error Occured...Enter Valid Input!!"<<endl;
        Sleep(1500);
        goto no;
    }
	if(rcd<=0)
    {
        cout<<"\n\n"<<setfill(' ')<<setw(15)<<' '<<" Enter Valid Menu Identity number greater than '0'! "<<endl;
        goto no;
    }
    else if(rcd>0)
    {
        if(rcd==update_no)
        {
            food_obj.menu_number=rcd;
            goto continu;
        }
        else
        {
            if(search_duplicate(rcd)==1)
            {
                display_menu();
                cout<<"\n\t\t Identity Number already exist.\n\t\t Enter Non_existing Number ... "<<endl;
                goto no;
            }
        }
    }
    food_obj.menu_number=rcd;
    continu:
	cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<" Enter the name of menu: ";
    cin>>food_obj.menu_name;

	cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<" Enter price: ";
    cin>>food_obj.price;

	cout<<"\n"<<setfill(' ')<<setw(15)<<' '<<" Enter Availability: "<<"\n"<<setfill(' ')<<setw(25)<<' '<<" (Enter 1 for AVAILABLE, 0 for UNAVAILABLE ): ";
	cin>>food_obj.availability;
	cout<<"\n\n"<<setfill(' ')<<setw(10)<<' '<<"----------------------------------------------------------------"<<endl;
}

//---------------------------------------------------------------------------------------------
void menu::add_menu()
{
    int n,i;
	//cout<<"\n Enter the Number of Menus you wish to add: ";
    //cin>>n;
    //if (n!=0)
    //{
        //int j,l,sum=0;
        fout.open("food.dat",ios::binary|ios::app);
       // for(i=0;i<n;i++)
        //{
            get_menu_data();
            fout.write((char*)&food_obj,sizeof(food_obj));
            cout<<"\n\n"<<setfill(' ')<<setw(30)<<' '<<" New Menu is added in List";
            cout<<"\n\n"<<setfill(' ')<<setw(10)<<' '<<"----------------------------------------------------------------";
        //}
   // }
    fout.close();
    _getch();
    system("cls");
    display_menu();
    //cout<<"\n\n Menu List Updated!!";
   _getch();
}

int menu::search_duplicate(int rno)
{
    int i=0;
    fio1.open("food.dat",ios::binary|ios::in|ios::out);
    fio1.seekg(ios::beg);
    while(!fio1.eof())
    {
        fio1.read((char*)&food_obj,sizeof(food_obj));
        if(food_obj.menu_number==rno)
        {
            i++;
            break;
        }
    }
    fio1.close();
    if(i!=0)
        return 1;
    else
        return 0;
}

int menu::search_menu(int nm)
{
	if(nm==menu_obj.menu_number1)
        return 1;
	else
        return 0;
}

void menu::display_menu_()
{
    string availab;
    if(food_obj.availability==1)
        availab="Available";
    else
        availab="Unavailable";
    cout<<endl;
	cout<<setfill(' ')<<setw(7)<<' '<<setw(8)<<food_obj.menu_number<<setw(15)<<food_obj.menu_name<<setw(15)<<food_obj.price<<setw(15)<<availab;
}

void menu::display_menu()
{
	int i=1;
	cout.setf(ios::left);
	cout<<"\n\n-----------------------\t MENU LIST \t--------------------------";
	cout<<"\n\n==================================================================\n\n\n";
	cout<<setfill(' ')<<setw(5)<<' '<<setw(10)<<"#MENU"<<setw(15)<<"MENU NAME"<<setw(15)<<"PRICE(INR)"<<setw(15)<<"AVAILABILITY";
	cout<<"\n\n------------------------------------------------------------------\n";
    fin.open("food.dat",ios::binary);
    fin.seekg(ios::beg);
    while(!fin.eof())
    {
        fin.read((char*)&food_obj,sizeof(food_obj));
        if(!fin.eof())
        {
            if(fin.tellg()<0)
            {
                i=0;
                break;
            }
            display_menu_();
        }
    }
    if(i==0)
    {
        cout<<"\n\n\t\t Menu List is Empty!!";
        _getch();
    }
    cout<<"\n------------------------------------------------------------------\n";
    cout.unsetf(ios::left);
    fin.close();
}

void menu::update_menu()
{
	system("cls");
	int re_no,flag=0;
	int avlb;
	long int pos=0;
	display_menu();
	cout<<"\n\t\t\t To Update Menu:-";
	cout<<"\n\n"<<setfill(' ')<<setw(22)<<' '<<"\n Enter Menu Identity Number: ";
	cin>>re_no;

	fio.open("food.dat",ios::binary|ios::out|ios::in);
    while(!fio.eof())
    {
        pos=fio.tellp();
	    fio.read((char*)&food_obj,sizeof(food_obj));
	    if(food_obj.menu_number==re_no)
	    {
            //food_obj.admin_update(avlb);
            flag++;
            fio.seekp(pos);
            cout<<"\n\n"<<setfill(' ')<<setw(20)<<' '<<"******** Enter New data for the menu ********";
            update_menu_getdata(re_no);
            fio.write((char*)&food_obj,sizeof(food_obj));
            break;
	    }
	    //else
           // cout<<"\n\n!! Menu not found !!";
    }
    fio.close();
    if(flag==0)
    {
        cout<<"\n\n\t\t\t !! Menu not found !!";
        _getch();
    }
    else
    {
        system("cls");
        display_menu();
        cout<<"\n\t\t\t Menu is updated !"<<endl;
        _getch();
    }
}

void menu::remove_menu()
{
    system("cls");
    display_menu();
    int i=0;
    int del;
    cout<<"\n\t\t\t To Delete Menu:-";
    cout<<"\n\n Enter the Menu Identity Number: ";
    cin>>del;
    fout.open("temp.dat",ios::binary);
    fin.open("food.dat",ios::binary);
    while(!fin.eof())
    {
        fin.read((char*)&food_obj,sizeof(food_obj));
        if(!fin.eof())
            if(food_obj.menu_number==del)
            {
                i++;
            }
            else
                fout.write((char*)&food_obj,sizeof(food_obj));
    }
    fin.close();
    fout.close();
    remove("food.dat");
    rename("temp.dat","food.dat");
    if(i==0)
        cout<<"\n\n\t\t\t  Menu not found !!";
    else
    {
        display_menu();
        cout<<"\n\n\t\t Menu deleted successfully!!";
    }
}
//---------------------------------------------------------------------------------------------------------

void menu::buy_food()
{
	system("cls");
	int r_no, qty;
	int i=0;
	long int pos=0;
	display_menu();
	do
    {
        cout<<"\n\n Enter 0(zero) to Go back to Main Menu"<<endl;
        cout<<"\n Enter the Menu Number: ";
        cin>>r_no;
        if(r_no==0)
           break;
        cout<<"\n\n Enter Quantity: ";
        cin>>qty;
        fio.open("food.dat",ios::binary|ios::out|ios::in);
        while(fio)
        {
            //pos=fio.tellp();
            fio.read((char*)&food_obj,sizeof(food_obj));
            if(food_obj.menu_number==r_no)
            {
                if(food_obj.availability==1)
                {
                    cout<<"\n\n Menu added to your cart.";
                    generate_bill(qty);
                    //fio.seekp(pos);
                    //fio.write((char*)&food_obj,sizeof(food_obj));
                    i++;
                    break;
                }
                else
                {
                    cout<<"\n\n Menu currently 'UNAVAILABLE' !";
                    goto buynew;
                }
            }

        }
        if(i==0)
        {
            cout<<"\n\n\t Menu not found !!";
        }
        fio.close();
        buynew:
        _getch();
        system("cls");
        display_menu();
    }
    while(r_no!=0);
}
/*
int menu::avl_check(int check)
{
	if(food_obj.availability==1)
		return 1;
	else
        return 0;
}*/

void menu::generate_bill(int qty)
{
    menu_number1=food_obj.menu_number;
    menu_name1=food_obj.menu_name;
    quantity=qty;
    price1=food_obj.price;
    total_cost=qty*food_obj.price;
    sum=sum+total_cost;
    fout.open("menu_bill.dat",ios::binary|ios::app);
    fout.write((char*)&menu_obj,sizeof(menu_obj));
    fout.close();
}

void menu::display_bill_()
{
    cout<<endl;
    cout<<setfill(' ')<<setw(7)<<' '<<setw(8)<<menu_number1<<setw(12)<<menu_name1<<setw(12)<<quantity<<setw(12)<<price1<<setw(12)<<total_cost;
}

void menu::display_bill()
{
	int r=1;
	cout.setf(ios::left);
	cout<<"\t CUSTOMER NAME : "<<user_name;
	cout<<"\t MOBILE NUMBER : "<<user_mob_no;
	cout<<"\n\n------------------------------\tYOUR CART\t---------------------------------\n";
	cout<<"\n\n======================================================================================\n";
	cout<<setw(10)<<"#MENU"<<setw(12)<<"MENU NAME "<<setw(12)<<"QUANTITY"<<setw(12)<<"PRICE(INR)"<<setw(12)<<"TOTAL PRICE(INR)";
	cout<<"\n\n--------------------------------------------------------------------------------------\n";
    fin.open("menu_bill.dat",ios::binary);
    while(!fin.eof())
    {
        fin.read((char*)&menu_obj,sizeof(menu_obj));
        if(!fin.eof())
        {
            if(fin.tellg()<0)
            {
                r=0;
                break;
            }
            display_bill_();
        }
    }
    if(r==0)
    {
        cout<<"\n\n\t\t\t!!Cart is Empty!!";
    }
    cout<<"\n\n--------------------------------------------------------------------------------------\n";
    cout<<"\n\t\t Total amount to be paid: Rs."<<sum;
    cout<<"\n\n--------------------------------------------------------------------------------------\n";
    //cout.unsetf(ios::left);
    _getch();
    fin.close();
}

void menu::removefromcart()
{
    system("cls");
    int q=0;
    int del,temp;
    display_bill();
    cout<<"\n\nTo Delete Food Item:-";
    cout<<"\nEnter Menu Identity Number: ";
    cin>>del;
    fout.open("temp1.dat",ios::binary);
    fin.open("menu_bill.dat",ios::binary);
    while(!fin.eof())
    {
        fin.read((char*)&menu_obj,sizeof(menu_obj));
        //if(!fin.eof())
            if(menu_obj.search_menu(del)==1)
            {
                menu_obj.sum=menu_obj.sum-menu_obj.total_cost;
                cout<<"\n\n\t\t Food Item is removed from your cart!!";
                q++;
            }
            else
                fout.write((char*)&menu_obj,sizeof(menu_obj));
    }
    if(q==0)
        cout<<"\n\n\t Menu not found!!";
    fin.close();
    fout.close();
    remove("menu_bill.dat");
    rename("temp1.dat","menu_bill.dat");
    menu_obj.display_bill();
}

void menu::call_cust_section()
{
    int choice;
    system("cls");
    get_user_info();
    cust_section:
        system("cls");
        cout<<"\n\n\n\n"<<setfill(' ')<<setw(10)<<' '<<"==================== CUSTOMER SECTION ===================="<<endl;
        cout<<"\n\n"<<setfill(' ')<<setw(28)<<' '<<"1. ADD MENU TO CART"<<endl;
        cout<<"\n"<<setfill(' ')<<setw(28)<<' '<<"2. SHOW MENU LIST"<<endl;
        cout<<"\n"<<setfill(' ')<<setw(28)<<' '<<"3. REMOVE MENU FROM MY CART"<<endl;
        cout<<"\n"<<setfill(' ')<<setw(28)<<' '<<"4. SHOW MY CART"<<endl;
        cout<<"\n"<<setfill(' ')<<setw(28)<<' '<<"5. CONFIRM ORDER"<<endl;
        cout<<"\n"<<setfill(' ')<<setw(28)<<' '<<"6. CANCEL ORDER"<<endl;
        cout<<"\n\n"<<setfill(' ')<<setw(10)<<' '<<"----------------------------------------------------------"<<endl;
        cout<<"\n"<<setfill(' ')<<setw(28)<<' '<<"Enter your Choice: ";
        cin>>choice;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout<<"\n\n"<<setfill(' ')<<setw(25)<<' '<<"Error Occured...Enter Valid Input!!"<<endl;
            Sleep(1500);
            goto cust_section;
        }
        cout<<"\n\n"<<setfill(' ')<<setw(10)<<' '<<"=========================================================="<<endl;
        Sleep(200);
        switch(choice)
        {
            case 1:
                buy_food();
                _getch();
                goto cust_section;
                break;

            case 2:
                system("cls");
               display_menu();
                _getch();
                goto cust_section;
                break;

            case 3:
                removefromcart();
                _getch();
                goto cust_section;
                break;

            case 4:
                system("cls");
                display_bill();
                _getch();
                goto cust_section;
                break;

            case 5:
                system("cls");
                display_bill();
                cout<<"\n\n\n\t\tThank You For Ordering Food On our Platform!!";
                cout<<"\n\n\n\t   Your Order will be ready while you reached to us!";
                _getch();
                system("cls");
                return;
                break;

            case 6:
                system("cls");
                cout<<"\n\n\n\t\tThank You For Using our Platform!!";
                cout<<"\n\n\n\t\t\t  SEE YOU SOON!!";
                _getch();
                system("cls");
                return;
                break;

            default:
                cout<<"\nEnter valid choice."<<endl;
                goto cust_section;
                break;
        }
}

void menu::call_admin_section()
{
    string pass,paswrd="admin";
    password:
        system("cls");
        cout<<"\n\n\tEnter the password letter by letter: ";
        //for(int z=0;z<5;z++)
        //{
            cin>>pass;
            //system("cls");
            //cout<<"\n\n\tEnter the password letter by letter: ";
            /*for(int i=1;i<=(z+1);i++)
            {
                cout<<"*";
            }*/
       // }
        if(pass==paswrd)
        {
            int choice;
            admin_section:
                system("cls");
                cout<<"\n\n\n\n"<<setfill(' ')<<setw(10)<<' '<<"======================= ADMIN SECTION ======================="<<endl;
                cout<<"\n\n"<<setfill(' ')<<setw(30)<<' '<<"1. ADD NEW MENU"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(30)<<' '<<"2. SHOW MENU LIST"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(30)<<' '<<"3. UPDATE MENU"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(30)<<' '<<"4. REMOVE MENU"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(30)<<' '<<"5. EXIT"<<endl;
                cout<<"\n\n"<<setfill(' ')<<setw(10)<<' '<<"-------------------------------------------------------------"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(30)<<' '<<"Enter your Choice: ";
                cin>>choice;
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                    cout<<"\n\n"<<setfill(' ')<<setw(25)<<' '<<"Error Occured...Enter Valid Input!!"<<endl;
                    Sleep(1500);
                    goto admin_section;
                }
                cout<<"\n\n"<<setfill(' ')<<setw(10)<<' '<<"=============================================================="<<endl;
                Sleep(200);
                switch(choice)
                {
                    case 1:
                        add_menu();
                        _getch();
                        goto admin_section;
                        break;

                    case 2:
                        system("cls");
                        display_menu();
                        _getch();
                        goto admin_section;
                        break;

                    case 3:
                        update_menu();
                        _getch();
                        goto admin_section;
                        break;

                    case 4:
                       remove_menu();
                        _getch();
                        goto admin_section;
                        break;

                    case 5:
                        system("cls");
                        cout<<"\n\n\n\n\n\n\n\n\n\n"<<setfill(' ')<<setw(20)<<' '<<"***** Thank You For Choosing Us *****"<<endl;
                        Sleep(1000);
                        system("cls");
                        return;
                        break;

                    default:
                        cout<<"\nEnter valid choice."<<endl;
                        goto admin_section;
                        break;
                }
        }
        else
        {
            cout<<"\n\n\n\n\n\n\n\n\n\n"<<setfill(' ')<<setw(20)<<' '<<"Access Denied! Authorized Persons Only!!"<<endl;
            cout<<"\n\n "<<setfill(' ')<<setw(20)<<' '<<"Enter correct password."<<endl;
            _getch();
            goto password;
        }
}

void menu::menu_main_function()
{
    //get_user_info();
	int i,j;
	system("cls");
	//cout<<" HELLO "<<user_name;
	cout<<"\n\n|================= WELCOME TO DRIVE IN FOOD SERVICE =================|";
	cout<<"\n\n\t\t   1. CUSTOMER SECTION\n\n\t\t   2. ADMIN SECTION\n\n\t\t   3. EXIT";
	cout<<"\n\n|====================================================================|\n";
	cout<<"\n\nSELECT YOUR CHOICE: ";
	cin>>j;
	if(j==2)
	{
        /*password:
        system("cls");
        cout<<"\n\n\tEnter the password letter by letter: ";
        for(int z=0;z<5;z++)
        {
            pass[z]=getch();
            system("cls");
            cout<<"\n\n\tEnter the password letter by letter: ";
            for(i=1;i<=(z+1);i++)
            {
                cout<<"*";
            }
        }
        if(strcmp(pass,"owner")==1)
        {*/
            system("cls");
            ownermenu:
            system("cls");
            cout<<"====================== ADMIN SECTION ===========================";
            cout<<"\n\n\t\t\t 1. Add New Menu\n\t\t\t2. Show Menu List\n\t\t\t3. Update Menu\n\t\t\t4. Remove Menu\n\t\t\t5. Exit";
            cout<<"\n\n\n========================== END OF SECTION =============================";
            cout<<"\n\n SELECT YOUR CHOICE: ";
            cin>>i;
            switch(i)
            {
                case 1:
                    menu_obj.add_menu();
                    _getch();
                    goto ownermenu;
                    break;

                case 2:
                    system("cls");
                    menu_obj.display_menu();
                    _getch();
                    goto ownermenu;
                    break;

                case 3:
                    menu_obj.update_menu();
                    _getch();
                    goto ownermenu;
                    break;

                case 4:
                    menu_obj.remove_menu();
                    _getch();
                    goto ownermenu;
                    break;

                case 5:
                    system("cls");
                    cout<<"\n\n\n\t\t\tThank You For Choosing Us!!";
                    _getch();
                    exit(0);
                    break;

                default:
                    cout<<"\nEnter valid choice."<<endl;
                    goto ownermenu;
                    break;
            }
        //}
        /*else
        {
            cout<<"\n\nAccess Denied! Authorized Persons Only.\n\n";
            cout<<"\n Please, enter correct password."<<endl;
            getch();
            goto password;
            exit(0);
        }*/
	}
    if(j==1)
	{
		custmenu:
        system("cls");
        cout<<"\n\n\t===================== CUSTOMER SECTION ===========================";
        cout<<"\n\n\t\t\t1. Add Food to Cart\n\t\t\t2. Show Menu\n\t\t\t3. Remove Food from Cart\n\t\t\t4. Show My Cart\n\t\t\t5. Exit";
        cout<<"\n\n========================== END OF SECTION =============================";
        cout<<"\n\n Enter your Choice: ";
        cin>>i;
        switch(i)
        {
            case 1:
                menu_obj.buy_food();
                _getch();
                goto custmenu;
                break;

            case 2:
                system("cls");
                menu_obj.display_menu();
                _getch();
                goto custmenu;
                break;

            case 3:
                menu_obj.removefromcart();
                _getch();
                goto custmenu;
                break;

            case 4:
                system("cls");
                menu_obj.display_bill();
                _getch();
                goto custmenu;
                break;

            case 5:
                system("cls");
                menu_obj.display_bill();
                cout<<"\n\n\n\t\t\tThank You For Shopping!!";
                cout<<"\n\n\n\t\t\t  Visit Again!!";
                _getch();
                exit(0);
                break;

            default:
                cout<<"\nEnter valid choice."<<endl;
                goto custmenu;
                break;
        }
    }
    else if(j!=1 && j!=2 && j==3)
    {
        goto programend;
    }
    _getch();
    programend:
    return ;
}
