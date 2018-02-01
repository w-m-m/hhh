#include<bits/stdc++.h>
using namespace std;

int N,K;
string str; //输入
map<string,int> spell_value;  //map[spell]=value 
map<char,vector<string> > letter_spells; //map[letter]=spells，首字母为letter的spells 
map<string,int> word_maxvalue; //map[word] = max_value,字符串word对应的得到word时的最大value  
int max_value=-1; //标记最大的value 
string bestway=""; //标记最大的value对应的切割过程 

struct node{
    string s;	 //结点对应的字符串 
    string cutway; 	//对应得到当前字符串的切割方法 
    int value;	 //当前累积的value 
    vector<node*> kid_nodes; 	//该结点字符串切割后的可能结果 
};

void readInput(char*file_in){ //读输入文件 
	fstream f;
	f.open(file_in);
	char ch[50];
	f.getline(ch,50);
	string s = ch;
	istringstream stream(s);
	stream>>N;
	stream>>K;
	f.getline(ch,50);
	str=ch;
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
	}
}

node* spanTree(node *last){
	string s="",spell="",cut_s="";
	if(last->s == "" && last->value>max_value){ //字符串切割完
		max_value = last->value;
		bestway = last->cutway;
	} 
	else{
		int flag=0;
        s=last->s;
	    for(int i=0;i<s.size();i++){ //遍历字符串 
            for(int j=0;j<letter_spells[s[i]].size();j++){ //遍历首字母的词袋 
                spell=letter_spells[s[i]][j];
                if((s.size()-i >= spell.size()) && s.substr(i,spell.size()) == spell){ //匹配可切割 
                    cut_s = s.erase(i,spell.size());
		            s=last->s;
		            int value = last->value + spell_value[spell];
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
			            n-> cutway = last->cutway +pos+ "," + spell + ",";
			            n-> value = value;
			            last->kid_nodes.push_back(spanTree(n));
			            flag++;
		            }   
                }
            }
        }
	    if(flag==0 && last->value>max_value){ //当前字符串无法再切割 
	    	max_value = last->value;
			bestway = last->cutway;
	    }
	}
	return last;
}

void getResult(char*file_out){ //根据bestway输出结果 
	vector<string> pos;
	vector<string> spell;
	int j=1,temp=0;
	while(j<bestway.size()-1){
		if(bestway[j] == ','){
			pos.push_back(bestway.substr(temp,j-temp));
			temp=j+1;
			for(int k=j+1;k<bestway.size();k++){
				if(bestway[k]==','){
					spell.push_back(bestway.substr(temp,k-temp));
					temp=k+1;
					j=temp+1; 
					break;
				}
			}
		}
		else	j++;
	}
	//输出结果 
	ofstream f(file_out);
	if(f.is_open()){
		for(int i=0;i<pos.size();i++){
			f<<pos[i]<<" "<<spell[i]<<endl;		
		}
		f<<max_value<<endl;
	}
}

int main(int argc , char*argv[]){
	readInput(argv[1]);
    node *root=new node();
    root->s=str;
    root->cutway="";
    root->value=0;
    root=spanTree(root);
    getResult(argv[2]);
}
