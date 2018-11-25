/*
Author: I063040008 �J���j
Date: Nov. 9,2018
Purpose:  Linkedlist�B�z��h�����[�k�P���k 
*/ 
#include<iostream>
#include<cstdlib>
using namespace std;

struct Node	//Node �̭��i��Y�ƩM����,�٦��e����� 
{
	float Coefficient;
	int Exponent;
	struct Node *Next=NULL;
	struct Node *Prev=NULL;
};

class Polynomial{
	public:
		Polynomial(); //initialize 
		bool IsEmpty();	//�ˬd�O�_���� 
		void Add(float c,int e);	//�[�k	
		void Add(Node *inputNode);	// �[�k�h�� 
	 	static Polynomial Add(Polynomial inputA,Polynomial inputB);	//�[�k��@operator overloading; 
		void Multiply(float c,int e);	//���k 
		void Multiply(Node *inputNode);	//���k�h�� 
		static Polynomial Multiply(Polynomial inputA,Polynomial inputB);	//���k��@operator overloading; 
		void RemoveByCoefficient(float c);	//�����S�w�Y�ƪ�node 
		void RemoveByExponent(int e);	//�����S�w���ƪ�node 
		Node *SearchNodeByExponent(int Exp);	//�M��ۦP���ƪ�node 
		void Insert(Node *newNode);	//���Jnode 
		void Remove(Node *newNode);	//�����Y�� 
		Polynomial CopyPolynomial();	//�ƻs��Ӧh�������B�� 
		friend Polynomial operator+(Polynomial inputA,Polynomial inputB){ //operator overloaing 
			return Polynomial::Add(inputA,inputB);
		}
		friend Polynomial operator*(Polynomial inputA,Polynomial inputB){ //operator overloaing
			return Polynomial::Multiply(inputA,inputB);
		}
		void show(); //�L�X 
	private:
		Node *head;
		Node *tail;	
};

Polynomial::Polynomial(){  
	head=NULL;
	tail=NULL;
}

bool Polynomial::IsEmpty(){
	return head==NULL;
}

void Polynomial::Add(float c,int e){ //�Y��c����e 
	Node *newNode=new Node;				//�إ߷s���I 
	newNode->Coefficient=c;
	newNode->Exponent=e;	
	Node *NodeToBeSearched=SearchNodeByExponent(e); //�M�䦹�����ƬO�_�s�b�A�s�b�����[ 
	if(IsEmpty()||NodeToBeSearched==NULL){
		Insert(newNode);
	}else{
		NodeToBeSearched->Coefficient+=c;
		delete newNode;
	}
}

void Polynomial::Multiply(float c,int e){	//�h�������W�Y��c����e���涵�� 
	Node *newNode=head;
	while(newNode!=NULL){
		newNode->Coefficient*=c;
		newNode->Exponent+=e;
		newNode=newNode->Next;
	}
}

void Polynomial::Add(Node *inputNode){	//�h�� 
	Add(inputNode->Coefficient,inputNode->Exponent);
}

void Polynomial::Multiply(Node *inputNode){	//�h�� 
	Multiply(inputNode->Coefficient,inputNode->Exponent);
}

Polynomial Polynomial::Add(Polynomial inputA,Polynomial inputB){ //operator overloading��@ 
	Polynomial ans=inputA.CopyPolynomial();
	Node *newNodeB=inputB.head;
	while(newNodeB!=NULL){
		ans.Add(newNodeB);
		newNodeB=newNodeB->Next;
	}
	return ans;
}


Polynomial Polynomial::Multiply(Polynomial inputA,Polynomial inputB){ //operator overloading��@  
	Polynomial flag;
	Polynomial ans;
	Node *newNodeB=inputB.head;
	while(newNodeB!=NULL){
		flag=inputA.CopyPolynomial();
		flag.Multiply(newNodeB);
		ans=Polynomial::Add(ans,flag);
		newNodeB=newNodeB->Next;
	}
	return ans;
}

void Polynomial::RemoveByCoefficient(float c){
	Node *newNode=head;
	while(newNode!=NULL){
		if(newNode->Coefficient==c){
			Remove(newNode);
			RemoveByCoefficient(c);
			return;
		}
			newNode=newNode->Next;
	}
}

void Polynomial::RemoveByExponent(int e){ //��������e���� 
	Node *newNode=head;
	while(newNode!=NULL){
		if(newNode->Exponent==e){
			Remove(newNode);
			RemoveByExponent(e);
			return;
		}
		newNode=newNode->Next;
	}
}

