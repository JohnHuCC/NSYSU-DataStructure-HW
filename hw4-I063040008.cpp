/*
Author: I063040008 �J���j
Date: Oct. 27,2018
Purpose:  ��v���M�h(knight) �����ѽL������ �A�ϥ�recursive 
*/ 
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

int **board; //�ŧi�ʺA�}�C���쳣�i�ϥ� 
int n=-1,steps; //�@�}�l�}�C�j�p�]��-1 

enum Setting{	//�ϥΦC�|�A�N���L�P�����L���I���аO 
	WalkedPoint,
	UnWalkedPoint
};

class Knight_Travel{  
	public:
		int Row,Col;
		Knight_Travel(){ //constructor�A��l�ư_�I 
			init();
		}
		
		Knight_Travel(int row,int col){ //constructor�A�ǤJ�_�I 
			Row=row;
			Col=col;
		}
		
		Knight_Travel Next_Direction(int DirNum){	//���o���U�@�B�᪺��m 
			if(DirNum<0||DirNum>=8){
				throw "Error Direction";
			}
			Knight_Travel newKnight(Row,Col);
			newKnight.Knight_Move(DirNum);
			return newKnight;
		}
	private:
		int	rowMove[8]={-2,-1,1,2,2,1,-1,-2}; //y�b�������첾 
		int colMove[8]={1,2,2,1,-1,-2,-2,-1}; //x�b��V���첾 
		void init(){	//��l�ư_�I 
			Row=0;
			Col=0;
		}
		
		void Knight_Move(int DirNum){	//��Ҧb��m������ 
			if(DirNum<0||DirNum>7){
				throw "Error Direction";
			}
			Row+=rowMove[DirNum];
			Col+=colMove[DirNum];
		}
};

void CreateBoard(){	//�Q�ΰʺA�}�C�إߴѽL 
		if(n<0)cout<<"Error size of board"<<endl;
		board=new int*[n];
		for(int i=0;i<n;i++){
			board[i]=new int[n];
		}
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				board[i][j]=0;
			}
		}
}

void DeleteBoard(){	//������R���ѽL 
	if(n<=0)cout<<"Error delete board"<<endl;
	for(int i=0;i<n;i++){
			delete []board[i];
	}
	delete []board;
}

bool If_Is_GoodStep(Knight_Travel knight){ //�P�_�U�@�B�O���O�i�H���A����W�X�ѽL�B��0 
	if(knight.Row>=n||knight.Col>=n||knight.Row<0||knight.Col<0)return false;
    else if(board[knight.Row][knight.Col]>0)return false;
    return true;
}

void SetBoard(Setting inputSetting,Knight_Travel knight,int steps){	//�i�H�����ܡA��ĴX�B�[�W 
	if(inputSetting==WalkedPoint&&If_Is_GoodStep(knight)){
		board[knight.Row][knight.Col]=steps;
	}else if(inputSetting==UnWalkedPoint){
		board[knight.Row][knight.Col]=0;
	}			
}

int GetNumOfNextStep(Knight_Travel knight){	//���o�Y�I�i�H�����U�@�B���ƶq 
	int NumOfNextStep=0;
	for(int i=0;i<8;i++){
		Knight_Travel newKnight=knight.Next_Direction(i);
        if(!If_Is_GoodStep(newKnight))continue;
        else NumOfNextStep++;
    }
   // cout<<NumOfNextStep<<endl;
    return NumOfNextStep;
}
void Print_Board(){	//�L�X���G 
	if(n<=0)cout<<"Error print board"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<board[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
}



void SetVisitOrder(int *data,Knight_Travel knight){	//J.C. Warnsdorff���t��k�A��X�U�@�B�����ƶq�A���ƶq�֪���V���A�F��[�t���ت� 
    int minNumber,minDir;
    bool IsBook[8];
    memset(IsBook,false,sizeof(IsBook));
    for(int i=0;i<8;i++){
        minNumber=-1;
        minDir=0;
        for(int j=0;j<8;j++){
            if((minNumber==-1||minNumber>GetNumOfNextStep(knight.Next_Direction(j)))&&!IsBook[j]){
                minNumber=GetNumOfNextStep(knight.Next_Direction(j));
                minDir=j;
            }
   		}
        data[i]=minDir;
        IsBook[minDir]=true;	
	}
}

void DFS(Knight_Travel knight){	//���j���X 
	if(!If_Is_GoodStep(knight))return;
	int visitOrder[8];
	SetVisitOrder(visitOrder,knight);
	SetBoard(WalkedPoint,knight,++steps); //�]�w�{�b��m�w�g���L 
	for(int i =0;i<8;i++){
		DFS(knight.Next_Direction(visitOrder[i])); //�`�J���X 
		if(steps==n*n)return; //���j�������� 
	}
	SetBoard(UnWalkedPoint,knight,steps--); //�]�w�{�b��m�|�����L 
}

int main(){	//main 
	Knight_Travel RealKnight;
	for(n=1;n<=6;n++){
		if(n==1){
			cout<<"n="<<n<<endl;
            cout<<n<<endl<<endl;
            continue;
        }
		CreateBoard();
		steps=0;
		RealKnight=Knight_Travel(0,0); //�_�I 
		DFS(RealKnight);
		if(steps==n*n){
			cout<<"n="<<n<<endl;
			Print_Board();
		}else{
			cout<<"n="<<n<<endl<<"\nNo Solution"<<endl<<endl;
		}
		DeleteBoard();
	}	
}
