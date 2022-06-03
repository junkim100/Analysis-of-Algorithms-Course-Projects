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
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

vector< queue<double> > readInput(string filename) {
    ifstream ifs(filename);

    //Get length of the 2 sequences
    string input1, input2;
    int length1, length2, lengthTarget;

    getline(ifs, input1, ' ');
    getline(ifs, input2);
    length1 = stoi(input1);
    length2 = stoi(input2);
    lengthTarget = length1 + length2;

    //Get each element and store them to a float array
    string input3[length1], input4[length2], input5[lengthTarget];
    queue<double> seq1, seq2, target;
    double in;
    for(int i = 0; i < length1; i++) {
        ifs >> in;
        seq1.push(in);
        // if(i == length1-1)
        //     getline(ifs, input3[i]);
        // else
        //     getline(ifs, input3[i], ' ');
        // seq1.push(stof(input3[i]));
    }
    for(int i = 0; i < length2; i++) {
        ifs >> in;
        seq2.push(in);
        // if(i == length2-1)
        //     getline(ifs, input4[i]);
        // else
        //     getline(ifs, input4[i], ' ');
        // seq2.push(stof(input4[i]));
    }
    for(int i = 0; i < lengthTarget; i++) {
        ifs >> in;
        target.push(in);
        // if(i == length1+length2-1)
        //     getline(ifs, input5[i]);
        // else
        //     getline(ifs, input5[i], ' ');
        // target.push(stof(input5[i]));
    }

    ifs.close();
    
    vector< queue<double> > r;
    r.push_back(seq1);
    r.push_back(seq2);
    r.push_back(target);
    return r;
}

void writeOutput(double score, vector<double> answer) {
    ofstream ofs("output.txt");
    ofs << score << endl;

    for (int i = 0; i < answer.size(); i++)
            ofs << answer.at(i) << ' ';

}

bool isEmpty(queue<double>  seq) {
    if(seq.size() ==0)
        return true;
    else
    return false;
}

vector<double> choose(queue<double>  seq1, queue<double>  seq2) {
    int length1 = seq1.size();
    int length2 = seq2.size();
    int lenghtTarget = length1 + length2;
    vector<double> temp;

    while (true) {
        //if both empty
        if (length1 == 0 && length2 == 0) {
            break;
        }
        //if both not empty
        else if (length1 != 0 && length2 != 0) {
            length1--;
            temp.push_back(1);
        }
        //if one of the sequence is empty
        else {
            if (length1 == 0) {
                length2--;
                temp.push_back(2);
            } else {
                length1--;
                temp.push_back(1);
            }
        }
    }

    // for (int i = 0; i < lenghtTarget; i++) 
    //     cout << temp.at(i) << ' ';

    return temp;
}

//returns [ending number, position, countOne, countTwo]
vector<double> checkEnd(vector<double> a, queue<double> target) {
    int countOne = 0;
    int countTwo = 0;
    vector<double> r;
    for (int i = 0; i < target.size(); i++) {
        if (countOne == 3) {
            r.push_back(1);
            break;
        }
        else if (countTwo == 3) {
            r.push_back(2);
            break;
        }
        else if (a.at(i) == 1)
            countOne++;
        else
            countTwo++;
    }
    //pushing back position
    r.push_back(countOne + countTwo - 1);

    //pushing back counts
    r.push_back(countOne);
    r.push_back(countTwo);

    return r;
}

int factorial(int a) {
    if(a > 1)
        return a * factorial(a - 1);
    else
        return 1;
}

int combination(int one, int two) {
    return factorial(one+two) / (factorial(one) * factorial(two));
}

