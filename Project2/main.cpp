#include "helper.cpp"

int main() {
    string filename = "sample-input.txt";
    vector< queue<double> > setup;
    vector< vector<double> > generated;
    vector< vector<double> > possible;

    setup = readInput(filename);
    queue<double> seq1 = setup[0];
    queue<double> seq2 = setup[1];
    queue<double> target = setup[2];

    algorithm(possible, generated, seq1, seq2, target);

}
