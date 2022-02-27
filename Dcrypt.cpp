#define SEG_N (2000001)
//#define DBG
#include<iostream>
#include<fstream>
#include<vector>
using namespace std; 
typedef pair<int,int> ii;


int seg[SEG_N];
static int segSz=0;

#ifdef DBG
void print(vector<ii>& sracmblr){
	int sz=sracmblr.size();
	for(int i=0;i<sz;i++)
		cout<<sracmblr[i].first<<" "<<sracmblr[i].second<<endl;
	cout<<"---------\n\n";
}
#endif
inline bool mutateChar(int ch_){
	char ch=(char)ch_;
	if(ch==' ' || ch=='\n' || ch==0)return false;
	return true;
}
int main(){
	FILE* in=fopen("temp.ENCRYPT","r");
	ifstream sMap("MAP.txt",ios::in);
	FILE* op=fopen("res.txt","w");
	if(!in){
		cout<<"Error Opening File!!\n";
		return 1;
	}
	string key,word;
	cout<<"Enter key:\t";cin>>key;
	int m=key.length(),j,segNo=0;
	char ch;

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
	ofstream dbg_("res_Uread.txt",ios::out);
	dbg_.write((char*)seg,sizeof(seg));
	dbg_.close();
#endif
//UNDO SCRAMBLING
	vector<ii> sracmblr;
	int p1=0,p2=0,iter=0;
	do{
		sMap>>word;
		if(word[iter]=='<'){
			iter++;
			while(word[iter]!=',')p1=p1*10+(int)(word[iter++]-'0');
			iter++;
			while(word[iter]!='>')p2=p2*10+(int)(word[iter++]-'0');
			sracmblr.push_back(ii(p1,p2));
			iter=0;p1=0;p2=0;
		}
	}while(word!="END");
#ifdef DBG
	print(sracmblr);
#endif
	int sracmblr_sz=sracmblr.size();
	for(int i=sracmblr_sz-1;i>=0;i--)
		swap(seg[sracmblr[i].first],seg[sracmblr[i].second]);
	sMap.close();
#ifdef DBG
	for(int i=0;i<segSz;i++)
		cout<<seg[i];
	cout<<"\n--------\n";
	ofstream dbg_1("res_Uscram.txt",ios::out);
	dbg_1.write((char*)seg,sizeof(seg));
	dbg_1.close();
#endif
//UNDO ADD.
	for(int i=0;i<segSz;i++){
		if(mutateChar(seg[i])){
			seg[i]=seg[i]-(int)key[i % m];
		}
		fprintf(op,"%c",seg[i]);
	}
	fclose(op);
#ifdef DBG
	for(int i=0;i<segSz;i++)
		cout<<seg[i];
	cout<<"\n--------\n";
	ofstream dbg_2("res_Uadd.txt",ios::out);
	dbg_2.write((char*)seg,sizeof(seg));
	dbg_2.close();
#endif
/********************* EACH SEGMENT ************************/
	cout<<"Check res.txt >>>\nClick to continue...";
	getchar();
	return 0;
}