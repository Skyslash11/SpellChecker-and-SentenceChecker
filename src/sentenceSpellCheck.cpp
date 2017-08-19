#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<cstdlib>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<cstring>
#include<string>
#include<math.h>
#include<algorithm>
#include <sys/param.h>
#include <unistd.h>



using namespace std;

#define ll long long int
#define ld long double;
#define pi pair<int,int>
#define ppi pair<pi,int>
#define vi vector<int>
#define vpi vector<pi>
#define vppi vector<ppi>
#define loop(i,n) for(int i=0;i<n;++i)
#define loopm(i,m,n) for(int i=m;i<n;++i)
#define loopv(it,vec) for(vi::iterator=vec.begin();it!=vec.end();++it)
#define ans(i,ans) cout<<"Case #"<<i<<": "<<ans<<"\n";

double editDistance(string correct,string typo);
string findMin(map<string,double> corrections);
vector<string> splitTypo(string typo);
string metaphonesConvert(string str);
vector<string> getContext(vector<string> tokens);
vector<string> getConfusionSet(string word);
string dropDuplicates(string str);
string transformation3(string str);
string transformation4(string str);
string transformation5(string str);
string transformation6(string str);
string transformation7(string str);
string transformation8(string str);
string transformation9(string str);
string transformation10(string str);
string transformation11(string str);
string transformation12(string str);
string transformation13(string str);
string transformation14(string str);
string transformation15(string str);
string transformation16(string str);
string transformation17(string str);
string transformation18(string str);
string transformation19(string str);


vector<map<string,int> > dictionary;
map<string,int> dictionaryMap;
map<string,double> check;
map<string,double> corrections;
map<string,double> phCorrections;
map<string,map<string,int> > contextWordMap;
map<string,vector<string> > confusionSet;
map<string,int> confusionWordsFreq;

int del[27][26];
int add[27][26];
int sub[26][26];
int rev[26][26];
int chr[26][26];
int chr1[26];
string input;
int maxDictionaryLength=0;
map<string,map<string,int> > trigramMap;
map<string,map<string,int> > digramMap;
map<string,map<string,int> > monoMap;


string getcwd(){
    char *buffer = new char[MAXPATHLEN];
    getcwd(buffer,MAXPATHLEN);
    if(buffer != NULL){
        string ret(buffer);
        delete[] buffer;
        return ret;
    }else{
        return string();
    }
}

