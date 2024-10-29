#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3) {
       return 0;
    }

    //////////// read the input file /////////////
    
    char buffer[200];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    fin.getline(buffer,200);
    fin.getline(buffer,200);
    int vertice, start, end, junk;
    fin >> vertice;
    int num_chords = vertice/2;
    vector<int> C(vertice, -1); // store the chords, index is the end, value is the start, -1 means no chord
    for(int i = 0; i < num_chords; i++) {
        fin >> start >> end;
        C[end] = start;
    }
    fin >> junk; // should be 0
    
    //////////// the algorithm part ////////////////
    vector<vector<int>> M; // dp table
    vector<int> used_chords; // store the used chords
    for(int i = 0; i < vertice; i++) {
        vector<int> temp;
        for(int j = 0; j < vertice; j++) {
            temp.push_back(0);
        }
        M.push_back(temp);
    }

    for(int l = 1; l < vertice; l++) {
        for(int i = 0; i < vertice - l; i++) {
            int j = i + l;
            int k = C[j];
            if(k > i && k < j){
                M[i][j] = M[i][j-1];
            }
            else if (k == i){
                M[i][j] = M[i+1][j-1] + 1;
                used_chords.push_back(j);
            }
            else {
                if(M[i][j-1] > M[i][k-1] + M[k+1][j-1] + 1)
                    M[i][j] = M[i][j-1];
                else{
                    M[i][j] = M[i][k-1] + M[k+1][j-1] + 1;
                    used_chords.push_back(j);
                }
            }
        }
    }


    //////////// write the output file ///////////
    fout << M[0][vertice-1] << endl;
    for(int i = 0; i < used_chords.size(); i++) {
        fout << C[used_chords[i]] << " " << used_chords[i] << endl;
    }
    fin.close();
    fout.close();
    return 0;
}