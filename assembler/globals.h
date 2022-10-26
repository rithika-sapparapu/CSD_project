#include <bits/stdc++.h>
using namespace std;

/* This struct is helpful for tying labels to their address for branch and jump instructions */
/* ----------------------------------------------------------------------------------------- */
struct Labels{
  string name;
  int address;
};

vector<Labels> label;
/* ----------------------------------------------------------------------------------------- */

int DEPTH = 256;

int tokenSize = 0; //The size of the tokenized original assembly file.
char token; //token holder.
vector<char> tokens; //Vector of tokens taken from the original file.
vector<string> symbols; //Vectr of symbols.