int main(int argc,char **argv)
{
	loop(i,33)
	{
		map<string,int> temp;
		dictionary.push_back(temp);
	}
    ifstream file;
    string cwd=getcwd();
    int index=0;
    int trim=0;
    loop(i,cwd.length())
    {
    	if(cwd[cwd.length()-1-i]=='/')
    	{
    		++trim;
    		break;
    	}
    	++trim;
    }
    cwd=cwd.substr(0,cwd.length()-trim);
    cwd+="/data/";
    //cout<<"hehe : "<<cwd<<"\n";
    string s1,s2,s3,s4,s5,s6,s7,s8,s9;
    s1=cwd+"dictionary";
    s2=cwd+"del";
    s3=cwd+"add";
    s4=cwd+"sub";
    s5=cwd+"rev";
    s6=cwd+"chr";
    s7=cwd+"chr1";
    s8=cwd+"final3.txt";
    s9=cwd+"finalconf.txt";
    file.open (s1.c_str());
    if (!file.is_open()) return 0;
    string word1,word2,word3,word4;
    while (file >> word1)
		{
		file >> word2;
		int freq;
		if(word2.length()>9)
			freq=1000000000;
		else
			freq=atoi(word2.c_str());
		int length=word1.length();
		if(length<33)
		{
			if(length==1 && (word1!="A" && word1!="I"))
				continue;
			dictionary[length].insert(pair<string,int>(word1,freq));
			if(maxDictionaryLength<length)
				maxDictionaryLength=length;
		}

		for(int i=0;i<(int)(word1.length())-2;++i)
		{
			
			string trigram=word1.substr(i,3);
			//cout<<i<<"   "<<trigram<<"...\n";
			if(trigramMap.count(trigram)==0)
			{
				map<string,int> tmp;
				tmp.insert(pair<string,int>(word1,freq));
				trigramMap.insert(pair<string,map<string,int> >(trigram,tmp));
				//cout<<trigramMap.size()<<"\n";
			}
			else
			{
				trigramMap[trigram].insert(pair<string,int>(word1,freq));
			}
		}
		
		for(int i=0;i<(int)(word1.length())-1;++i)
		{
			
			string digram=word1.substr(i,2);
			//cout<<i<<"   "<<trigram<<"...\n";
			if(digramMap.count(digram)==0)
			{
				map<string,int> tmp;
				tmp.insert(pair<string,int>(word1,freq));
				digramMap.insert(pair<string,map<string,int> >(digram,tmp));
				//cout<<trigramMap.size()<<"\n";
			}
			else
			{
				digramMap[digram].insert(pair<string,int>(word1,freq));
			}
		}
		
		for(int i=0;i<(int)(word1.length());++i)
		{
			
			string monogram=word1.substr(i,1);
			//cout<<i<<"   "<<trigram<<"...\n";
			if(monoMap.count(monogram)==0)
			{
				map<string,int> tmp;
				tmp.insert(pair<string,int>(word1,freq));
				monoMap.insert(pair<string,map<string,int> >(monogram,tmp));
				//cout<<trigramMap.size()<<"\n";
			}
			else
			{
				monoMap[monogram].insert(pair<string,int>(word1,freq));
			}
		}
		
    }
  

    //cout<<trigramMap["ABL"].size()<<"\n";

	ifstream file1,file2,file3,file4,file5,file6,file7,file8,inputfile;
	file1.open(s2.c_str());
	file2.open(s3.c_str());
	file3.open(s4.c_str());
	file4.open(s5.c_str());
	file5.open(s6.c_str());
	file6.open(s7.c_str());
	file7.open(s8.c_str());
	file8.open(s9.c_str());
	int i=0,j=0;
	while(file1 >> word1 && file2 >> word2)
	{
		del[i][j]=atoi(word1.c_str());
		add[i][j]=atoi(word2.c_str());
		if(j==25)
		{
			j=0;
			++i;
		}
		else
			j++;
	}
    i=0;
	j=0;
	while(file3 >> word1 && file4 >> word2 && file5 >> word3)
	{
		sub[i][j]=atoi(word1.c_str());
		rev[i][j]=atoi(word2.c_str());
		chr[i][j]=atoi(word3.c_str());
		if(j==25)
		{
			j=0;
			++i;
		}
		else
			j++;
	}

	i=0;
	while(file6 >> word1)
	{
		//cout<<"Hello    "<<word1<<"\n";
		chr1[i]=atoi(word1.c_str());
		++i;
	}
	i=0;
	string prev="#start";
	string presentConf="";
	while(getline(file7,word1))
	{
		istringstream iss(word1);
    	string word1,word2,head;
    	iss >> head;
    	transform(head.begin(), head.end(),head.begin(), ::toupper);
    	map<string,int> cxt;
    	while(iss >> word1) 
    	{
    		transform(word1.begin(), word1.end(),word1.begin(), ::toupper);
    		iss >> word2;
    		if(atoi(word2.c_str())!=0)
    			cxt.insert(pair<string,int>(word1,atoi(word2.c_str())));	
    	}
    	if(cxt.size()!=0)
    		contextWordMap.insert(pair<string,map<string,int> >(head,cxt));
	}

	while(getline(file8,word1))
	{
		istringstream iss(word1);
		vector<string> vec;
		int i=0;
		string head="";
		while(iss >> word1 && iss >> word2)
		{
			transform(word1.begin(), word1.end(),word1.begin(), ::toupper);
			confusionWordsFreq.insert(pair<string,int>(word1,atoi(word2.c_str())));
			vec.push_back(word1);
		}
		loop(i,vec.size())
		{
			confusionSet.insert(pair<string,vector<string> >(vec[i],vec));
		}
	}

	/*for(map<string,vector<string> >::iterator it=confusionSet.begin();it!=confusionSet.end();++it)
	{
		cout<<it->first<<"\t";
		loop(i,it->second.size())
			cout<<it->second[i]<<"\t";
		cout<<"\n";
	}*/
	
	/*loop(i,26)
	{
		loop(j,26)
			cout<<chr[i][j]<<" ";
		cout<<"\n";
	}*/

	//loop(i,26)
	//	cout<<chr1[i]<<"  "<<i<<"\n";
/************************************************************************/
	string input;
	int noInputs;
	inputfile.open(argv[1]);
	while(getline(inputfile,input))
	{
		corrections.clear();
		phCorrections.clear();
		vector<string> tokens;
		transform(input.begin(), input.end(),input.begin(), ::toupper);
		istringstream iss(input);
	    
	    //cout<<input<<"gg\n";
	    while(iss >> word1) 
	    {
	    	tokens.push_back(word1);
	    }

		//cout<<tokens.size()<<"\n";
		string typo;
		int flag =0;
		loop(i,tokens.size())
		{
			//cout<<tokens[i]<<"\n";
			if(dictionary[tokens[i].length()].count(tokens[i])==0)
			{
				typo.assign(tokens[i]);
				//cout<<"The typo is : "<<typo<<"\n";
				flag=1;
				break;
			}
		}

		if(flag==0)
		{
			//cout<<"Context Words\n";
			vector<string> presentContext,cnfusWords;
			vector<double> cnfusProb;
			presentContext=getContext(tokens);
			int find=0;
			//cout<<"I am here : "<<presentContext.size()<<"\n";
			if(presentContext.size()==0)
			{
				cout<<"NULL\tNULL\tNULL\tNULL\n";
				find=1;
			}
			if(find==0)
			{
				cnfusWords=getConfusionSet(presentContext[0]);
				loop(i,cnfusWords.size())
				{
					cnfusProb.push_back(1);
				}
				int maxVal=0;
				int maxIndex=0;
				loop(i,cnfusWords.size())
				{
					map<string,int> tempContext=contextWordMap[cnfusWords[i]];
					int Denominator=confusionWordsFreq[cnfusWords[i]];
					if(Denominator==0)
						cnfusProb[i]=1;
					else
					{
						loop(j,presentContext.size())
						{
							if(tempContext.count(presentContext[j])==1)
							{
								cnfusProb[i]*=(double)tempContext[presentContext[j]]/Denominator;
							}
						}
					}
					if(cnfusProb[i]!=1 && cnfusProb[i]>maxVal)
					{
						maxVal=cnfusProb[i];
						maxIndex=i;
					}
				}
				int flag=1;
				vector<long long int> rating;
				loop(i,cnfusWords.size())
				{
					rating.push_back(dictionary[cnfusWords[i].size()][cnfusWords[i]]);
					if(cnfusProb[i]==1)
						flag=0;
				}
				sort(rating.begin(),rating.end());
				if(flag==0)
				{
					int j=rating.size()-1;
					cout<<presentContext[0];
					loop(i,cnfusWords.size())
					{
						if(cnfusWords[i]==presentContext[0])
							continue;
						cout<<" "<<cnfusWords[i]<<" "<<rating[j];
						--j;
					}
					cout<<" "<<presentContext[0]<<" "<<rating[j]<<"\n";
				}
				else
				{
					cout<<presentContext[0]<<" "<<cnfusWords[maxIndex]<<" "<<rating[rating.size()-1];
					int j=rating.size()-2;
					loop(i,cnfusWords.size())
					{
						if(cnfusWords[i]==cnfusWords[maxIndex])
							continue;
						cout<<" "<<cnfusWords[i]<<" "<<rating[j];
						--j;
					}
					cout<<"\n";
				}
			}
		}
		else
		{
			//cout<<"Word Spell Check  "<<typo<<"\n";
			vector<string> splits=splitTypo(typo);
			//cout<<"Splits No. : "<<splits.size()<<"\n";
			if((splits.size()>(typo.length()/3)) || splits.size()==0)
			{
				string metaTypo;
				metaTypo=metaphonesConvert(typo);
				map<string,int> possibleCorrections;
				map<string,string> metaMap;
				if(typo.length()==1)
				{
					cout<<typo<<"\t";
					loop(i,10)
						cout<<(char)(65+i)<<"\t1\t";
					cout<<"\n";
				}
				else if(typo.length()==2)
				{
					loop(i,(int)typo.length())
					{
						string monogram=typo.substr(i,1);
						for(map<string,int>::iterator it=monoMap[monogram].begin();it!=monoMap[monogram].end();++it)
						{
							if(possibleCorrections.count(it->first)==1)
								continue;
							int len1=typo.length();
							int len2=it->first.length();
							int check=(len1/3)+1;
							if(abs(len1-len2)==0)
							{
							
								possibleCorrections.insert(pair<string,int>(it->first,it->second));
								//cout<<it->first<<"\n";
							}
						}

					}
				}
				else if(typo.length()==3 || typo.length()==4 || typo.length()==5)
				{
					loop(i,(int)typo.length()-1)
					{
						string digram=typo.substr(i,2);
						for(map<string,int>::iterator it=digramMap[digram].begin();it!=digramMap[digram].end();++it)
						{
							if(possibleCorrections.count(it->first)==1)
								continue;
							int len1=typo.length();
							int len2=it->first.length();
							int check=(len1/3)+1;
							if(abs(len1-len2)<=check && (len1-len2)<check)
							{
							
								possibleCorrections.insert(pair<string,int>(it->first,it->second));
								//cout<<it->first<<"\n";
							}
						}

					}
				}
				else
				{
					//cout<<"3  "<<typo<<"\n";

					loop(i,(int)typo.length()-2)
					{
						string trigram=typo.substr(i,3);
						for(map<string,int>::iterator it=trigramMap[trigram].begin();it!=trigramMap[trigram].end();++it)
						{
							if(possibleCorrections.count(it->first)==1)
								continue;
							int len1=typo.length();
							int len2=it->first.length();
							int check=(len1/3)+1;
							if(abs(len1-len2)<=check && (len1-len2)<check)
							{
							
								possibleCorrections.insert(pair<string,int>(it->first,it->second));
								//cout<<it->first<<"\n";
							}
						}

					}
				}
				//cout<<"Possible Corrections : "<<possibleCorrections.size()<<"\n";
				int ii=0;
				for(map<string,int>::iterator it=possibleCorrections.begin();it!=possibleCorrections.end();++it)
				{
					++ii;
					double val = editDistance(it->first,typo)*it->second;
					string tempMeta=metaphonesConvert(it->first);
					metaMap.insert(pair<string,string>(it->first,tempMeta));

					double phVal = editDistance(tempMeta,metaTypo)*it->second/10;
					//cout<<"_____  "<<it->first<<"   "<<tempMeta<<"    "<<it->second<<"\n";

					if(corrections.size()<10)
						corrections[it->first]=val;
					else
					{
						string min=findMin(corrections);
						if(corrections[min]<val)
						{
							corrections.erase(min);
							corrections.insert(pair<string,double>(it->first,val));
						}
					}
					if(phCorrections.size()<1)
						phCorrections[it->first]=phVal;
					else
					{
						string min=findMin(phCorrections);
						int test=typo.length()-it->first.length();
						if(phCorrections[min]<phVal && (abs(test)<=typo.length()/3))
						{
							phCorrections.erase(min);
							phCorrections.insert(pair<string,double>(it->first,phVal));
						}
					}
				}
				string phString;
				double phValMax;
				for(map<string,double>::iterator it=phCorrections.begin();it!=phCorrections.end();++it)
				{
					phString=it->first;
					phValMax=it->second;
				}
				vector<pair<string,double> > ranking;
				while(corrections.size()!=0)
				{
					string min=findMin(corrections);
					ranking.push_back(pair<string,double>(min,corrections[min]));
					corrections.erase(min);
				}
				cout<<typo<<"\t";
				int flag=0;
				int j=0;
				if(ranking[ranking.size()-1].second>10000)
					phValMax=0;
				loop(i,10)
				{
					if(phValMax>ranking[ranking.size()-1-j].second && flag==0)
					{
						cout<<phString<<"\t"<<phValMax<<"\t";
						flag=1;
						--j;

					}
					else if(flag==1 && ranking[ranking.size()-1-j].first==phString )
					{
						--i;
					}
					else
						cout<<ranking[ranking.size()-1-j].first<<"\t"<<ranking[ranking.size()-1-j].second<<"\t";
					++j;
				}
				cout<<"\n";



			}
			else
			{
				cout<<typo<<" ";
				loop(i,splits.size())
					cout<<splits[i]<<" ";
				cout<<"\n";
			}
		}
	}


	return 0;

}

