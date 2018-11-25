/*
Author: I063040008 �J���j
Date: Oct. 13,2018
Purpose: �سyc++�����X���O 
*/ 
#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
class set{
	public:
		set(); //default constructor 
		set(char *str); //constructor �ΨӱN����ǤJ���}�C���ƧǻP�������Ʀr���A�ñN��Ʀs��binaryv���A 
		void selectionsort(char *a); //sort 
		void swap(char *a,char *b); 
		int RemoveDuplicateChar(char *ArrayToSave,char *str); //�������Ʀr�� 
		friend const set operator +(const set& A,const set& B); //�p�� 
		friend const set operator *(const set& A,const set& B); //�涰 
		friend const set operator -(const set& A,const set& B);	//�t�� 
		friend const bool operator >=(const set& A,const set& B); //�]�t 
		friend ostream& operator <<(ostream& outputStream,const set& s); //output operator 
	    bool in(char input,char *str); //�ݩ� 
	private:
		char C[256];
		bool D[256];
};
int main(){
	int Input_times;
	cin>>Input_times;
	for(int i=0;i<Input_times;i++){
		char strA[1000],strB[1000],word=' ';
		cin.ignore();
		gets(strA); //Ū�J�r��]�t�ť� 
		gets(strB);
		cin.get(word); //Ū�J�r���]�t�ť� 
		cout<<"Test Case "<<i+1<<":"<<endl;
		cout<<"A: ";
		set s1(strA);
		cout<<"B: ";
		set s2(strB);
		cout<<"A+B: {"<<s1+s2<<"}"<<endl;
		cout<<"A*B: {"<<s1*s2<<"}"<<endl;
		cout<<"A-B: {"<<s1-s2<<"}"<<endl;
		cout<<"B-A: {"<<s2-s1<<"}"<<endl;
		if(s1>=s2)
			cout<<"A contain B"<<endl;
		else
			cout<<"A does not contain B"<<endl;
		if(s2>=s1)
			cout<<"B contain A"<<endl;
		else
			cout<<"B does not contain A"<<endl;
		if(s1.in(word,strA))
			cout<<"'"<<word<<"' is in A"<<endl;
		else
			cout<<"'"<<word<<"' is not in A"<<endl;	
		if(s1.in(word,strB))
			cout<<"'"<<word<<"' is in B"<<endl;
		else
			cout<<"'"<<word<<"' is not in B"<<endl;		
		cout<<endl;
	}
}

const set operator +(const set& A,const set& B){
	set save;
	for(int i=0;i<256;i++){
		save.D[i]=A.D[i]||B.D[i]; //�p��,binary��ư�OR�B�� 
	}
	return save;
}


const set operator *(const set& A,const set& B){
	set save;
	for(int i=0;i<256;i++){
		save.D[i]=A.D[i]&&B.D[i]; //�涰,binary��ư�AND�B��  
	}
	return save;
}

const set operator -(const set& A,const set& B){
	set save;
	for(int i=0;i<256;i++){
		save.D[i]=A.D[i]&&!B.D[i];  //�t��,binary��ư�AND�B��,�䤤�@��set�Ϭ�  
	}
	return save;
}

const bool operator >=(const set& A,const set& B){
	for(int i=0;i<256;i++){
		if(!A.D[i]&&B.D[i]){ //�]�t,�䤤�@����ƨS���b�t�@�����^��false  
			return false;
		}
	}
	return true;
}

bool set::in(char input,char *str){ //�ݩ�,�N��J���r����}�C�����r�����A���N�^��true 
	for(int i=0;i<256;i++){
		C[i]=0;		
	}
	RemoveDuplicateChar(C,str);
	selectionsort(C);
	int n=strlen(C);
	for(int i=0;i<n;i++){
		if(input==C[i])
		return true;
	}
	return false;
}
ostream& operator <<(ostream& outputStream,const set& s){ //��X�B��l�A�Nbool�}�C����1����ƿ�X���r�� 
	for(int i=0;i<256;i++){
		if(s.D[i]==1)
			outputStream<<(char)i;
	}
	return outputStream;
}
set::set(){ //default constructor
} 
set::set(char *str){ //constructor �N��J���}�C�h�ۦP�r���ñƧ��x�s��binary���A 
	for(int i=0;i<256;i++){  
		C[i]=0;		
	}
	RemoveDuplicateChar(C,str);
	selectionsort(C);
	int n=strlen(C);
	cout<<"{";
	for(int i=0;i<n;i++){
		cout<<C[i];
	}
	cout<<"}"<<endl;
	for(int i=0;i<256;i++){
		D[i]=0;		
	}
	for(int i=0;i<n;i++){
		D[C[i]]=1;
	}
}

int set::RemoveDuplicateChar(char *ArrayToSave,char *str){
	int index=0,n=strlen(str);
	ArrayToSave[index]=str[0];
	int j;
	for(int i=1;i<n;i++){
		for(j=0;j<n;j++){
			if(ArrayToSave[j]==str[i])
			break;
		}
		if(j==n){
			index++;
			ArrayToSave[index]=str[i];
		}
	}
	return index+1;
}

void set::selectionsort(char *a){
	int n=strlen(a); 
	for(int i=0;i<n;i++){
		int j=i;
		for(int k=i+1;k<n;k++){
			if(a[k]<a[j]) j=k;
		}
		swap(&a[i],&a[j]);
	}
}

void set::swap(char *a,char *b){ //swap�A�n�Q�ζǧ}�}�C���e�~�|�u���洫 
	char temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
