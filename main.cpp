
#include<iostream>
#include<cstring>
#include<fstream>
#include<graphics.h>
#include<string.h>
#include<stdio.h>
#include "menu.h"
#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include<iomanip>
#define INFINITY 999
#define v 14        // total vertices
using namespace std;

using namespace std;
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void loading_bar(string loading)
{
    char c=219;
    system("cls");
    int i=1,limit=40,x=20,y=12;
    gotoxy(35,10);
    cout<<loading;
    while(i<=limit)
    {
        gotoxy(x++,y);
        putchar(c);
        i+=1;
        Sleep(20);
    }
    system("cls");
}

class node
{
	string hotel_name;
	int hotel_x,hotel_y;
	int distance;
	node* next;
    int V;
	public:
		node()
		{
			hotel_name=" ";
			distance=0;
			next=NULL;
		}
		friend class graph;
};

class graph
{

	node* head[15];
    int finalarr[100];
    int route[100];         //new addition
    int adjacency_matrix[v+1][v+1];
    int co_ordinates[v+1][2];
    int z,z1;
    int nearest_node_from_user[v];              //to store distance of nearest node from user
    char hotel_name[v]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N'};
    char nearest_node_array[v]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N'};
    public:
        int user_x,user_y;
        int no_of_nodes=v;
        graph()
        {
            ifstream fin2("input1.txt",ios::in);
            for(int i=0;i<v;i++)
            {

                head[i]=new node;
                head[i]->V=i;
                fin2>>head[i]->hotel_name;
                fin2>>head[i]->hotel_x;
                fin2>>head[i]->hotel_y;
                //cout<<head[i]->V<<head[i]->hotel_name<<head[i]->hotel_x<<head[i]->hotel_y;
            }
            fin2.close();
            head[v]=new node;
            head[v]->V=v;
            head[v]->hotel_name="O";
            head[v]->hotel_x=user_x;
            head[v]->hotel_y=user_y;

            for(int i=0;i<v+1;i++){
				for(int j=0;j<2;j++)
					co_ordinates[i][j]=0;
            }

			for(int i=0;i<v+1;i++){
				for(int j=0;j<v+1;j++)
                    adjacency_matrix[i][j]=INFINITY;             //adjacency matrix
            }

            for(int i=0;i<v;i++){
                    adjacency_matrix[i][i]=0;
            }

            for(int i=0;i<100;i++){
                    route[i]=0;
            }
        }

        void dijkstras(string,string,int);
        int getindex(string);
        int check(int*);
		int findmin(int*,int*,int&);
		void display_adjlist();
        void create_adj_list();
        void display_adj_matrix();
        void calculateDistance();
        void output();
        void printPath(int);
        void read();
        void initialize();
        int getClosestUnmarkedNode();

		void nearshops(int*,int*,string,string);

        void create_graph()
        {
            int x,y,d;
            ifstream fin,fin1;
            fin.open("map2.txt");
            for(int i=0;i<14;i++){
                for(int j=0;j<2;j++){
                    fin>>co_ordinates[i][j];
                }
            }
            fin.close();
            fin1.open("distance.txt");
            while(!fin1.eof())
            {
                fin1>>x;
                fin1>>y;
                fin1>>d;
                adjacency_matrix[x][y]=d;
                adjacency_matrix[y][x]=adjacency_matrix[x][y];
            }
            fin1.close();
        }

        void display_graph(int flag=0)
        {

            int gd=DETECT,gm;
            initgraph(&gd, &gm, NULL);
            if(!flag)
            {
                put_vertices();
                setcolor(15);
                put_edges();
                cout<<"\n\n\n"<<setfill(' ')<<setw(30)<<' '<<"*** PRESS ANY KEY ***"<<endl;
                _getch();
            }
            if(flag)
            {
                put_vertices();
                setcolor(15);
                put_edges();
                highlight_path();
                cout<<"\n\n\n"<<setfill(' ')<<setw(25)<<' '<<"*** PRESS ENTER TO RETURN ***"<<endl;
                _getch();
            }
            closegraph();
        }