vector<string> splitTypo(string typo)
{
	vector<string> ret;
	double max=0;
	if(typo.size()==0)
		return ret;
	for(int i=1;i<typo.length()+1;++i)
	{
		vector<string> rt;
		string s1,s2;
		s1=typo.substr(0,i);
		rt.push_back(s1);
		double val=(double)dictionary[s1.length()][s1]/100000000000;
		if(dictionary[s1.length()].count(s1)!=0)
		{
			if(i==typo.length())
			{
				if(val>max)
					ret.assign(rt.begin(),rt.end());
			}
			vector<string> tail=splitTypo(typo.substr(i,typo.length()-i));
			if(tail.size()==0)
				continue;
			else
			{
				loop(j,tail.size())
				{
					if(dictionary[tail[j].length()][tail[j]]<10000000)
						val=0;
					else
						val=val*(double)dictionary[tail[j].length()][tail[j]]/100000000000;
					rt.push_back(tail[j]);
				}
				if(val>max)
				{
					ret.assign(rt.begin(),rt.end());
					max=val;
				}
			}
		}
	}
	return ret;
}

double editDistance(string correct,string typo)
{
	double matrix[typo.length()+1][correct.length()+1];
	loop(x,typo.length()+1)
		loop(y,correct.length()+1)
			{
				//cout<<x<<"   "<<y<<"\n";
				if(x==0 && y==0)
				{
					//cout<<"hi\n";
					matrix[x][y]=1;
					//cout<<"bye\n";
				}
				else if(x==0 && y!=0)
					matrix[x][y]=(double)del[26][(int)correct[y-1]-65]/100000;
				else if(x!=0 && y==0)
					matrix[x][y]=(double)add[26][(int)typo[x-1]-65]/100000;
				else
				{
					double max=0;
					if(correct[y-1]==typo[x-1])
					{
						max=matrix[x-1][y-1];
						double val = matrix[x-1][y]*((double)add[(int)correct[y-1]-65][(int)typo[x-1]-65])/chr1[(int)correct[y-1]-65];
						if(max < val)
							max=val;
						//cout<<del[(int)correct[y-1]-65][(int)typo[x-1]-65]<<"    "<<(int)correct[y-1]<<"  "<<(int)typo[x-1]<<"\n";
						val = matrix[x][y-1]*((double)del[(int)correct[y-1]-65][(int)typo[x-1]-65])/chr[(int)correct[y-1]-65][(int)typo[x-1]-65];
						if(max < val)
							max = val;
						matrix[x][y] = max;
					}
					else
					{
						max=matrix[x-1][y-1]*((double)sub[(int)typo[x-1]-65][(int)correct[y-1]-65]/chr1[(int)correct[y-1]-65]);
						double val = matrix[x-1][y]*((double)add[(int)correct[y-1]-65][(int)typo[x-1]-65])/chr1[(int)correct[y-1]-65];
						if(max < val)
							max=val;
						val = matrix[x][y-1]*((double)del[(int)correct[y-1]-65][(int)typo[x-1]-65])/chr[(int)correct[y-1]-65][(int)typo[x-1]-65];
						if(max < val)
							max = val;
						matrix[x][y] = max;
					}
				}
			}

	

	return matrix[typo.length()][correct.length()];
}

