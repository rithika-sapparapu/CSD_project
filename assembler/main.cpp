#include <bits/stdc++.h>
using namespace std;

//This struct is helpful for tying tags to their address for branch and jump instructions
struct tags{
  string name;
  int address;
};

vector<tags> tag;

int tokenSize = 0; //The size of the tokenized original assembly file.
char token; //token holder.
vector<char> tokens; //Vector of tokens taken from the original file.
vector<string> symbols; //Vectr of symbols.

//-------------------------------------------------------------------------------------------------------------------
void openFile(char *filename){
    ifstream file;
    file.open(filename);

    if(!file.is_open()){ //If the file does not exist the program crashes.
        cout << "Failed to open the file." << endl;
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
/*
        for(int i = 0; i < tokenSize; i++){
            // if(tokens[i] == '\n'){
            //     cout << "new line" << endl;
            // }
            cout << tokens[i] << "";
        }
        cout << endl;
        cout << "value of variable tokenSize" << tokenSize << endl;
*/
    }
}

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
//-------------------------------------------------------------------------------------------------------------------

/* The firstPass function runs through the symbol list and records all tags and their addresses */
void firstPass(int &numberOfSymbols, int &symbolsCounter, int &lineCounter, int &tagsCounter) {//This function looks through all symbols to find tags.
    if(numberOfSymbols == symbolsCounter){
        return;
    }
    string temp_symbol = symbols[symbolsCounter];

    if(temp_symbol == "add")    symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "addi") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "addiu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "addu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "and") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "andi") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "beq") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "bne") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "j") symbolsCounter = symbolsCounter + 2;
    else if(temp_symbol == "jal") symbolsCounter = symbolsCounter + 2;
    else if(temp_symbol == "jr") symbolsCounter = symbolsCounter + 2;
    else if(temp_symbol == "lbu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "lhu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "lui") symbolsCounter = symbolsCounter + 3;
    else if(temp_symbol == "lw") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "nor") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "or") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "ori") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "slt") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "slti") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sltiu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sltu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sll") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "srl") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sb") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sh") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sw") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sub") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "subu") symbolsCounter = symbolsCounter + 4;
    else{
            //If a tag is found that isn't an instruction is probably is a tag and is recorded.
            tags newtag; //We create a new tags object.
            newtag.name = temp_symbol; //We store the name of the tag.
            newtag.address = lineCounter; //We store the lineCounter (address in decimal).
            tag.push_back(newtag); //Then we push the object into a vector for storage.
            //We do not increment lineCounter because a tag is just a placeholder for the next instruction's address not it's own.
            tagsCounter++; //We increment the tags counter keeping track of the size of our vector.
            symbolsCounter++; //We increment symbolsCounter because the tag is a symbol in our symbols vector.
            lineCounter++;
            return;
    }
    lineCounter++;
}

void printFile(){
    int lineCounter = 0; //The line counter records the line address count.
    int numberOfSymbols = symbols.size(); //This is the number of symbols we parsed from the assembly file.
    int symbolCounter = 0; //Whenever we iterate through the symbols vector we want to keep count as to not overflow.
    string instruction; //This string holds the final instruction in HEX for printing.
    int tagsCounter = 0; //We keep a count of the tags we find in the symbols vector.

    for(int i = 0; i < numberOfSymbols; i++){ //1st pass through symbols list to see if there are any tags, to record their addresses.
        firstPass(numberOfSymbols, symbolCounter, lineCounter, tagsCounter);
    }
    cout << setw(23) <<  "SYMBOL TABLE" << endl;
    cout << setw(15) << "tag" << setw(10) << "ADDRESS" << endl;

    for(int i=0; i<tag.size()-1; i++){
        cout << setw(15) << tag[i].name << setw(10) << tag[i].address +1<< endl;
    }
}

int main(int argc, char *argv[]){
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    openFile(argv[1]);
    compareTokens();
    printFile();
    return 0;
}