        void highlight_path()
        {
            setlinestyle(0,0,5);
            int j=0;
            for(j=0;j<z-1;j++)
            {
                setcolor(9);
                line(co_ordinates[route[j]][0],co_ordinates[route[j]][1],co_ordinates[route[j+1]][0],co_ordinates[route[j+1]][1]);
            }
        }

        void put_vertices()
        {
            char A[]="A",B[]="B",C[]="C",D[]="D",E[]="E",F[]="F",G[]="G",H[]="H",I[]="I",J[]="J",K[]="K",L[]="L",M[]="M",N[]="N",O[]="O(YOU)";
            setcolor(14);
            outtextxy(co_ordinates[0][0],co_ordinates[0][1]-20,A);
            outtextxy(co_ordinates[1][0],co_ordinates[1][1]-20,B);
            outtextxy(co_ordinates[2][0],co_ordinates[2][1]-20,C);
            outtextxy(co_ordinates[3][0],co_ordinates[3][1]-20,D);
            outtextxy(co_ordinates[4][0],co_ordinates[4][1]-20,E);
            outtextxy(co_ordinates[5][0],co_ordinates[5][1]-20,F);
            outtextxy(co_ordinates[6][0],co_ordinates[6][1]-20,G);
            outtextxy(co_ordinates[7][0],co_ordinates[7][1]-20,H);
            outtextxy(co_ordinates[8][0]+5,co_ordinates[8][1]-20,I);
            outtextxy(co_ordinates[9][0],co_ordinates[9][1]-20,J);
            outtextxy(co_ordinates[10][0],co_ordinates[10][1]-20,K);
            outtextxy(co_ordinates[11][0],co_ordinates[11][1]-20,L);
            outtextxy(co_ordinates[12][0],co_ordinates[12][1]-20,M);
            outtextxy(co_ordinates[13][0],co_ordinates[13][1]-20,N);
            setcolor(2);
            outtextxy(co_ordinates[14][0],co_ordinates[14][1]+10,O);
            setcolor(12);
            for(int i=0;i<v;i++)
            {
                circle(co_ordinates[i][0],co_ordinates[i][1],5);
            }
            setcolor(RED);
                circle(co_ordinates[v][0],co_ordinates[v][1],5);
            setcolor(CYAN);
                circle(co_ordinates[v][0],co_ordinates[v][1],7);
        }

        void put_edges()
        {
            int i;
            char n;
            for(i=0;i<v;i++){
                for(int j=i;j<v;j++){
                    if(adjacency_matrix[i][j]!=INFINITY){
                        line(co_ordinates[i][0],co_ordinates[i][1],co_ordinates[j][0],co_ordinates[j][1]);
                        //cout<<co_ordinates[i][0]<<"\t"<<co_ordinates[i][1]<<"\t"<<co_ordinates[j][0]<<"\t"<<co_ordinates[j][1]<<endl;
                    }
                }
            }
            for(i=0;i<z1;i++){
                    n=nearest_node_array[i];
                    line(user_x,user_y,co_ordinates[n-65][0],co_ordinates[n-65][1]);

            }
        }

        void reset_adj_matrix()
        {
                co_ordinates[v][0]=co_ordinates[v][1]=0;
                user_x=user_y=0;
                for(int i=0;i<v;i++)
                {
                    adjacency_matrix[v][i]=INFINITY;
                    nearest_node_from_user[i]=0;
                }
                adjacency_matrix[v][v]=0;
                for(int j=0;j<14;j++)
                {
                    nearest_node_array[j]=(char)(65+j);
                }
        }

        int get_min_dist(int x1, int y1, int x2, int y2)
        {
            return sqrt(pow(x2-x1,2)+pow(y2-y1,2))/10;
        }

        void bubble_sort()
        {
            int temp;
            char temp1;
            for(int i=0;i<v;i++)
            {
                for(int j=0;j<v-1;j++)
                {
                    if(nearest_node_from_user[j]>nearest_node_from_user[j+1])
                    {
                        temp=nearest_node_from_user[j];
                        nearest_node_from_user[j]=nearest_node_from_user[j+1];
                        nearest_node_from_user[j+1]=temp;

                        temp1=nearest_node_array[j];
                        nearest_node_array[j]=nearest_node_array[j+1];
                        nearest_node_array[j+1]=temp1;
                    }
                }
            }
        }