string findMin(map<string,double> corrections)
{
	string minStr;
	double min=1000000000000;
	for(map<string,double>::iterator it=corrections.begin();it!=corrections.end();++it)
	{
		if(it->second<min)
		{
			min=it->second;
			minStr=it->first;
		}
	}
	return minStr;
}

vector<string> getContext(vector<string> tokens)
{
	string mark="NULL";
	int index=-1;

	loop(i,tokens.size())
	{
		if(confusionWordsFreq.count(tokens[i])!=0)
		{
			mark=tokens[i];
			index=i;
			break;
		}
	}
	//cout<<"Marker : "<<mark<<"\n";
	vector<string> ret;
	if(index==-1)
		return ret;
	ret.push_back(mark);
	for(int i=index-1;i>=0;--i)
	{
		if(index-i==3)
			break;
		ret.push_back(tokens[i]);
	}
	for(int i=index+1;i<tokens.size();++i)
	{
		if(i-index==3)
			break;
		ret.push_back(tokens[i]);
	}
	//cout<<"The context is : "<<ret.size()<<"    ";
	//loop(i,ret.size())
	//	cout<<ret[i]<<"  ";
	//cout<<"\n";
	return ret;
}

vector<string> getConfusionSet(string word)
{
	//cout<<"The confusion set is : "<<confusionSet.count(word)<<"\t"<<word<<"\n";
	/*loop(i,confusionSet[word].size())
	{
		cout<<confusionSet[word][i]<<"\t";
	}*/
	//cout<<"\n";
	return confusionSet[word];
}

