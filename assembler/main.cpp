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

/* This is the main print function that utilizes all the functions above it to print out the assembled instructions */
void printFile() //This function prints to file.
{

    ofstream oFile;
    oFile.open("f.txt");

    //First we want to print out the header of the file.
    oFile << "WIDTH=32;" << endl;
    oFile << "DEPTH=256;" << endl;
    oFile << endl;
    oFile << "ADDRESS_RADIX=HEX;" << endl;
    oFile << "DATA_RADIX=HEX;" << endl;
    oFile << endl;
    oFile << "CONTENT BEGIN" << endl;

    int lineCounter = 0; //The line counter records the line address count.
    int numberOfSymbols = symbols.size(); //This is the number of symbols we parsed from the assembly file.
    int symbolCounter = 0; //Whenever we iterate through the symbols vector we want to keep count as to not overflow.
    string instruction; //This string holds the final instruction in HEX for printing.
    int labelsCounter = 0; //We keep a count of the labels we find in the symbols vector.

    for(int i = 0; i < numberOfSymbols; i++) //1st pass through symbols list to see if there are any labels, to record their addresses.
    {
        firstPass(numberOfSymbols, symbolCounter, lineCounter, labelsCounter);
    }

    symbolCounter = 0; //Reset symbolCounter and lineCounter to be used in the second pass.
    lineCounter = 0;

    for(int i = 0; i < 255; i++) //2nd pass goes through the symbol list and starts concatenating the correct string/instruction.
    {

        if((symbolCounter == numberOfSymbols) && (lineCounter != 255))
        {
            oFile << "   [";
            oFile << setw(3) << setfill('0') << hex << lineCounter;
            oFile << "..";
            oFile << setw(3) << setfill('0') << hex << 255;
            oFile << "]" << "  :   00000000;" << endl;
            break;
        }

        oFile << "   ";
        oFile << setw(3) << setfill('0') << hex << lineCounter << "  :   ";
        instruction = symbolPrint(i,numberOfSymbols, symbolCounter, labelsCounter, lineCounter);
        oFile << instruction << ";" << endl;

    }
    oFile << endl;
    oFile << "END;";
    oFile.close();

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