        void get_nearest_node(int x,int y)
        {
            for(int i=0;i<v;i++){
                    nearest_node_from_user[i]=get_min_dist(x,y,co_ordinates[i][0],co_ordinates[i][1]);}
            bubble_sort();
            /*for(int i=0;i<v;i++)
             {
                 cout<<nearest_node_from_user[i]<<"\n";
                 cout<<nearest_node_array[i]<<"\n";
             }*/
        }

        void add_user_loc(int userx,int usery)
        {
            //z=0;
            co_ordinates[v][0]=userx;
            co_ordinates[v][1]=usery;

            char n;     //nearest node

            if(nearest_node_from_user[0]>12)
            {
                n=nearest_node_array[0];
                adjacency_matrix[v][n-65]=nearest_node_from_user[0];
                adjacency_matrix[n-65][v]=nearest_node_from_user[0];
            }
            else
            {
                for(int j=0;j<=v;j++)
                {
                    n=nearest_node_array[j];
                    if(nearest_node_from_user[j]<=12)
                    {
                        adjacency_matrix[v][n-65]=nearest_node_from_user[j];
                        adjacency_matrix[n-65][v]=nearest_node_from_user[j];
                        z1++;
                    }
                }
            }
        }

        void get_location()
        {
            z1=0;
            system("cls");
            cout<<"\n\n"<<setfill(' ')<<setw(12)<<' '<<"NOTE: CO-ORDINATES LIMIT: X->(0 to 640)   Y->(0 to 480)"<<endl;
            cout<<"\n\n"<<setfill(' ')<<setw(20)<<' '<<"========== Enter your location ==========="<<endl;
            getx:
            cout<<"\n\n"<<setfill(' ')<<setw(30)<<' '<<" X-coordinate : ";
            cin>>user_x;
            if(user_x>640)
            {
                cout<<"\n\n"<<setfill(' ')<<setw(13)<<' '<<" INCORRECT CO-ORDINATE........ Enter again....\n";
                goto getx;
            }
            gety:
            cout<<"\n"<<setfill(' ')<<setw(30)<<' '<<" Y-coordinate : ";
            cin>>user_y;
             if(user_y>480)
            {
                cout<<"\n\n"<<setfill(' ')<<setw(13)<<' '<<" INCORRECT CO-ORDINATE........ Enter again....\n";
                goto gety;
            }
            cout<<"\n\n"<<setfill(' ')<<setw(20)<<' '<<"=========================================="<<endl;
            no_of_nodes++;
            get_nearest_node(user_x,user_y);
            add_user_loc(user_x,user_y);
            create_adj_list();
            loading_bar("GETTING LOCATION");
            Sleep(200);
        }
};

void graph::create_adj_list()
{
	node *curr, *temp;
	for(int i=0;i<=v;i++)
    {
        temp=head[i];
        for(int j=0;j<=v;j++)
        {
            if(adjacency_matrix[i][j]!=INFINITY )
            {
                if(adjacency_matrix[i][j]!=0 )
                {curr=new node;
                curr->V=head[j]->V;
                curr->hotel_name=head[j]->hotel_name;
                curr->hotel_x=head[j]->hotel_x;
                curr->hotel_y=head[j]->hotel_y;
                curr->distance=adjacency_matrix[i][j];
                curr->next=NULL;
                temp->next=curr;
                temp=curr;}
            }

        }
    }
}

void graph::display_adjlist()
{
    node *temp;
    system("cls");
    cout<<"\n"<<setfill(' ')<<setw(12)<<' '<<"******************** ADJACENCY LIST ********************"<<endl;
    cout<<"\n";
    for(int i=0;i<=v;i++)
    {
        temp=head[i]->next;
        cout<<"\n"<<setfill(' ')<<setw(5)<<' '<<head[i]->hotel_name<<" "<<head[i]->distance;
        while(temp!=NULL)
        {
            if(head[i]->next!=NULL)
                cout<<"----->"<<temp->hotel_name<<" "<<temp->distance;
            temp=temp->next;
        }
        cout<<endl;
    }
    cout<<"\n"<<setfill(' ')<<setw(30)<<' '<<"*** PRESS ANY KEY ***"<<endl;
    _getch();
}

