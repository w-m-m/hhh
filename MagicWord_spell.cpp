#include<bits/stdc++.h>
using namespace std;

string file_out,file_in;
int N,K;
string str;
map<string,int> spell_map;
map<string,int> word_maxvalue; //map[word] = max_value,字符串word对应的得到word时的最大value  
int max_value=-1;
string bestway="";

struct node{
    string s;
    string cutway;
    int value;
    vector<node*> kid_nodes;
};

void readInput(char*file_in){
	fstream f;
	f.open(file_in);
	char ch[50];
	f.getline(ch,50);
	string s = ch;
	istringstream stream(s);
	stream>>N;
	stream>>K;
	//cout<<N<<" "<<K<<endl;
	f.getline(ch,50);
	str=ch;
	//cout<<str<<endl;
	string spell;
	int value;
	while(K--){
		f.getline(ch,50);
		s = ch;
		istringstream stream(s);
		stream>>spell;
		stream>>value;
		spell_map[spell]=value;
	}
}


node* spanTree(node *last){
	string s="",spell="",cut_s="";
	if(last->s == ""){
		if(last->value>max_value){
			max_value = last->value;
			bestway = last->cutway;
		}
	}
	else{
		int flag=0;
	    map<string,int>::iterator it;
	    it = spell_map.begin();
	    while(it != spell_map.end()){
	    	spell = it->first;
			s=last->s;
			//cout<<s<<" "<<spell<<endl;
	        for(int i=0;i<s.size();i++){
		        if((s.size()-i >= spell.size()) && s.substr(i,spell.size()) == spell){
		            cut_s = s.erase(i,spell.size());
		            s=last->s;
		            int value = last->value + spell_map[spell];
		            int temp=0;
		            /*若该切割结果字符串之前有出现过且之前达到该字符串时的值大于等于当前值，则当前子串不再加入结点*/ 
		            if(word_maxvalue.find(cut_s)!=word_maxvalue.end() && (value <= word_maxvalue[cut_s]))
		            	temp++;
		            else	
						word_maxvalue[cut_s] = value;
		            if(temp==0){
			            node * n = new node();
			            n->s = cut_s;
			            string pos;
						stringstream ss;
			            ss<<i;
			            ss>>pos;
			            n->value = value;
			            n-> cutway = last->cutway +pos+ "," + spell + ",";
			            last->kid_nodes.push_back(spanTree(n));
			            flag++;
		            }   
		   	 	}
	    	}
	    	it++;
	    }
	    if(flag==0){
		    if(last->value>max_value){
				max_value = last->value;
				bestway = last->cutway;
			}
	    }
	}
	return last;
}

void getResult(char*file_out){
	vector<string> pos;
	vector<string> spell;
	int j=1,temp=0;
	while(j<bestway.size()-1){
		if(bestway[j] == ','){
			//cout<<"test  "<<bestway.substr(temp,j-temp)<<" ";
			pos.push_back(bestway.substr(temp,j-temp));
			temp=j+1;
			for(int k=j+1;k<bestway.size();k++){
				if(bestway[k]==','){
					//cout<<bestway.substr(temp,k-temp)<<endl;
					spell.push_back(bestway.substr(temp,k-temp));
					temp=k+1;
					j=temp+1; 
					break;
				}
			}
		}
		else	j++;
	}
	ofstream f(file_out);
	if(f.is_open()){
		for(int i=0;i<pos.size();i++){
			f<<pos[i]<<" "<<spell[i]<<endl;		
		}
		f<<max_value<<endl;
	}
	
}

int main(int argc,char*argv[]){
	readInput(argv[1]);
    node *root=new node();
    root->s=str;
    root->cutway="";
    root->value=0;
    root=spanTree(root);
    getResult(argv[2]);
}

/*
6 4
AABBAA
AA 1
BB 1
AB 3
AAAA 4
*/
