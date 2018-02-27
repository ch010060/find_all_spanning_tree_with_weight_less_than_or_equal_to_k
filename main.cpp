#include<iostream>
#include<sstream>
#include<fstream>
#include<memory.h>
#include<ctime>
#define SIZE 800


using namespace std;


struct Node
{
	int ID;          //記名字的
	int NEXTnumber;  //nextnode的數量
	int cost[SIZE];  //距離
	int x; //source
	int y; //destination
    struct Node *nextnode[SIZE];
};

void visit(Node **,Node *);
void visit2(Node **,Node *);
void combination(string, int, int);

int run[SIZE] = {0}; //點的走訪 0:沒走過 1:走過
int run2[SIZE][SIZE];//路的走訪 0:沒走過 1:走過
int run4[SIZE][SIZE];// 2:不給走 2以外:給走

int record[SIZE] = {0};
int recordIndex = 0;

int recordoutput[SIZE] = {0};
int recordoutputIndex = 0;
int output[SIZE][SIZE];


int cycle = 0;
int cycletime = 0;

int totalrun = 0;    // 記錄若干點已走過
int totalcost = 0;   // 記錄走訪的路徑長度

int row = 0;
int col = 0;
int K;
int visitIndex = 0 ;
int num[100];
int roadnumber = 0;
struct Node **point=NULL;
struct Node **run3=NULL;
int TEMPary[SIZE][SIZE];
int DistanceAry[SIZE][SIZE];
int TEMProw=0;
int TEMPcol=0;	
char TEMPbuffer[SIZE];



int main()
{

	clock_t start, stop;

    start = clock(); //開始時間
	
	stringstream ss (stringstream::in | stringstream::out);


//讀檔
	 fstream file;
	file.open("final.in");
	if(!file)
	{
		cout<<"開檔失敗!\n";
		system("pause");
		return 0;
	}
	else
	{

		while(!file.eof()){

		

		if(file.getline(TEMPbuffer,sizeof(TEMPbuffer))==NULL)
			break;
		for(int i=0;TEMPbuffer[i]!='\0';i++)
		{
			if(TEMPbuffer[i]=='-')
				TEMPbuffer[i]='0';
		}

		ss << TEMPbuffer;

		int k=0;//暫時的col		
		while (1)
        {
				
			ss >> TEMPary[TEMProw][k];
			if(TEMProw!=k && TEMPary[TEMProw][k]==0)
			{
				TEMPary[TEMProw][k]=-1;
			}
			k++;

			
			
			if(TEMProw==0)
				TEMPcol++;
			
			if(ss.fail())  //如果全部丟完，就跳出while
				break;
		}

		TEMProw++;
		
		ss.clear();
	
		}
		file.close();
//讀檔結束
		TEMPcol=TEMPcol-1;

		for(int i=0;i<TEMProw-1;i++)
		{
			for(int j=0;j<TEMPcol;j++)
			{
				DistanceAry[i][j]=TEMPary[i][j];
			}

		}

		K=TEMPary[TEMProw-1][0];
		row=TEMProw-1;
		col=TEMPcol;



	}


//檢驗觀賞用
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			cout<<DistanceAry[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"row : "<<row<<"  col : "<<col<<endl;
	cout<<"K : "<<K<<endl;


//建立point
	point = new struct Node *[row];  //點的個數等於方陣大小
	for(int i=0;i<row;i=i+1)
		point[i] = new struct Node;
	for(int i=0;i<row;i=i+1){
		point[i]->ID = i;
	}


//建立run3
	run3 = new struct Node *[SIZE];  //點的個數等於方陣大小
	for(int i=0;i<SIZE;i=i+1)
		run3[i] = new struct Node;
	for(int i=0;i<SIZE;i=i+1){
		run3[i]->ID = i;
	}


int roundtime = 0;
//建立各點的nextnode
	int index;
	for(int i=0;i<row;i++)
	{
		
		index=0;
		point[i]->NEXTnumber=0;
		for(int j=0;j<col;j++)
		{
			point[i]->cost[index] = DistanceAry[i][j];
			if(i!=j && DistanceAry[i][j]>0) //不掃對角,不掃 -1
			{
				point[i]->nextnode[index] = point[j];
				
				if(i<j){
				run3[roundtime]->x = i;
				run3[roundtime]->y = j;
				run4[i][j] = 0;
				run4[j][i] = 0;
				roundtime++;
				}

				point[i]->NEXTnumber++;
				index++;
				roadnumber++;
				
			}
		
		}

	}
	run3[roadnumber/2]='\0';


cout<<"\n";
//檢驗觀賞用
	for(int i=0;i<row;i++)
	{
		int time=point[i]->NEXTnumber;
		int k=0;
		for(int j=0;j<col;j++)
		{
		  if(time>0)
		  {
		  cout<<"point"<<i<<"的nextnode["<<k<<"] : ";
		  cout<<point[i]->nextnode[k]->ID<<" cost:"<<point[i]->cost[k]<<"\n";
		  }
		  time--;
		  k++;

		}
		cout<<"\n";
	}

//run2所有元素初始化為0
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			run2[i][j]=0;
		}
	}




