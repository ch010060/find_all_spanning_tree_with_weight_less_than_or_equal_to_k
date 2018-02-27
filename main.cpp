#include<iostream>
#include<sstream>
#include<fstream>
#include<memory.h>
#include<ctime>
#define SIZE 800


using namespace std;


struct Node
{
	int ID;          //�O�W�r��
	int NEXTnumber;  //nextnode���ƶq
	int cost[SIZE];  //�Z��
	int x; //source
	int y; //destination
    struct Node *nextnode[SIZE];
};

void visit(Node **,Node *);
void visit2(Node **,Node *);
void combination(string, int, int);

int run[SIZE] = {0}; //�I�����X 0:�S���L 1:���L
int run2[SIZE][SIZE];//�������X 0:�S���L 1:���L
int run4[SIZE][SIZE];// 2:������ 2�H�~:����

int record[SIZE] = {0};
int recordIndex = 0;

int recordoutput[SIZE] = {0};
int recordoutputIndex = 0;
int output[SIZE][SIZE];


int cycle = 0;
int cycletime = 0;

int totalrun = 0;    // �O���Y�z�I�w���L
int totalcost = 0;   // �O�����X�����|����

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

    start = clock(); //�}�l�ɶ�
	
	stringstream ss (stringstream::in | stringstream::out);


//Ū��
	 fstream file;
	file.open("final.in");
	if(!file)
	{
		cout<<"�}�ɥ���!\n";
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

		int k=0;//�Ȯɪ�col		
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
			
			if(ss.fail())  //�p�G�����᧹�A�N���Xwhile
				break;
		}

		TEMProw++;
		
		ss.clear();
	
		}
		file.close();
//Ū�ɵ���
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


//�����[���
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


//�إ�point
	point = new struct Node *[row];  //�I���ӼƵ����}�j�p
	for(int i=0;i<row;i=i+1)
		point[i] = new struct Node;
	for(int i=0;i<row;i=i+1){
		point[i]->ID = i;
	}


//�إ�run3
	run3 = new struct Node *[SIZE];  //�I���ӼƵ����}�j�p
	for(int i=0;i<SIZE;i=i+1)
		run3[i] = new struct Node;
	for(int i=0;i<SIZE;i=i+1){
		run3[i]->ID = i;
	}


int roundtime = 0;
//�إߦU�I��nextnode
	int index;
	for(int i=0;i<row;i++)
	{
		
		index=0;
		point[i]->NEXTnumber=0;
		for(int j=0;j<col;j++)
		{
			point[i]->cost[index] = DistanceAry[i][j];
			if(i!=j && DistanceAry[i][j]>0) //�����﨤,���� -1
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
//�����[���
	for(int i=0;i<row;i++)
	{
		int time=point[i]->NEXTnumber;
		int k=0;
		for(int j=0;j<col;j++)
		{
		  if(time>0)
		  {
		  cout<<"point"<<i<<"��nextnode["<<k<<"] : ";
		  cout<<point[i]->nextnode[k]->ID<<" cost:"<<point[i]->cost[k]<<"\n";
		  }
		  time--;
		  k++;

		}
		cout<<"\n";
	}

//run2�Ҧ�������l�Ƭ�0
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			run2[i][j]=0;
		}
	}




//���F�p��cycle�ƪ����X:�}�l
	int visittime = 0;
//��ܥu���@����~�D����node��_�I�A�B���@�ӴN����j��
	for(int i=0;i<row;i++)
	{
		if(point[i]->NEXTnumber==1)
		{
	     visit(point,point[i]);
		 visittime++;
		 break;
		}
	}

//�p�G��n��~�u���@������node���s�b�A�qpoint0�}�l���X
	if(visittime==0)
		 visit(point,point[0]);
//���F�p��cycle�ƪ����X:����



//run1�Ҧ�������l�Ƭ�0
	for(int i=0;i<row;i++)
		run[i]=0;
	
//run2�Ҧ�������l�Ƭ�0
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



	cout<<"����!"<<endl;

	stop = clock(); //�����ɶ�

    cout <<"�@�@�ӶO "<< double(stop - start) / CLOCKS_PER_SEC<<" ��"<<endl;
	system("PAUSE");
}





void visit(Node **exp,Node *exp2){


	
	record[recordIndex] = exp2[0].ID;
	/*cout<<(char)(record[recordIndex]+65)<<" �� "<<" ";*/
	recordIndex++;
	

	if( run[exp2[0].ID]==0 )   //�p�G�S���L�N�i�Ө�
	{ 
        run[exp2[0].ID] = 1;   //���L�аO��1
		
		 //�w�w:push
		 

		 totalrun=0;
		 for(int i=0;i<row;i++)
			 totalrun = totalrun + run[i];

		

//�w�w:�@�����j����;�g��
		 if(totalrun == row) //���L�I���Ӽ�=�Ҧ��I
	    {

			for(int i=0;i<exp2[0].NEXTnumber;i++)
			 {
			     if( (run[exp2[0].nextnode[i]->ID]==1) && (run2[exp2[0].ID][exp2[0].nextnode[i]->ID]==0) && (cycletime == 0) )
				 {
					 /*cout<<"\ncycle!\n";*/

					 cycle++;
					 
				 }
			 }

				/*cout<<"���\!\n\n";*/			
				cycletime++;
				
				
				
			

			

//�w�w:�ӱ����j�g�ɵ���			  
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
		 //�w�w:pop();

		/*cout<<"\n�h�^"<<(char)(exp2[0].ID+65)<<"\n";*/
	
		
	



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


//output��l��
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

//�����������|�A�A�����X
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
//��ܥu���@����~�D����node��_�I�A�B���@�ӴN����j��
	for(int j=0;j<row;j++)
	{
		if(point[j]->NEXTnumber==1)
		{
	     visit2(point,point[j]);
		 visittime++;
		 break;
		}
	}

//�p�G��n��~�u���@������node���s�b�A�qpoint0�}�l���X
	if(visittime==0)
		 visit2(point,point[0]);

//�}�l�����e����l��
	//run1�Ҧ�������l�Ƭ�0
	for(int i=0;i<row;i++)
		run[i]=0;
	
    //run2�Ҧ�������l�Ƭ�0
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			run2[i][j]=0;
		}
	}

//���ਫ�����|��l��
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
//�}�l�����e����l�Ƶ���
cout<<"\n<next>\n";


return;
}
combination(x+" "+itoa(num[n-1],buffer,10),n-1,r-1);
combination(x,n-1,r);
}







void visit2(Node **exp,Node *exp2){





	cout<<(char)(exp2[0].ID+65)<<" �� "<<" ";

	

	if( run[exp2[0].ID]==0 )   //�p�G�S���L�N�i�Ө�
	{ 
        run[exp2[0].ID] = 1;   //���L�аO��1
		
		
		 
		 

		 totalrun=0;
		 for(int i=0;i<row;i++)
			 totalrun = totalrun + run[i];
		

		

//�@�����j����
		 if(totalrun == row) //���L�I���Ӽ�=�Ҧ��I
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

			    cout<<"���\!\n\n";

//�g�ɶ}�l
				char filename[]="final.out";
				fstream file2;
				file2.open((char*) filename, ios::out);      //�Hout�Ҧ��}���ɮסA�ǳƼg�J

        if(!file2)     //�ˬd�ɮ׬O�_���\�}��

        {

                cerr << "Can't open file!\n";

                exit(1);     //�b�����`���ΤU�A���_�{��������

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
//�ӱ����j�g�ɵ���



			   
			}
//��l��
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
		 cout<<"\n�h�^"<<(char)(exp2[0].ID+65)<<endl;


	}


}

