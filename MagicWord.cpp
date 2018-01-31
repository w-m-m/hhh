/*
	����s����s��ÿ����ĸ�����ʴ� 
*/


#include<bits/stdc++.h>
using namespace std;

string file_out,file_in;
int N,K;
string str;
map<string,int> spell_value;
map<char,vector<string> > letter_spells;
vector<string> result;

struct node{
    string s;
    string cutway;
    vector<node*> kid_nodes;
};

void readInput(string file_in){

}

void writeOutput(string file_out){

}

node* spanTree(node *last){
	string s="",spell="",cut_s="";
	if(last->s == ""){
		result.push_back(last->cutway);
	}
	else{
		int flag=0;
        s=last->s;
	    for(int i=0;i<s.size();i++){
            for(int j=0;j<letter_spells[s[i]].size();j++){
                spell=letter_spells[s[i]][j];
                if((s.size()-i >= spell.size()) && s.substr(i,spell.size()) == spell){
                    cut_s = s.erase(i,spell.size());
		            s=last->s;
		            int temp=0;
		            for(int j=0;j<last->kid_nodes.size();j++){
		            	if(last->kid_nodes[j]->s == cut_s){
		            		temp++;
		            		break;
		            	}
		            }
		            if(temp==0){
			            node * n = new node();
			            n->s = cut_s;
			            string pos;
						stringstream ss;
			            ss<<i;
			            ss>>pos;
			            n-> cutway = last->cutway +pos+ "," + spell + ",";
			            last->kid_nodes.push_back(spanTree(n));
			            flag++;
			            //cout<<i<<" "<<cut_s<<" "<<n->cutway<<endl;
		            }   
                }
            }
        }
	    if(flag==0){
	    	result.push_back(last->cutway);
	    }
	}
	return last;
}

void getResult(){
	vector<string> pos_best;
	vector<string> spell_best;
	int max_value=-1;
	for(int i=0;i<result.size();i++){
		int temp=0,value=0;
		vector<string> pos;
		vector<string> spell;
		int j=1;
		while(j<result[i].size()-1){
			if(result[i][j] == ','){
				//cout<<"test  "<<result[i].substr(temp,j-temp)<<" ";
				pos.push_back(result[i].substr(temp,j-temp));
				temp=j+1;
				for(int k=j+1;k<result[i].size();k++){
					if(result[i][k]==','){
						//cout<<result[i].substr(temp,k-temp)<<endl;
						spell.push_back(result[i].substr(temp,k-temp));
						value+=spell_value[result[i].substr(temp,k-temp)];
						temp=k+1;
						j=temp+1; 
						break;
					}
				}
			}
			else	j++;
		}
		if(value>max_value){
			max_value=value;
			pos_best = pos;
			spell_best = spell;
		}
	}
	for(int i=0;i<pos_best.size();i++){
		cout<<pos_best[i]<<" "<<spell_best[i]<<endl;		
	}
	cout<<max_value<<endl;
}


int main(){
	cin>>N>>K;
	cin>>str;
	string spell;
	int value;
	while(K--){
		cin>>spell>>value;
		spell_value[spell]=value;
        letter_spells[spell[0]].push_back(spell);
	}

    node *root=new node();
    root->s=str;
    root->cutway="";
    root=spanTree(root);
//	for(int i=0;i<result.size();i++){
//		cout<<result[i]<<endl;
//	}
    getResult();
}


/*
6 4
AABBAA
AA 1
BB 1
AB 3
AAAA 4

2 1 
AA
AA 2

6 3
AABBAA
BB 1
AA 1
AAAA 4

*/