int graph::getindex(string sname)
{
	int i=0;
	while(i<no_of_nodes && sname!=head[i]->hotel_name){
		i++;
	}
	if(i>=no_of_nodes){
		return -1;
	}
	else{
		return i;
	}
}

void graph::display_adj_matrix()
{
    for(int i=0;i<=v;i++)
    {
       for(int j=0; j<=v;j++)
            cout<<adjacency_matrix[i][j]<<" ";
        cout<<"\n";
    }
    /*for(int i=0;i<=v;i++)
    {
       for(int j=0; j<2;j++)
            cout<<co_ordinates[i][j]<<" ";
        cout<<"\n";
    }*/
}

int graph::check(int* visited)
{
	for(int i=0;i<no_of_nodes;i++)
		if(!visited[i])
			return 1;

	return 0;
}

int graph::findmin(int* distances,int* visited,int& min)
{
	int minindex=-1;
	for(int i=0;i<no_of_nodes;i++)
	{
		if(distances[i]<min && visited[i]==0)
		{
			min=distances[i];
			minindex=i;
		}
	}
	return minindex;
}

void graph::nearshops(int* distances,int* visited,string dhotel,string shotel)
{
	int* tdistances;
	tdistances=new int[no_of_nodes];

	int loc[20]={0};

	for(int i=0;i<no_of_nodes;i++)
	{
		tdistances[i]=distances[i];
	}

	sort(tdistances,tdistances+no_of_nodes);
	//cout<<setfill(' ')<<setw(15)<<' '<<" ******You could try even our centers nearest to your location******* ";
    cout<<"\n\n\n"<<setfill(' ')<<setw(16)<<' '<<" ******* OUR OTHER RESTAURENTS NEAR YOU *******"<<endl;
    cout<<"\n";
    int count=0;
   for(int i=0;i<6;i++)
	{
		int key=tdistances[i];
		for(int j=0;j<no_of_nodes;j++)
		{
			if(distances[j]==key && head[j]->hotel_name!=dhotel && loc[j]!=1)
			{
				cout<<"\n"<<setfill(' ')<<setw(30)<<' '<<head[j]->hotel_name<<" --> DISTANCE = "<<distances[j]<<" KM "<<endl;
				loc[j]=1;
				count++;
				break;
			}
		}
	}
}


void graph::dijkstras(string shotel,string dhotel,int flag=0)
{
	int *distances;
	distances=new int[no_of_nodes];

	int *visited;
	visited=new int[no_of_nodes];

	int previndex[no_of_nodes];
	for(int i=0;i<no_of_nodes;i++)
	{
		previndex[i]=-1;
	}

	for(int i=0;i<no_of_nodes;i++)
	{
		distances[i]=9999;		// infinity
	}
	int j=getindex(shotel);
	distances[j]=0;							//source
	node* temp;

	temp=head[j];
	temp=temp->next;
	while(temp!=NULL)
	{
		if(temp->distance!=0)
		{
			distances[getindex(temp->hotel_name)]=temp->distance;
			previndex[getindex(temp->hotel_name)]=j;
		}
		temp=temp->next;
	}

	memset(visited,0,no_of_nodes*sizeof(int));
	while(check(visited))
	{
		int min=9999;
		int minindex=findmin(distances,visited,min);
		temp=head[minindex];
		temp=temp->next;
		while(temp!=NULL)
		{
			if(visited[getindex(temp->hotel_name)]==0)
			{
				if(((temp->distance)+min)<distances[getindex(temp->hotel_name)])
				{
					distances[getindex(temp->hotel_name)]=min+(temp->distance);
					previndex[getindex(temp->hotel_name)]=minindex;
				}
			}
			temp=temp->next;
		}
		visited[minindex]=1;
	}

	int tempindex=getindex(dhotel);
	int finalarr[100];
	int y=1;
	finalarr[0]=tempindex;
	while(tempindex!=getindex(shotel))
	{
		tempindex=previndex[tempindex];
		finalarr[y]=tempindex;
		y++;
    }

    if(!flag)
    {
        system("cls");
        cout<<"\n\n\n"<<setfill(' ')<<setw(9)<<' '<<"***** DIRECTIONS FROM YOUR LOCATION TO YOUR DESTINATION *****"<<endl;
        cout<<"\n\n\n";
        int x=0;
        z=0;
        y=y-1;
        while(y!=-1)
        {
            route[x]=finalarr[y];
            x++;z++;
            if(y==0)
                break;
            cout<<setfill(' ')<<setw(18)<<' '<<head[finalarr[y]]->hotel_name<<"\t-----> "<<head[finalarr[y-1]]->hotel_name<<"\t Distance: "<<adjacency_matrix[getindex(head[finalarr[y]]->hotel_name)][getindex(head[finalarr[y-1]]->hotel_name)]<<" KM"<<endl;;
            y--;
        }

        cout<<"\n\n"<<setfill(' ')<<setw(18)<<' '<<" MINIMUM DISTANCE FROM "<<shotel<<" to "<<dhotel<<" is = "<<distances[getindex(dhotel)]<<" KM "<<endl;
        cout<<"\n\n"<<setfill(' ')<<setw(9)<<' '<<"*************************************************************"<<endl;
    }
    if(flag)
	{
	    system("cls");
        nearshops(distances,previndex,shotel,dhotel);
	}
}

