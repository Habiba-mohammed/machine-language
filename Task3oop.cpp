// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Task3oop.h"
#include <bits/stdc++.h>
using namespace std ;



memory::memory(){
        for (int i = 0; i < 256; i++) {
            int x = i;
            // Convert decimal value to uppercase hexadecimal string
            std::stringstream stream;
            stream << hex << uppercase << x;  // Add std::uppercase
            string hexString = stream.str();
            while (hexString.length() < 2) {
                hexString.insert(0, "0"); } // memory cell turn to hexa
             m.emplace(hexString,"00"); // initialize them with 00 from the beginning
        }
}

void memory::set_memory(const string& x, const string& y) {
    m[x] = move(y);
}

void memory::display_memory(){
    for(auto &x:m){
        cout<<"memory address "<<x.first<<" has "<<x.second<<endl;
    }
}

Register::Register(){
    for(int i=0;i<16;i++){
        r.insert({i,"00"}); // all 16 registers now have "00"
    }
}

void Register::display_Register(){
    for(int i{0};i<16;i++){
        stringstream ss;
        ss << setw(2) << setfill('0') << hex << i;
        string s= ss.str();
        transform(s.begin(), s.end(), s.begin(), ::toupper);

        cout<<"Register "<<s<<" has "<<r[i]<<endl;
    }
}

instructions::instructions() {
    ifstream infile;
    infile.open("C:\\Users\\Abdelaziz Ali\\Desktop\\Task 3\\input.txt",ios::in);
    string line;

    while (getline(infile,line)&&!line.empty()){
        string t1="";
        t1+=line[2];// operand
        t1+=line[6]; // register
        string t2=""; // XY
        t2+=line[10];
        t2+=line[11];
        v.push_back(t1);
        v.push_back(t2);} // {t11,t12   t21,t22, ... } ( kol 2 wra b3d instruction }
        while(v.size()!=256){
            v.push_back("00");
        }
    infile.close();
}

void machine::set_instructions_into_memory(){ // assign memory cells its values
    int x=v.size();
    for(int i=0;i<x;i++){
        std::stringstream stream;
        stream << hex << uppercase << i;  // Add std::uppercase
        string hexString = stream.str();
        while (hexString.length() < 2) {
            hexString.insert(0, "0"); }
        string y=move(hexString);
        set_memory(y,v[i]);
    }
    //storage.display_memory();
}
void machine::execute() {
    int x=v.size();
    bool halt=false;
    for(int i{0}; i<x && !halt; i+=2){
        // get the program counter
        stringstream ss;
        ss << setw(2) << setfill('0') << hex << i;
         pc= ss.str();
        transform(pc.begin(), pc.end(), pc.begin(), ::toupper);

        // analyse the current instruction
        char operand=v[i][0];

        string temp="";
        temp+=(v[i][1]);
        int R=stoi(temp, nullptr, 16); // R in integer form <3

        string XY=v[i+1];


        // decode and execute :D
        switch (operand) {
            case '1':
                r[R] = m[XY]; // Put Memory cell XY in R
                break;
            case '2':
                //; //Put R in memory cell XY
                r[R]=XY;
                break;
            case '3':
                if(true){
                    m[XY] = r[R];
                    int index=stoi(XY,nullptr,16);
                    v[index]=r[R];
                }
                // change it in the vector too
                break;
            case '4':
              Move_From_R_to_S(XY); //RS
              break;
            case '5':
                ADD(R,XY);// R = X+Y
                break;
            case 'B':
                // Jump will only occur to a cell in the first part of an instruction
                // (imagine the second part was FF, doesn't make any sense, no F operand)
                if (r[R] == r[0]) {
                    i=stoi(XY,nullptr,16);// turn to decimal
                    i-=2; // because it will +2 at the end of the for loop so we cancel that effect by subtracting.
                }
                break;
            case 'C':
                // HALT instruction
                cout << "HALT\n";
                halt=true;
                break;
            default:
               cerr << "Unknown opcode: " << operand << "\n";
                halt=true;
                break;
        }

    }
    cout<<"The program counter's Memory cell right before HALT: "<<pc<<"\n";
   display_Register();
   display_memory();


    }