vector<double> algorithmDynamic(vector< vector<double> > generated, queue<double> seq1, queue<double> seq2, queue<double> target, vector<double> end, int count) {

    // vector<int> end = checkEnd(generated.at(count), target);
    // cout << "end: " << end.at(0) << " position: " << end.at(1) << " countOne: " << end.at(2) << " countTwo: " << end.at(3) << endl;
    
    vector<double> temp;

    //if sequence ended in 1
    if (end.at(0) == 1) {
        queue<double> newSeq1 = seq1;
        queue<double> newSeq2 = seq2;

        for (int i = 0; i < end.at(1); i++)
            temp.push_back(generated.at(count).at(i));
            
        temp.push_back(2);
        
        for (int i = 0; i < end.at(2) - 1; i++)
            newSeq1.pop();
        for (int i = 0; i < end.at(3) + 1; i++)
            newSeq2.pop();

        vector<double> temp2 = choose(newSeq1, newSeq2);
        for (int i = 0; i < temp2.size(); i++)
            temp.push_back(temp2.at(i));

        return temp;
    }
    //if sequence ended in 2
    else {
        queue<double> newSeq1 = seq1;
        queue<double> newSeq2 = seq2;

        int lastFoundOne = end.at(1);

        for (int i = lastFoundOne; i > 0; i--) {
            if (generated.at(count).at(i) == 1) {
                lastFoundOne = i;
                break;
            }
        }

        //number of 1 before lastFoundOne
        int oneToPop = 0;
        
        for(int i = 0; i < lastFoundOne; i++) {
            if (generated.at(count).at(i) == 1) {
                oneToPop ++;
            }
        }

        //number of 2 before lastFoundOne
        int twoToPop = 0;
        
        for(int i = 0; i < lastFoundOne; i++) {
            if (generated.at(count).at(i) == 2) {
                twoToPop ++;
            }
        }
        
        for (int i = 0; i < lastFoundOne; i++)
            temp.push_back(generated.at(count).at(i));

        temp.push_back(2);

        // cout << "lastFoundOne: " << lastFoundOne << " oneToPop: " << oneToPop << " twotoPop: " << twoToPop << endl;
        
        for (int i = 0; i < oneToPop; i++)
            newSeq1.pop();
        for (int i = 0; i < twoToPop + 1; i++)
            newSeq2.pop();

        vector<double> temp2 = choose(newSeq1, newSeq2);
        for (int i = 0; i < temp2.size(); i++)
            temp.push_back(temp2.at(i));

        return temp;
    }
}

void algorithm(vector< vector<double> > possible, vector< vector<double> > generated, queue<double> seq1, queue<double> seq2, queue<double> target) {

    int comb = combination(seq1.size(), seq2.size()) / 2;

    //Initialization
    generated.push_back(choose(seq1, seq2));
    // for (int i = 0; i < target.size(); i++) 
    //     cout << generated.at(0).at(i) << ' ';
    // cout << endl;
    vector<double> end = checkEnd(generated.at(0), target);
    //cout << "end: " << end.at(0) << " position: " << end.at(1) << " countOne: " << end.at(2) << " countTwo: " << end.at(3) << endl;
    generated.push_back(algorithmDynamic(generated, seq1, seq2, target, end, 0));

    //Combination 1 (first half that starts with 1)
    for (int i = 0; i < comb - 1; i++) {
        // for (int j = 0; j < target.size(); j++) 
        //     cout << generated.at(i+1).at(j) << ' ';
        // cout << endl;
        end = checkEnd(generated.at(i+1), target);
        //cout << "end: " << end.at(0) << " position: " << end.at(1) << " countOne: " << end.at(2) << " countTwo: " << end.at(3) << endl;
        generated.push_back(algorithmDynamic(generated, seq1, seq2, target, end, i+1));
    }

    generated.pop_back();

    //Combination 2: reverse of combination 1 (second half that starts with 2)
    for (int i = 0; i < comb+1; i++) {
        vector<double> temp;
        for (int j = 0; j < target.size(); j++) {
            if (generated.at(i).at(j) == 1)
                temp.push_back(2);
            else
                temp.push_back(1);
        }
        generated.push_back(temp);
    }

    //print generated for testing
    // cout << "////////////////////////////////////////" << endl;
    for (int i = 0; i < 2*comb; i++) {
        for (int j = 0; j < target.size(); j++)
            cout << generated.at(i).at(j) << ' ';
        cout << endl;
    }





    for (int i = 0; i < 2*comb; i++) {
        vector<double> temp;
        queue<double> seq1Copy = seq1;
        queue<double> seq2Copy = seq2;

        for (int j = 0; j < target.size(); j++) {
            if (generated.at(i).at(j) == 1) {
                temp.push_back(seq1Copy.front());
                seq1Copy.pop();
            }
            else {
                temp.push_back(seq2Copy.front());
                seq2Copy.pop();
            }
        }
        possible.push_back(temp);
    }

    //print possible for testing
    cout << "////////////////////////////////////////" << endl;
    for (int i = 0; i < 2*comb; i++) {
        for (int j = 0; j < target.size(); j++)
            cout << possible.at(i).at(j) << ' ';
        cout << endl;
    }
    
    vector<double> answer;
    double score = 0;
    int index;
    int count = 0;

    cout << "////////////////////////////////////////" << endl;

    for (int i = 0; i < 2*comb; i++) {
        queue<double> targetCopy = target;
        double sum = 0;

        for (int j = 0; j < target.size(); j++) {
            sum += possible.at(i).at(j) * targetCopy.front();
            cout << sum << ' ';
            targetCopy.pop();
        }
        cout << endl;
        
        if (sum > score) {
            score = sum;
            index = count;
        }
        count++;
    }

    for (int i = 0; i < target.size(); i++) {
        answer.push_back(possible.at(index).at(i));
    }

    writeOutput(score, answer);

}
