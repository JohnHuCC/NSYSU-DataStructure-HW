/*
Author: I063040008 �J���j
Date: Oct. 27,2018
Purpose:  ��v���M�h(knight) �����ѽL������ 
*/ 
#include<iostream>
using namespace std;

typedef struct Knight{ 	//�Q��struct�N��class�N�n�s�Jstack����ƥ]�b�@�_ 
	int row,col,d,steps;
}KNIGHT;

template<class T>
class StackArray{	 //�Q�ΰ}�C��@stack 
	public:
		StackArray(int stackCapacity=10); //constructor 
		void Push(const KNIGHT& x); //push
		KNIGHT Pop(); //pop
		bool IsEmpty() const; //�ˬdstack�O�_���� 
		KNIGHT Top() const; //�^��stack�̳��ݸ�� 
		int getSize(); //�^��stack����ƶq 
	private:
		int capacity; //stack���j�p 
		int top; //���stack�̳��� 
		KNIGHT *stack; //�ʺA�}�C�קKoverflow 
}; 


template<class T>
StackArray<T>::StackArray(int stackCapacity):capacity(stackCapacity) //constructor�A��l��stack 
{
	top=-1;
	stack=new KNIGHT[capacity];
}

template<class T>
inline bool StackArray<T>::IsEmpty() const //�p�G���ݨS���Ȧ^��false 
{
	return top==-1;
}

template<class T>
inline KNIGHT StackArray<T>::Top() const{ //�^��stack�̳��ݸ�� 
	if(IsEmpty()) cout<<"Stack is empty"<<endl;
	return stack[top];
}

template<class T>
void StackArray<T>::Push(const KNIGHT& x){ //push
	if(top==capacity-1){
		cout<<"Stack Overflows"<<endl;
	}
	++top;
	stack[top]=x;
}

template<class T>
KNIGHT StackArray<T>::Pop(){ //pop
	if(IsEmpty()){
		cout<<"Stack is empty. Cannot delete."<<endl;
	}else{
		return(stack[top--]); //�]���^�ҭn�Ψ�e�@����ƩҥH����ϥ�destructor 
		//stack[top--].~KNIGHT();
	}
}

template<class T>
int StackArray<T>::getSize(){  //�^�Ǥj�p 
	return top+1;
}

int If_In_board(int x,int y,int N){ //�P�_�O�_�U�@�B�b�ѽL�� 
	if(x>=0&&x<N&&y>=0&&y<N)
		return 1;
	else
		return 0;
}  

void Print_board(int **board,int d,int steps,int n){ //�L�X���G 
	if(d!=8&&steps!=1)
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					cout<<board[i][j]<<"\t";
				}
			cout<<endl;
			}
		cout<<endl;
}

int KnightTravel(int row,int col){ //�M�h�M�� 
	StackArray<int> s(100); //stack�j�p�w�]100 
	int colMove[]={1,2,2,1,-1,-2,-2,-1}; //x�b��V���첾 
	int	rowMove[]={-2,-1,1,2,2,1,-1,-2}; //y�b�������첾 
	
	for(int n=1;n<=6;n++){  
		if(n==1){ //n=1 �L�X1 
			cout<<"n="<<n<<endl;
			cout<<n<<endl<<endl;
			continue;	
		}
		row=0;col=0;
		cout<<"n="<<n<<endl;
		int **board=new int*[n];
		for(int i=0;i<n;i++){
			board[i]=new int[n]; //��l�ưʺA�}�C 
		}
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				board[i][j]=0; //�ѽL�k�s 
			}
		}
		int steps=1,d=0,nRow,nCol;
		Knight k1;
		board[row][col]=steps; //�X�o���a��]���Ĥ@�B 
		while(steps<n*n){	//start
			for(;d<8;d++){	//����8�Ӥ�V 
				nCol=col+colMove[d];
				nRow=row+rowMove[d];
				if(If_In_board(nRow,nCol,n)&&board[nRow][nCol]==0){ //�P�_8�Ӥ�V�A�i�H���N�N�Ҧb��m�H�Τ�V�٦��ĴX�B����Ƥ@�_���Jstack 
					k1.row=row;
					k1.col=col;
					k1.d=d;
					k1.steps=steps;
					s.Push(k1);
					board[nRow][nCol]=++steps;
					
					d=0; //��V�k�s 
					row=nRow; //�Ҧb��m�e�i 
					col=nCol;
					break;  
				}
			}
			if(d==8){ //��K�Ӥ�V������A�� 
				if(steps==1){
					cout<<"no solution!"<<endl<<endl; //�h�줣��A�h�N�L�� 
					break;
				}
				board[row][col]=0; //�Ҧb��m�k�s 
				k1=s.Pop(); //���X��� 
				row=k1.row; //�h�^��� 
				col=k1.col;
				d=k1.d;
				steps=k1.steps;
				d++; //����L��V 
			}
		
		}
		Print_board(board,d,steps,n); //�L�X 
	}
	cout<<endl;
}

int main(){ //main 
	KnightTravel(0,0);  
}

