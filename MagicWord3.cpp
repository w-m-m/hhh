/*
	存储每个节点的value 
*/

#include<bits/stdc++.h>
using namespace std;

string file_out,file_in;
int N,K;
string str;
map<string,int> spell_value;
map<char,vector<string> > letter_spells;
vector<string> result;
int max_value=-1;
string bestway="";

struct node{
    string s;
    string cutway;
    int value;
    vector<node*> kid_nodes;
};

void readInput(string file_in){
	fstream f;
	f.open("Input.txt");
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
		spell_value[spell]=value;
        letter_spells[spell[0]].push_back(spell);	
        //cout<<spell<<" "<<value<<endl;
	}
}


node* spanTree(node *last){
	string s="",spell="",cut_s="";
	if(last->s == ""){
		//result.push_back(last->cutway);
		if(last->value>max_value){
			max_value = last->value;
			bestway = last->cutway;
		}
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
			            n->value = last->value + spell_value[spell];
			            last->kid_nodes.push_back(spanTree(n));
			            flag++;
			            //cout<<i<<" "<<cut_s<<" "<<n->cutway<<endl;
		            }   
                }
            }
        }
	    if(flag==0){
	    	//result.push_back(last->cutway);
	    	if(last->value>max_value){
				max_value = last->value;
				bestway = last->cutway;
			}
	    }
	}
	return last;
}

void getResult(){
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
	ofstream f("Output.txt");
	if(f.is_open()){
		for(int i=0;i<pos.size();i++){
			f<<pos[i]<<" "<<spell[i]<<endl;		
		}
		f<<max_value<<endl;
	}
	
}


int main(){
//	cin>>N>>K;
//	cin>>str;
//	string spell;
//	int value;
//	while(K--){
//		cin>>spell>>value;
//		spell_value[spell]=value;
//        letter_spells[spell[0]].push_back(spell);
//	}
	readInput("Input.txt");
    node *root=new node();
    root->s=str;
    root->cutway="";
    root->value=0;
    root=spanTree(root);
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
