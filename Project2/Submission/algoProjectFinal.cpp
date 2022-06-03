#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <cctype>
#include <functional>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
//g++ -std=c++14 algoProject3.cpp

double MASalgo(queue<double> q1, queue<double>q2, vector<double> target, vector<double>& sequence, vector<vector<double>>& memo){

    double a, b;
    double suma = 0;
    double sumb = 0;

    vector<double> seq1;
    vector<double> seq2;

    queue<double> q11 = q1;//temp storage
    queue<double> q22 = q2;//temp storage


    if(!q1.empty() && !q2.empty()){//Non base case scenario: neither queue is empty

        if(memo.at(q1.size()).at(q2.size()) > 1){

            memo.at(q1.size()).at(q2.size()) = 0;

            suma = q1.front()*target.at(0);
            sumb = q2.front()*target.at(0);
            
            target.erase(target.begin());

            

            q1.pop();
            a = suma + MASalgo(q1, q2, target, seq1, memo);
            
            q2.pop();
            b = sumb + MASalgo(q11, q2, target, seq2, memo);
            
            if(a >= b){
                sequence.push_back(q11.front());
                for(int i = 0; i < seq1.size(); i++){
                    sequence.push_back(seq1.at(i));
                }
                
               
            }else{
                sequence.push_back(q22.front());
                for(int i = 0; i < seq2.size(); i++){
                    sequence.push_back(seq2.at(i));
                }
                
            }
            
            memo.at(q1.size()+1).at(q2.size()+1) = max(a,b);

        }else{

            return memo.at(q1.size()).at(q2.size());

        }

    //BASE CASES
    }else if(q1.empty() && q2.size() == 1){//BASE CASE 1: q1 empty and q2 has 1 element

        if(memo.at(0).at(1) > 1){    
            memo.at(0).at(1) = q2.front()*target.at(0);
        }

        sequence.push_back(q2.front());

        return memo.at(0).at(1);

    }else if(q1.empty() && q2.size() > 1){//BASE CASE 2: q1 empty and q2 has more than 1 element

        int size2 = q2.size();

        if(memo.at(0).at(q2.size()) > 1){

            memo.at(0).at(q2.size()) = 0;

            for(int i = 0; i < target.size(); i++){
                memo.at(0).at(size2) += q2.front()*target.at(i);
                q2.pop();
            }

        }

        for(int i = 0; i < size2; i++){

            sequence.push_back(q22.front());
            q22.pop();

        }
        
        return memo.at(0).at(size2);

    }else if(q2.empty() && q1.size() == 1){//BASE CASE 3: q2 empty and q1 has 1 element

        if(memo.at(1).at(0) > 1){

            memo.at(1).at(0) = q1.front()*target.at(0);

        }

        sequence.push_back(q1.front());

        return memo.at(1).at(0);

    }else if(q2.empty() && q1.size() > 1){//BASE CASE 4: q2 empty and q1 has more than 1 element

        int size1 = q1.size();

        if(memo.at(q1.size()).at(0) > 1){

            
            memo.at(q1.size()).at(0) = 0;

            for(int i = 0; i < target.size(); i++){

                memo.at(size1).at(0) += q1.front()*target.at(i);
                q1.pop();

            }

        }

        for(int i = 0; i < size1; i++){
            sequence.push_back(q11.front());
            q11.pop();
        }

        return memo.at(size1).at(0);

    }

    return memo.at(q11.size()).at(q22.size());

}


int max(int a, int b){
    if(a >= b){
        return a;
    }else{
        return b;
    }
}


double wrapper(queue<double> q1, queue<double>q2, vector<double> target, vector<double>& sequence, vector<vector<double>>& memo){

    vector<double> inner;

    //initializing 2d vector
    for(int i = 0; i < q1.size()+1; i++){
        for(int j = 0; j < q2.size()+1; j++){
            inner.push_back(9);
        }
        memo.push_back(inner);
        inner = {};
    }

    return MASalgo(q1, q2, target, sequence, memo);

}


int main(){

//INPUT.TXT CODE
queue<double> q1;
queue<double> q2;
vector<double> target, myVec;
vector<int> myVec2;
vector<vector<int>> myVec3;
int n, m;
double in;

ifstream ifile;

ifile.open("input.txt");
ifile >> n >> m;

for(int i = 0; i < n; i++){
    ifile >> in;
    q1.push(in);
}

for(int i = 0; i < m; i++){
    ifile >> in;
    q2.push(in);
}

for(int i = 0; i < n+m; i++){
    ifile >> in;
    target.push_back(in);
}

ifile.close();
//END INPUT.TXT CODE



vector<double> sequence;
vector<vector<double>> twoDvec;

double MAS = wrapper(q1,q2,target, sequence, twoDvec); //maximum alignment score


//OUTPUT.TXT CODE
ofstream ofile;
ofile.open("output.txt");
ofile << MAS << endl;
for(int i = 0; i< sequence.size(); i++){ //writing sequence to output
    ofile << sequence.at(i) << " ";
}
//END OUTPUT.TXT CODE



}