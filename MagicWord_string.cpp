#include<bits/stdc++.h>
using namespace std;

int N,K;
string str; //����
map<string,int> spell_value;  //map[spell]=value 
map<char,vector<string> > letter_spells; //map[letter]=spells������ĸΪletter��spells 
map<string,int> word_maxvalue; //map[word] = max_value,�ַ���word��Ӧ�ĵõ�wordʱ�����value  
int max_value=-1; //�������value 
string bestway=""; //�������value��Ӧ���и���� 

struct node{
    string s;	 //����Ӧ���ַ��� 
    string cutway; 	//��Ӧ�õ���ǰ�ַ������и�� 
    int value;	 //��ǰ�ۻ���value 
    vector<node*> kid_nodes; 	//�ý���ַ����и��Ŀ��ܽ�� 
};

void readInput(char*file_in){ //�������ļ� 
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
	if(last->s == "" && last->value>max_value){ //�ַ����и���
		max_value = last->value;
		bestway = last->cutway;
	} 
	else{
		int flag=0;
        s=last->s;
	    for(int i=0;i<s.size();i++){ //�����ַ��� 
            for(int j=0;j<letter_spells[s[i]].size();j++){ //��������ĸ�Ĵʴ� 
                spell=letter_spells[s[i]][j];
                if((s.size()-i >= spell.size()) && s.substr(i,spell.size()) == spell){ //ƥ����и� 
                    cut_s = s.erase(i,spell.size());
		            s=last->s;
		            int value = last->value + spell_value[spell];
		            int temp=0;
		            /*�����и����ַ���֮ǰ�г��ֹ���֮ǰ�ﵽ���ַ���ʱ��ֵ���ڵ��ڵ�ǰֵ����ǰ�Ӵ����ټ�����*/ 
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
	    if(flag==0 && last->value>max_value){ //��ǰ�ַ����޷����и� 
	    	max_value = last->value;
			bestway = last->cutway;
	    }
	}
	return last;
}

void getResult(char*file_out){ //����bestway������ 
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
	//������ 
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
