#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <iomanip>

using namespace std;

// Recursive function to trace back the solution
void traceback(const vector<vector<int>>& M, const vector<int>& C, int i, int j, set<pair<int, int>>& result, int vertice) {
    if (i >= j) return; // Base case: no chords in this range
    
    int k = C[j];
    
    if (k < i || k > j) {
        // No chord for `j`, so move to the previous position
        traceback(M, C, i, j - 1, result, vertice);
    }
    else if (k == i) {
        // Chord between i and j is part of the subset
        result.insert({i, j});
        traceback(M, C, i + 1, j - 1, result, vertice); // Move inside
    }
    else {
        // Decision point: choose the maximum subset
        if (M[i][(vertice - 1) -j] == M[i][(vertice - 1) - (j - 1)]) {
            traceback(M, C, i, j - 1, result, vertice);
        }
        else {
            result.insert({k, j});
            traceback(M, C, i, k - 1, result, vertice);
            traceback(M, C, k + 1, j, result, vertice);
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
       cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
       return 1;
    }

    //////////// read the input file /////////////
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    int vertice, start, end, junk;
    fin >> vertice;
    int num_chords = vertice / 2;
    vector<int> C(vertice, -1); // store the chords, index is the end, value is the start, -1 means no chord
    
    for(int i = 0; i < num_chords; i++) {
        fin >> start >> end;
        C[end] = start;
        C[start] = end;
    }
    fin >> junk; // should be 0

    //////////// the algorithm part ////////////////
    vector<vector<int>> M; // dp table

    // need the dp table to be a upper left triangle matrix
    for(int i = vertice ; i >= 1; i--){
        vector<int> row(i, 0);
        M.push_back(row);
    }

    for(int l = 1; l < vertice; l++) {
        for(int i = 0; i < vertice - l; i++) {
            int j = i + l;
            int k = C[j];
            if (k < i || k > j) { // if the chord is not in the range
                M[i][(vertice - 1) - j] = M[i][(vertice - 1) - (j - 1)];
            }
            else if (k == i) { // if the chord is the first chord
                M[i][(vertice - 1) - j] = M[i+1][(vertice - 1) - (j - 1)] + 1;
            }
            else { // if the chord is in the range
                M[i][(vertice - 1) - j] = max(M[i][(vertice - 1) - (j - 1)], M[i][(vertice - 1) - (k - 1)] + M[k + 1][(vertice - 1) - j] + 1);
            }
        }
    }

    // print the dp table
    /*
    for(int i = 0; i < vertice; i++) {
        for(int j = 0; j < vertice; j++) {
            if(j + i >= vertice) {
                cout << setw(3) << " ";
            } else {
                cout << setw(3) << M[i][j];
            }
        }
        cout << endl;
    }
    */


    // Traceback to find the actual chords in the maximum planar subset
    set<pair<int, int>> result;
    traceback(M, C, 0, vertice - 1, result, vertice);

    //////////// write the output file ///////////
    fout << M[0][0] << endl;
    for (const auto& p : result) {
        fout << p.first << " " << p.second << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
