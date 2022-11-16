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

int tokenSize = 0; //The size of the tokenized textfile assembly file.
int tSize = 0;
int tokenSize_data = 0;
char token; //token holder.
vector<char> dataTokens; 
vector<char> textTokens; 
vector<char> tokens; //Vector of tokens taken from the original file.
vector<string> symbols; //Vectr of symbols.
vector<string> data_symbols;

//struct used for lebels in .data section
struct data_label{
  string name;
  string type;
  vector <string> values;
  int offsetBytes_forLbales;
};

vector<data_label> dataLabels;