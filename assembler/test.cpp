#include <bits/stdc++.h>
using namespace std;

int main(){
    string temp_symbol = "5";
    string temp;
    string bin;

    signed decimal = atoi(temp_symbol.c_str());
    // cout << endl << "decimal " << decimal << endl; 

    stringstream ht;    //After finding it we increment the address and turn it into binary form.
    ht << hex << decimal;
    // cout << "ht " << ht << endl; 
    stringstream bt;
    bt << hex << ht.str();
    // cout << "bt " << bt << endl; 
    signed n;
    bt >> n;
    bitset<16> b(n);
    // cout << "b(n) " << b(n) << endl; 

    bin = b.to_string();
    temp = bin;
    cout << temp << endl;
    return 0;
}

