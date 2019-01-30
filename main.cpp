#include <functional>
#include <unordered_map>
#include<iostream>
#include<fstream>
#include<list>
#include<stdio.h>
#include<math.h>
#include <map>
#include <queue>
#include <utility>
#include <vector>
#include <unordered_set>
#include <stack>
#include <utility>
#include <sstream>
#include <iterator>
using namespace std;

int main()
{
	std::map<int,char> map;
	map[26] = ' ';
	map[0] = 'a';
	map[1] = 'b';
	map[2] = 'c';
	map[3] = 'd';
	map[4] = 'e';
	map[5] = 'f';
	map[6] = 'g';
	map[7] = 'h';
	map[8] = 'i';
	map[9] ='j';
	map[10] ='k';
	map[11] = 'l';
	map[12] ='m';
	map[13] ='n';
	map[14] = 'o';
	map[15]= 'p';
	map[16] = 'q';
	map[17] = 'r';
	map[18] ='s';
	map[19] = 't';
	map[20] = 'u';
	map[21] = 'v';
	map[22]= 'w';
	map[23] ='x';
	map[24]= 'y';
	map[25]= 'z';
	
	const char *fileName= "initialStateDistribution.txt";
        const char *fileName2 = "emissionMatrix.txt";
	const char * fileName3 = "observations.txt";
	const char * fileName4 = "transitionMatrix.txt";
	
	ifstream file;
	ifstream file2;
	ifstream file3;
	ifstream file4;	

        file.open(fileName,ios::in);
	file2.open(fileName2,ios::in);
	file3.open(fileName3,ios::in);	
	file4.open(fileName4,ios::in);

	double hidden;
	double emmission;
	double initial ;

	double li1 = 0;
	int width = 308000;
	int height = 27;
	double emmA [27];
	double hiddA[27];
	double InitA [27];


	std::vector <vector<int> > Result;	 
	std::vector<vector<double> > Table;
	std::vector<vector <double> > transition;
	std::unordered_map<double,double> emm;
        std::vector<double> vecEmm;
	std::vector<double> vecInit;
	std::vector<double> vecHidd;
	std::vector<int> obs;
	std::vector <double> inTrans;	
	double tr;
	int fill;
	std::vector <int> firstCol;
	Result.push_back(firstCol);
	 if(!file || !file2) 
        {
                return -1; //return from main
        }
	int index=0;
	while(file2 >>hidden >> emmission){
		emmA[index] = emmission;
		hiddA[index]= hidden;	
		index ++;
		emm[hidden] = emmission;
		vecHidd.push_back(hidden);		
		vecEmm.push_back(emmission);		

	}
	file2.close();
	int index2 = 0;
	while (file>> initial ){
		InitA[index2] = initial;
		index2 ++;
		vecInit.push_back(initial);
			
	}
	
	file.close();
	while(file3 >> fill){

		obs.push_back(fill);
	}
	file3.close();
	int count = 0;

	while(file4 >> tr){
		
		if(count < 27){

			inTrans.push_back(tr);
			count++;
		}
		if(count == 27){
			transition.push_back(inTrans);
			inTrans.clear();
			count = 0;
		}
		
	}
	file4.close();
	double liPlus = 0; 
	std::vector <double> col1;
	for(int i =0; i < 27 ; i++){
		if(obs.at(0) == 0){
			col1.push_back(log(vecHidd.at(i) * vecInit.at(i)));
		}
		if(obs.at(0) == 1){
			col1.push_back(log(vecEmm.at(i) * vecInit.at(i)));
		}
	}
	Table.push_back(col1);
	double max = -9999999;

	std::vector <double> cal2;
	std::vector <int > cal3;
	int fill2 = 0;
	int tranIndex;
	for(int i = 1; i < 308000; i ++){
		fill2 = obs.at(i);
		
		std::vector < double> cal;
		cal = Table.at(i -1 );			//values of previous column
		for(int k = 0; k < 27 ; k ++){
			 max = -9999999;
			double trying = 0;		
			for(int u = 0; u < 27; u++){
				trying = cal.at(u) + log(transition.at(u).at(k));
				if(trying>max){
					
					tranIndex = u;		
					max = trying;
				}
			}
			if(fill2 == 0){
				max = max + log(vecHidd.at(k)); 
			}
			else{
				max = max + log(vecEmm.at(k));
			}
			
			cal3.push_back(tranIndex);
			cal2.push_back(max);	
		}		
		Table.push_back(cal2);
		Result.push_back(cal3);
		cal2.clear();
		cal3.clear();	
	}
	
	double maxNum = -9999999;
	for(double v : Table.at(307999)){
		if(v > maxNum){
			maxNum = v;
		}	
	}
	int indexCount = 0;
	for(double f : Table.at(307999)){
		if(maxNum ==  f){
			break;
		}
		indexCount ++;
	}
	int track = 307998;
	int ret = indexCount;
	int count2;
	
	std::vector <int > finalRes;
	for(int yy = 307999; yy > 1; yy --){
		count2 = 0;
			
		ret =Result.at(yy).at(ret);
		finalRes.push_back(ret);
		
	}
	std::map <char,int> m;
	int checking = 0;
	std::stack<double> st;
	int fin = finalRes.at(0);
	m.insert(std::make_pair(map[fin],checking));
	st.push(fin);
	for(int se :finalRes){
		if(se == fin){
			m[map[fin]]++;
			continue;
			
		}
		else{
			checking = 0;
			st.push(se);
			fin = se;
			m.insert(make_pair(map[fin],checking));
		}
	}
	while(st.size() != 0){

		cout << map[st.top()];
		st.pop();
	}
	std::cout << endl;
	std::cout <<endl;
	int checking2 = 1;
	finalRes.push_back(-1);
	int ch = finalRes.at(0);
	std::pair<char, int> pair;
	std::stack <std::pair <char,int> > stack;
	pair = make_pair(map[ch],checking2);
	cout << "letter  " << " " << "iteration" << endl;
	

	for(int v : finalRes){
		
		if(v == ch ){
			
			pair.second = checking2 ++;
			ch = v;	
		}
		else{
			checking2 = 1;
			stack.push(pair);
			pair = make_pair(map[v],checking2);
			ch = v;
		}

	}
	std::pair <char, int> out;
	while(stack.size() != 0){

		out = stack.top();
		cout << out.first << "          " << out.second << endl;
		stack.pop();

	}
	cout <<endl;
	cout << " note: when there is not letter and a number that means the letter is a space " << endl;
	
}