string metaphonesConvert(string str)
{
	str=dropDuplicates(str);
	int i=0;
	string ret;
	ret.assign(str);
	string begin=str.substr(0,2);
	if(begin=="KN" || begin=="GN" || begin=="PN" || begin=="AE" || begin=="WR")
	{
		ret=str.substr(1,str.length()-1);	
	}
	if(str.substr(0,2)=="WH")
		ret='W'+str.substr(2,str.length()-2);
	if(str[0]=='X')
		ret='S'+str.substr(1,str.length()-1);

	
	ret=transformation3(ret);
	ret=transformation4(ret);
	ret=transformation5(ret);
	ret=transformation6(ret);
	ret=transformation7(ret);
	ret=transformation8(ret);
	ret=transformation9(ret);
	ret=transformation10(ret);
	ret=transformation11(ret);
	ret=transformation12(ret);
	ret=transformation13(ret);
	ret=transformation14(ret);
	ret=transformation15(ret);
	ret=transformation16(ret);
	ret=transformation17(ret);
	ret=transformation18(ret);
	ret=transformation19(ret);
	ret=dropDuplicates(ret);
	return ret;
}

string dropDuplicates(string str)
{
	string ret="";
	ret+=str[0];
	for(int i=1;i<str.length();++i)
	{
		if(str[i]!=ret[ret.length()-1] || str[i]=='C')
			ret+=str[i];
	}
	return ret;
}

