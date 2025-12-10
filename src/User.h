#pragma once
#include <string>

using namespace std;

struct User
{
    string username;
    string password;
    string fullName;

    static User fromCsvLine(const string &line);
    string toCsvLine() const;
};