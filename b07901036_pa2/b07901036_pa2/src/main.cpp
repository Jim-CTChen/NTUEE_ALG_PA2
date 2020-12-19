#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int endpoints = 0; // total amount of chords
int chord_set[100000];
int** M;
uint8_t** R;
vector<int> final_vec;

void trace_back_M(int i, int j) {
  if (M[i][j] != -1) return;
  if (i >= j) {
    M[i][j] = 0;
    return;
  } 
  int k = chord_set[j];
  if (k > j || k < i) {
    trace_back_M(i, j-1);
    M[i][j] = M[i][j-1];
  }
  else if (k == i) {
    trace_back_M(i, j-1);
    M[i][j] = M[i][j-1]+1;
    R[i][j] = 1;
  }
  else {
    int a, b;
    trace_back_M(i, j-1);
    trace_back_M(i, k-1);
    trace_back_M(k+1, j-1);
    a = M[i][j-1];
    b = M[i][k-1] + M[k+1][j-1] + 1;
    if (b > a) {
      M[i][j] = b;
      R[i][j] = 2;
    }
    else M[i][j] = a;
  }
}

void trace_back_R(int i, int j) {
  if (i >= j) return;
  switch (R[i][j])
  {
    case 0:
      trace_back_R(i, j-1);
      break;
    case 1:
      final_vec.push_back(i);
      trace_back_R(i, j-1);
      break;
    case 2:
      int k = chord_set[j];
      final_vec.push_back(k);
      trace_back_R(i, k-1);
      trace_back_R(k+1, j-1);
      break;
  }
}

int main(int argc, char* argv[])
{
  string in_file = argv[1];
  string out_file = argv[2];
  ifstream infile(in_file);
  ofstream outfile(out_file);

  infile >> endpoints;

  for (int i = 0; i < endpoints/2; i++) {
    int n1, n2;
    infile >> n1 >> n2;
    chord_set[n1] = n2;
    chord_set[n2] = n1;
  }

  M = new int*[endpoints];
  R = new uint8_t*[endpoints];
  for (int i = 0; i < endpoints; ++i) {
    M[i] = new int[endpoints];
    R[i] = new uint8_t[endpoints];
    for (int j = 0; j < endpoints; ++j) {
      M[i][j] = -1;
    }
  }

  trace_back_M(0, endpoints-1);
  trace_back_R(0, endpoints-1);

  sort(final_vec.begin(), final_vec.end());

  outfile << final_vec.size() << endl;
  for (auto& it : final_vec) {
    outfile << it << " " << chord_set[it] << endl;
  }
  
}