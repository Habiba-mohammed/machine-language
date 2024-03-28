// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#ifndef CPP_FILES_TASK3OOP_H
#define CPP_FILES_TASK3OOP_H

#include <bits/stdc++.h>
using namespace std;

class memory {
public:
    map<string, string> m;
    memory();
    void set_memory(const string& x, const string& y);
    void display_memory();
};

class Register {
public:
    Register();
    unordered_map<int, string> r;
    void display_Register();
};

class instructions {
public:
    instructions();
    vector<string> v;
};

class machine : public memory, public Register, public instructions {
private:
    string pc;

public:
    void set_instructions_into_memory();
    void execute();

    void Move_From_R_to_S(const string& XY) {
        string temp1 = "";
        temp1 += XY[0];
        string temp2 = "";
        temp2 += XY[1];
        int rr = stoi(temp1, nullptr, 16);
        int s = stoi(temp2, nullptr, 16);
        r[s] = r[rr];
    };

    void ADD(int R, const string& XY) {
        string temp1 = "";
        temp1 += XY[0];
        string temp2 = "";
        temp2 += XY[1];
        int rr = stoi(temp1, nullptr, 16);
        int s = stoi(temp2, nullptr, 16);

        int a1 = stoi(r[rr], nullptr, 16);
        int a2 = stoi(r[s], nullptr, 16);

        // Perform addition
        int sum = a1 + a2;

        // Convert the sum to a string in uppercase
        stringstream ss;
        ss << setw(2) << setfill('0') << hex << sum;
        string result = ss.str();

        // Convert the string to uppercase
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        r[R] = result;
    };

};

#endif //CPP_FILES_TASK3OOP_H