Polynomial Polynomial::CopyPolynomial(){ //copy��Ӧh���� 
	Polynomial newPolynomial;
	Node *newNode=head;
	while(newNode!=NULL){
		newPolynomial.Add(newNode);
		newNode=newNode->Next;
	}
	return newPolynomial;
}
Node* Polynomial::SearchNodeByExponent(int Exp){	//�M��o�ӫ��Ʀh�����s���s�b 
	Node *newNode=head;
	while(newNode!=NULL){
		if(newNode->Exponent==Exp){
			return newNode;
		}
		newNode=newNode->Next;
	}
	return NULL;
}

void Polynomial::Insert(Node *newNode){ //���J�h�����åB�Ƨ� 
	if(IsEmpty()){							
		head=newNode;
		tail=newNode;
		return;
	}
	Node *NodeToBeCompared=head;
	while(NodeToBeCompared!=NULL){ //�������J����Ĥ@���j�B�������A���J����̫�@���p�T�ر��p 
		if(NodeToBeCompared->Prev==NULL&&newNode->Exponent>NodeToBeCompared->Exponent){
			newNode->Next=head;
			head->Prev=newNode;
			head=newNode;
			return;
		}else if(NodeToBeCompared->Exponent>newNode->Exponent&&NodeToBeCompared->Next!=NULL&&newNode->Exponent>NodeToBeCompared->Next->Exponent){
					newNode->Next=NodeToBeCompared->Next;
					newNode->Prev=NodeToBeCompared;
					NodeToBeCompared->Next->Prev=newNode;
					NodeToBeCompared->Next=newNode;
					return;
		}else if(NodeToBeCompared->Next==NULL){
			newNode->Prev=tail;
			tail->Next=newNode;
			tail=newNode;
			return;
		}
		NodeToBeCompared=NodeToBeCompared->Next;
	}
	return;
}

void Polynomial::Remove(Node *newNode){ //�����Y�� 
	if(newNode->Prev==NULL&&newNode->Next==NULL){ //�u���@���B���Ĥ@�� �B�������B�̫�@���A�|�ر��p���O�B�z 
		head=NULL;
		tail=NULL;
	}else if(newNode->Prev==NULL){
		head=newNode->Next;
		newNode->Next->Prev=NULL;
	}else if(newNode->Next==NULL){
		tail=newNode->Prev;
		newNode->Prev->Next=NULL;  
	}else{
		newNode->Prev->Next=newNode->Next;
		newNode->Next->Prev=newNode->Prev;
	}
	delete newNode;
}

void Polynomial::show(){ //�L�X���G 
	if(IsEmpty()){
		cout<<"0*X^0";
		return;
	}
	Node *newNode=head;
	bool IsFirst=true;
	while(newNode!=NULL){
		if(!IsFirst){
			if(newNode->Coefficient>=0)cout<<"+";
		}
		cout<<newNode->Coefficient<<"X^"<<newNode->Exponent;
		IsFirst=false;
		newNode=newNode->Next;
	}
	return;
}

int main(){
	int NumA,NumB;
	Polynomial PolyA,PolyB;
	float coefficient;
	int exponent;
	int counter=0;
	while(1){ //��J���0���X 
		counter++;
		PolyA=Polynomial();
		PolyB=Polynomial();
		cin>>NumA;	//�Ĥ@�Ӧh�������� 
		if(NumA>0){
			while(NumA--){
				cin>>coefficient>>exponent;
				PolyA.Add(coefficient,exponent);
			}
		}
		cin>>NumB; //�ĤG�Ӧh��������  
		if(NumA==0&&NumB==0){
			break;
		}else if(NumB>0){
			while(NumB--){
				cin>>coefficient>>exponent;
				PolyB.Add(coefficient,exponent);
			}
		}
		cout<<"Case"<<counter<<":"<<endl;
		PolyA.RemoveByCoefficient(0); //�M���Y�Ƭ�0���� 
		PolyB.RemoveByCoefficient(0);	//�M���Y�Ƭ�0���� 
		Polynomial AnsOfAdd=(PolyA+PolyB);
		AnsOfAdd.RemoveByCoefficient(0); //�M���Y�Ƭ�0����  
		cout<<"ADD Result: ";
		AnsOfAdd.show();
		cout<<endl;
		Polynomial AnsOfMultiply=(PolyA*PolyB);
		AnsOfMultiply.RemoveByCoefficient(0); //�M���Y�Ƭ�0����  
		cout<<"MULTIPLY Result: ";
		AnsOfMultiply.show();
		cout<<endl;
	}
	return 0;
}