int main()
{
    menu m;                                    //object of class menu
    graph g;                                   //object of class graph
    system("cls");
    int choice,choice1;
    char ch1;
    system("color 3E");
    string source="O",destination;
    g.create_graph();
    do
    {
        label1:
        system("cls");
        cout<<"\n\n\n\n\n\n"<<setfill(' ')<<setw(11)<<' '<<"********** WELCOME TO DRIVE IN FOOD SERVICE **********"<<endl;
        cout<<"\n\n"<<setfill(' ')<<setw(30)<<' '<<"1. CUSTOMER SECTION"<<endl;
        cout<<"\n"<<setfill(' ')<<setw(30)<<' '<<"2. ADMIN SECTION"<<endl;
        cout<<"\n"<<setfill(' ')<<setw(30)<<' '<<"3. EXIT"<<endl;
        cout<<"\n\n"<<setfill(' ')<<setw(11)<<' '<<"------------------------------------------------------"<<endl;
        cout<<"\n"<<setfill(' ')<<setw(28)<<' '<<"Enter Your Choice: ";
        cin>>choice;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout<<"\n\n"<<setfill(' ')<<setw(25)<<' '<<"Error Occured...Enter Valid Input!!"<<endl;
            Sleep(1500);
            goto label1;
        }
        cout<<"\n\n"<<setfill(' ')<<setw(11)<<' '<<"******************************************************"<<endl;
        Sleep(250);
        switch(choice)
        {
            case 1:
                system("cls");
                cout<<"\n\n\n"<<setfill(' ')<<setw(11)<<' '<<"********** WELCOME TO DRIVE IN FOOD SERVICE **********"<<endl;
                cout<<"\n\n"<<setfill(' ')<<setw(20)<<' '<<"********** CUSTOMER SECTION **********"<<endl;
                g.get_location();
                changedest:
                system("cls");
                cout<<"\n\n\n"<<setfill(' ')<<setw(11)<<' '<<"*** CHOOSE YOUR FAVOURITE RESTAURANT FROM OUR NETWORK ***"<<endl;
                cout<<"\n\n"<<setfill(' ')<<setw(22)<<' '<<"A. BRANCH 1"<<setfill(' ')<<setw(9)<<' '<<"B. BRANCH 2"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(22)<<' '<<"C. BRANCH 3"<<setw(20)<<"D. BRANCH 4"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(22)<<' '<<"E. BRANCH 5"<<setw(20)<<"F. BRANCH 6"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(22)<<' '<<"G. BRANCH 7"<<setw(20)<<"H. BRANCH 8"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(22)<<' '<<"I. BRANCH 9"<<setw(21)<<"J. BRANCH 10"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(22)<<' '<<"K. BRANCH 11"<<setw(20)<<"L. BRANCH 12"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(22)<<' '<<"M. BRANCH 13"<<setw(20)<<"N. BRANCH 14"<<endl;
                cout<<"\n\n"<<setfill(' ')<<setw(11)<<' '<<"----------------------------------------------------------"<<endl;
                g.display_graph();
                enterdestagain:
                cout<<"\n\n"<<setfill(' ')<<setw(28)<<' '<<"Enter Your Choice: ";
                cin>>destination;
                while(destination[0]<65 || destination[0]>90)
                {
                    cin.clear();
                    cin.ignore();
                    cout<<"\n\n"<<setfill(' ')<<setw(25)<<' '<<"Error Occured...Enter Valid Input!!"<<endl;
                    goto enterdestagain;
                }
                label2:
                system("cls");
                cout<<"\n\n"<<setfill(' ')<<setw(22)<<' '<<"YOUR LOCATION:  X->"<<g.user_x<<"   "<<" Y->"<<g.user_y<<endl;
                cout<<"\n\n"<<setfill(' ')<<setw(22)<<' '<<"YOUR DESTINATION: "<<destination<<endl;
                cout<<"\n\n"<<setfill(' ')<<setw(11)<<' '<<"****************** CUSTOMER SECTION ******************"<<endl;
                cout<<"\n\n"<<setfill(' ')<<setw(25)<<' '<<"1. BUY FOOD"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<"2. SEE ROUTE TO YOUR DESTINATION"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<"3. SEE NEAREST RESTAURENTS"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<"4. SEE OUR NETWORK(MAP)"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<"5. SEE ADJACENCY LIST"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<"6. CHANGE DESTINATION"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<"7. RETURN"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(25)<<' '<<"8. EXIT"<<endl;
                cout<<"\n\n"<<setfill(' ')<<setw(11)<<' '<<"------------------------------------------------------"<<endl;
                cout<<"\n"<<setfill(' ')<<setw(28)<<' '<<"Enter Your Choice: ";
                cin>>choice1;
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                    cout<<"\n\n"<<setfill(' ')<<setw(25)<<' '<<"Error Occured...Enter Valid Input!!"<<endl;
                    Sleep(1500);
                    goto label2;
                }
                cout<<"\n"<<setfill(' ')<<setw(11)<<' '<<"******************************************************"<<endl;
                Sleep(200);
                switch(choice1)
                {
                    case 1:
                        m.call_cust_section();
                        goto label2;
                        break;

                    case 2:
                        g.dijkstras(source,destination);
                        g.display_graph(1);
                        goto label2;
                        break;

                    case 3:
                        g.dijkstras(source,destination,1);
                        g.display_graph();
                        goto label2;
                        break;

                    case 4:
                        g.display_graph();
                        goto label2;
                        break;

                    case 5:
                        g.display_adjlist();
                        cout<<"\n\n\n"<<setfill(' ')<<setw(25)<<' '<<"*** PRESS ENTER TO RETURN ***"<<endl;
                        cin.get();
                        goto label2;
                        break;

                    case 6:
                        goto changedest;
                        break;

                    case 7:
                        g.reset_adj_matrix();
                        g.no_of_nodes--;
                        goto label1;
                        break;

                    case 8:
                        return 0;
                        break;

                    default:
                    cout<<"\n"<<setfill(' ')<<setw(28)<<' '<<"Enter valid choice!"<<endl;
                    Sleep(500);
                    goto label1;
                    break;
                }
                break;

            case 2:
                system("cls");
                m.call_admin_section();
                goto label1;
                break;

            case 3:
                gotoxy(0,25);
                cout<<"\n"<<setfill(' ')<<setw(22)<<' '<<"*** THANK YOU FOR CHOOSING US ***"<<endl;
                Sleep(200);
                return 0;
                break;

            default:
                cout<<"\n"<<setfill(' ')<<setw(28)<<' '<<"Enter valid choice!"<<endl;
                Sleep(500);
                goto label1;
                break;
        }
         cout<<"\n\n"<<setfill(' ')<<setw(11)<<' '<<"------------------------------------------------------"<<endl;
        cout<<"\n"<<setfill(' ')<<setw(22)<<' '<<"Do you want to continue?(y or n): ";
        cin>>ch1;
        Sleep(100);
        system("cls");
    }while(ch1=='y'||ch1=='Y');
    return 0;
}
