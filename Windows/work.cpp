#include<bits/stdc++.h>
using namespace std;
ifstream fin;
ofstream fout;
string s[10005];
int k;
struct submission{
	string filename,owner,task,id;
};
int n;//题目数 
string taskname[20];//题目编号 
struct player{
	string name;
	submission sub[20];
};
int m;//记录数 
submission d[5005];//记录 
player p[3005];//选手信息 
int g;//选手数 
bool ok(string s){
	int cnt=0;
	for(int i=0;i<s.size();i++) if(s[i]=='_') cnt++;
	return cnt==2;
}
void copy_file(string s1,string s2){
	cerr<<s1.c_str()<<' '<<s2.c_str()<<' ';
//	s2="1\\1.cpp";
	freopen(s1.c_str(),"r",stdin);
	freopen(s2.c_str(),"w",stdout);
	char c;
	int cnt=0;
	while((c=getchar())!=-1){
		cnt++;
		putchar(c);
	}
	cerr<<cnt<<"B\n";
}
signed main(){
	freopen("input.txt","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>taskname[i];
	system("getall.exe");
	fin.open("ls.txt");
	while(fin>>s[++k]); k--;
	fin.close();
	for(int i=1;i<=k;i++){
		if(ok(s[i])){
			m++;
			int u=s[i].find("_");
			int v=(s[i].substr(u+1,200)).find("_")+u+1;
			int w=s[i].find(".");
			d[m].filename=s[i];
			d[m].owner=s[i].substr(0,u);
			d[m].task=s[i].substr(u+1,v-u-1);
			d[m].id=s[i].substr(v+1,w-v-1);
		}
	}
	cerr<<"1st done.\n";
	for(int i=1;i<=m;i++){
		int id=g+1;
		for(int j=1;j<=g;j++){
			if(p[j].name==d[i].owner) id=j;
		}
		if(id==g+1){
			g++;
			p[id].name=d[i].owner;
		}
		int tid=-1;
		for(int j=1;j<=n;j++) if(taskname[j]==d[i].task) tid=j;
		assert(tid!=-1);
		if(p[id].sub[tid].filename==""||p[id].sub[tid].id<d[i].id){
			p[id].sub[tid]=d[i];
		}
	}
	cerr<<"2nd done.\n";
	for(int i=1;i<=g;i++){
		for(int j=1;j<=n;j++){
			if(p[i].sub[j].filename!=""){
				system(("mkdir source\\"+p[i].name+"\\"+p[i].sub[j].task).c_str());
				copy_file(p[i].sub[j].filename,"source\\"+p[i].name+"\\"+p[i].sub[j].task+"\\"+p[i].sub[j].task+".cpp");
			}
		}
		cerr<<"3rd:"<<i<<"/"<<g<<" done.\n";
	}
	cerr<<"3rd done.\n";
	return 0;
}