string transformation3(string str)
{
	if(str.length()>=2)
	{
		if(str.substr(str.length()-2,2)=="MB")
			return str.substr(0,str.length()-1);
	}
	return str;
}

string transformation4(string str)
{
	if(str.length()<=2)
			return str;
	string ret="";
	loop(i,str.length()-1)
	{
		if(str[i]=='C')
		{
			if(str[i+1]=='H')
			{
				if(i>0 && str[i-1]=='S')
					ret+='K';
				else
					ret+='X';
			} 
			else if(str.substr(i+1,2)=="IA")
				ret+='X';
			else if(str[i+1]=='I' || str[i+1]=='E' || str[i+1]=='Y')
				ret+='S';
			else
				ret+='K';
		}
		else
			ret+=str[i];
	}
	ret+=str[str.length()-1];
	return ret;
}

string transformation5(string str)
{
		if(str.length()<=2)
			return str;
		string ret="";
		loop(i,str.length()-2)
		{
			if(str[i]=='D')
			{
				if(str.substr(i+1,2)=="GE" || str.substr(i+1,2)=="GY" || str.substr(i+1,2)=="GI")
					ret+='J';
				else
					ret+='D';
			}
			else
				ret+=str[i];
		}

		if(str[str.length()-2]=='D')
			ret+='D';
		else
			ret+=str[str.length()-2];
		if(str[str.length()-1]=='D')
			ret+='D';
		else
			ret+=str[str.length()-1];
		return ret;
}

string transformation6(string str)
{
	if(str.length()<=2)
			return str;
	string ret="";
	loop(i,str.length()-2)
	{
		if(str[i]=='G')
		{
			if(str[i+1]=='H' && (str[i+2]!='A' || str[i+2]!='E' || str[i+2]!='I' || str[i+2]!='O' || str[i+2]!='U'))
			{

			}
			else if(i==str.length()-4 && str.substr(i+1,3)=="NED")
			{

			}
			else
				ret+=str[i];

		}
		else
			ret+=str[i];
	}
	if(str[str.length()-2]=='G' && str[str.length()-1]=='N')
		ret+='N';
	else
		ret+=str.substr(str.length()-2,2);
	return ret;
}

string transformation7(string str)
{
	if(str.length()<=2)
			return str;
	string ret;

	loop(i,str.length()-1)
	{
		if(str[i]=='G')
		{
			if(str[i+1]=='I' || str[i+1]=='E' || str[i+1]=='Y')
				ret+='J';
			else
				ret+='K';
		}
		else
			ret+=str[i];
	}
	if(str[str.length()-1]=='G')
		ret+='G';
	else
		ret+=str[str.length()-1];
	return ret;
}

