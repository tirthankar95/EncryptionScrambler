#define SEG_N (2000001)
//#define DBG
#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;

int seg[SEG_N];
static int segSz=0;

inline bool mutateChar(int ch_){
	char ch=(char)ch_;
	if(ch==' ' || ch=='\n' || ch==0)return false;
	return true;
}

//Driver Function.
int main(){
	srand(time(0));
	FILE* in=fopen("ip.txt","r");
	ofstream sMap("MAP.txt",ios::out);
	FILE* op=fopen("temp.ENCRYPT","w");
	if(!in){
		cout<<"Error Opening File!!\n";
		return 1;
	}
	string key;
	cout<<"Enter key:\t";cin>>key;
	int m=key.length(),j;
	int segNo=0;
/********************* EACH SEGMENT ************************/
//READ.
	while(!feof(in)){
		fscanf(in,"%c",&seg[segSz++]);
	}
	fclose(in);
#ifdef DBG
	for(int i=0;i<segSz;i++)
		cout<<seg[i];
	cout<<"\n--------\n";
	ofstream dbg_("a_res_read.txt",ios::out);
	dbg_.write((char*)seg,sizeof(seg));
	dbg_.close();
#endif
//ADD
	for(int i=0;i<segSz;i++){
		if(mutateChar(seg[i]))
			seg[i]=(int)seg[i]+(int)key[i % m];
	}
#ifdef DBG
	for(int i=0;i<segSz;i++)
		cout<<seg[i];
	cout<<"\n--------\n";
	ofstream dbg_1("a_res_add.txt",ios::out);
	dbg_1.write((char*)seg,sizeof(seg));
	dbg_1.close();
#endif
//SCRAMBLE
	sMap<<"Seg "<<segNo<<": ";segNo++;
	for(int i=0;i<segSz;i++){
		j=rand()%(i+1);
		sMap<<"<"<<i<<","<<j<<"> ";
		swap(seg[i],seg[j]);
	}
	sMap<<"END\n";	
	sMap.close();
#ifdef DBG
	for(int i=0;i<segSz;i++)
		cout<<seg[i];
	cout<<"\n--------\n";
	ofstream dbg_2("a_res_scram.txt",ios::out);
	dbg_2.write((char*)seg,sizeof(seg));
	dbg_2.close();
#endif
//WRITE
	for(int i=0;i<segSz;i++)
		fprintf(op,"%c",seg[i]);
	fclose(op);
/********************* EACH SEGMENT ************************/
	return 0;
}