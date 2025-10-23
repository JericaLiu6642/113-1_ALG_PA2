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

// Function to convert (i, j) indices to 1D index in upper triangular matrix
long long get1DIndex(int i, int j, int vertice) {
    return static_cast<long long>(i) * vertice - (static_cast<long long>(i) * (i + 1)) / 2 + (j - i);
}

// Recursive function to trace back the solution
void traceback(const vector<long long>& M, const vector<int>& C, int i, int j, set<pair<int, int>>& result, int vertice) {
    if (i >= j) return; // Base case: no chords in this range
    
    int k = C[j];
    long long index = get1DIndex(i, j, vertice);
    
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
        long long index_j_minus_1 = get1DIndex(i, j - 1, vertice);
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

long long topdown(vector<long long>& M, const vector<int>& C, int i, int j, int vertice) {
    if (i >= j) return 0;
    
    long long index = get1DIndex(i, j, vertice);
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

    if (argc != 3) {
       cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
       return 1;
    }

    // Start measuring time
    //auto start = chrono::high_resolution_clock::now();

    //////////// read the input file /////////////
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    int vertice, s, e, junk;
    fin >> vertice;
    int num_chords = vertice / 2;
    vector<int> C(vertice, -1); // store the chords, index is the end, value is the start, -1 means no chord
    
    for (int i = 0; i < num_chords; i++) {
        fin >> s >> e;
        C[e] = s;
        C[s] = e;
    }
    fin >> junk; // should be 0

    //////////// the algorithm part ////////////////
    long long matrix_size = static_cast<long long>(vertice) * (vertice + 1) / 2; // Number of elements in the upper triangular matrix
    vector<long long> M(matrix_size, 0); // dp table in 1D array form

    topdown(M, C, 0, vertice - 1, vertice);

    // Traceback to find the actual chords in the maximum planar subset
    set<pair<int, int>> result;
    traceback(M, C, 0, vertice - 1, result, vertice);

    //////////// write the output file ///////////
    fout << M[get1DIndex(0, vertice - 1, vertice)] << endl;
    for (const auto& p : result) {
        fout << p.first << " " << p.second << endl;
    }

    // // Stop measuring time
    // auto end = chrono::high_resolution_clock::now();
    // chrono::duration<double> elapsed = end - start;

    // // Measure memory usage
    // long memory_usage_kb = getMemoryUsage();
    // double memory_usage_mb = memory_usage_kb / 1024.0; // Convert KB to MB

    // // Print time and memory usage
    // cout << "Total running time: " << elapsed.count() << " seconds" << endl;
    // cout << "Total memory usage: " << memory_usage_mb << " MB" << endl;

    fin.close();
    fout.close();
    return 0;
}