string transformation8(string str)
{
	if(str.length()<=2)
			return str;
	string ret="";
	ret+=str[0];
	for(int i=1;i<str.length()-1;++i)
	{
		if((str[i-1]=='A'||str[i-1]=='E'||str[i-1]=='I'||str[i-1]=='O'||str[i-1]=='U') && str[i]=='H' && (str[i+1]!='A'&& str[i+1]!='E'&& str[i+1]!='I'&& str[i+1]!='O'&& str[i+1]!='U'))
		{

		}
		else
			ret+=str[i];
	}
	int i=str.length()-1;
	if((str[i-1]=='A'||str[i-1]=='E'||str[i-1]=='I'||str[i-1]=='O'||str[i-1]=='U') && str[i]=='H')
	{

	}
	else
		ret+=str[i];
	return ret;
}

string transformation9(string str)
{
	return str;
}

string transformation10(string str)
{
	if(str.length()<=2)
			return str;
	string ret="";
	loop(i,str.length()-1)
	{
		if(str[i]=='P' && str[i+1]=='H')
		{
			ret+='F';
			++i;
		}
		else
			ret+=str[i];
	}
	ret+=str[str.length()-1];
	return ret;
}

string transformation11(string str)
{
	string ret="";
	loop(i,str.length())
	{
		if(str[i]=='Q')
			ret+='K';
		else
			ret+=str[i];
	}
	return ret;
}

string transformation12(string str)
{
	string ret="";
	if(str.length()<=2)
		return str;
	loop(i,str.length()-2)
	{
		if(str[i]=='S' && (str.substr(i+1,2)=="IO" || str.substr(i+1,2)=="IA" || str[i+1]=='H'))
			ret+='X';
		else
			ret+=str[i];
	}
	if(str[str.length()-2]=='S' && str[str.length()-1]=='H')
		ret+='X';
	else
		ret+=str[str.length()-2];
	ret+=str[str.length()-1];
	return ret;
}

string transformation13(string str)
{
	if(str.length()<=2)
		return str;
	string ret="";

	loop(i,str.length()-2)
	{
		if(str[i]=='T' && (str.substr(i+1,2)=="IA" || str.substr(i+1,2)=="IO"))
		{
			ret+='X';
		}
		if(str[i]=='T' && str.substr(i+1,2)=="CH")
		{

		}
		else
			ret+=str[i];
	}
	ret+=str.substr(str.length()-2,2);
	return ret;
}

string transformation14(string str)
{
	return str;
}

string transformation15(string str)
{
	if(str.length()<=2)
		return str;
	string ret="";
	loop(i,str.length()-1)
	{
		if(str[i]=='W' && (str[i+1]!='A' && str[i+1]!='E' && str[i+1]!='I' && str[i+1]!='O' && str[i+1]!='U'))
		{

		}
		else
			ret+=str[i];
	}
	if(str[str.length()-1]=='W')
	{

	}
	else
		ret+=str[str.length()-1];
	return ret;
}

string transformation16(string str)
{
	string ret="";
	loop(i,str.length())
	{
		if(str[i]=='X')
			ret+="KS";
		else
			ret+=str[i];
	}
	return ret;
}

string transformation17(string str)
{
	if(str.length()<=1)
		return str;
	string ret="";
	loop(i,str.length()-1)
	{
		if(str[i]=='Y' && (str[i+1]!='A' && str[i+1]!='E' && str[i+1]!='I' && str[i+1]!='O' && str[i+1]!='U'))
		{

		}
		else
			ret+=str[i];
	}
	if(str[str.length()-1]=='Y')
	{

	}
	else
		ret+=str[str.length()-1];
	return ret;
}

string transformation18(string str)
{
	string ret="";
	loop(i,str.length())
	{
		if(str[i]=='Z')
			ret+='S';
		else
			ret+=str[i];
	}
	return ret;
}

string transformation19(string str)
{
	if(str.length()<=1)
		return str;
	string ret="";
	ret+=str[0];
	for(int i=1;i<str.length();++i)
	{
		if(str[i]=='A' || str[i]=='E' || str[i]=='I' || str[i]=='O' || str[i]=='U')
		{

		}
		else
			ret+=str[i];
	}
	return ret;
}