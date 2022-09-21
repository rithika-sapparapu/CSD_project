#include <bits/stdc++.h>
using namespace std;

//This struct is helpful for tying labels to their address for branch and jump instructions
struct Labels{
  string name;
  int address;
};

vector<Labels> label;

int tokenSize = 0; //The size of the tokenized original assembly file.
char token; //token holder.
vector<char> tokens; //Vector of tokens taken from the original file.
vector<string> symbols; //Vectr of symbols.


/* Converts hex values to binary values (strings only) */
string hex2bin(string hexString)
{
    stringstream temp;
    temp << hex << hexString;
    unsigned n;
    temp >> n;
    bitset<16> b(n);

    return b.to_string();
}

/* Converts  binary values to hex values (strings only) */
string bin2hex(string binString)
{
    string hexString;
    bitset<32> b(binString);
    unsigned n = b.to_ulong();
    stringstream temp;
    temp << hex << setfill('0') << setw(8) << n;
    hexString = temp.str();
    transform(hexString.begin(), hexString.end(), hexString.begin(), ::toupper);
    return hexString;

}

/* Converts decimal values to hex values (Outputs a string) */
string dec2bin(int value)
{
    stringstream ht;
    ht << hex << value;

    stringstream bt;
    bt << hex << ht.str();
    unsigned n;
    bt >> n;
    bitset<16> b(n);

    return b.to_string();
}

void openFile(char *filename){
    ifstream file;
    file.open(filename);

    if(!file.is_open()){ //If the file does not exist the program crashes.
        cout << "FILE DOES NOT EXIST/FAILED TO OPEN FILE!" << endl;
        exit(EXIT_FAILURE);
    }

    else{
        int i = 0;
        char temp;

        while (!file.eof()){
            file.get(temp);
            tokens.push_back(temp);
            i++;
            tokenSize++;
        }
        i = 0;
        tokenSize--;

        for(int i = 0; i < tokenSize; i++){
            // if(tokens[i] == '\n'){
            //     cout << "new line" << endl;
            // }
            cout << tokens[i] << "";
        }
        cout << endl;
        cout << "value of variable tokenSize" << tokenSize << endl;
    }
}

/* Checks for identifiers (lowercase symbols, ex: addi, lw, etc.) */
void identifiers(char &value, int &i){
    string temp;

    while(islower(value)){
        if(i == tokenSize){
            break;
        }
        temp += value;
        i++;
        value = tokens[i];
    }

    symbols.push_back(temp);
}

/* Checks for registers, knows if a register is being parsed a '$' symbol is encountered then records the number */
void registers(char &value, int &i){
    string temp;
    temp += value;
    i++;
    value = tokens[i];

    while(isdigit(value)){
        if(i == tokenSize){
            break;
        }
        temp += value;
        i++;
        value = tokens[i];
    }
    symbols.push_back(temp);
}

/* Checks for digits, digits are usually addressees or offsets, it disguishes between the two and records appropriate symbols */
void digits(char &value, int &i){
    string temp;
    if(value == '0' && tokens[i+1] == 'x'){
        i = i + 2;
    }
    if(value == '-'){
        temp = value;
        i = i + 1;
    }
    value = tokens[i];
    while(isdigit(value) || islower(value)){
        if(i == tokenSize){
            break;
        }

        temp += value;
        i++;
        value = tokens[i];
    }
    symbols.push_back(temp);
}


/* This function generates the symbol vector using the functions above it to distinguish between symbols */
void compareTokens() {//This function turns all tokens into symbols.
    for(int i = 0; i < tokenSize; i++){
            token = tokens[i];

            if(islower(token)){
                identifiers(token, i);
            }
            if(token == '$'){
                registers(token, i);
            }
            if(isdigit(token) || token == '-'){
                digits(token, i);
            }
    }
}

/* This is a function used for tests only use if you need to see the way the symbols were parsed */
void printSymbols(){
    for(int i = 0; i < symbols.size(); i++){
        cout << symbols[i] << endl;
    }
}


int main(int argc, char *argv[])
{
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    openFile(argv[1]);
    cout << "file open and parsed..." << endl;
    compareTokens();
    cout << "Tokens Compared..." << endl;
    printSymbols();
    cout << "Symbols Printed..." << endl;
    // printFile();
    // cout << "Assembled file created..." << endl;
    // return 0;
}