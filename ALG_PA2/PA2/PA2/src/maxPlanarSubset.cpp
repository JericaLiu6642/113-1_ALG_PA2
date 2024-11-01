/*
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <set>
#include <sys/resource.h> // For memory usage on Linux/macOS

using namespace std;

// Function to get memory usage in KB on Linux/macOS
long getMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // Returns memory usage in KB
}

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

int topdown(vector<vector<int>>& M, const vector<int>& C, int i, int j, int vertice)
{
    if (i >= j) return 0;
    if (M[i][(vertice - 1) - j] != 0) return M[i][(vertice - 1) - j];

    int k = C[j];
    if (k < i || k > j) {
        M[i][(vertice - 1) - j] = topdown(M, C, i, j - 1, vertice);
    }
    else if (k == i) {
        M[i][(vertice - 1) - j] = topdown(M, C, i + 1, j - 1, vertice) + 1;
    }
    else {
        M[i][(vertice - 1) - j] = max(topdown(M, C, i, j - 1, vertice), topdown(M, C, i, k - 1, vertice) + topdown(M, C, k + 1, j, vertice) + 1);
    }

    return M[i][(vertice - 1) - j];
}

int main(int argc, char* argv[]) {

    if(argc != 3) {
       cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
       return 1;
    }

    // Start measuring time
    auto start = chrono::high_resolution_clock::now();

    //////////// read the input file /////////////
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    int vertice, s, e, junk;
    fin >> vertice;
    int num_chords = vertice / 2;
    vector<int> C(vertice, -1); // store the chords, index is the end, value is the start, -1 means no chord
    
    for(int i = 0; i < num_chords; i++) {
        fin >> s >> e;
        C[e] = s;
        C[s] = e;
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
    
    
    topdown(M, C, 0, vertice - 1, vertice);


    // Traceback to find the actual chords in the maximum planar subset
    set<pair<int, int>> result;
    traceback(M, C, 0, vertice - 1, result, vertice);

    //////////// write the output file ///////////
    fout << M[0][0] << endl;
    for (const auto& p : result) {
        fout << p.first << " " << p.second << endl;
    }

    // Stop measuring time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Measure memory usage
    long memory_usage_kb = getMemoryUsage();
    double memory_usage_mb = memory_usage_kb / 1024.0; // Convert KB to MB

    // Print time and memory usage
    cout << "Total running time: " << elapsed.count() << " seconds" << endl;
    cout << "Total memory usage: " << memory_usage_mb << " MB" << endl;

    fin.close();
    fout.close();
    return 0;
}*/

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <set>
#include <sys/resource.h> // For memory usage on Linux/macOS

using namespace std;

// Function to get memory usage in KB on Linux/macOS
long getMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // Returns memory usage in KB
}

// Recursive function to trace back the solution
void traceback(const vector<int>& M, const vector<int>& C, int i, int j, set<pair<int, int>>& result, int vertice) {
    if (i >= j) return; // Base case: no chords in this range
    
    int k = C[j];
    int index = ((2 * vertice - i - 1) * i) / 2 + j - i;
    
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
        int index_j_minus_1 = ((2 * vertice - i - 1) * i) / 2 + j - 1 - i;
        if (M[index] == M[index_j_minus_1]) {
            traceback(M, C, i, j - 1, result, vertice);
        }
        else {
            result.insert({k, j});
            traceback(M, C, i, k - 1, result, vertice);
            traceback(M, C, k + 1, j, result, vertice);
        }
    }
}

int topdown(vector<int>& M, const vector<int>& C, int i, int j, int vertice)
{
    if (i >= j) return 0;
    int index = ((2 * vertice - i - 1) * i) / 2 + j - i;
    if (M[index] != 0) return M[index];

    int k = C[j];
    if (k < i || k > j) {
        M[index] = topdown(M, C, i, j - 1, vertice);
    }
    else if (k == i) {
        M[index] = topdown(M, C, i + 1, j - 1, vertice) + 1;
    }
    else {
        M[index] = max(topdown(M, C, i, j - 1, vertice), topdown(M, C, i, k - 1, vertice) + topdown(M, C, k + 1, j, vertice) + 1);
    }

    return M[index];
}

int main(int argc, char* argv[]) {

    if(argc != 3) {
       cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
       return 1;
    }

    // Start measuring time
    auto start = chrono::high_resolution_clock::now();

    //////////// read the input file /////////////
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    int vertice, s, e, junk;
    fin >> vertice;
    int num_chords = vertice / 2;
    vector<int> C(vertice, -1); // store the chords, index is the end, value is the start, -1 means no chord
    
    for(int i = 0; i < num_chords; i++) {
        fin >> s >> e;
        C[e] = s;
        C[s] = e;
    }
    fin >> junk; // should be 0

    //////////// the algorithm part ////////////////
    int size = (vertice * (vertice + 1)) / 2;
    vector<int> M(size, 0); // dp table

    topdown(M, C, 0, vertice - 1, vertice);

    // Traceback to find the actual chords in the maximum planar subset
    set<pair<int, int>> result;
    traceback(M, C, 0, vertice - 1, result, vertice);

    //////////// write the output file ///////////
    fout << M[vertice - 1] << endl;
    for (const auto& p : result) {
        fout << p.first << " " << p.second << endl;
    }

    // Stop measuring time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Measure memory usage
    long memory_usage_kb = getMemoryUsage();
    double memory_usage_mb = memory_usage_kb / 1024.0; // Convert KB to MB

    // Print time and memory usage
    cout << "Total running time: " << elapsed.count() << " seconds" << endl;
    cout << "Total memory usage: " << memory_usage_mb << " MB" << endl;

    fin.close();
    fout.close();
    return 0;
}

