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

void openFile(char *filename)
{
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

int main(int argc, char *argv[])
{
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    openFile(argv[1]);
    cout << "file open and parsed..." << endl;
    return 0;
}