//為了計算cycle數的走訪:開始
	int visittime = 0;
//選擇只有一條對外道路的node當起點，且找到一個就停止迴圈
	for(int i=0;i<row;i++)
	{
		if(point[i]->NEXTnumber==1)
		{
	     visit(point,point[i]);
		 visittime++;
		 break;
		}
	}

//如果剛好對外只有一條路的node不存在，從point0開始走訪
	if(visittime==0)
		 visit(point,point[0]);
//為了計算cycle數的走訪:結束



//run1所有元素初始化為0
	for(int i=0;i<row;i++)
		run[i]=0;
	
//run2所有元素初始化為0
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			run2[i][j]=0;
		}
	}


	for(int i=0;i<roadnumber/2;i++)
		num[i]=i;

	combination("",roadnumber/2,cycle);



	cout<<"結束!"<<endl;

	stop = clock(); //結束時間

    cout <<"一共耗費 "<< double(stop - start) / CLOCKS_PER_SEC<<" 秒"<<endl;
	system("PAUSE");
}





void visit(Node **exp,Node *exp2){


	
	record[recordIndex] = exp2[0].ID;
	/*cout<<(char)(record[recordIndex]+65)<<" → "<<" ";*/
	recordIndex++;
	

	if( run[exp2[0].ID]==0 )   //如果沒走過就進來走
	{ 
        run[exp2[0].ID] = 1;   //走過標記為1
		
		 //預定:push
		 

		 totalrun=0;
		 for(int i=0;i<row;i++)
			 totalrun = totalrun + run[i];

		

//預定:一條遞迴結束;寫檔
		 if(totalrun == row) //走過點的個數=所有點
	    {

			for(int i=0;i<exp2[0].NEXTnumber;i++)
			 {
			     if( (run[exp2[0].nextnode[i]->ID]==1) && (run2[exp2[0].ID][exp2[0].nextnode[i]->ID]==0) && (cycletime == 0) )
				 {
					 /*cout<<"\ncycle!\n";*/

					 cycle++;
					 
				 }
			 }

				/*cout<<"成功!\n\n";*/			
				cycletime++;
				
				
				
			

			

//預定:該條遞迴寫檔結束			  
      	}
	    else 
		{


			for(int i=0;i<exp2[0].NEXTnumber;i++)
			 {	 
				 if( (run[exp2[0].nextnode[i]->ID]==1) && (run2[exp2[0].ID][exp2[0].nextnode[i]->ID]==0) && (cycletime == 0) )
				 {
					/* cout<<"\ncycle!\n";  */
                     cycle++;
				 }
			}


			 for(int i=0;i<exp2[0].NEXTnumber;i++)
			 {

				 if( run[exp2[0].nextnode[i]->ID]==0)
				 {
					 run2[exp2[0].ID][exp2[0].nextnode[i]->ID]=1;
					 run2[exp2[0].nextnode[i]->ID][exp2[0].ID]=1;
			         visit(exp,exp2[0].nextnode[i]);
				 }
				
			 }

			


			 
			
			
			
											  
		 }
		 //預定:pop();

		/*cout<<"\n退回"<<(char)(exp2[0].ID+65)<<"\n";*/
	
		
	



	}


}




void combination(string x, int n, int r)
{
stringstream ss (stringstream::in | stringstream::out);
char buffer[10];
if (r==n||r==0) {
for (int i=r;i>0;i--) x=x+" "+itoa(num[i-1],buffer,10);

char *a=new char[x.size()+1];
char *b=new char[x.size()+1];
a[x.size()]=0;
b[x.size()]=0;
memcpy(a,x.c_str(),x.size());
memcpy(b,x.c_str(),x.size());


//output初始化
				for(int i=0;i<row;i++)
				{
					for(int j=0;j<row;j++)
					{
						if(i==j)
						    output[i][j] = -1;
						else
							output[i][j] = 0;

					}
				}

//取不走的路徑，再做走訪
 ss << a;

int m=0;
while(1)
{
	ss >> m;
	if(ss.fail())
		break;

	run4[run3[m]->x][run3[m]->y] = 2;
	run4[run3[m]->y][run3[m]->x] = 2;
}

ss.clear();

	
	
	


int visittime = 0;
//選擇只有一條對外道路的node當起點，且找到一個就停止迴圈
	for(int j=0;j<row;j++)
	{
		if(point[j]->NEXTnumber==1)
		{
	     visit2(point,point[j]);
		 visittime++;
		 break;
		}
	}

//如果剛好對外只有一條路的node不存在，從point0開始走訪
	if(visittime==0)
		 visit2(point,point[0]);

//開始重走前的初始化
	//run1所有元素初始化為0
	for(int i=0;i<row;i++)
		run[i]=0;
	
    //run2所有元素初始化為0
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			run2[i][j]=0;
		}
	}

//不能走的路徑初始化
ss << b;

int n=0;
while(1)
{
	ss >> n;
	if(ss.fail())
		break;

	run4[run3[n]->x][run3[n]->y] = 0;
	run4[run3[n]->y][run3[n]->x] = 0;
}

ss.clear();



	totalcost=0;
//開始重走前的初始化結束
cout<<"\n<next>\n";


return;
}
combination(x+" "+itoa(num[n-1],buffer,10),n-1,r-1);
combination(x,n-1,r);
}







void visit2(Node **exp,Node *exp2){





	cout<<(char)(exp2[0].ID+65)<<" → "<<" ";

	

	if( run[exp2[0].ID]==0 )   //如果沒走過就進來走
	{ 
        run[exp2[0].ID] = 1;   //走過標記為1
		
		
		 
		 

		 totalrun=0;
		 for(int i=0;i<row;i++)
			 totalrun = totalrun + run[i];
		

		

//一條遞迴結束
		 if(totalrun == row) //走過點的個數=所有點
	    {

			cout<<"totalcost : "<<totalcost<<endl;
			if(totalcost<=K)
			{

				

				for(int i=0;i<row;i++)
				{
					for(int j=0;j<row;j++)
					{
						if(output[i][j] == -1)
						cout<<"-"<<" ";
						else
						cout<<output[i][j]<<" ";
					}
					cout<<"\n";
				}

			    cout<<"成功!\n\n";

//寫檔開始
				char filename[]="final.out";
				fstream file2;
				file2.open((char*) filename, ios::out);      //以out模式開啟檔案，準備寫入

        if(!file2)     //檢查檔案是否成功開啟

        {

                cerr << "Can't open file!\n";

                exit(1);     //在不正常情形下，中斷程式的執行

        }

		else
		{

			for(int i=0;i<row;i++)
				{
					for(int j=0;j<row;j++)
					{
						if(output[i][j] == -1)
						file2<<"-"<<" ";
						else
						file2<<output[i][j]<<" ";
					}
					file2<<"\n";
				}
			file2<<totalcost<<"\n\n";

		}
		file2.close();
//該條遞迴寫檔結束



			   
			}
//初始化
				totalcost = 0;
				totalrun = 0;
			
			
		  
      	}
	    else 
		{

			 for(int i=0;i<exp2[0].NEXTnumber;i++)
			 {

		
				 
				 if( (run[exp2[0].nextnode[i]->ID]==0) && (run4[exp2[0].ID][exp2[0].nextnode[i]->ID]!=2) && (run4[exp2[0].nextnode[i]->ID][exp2[0].ID]!=2) )
				 {

					
					 output[exp2[0].ID][exp2[0].nextnode[i]->ID] = 1;
					 output[exp2[0].nextnode[i]->ID][exp2[0].ID] = 1;
					 totalcost = totalcost + exp2[0].cost[i];
			         visit2(exp,exp2[0].nextnode[i]);
				 }
				
			 }		
											  
		 }
		 cout<<"\n退回"<<(char)(exp2[0].ID+65)<<endl;


	}


}

