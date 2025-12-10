#pragma once
#include <string>

using namespace std;

struct User
{
    string username;
    string password; // Para simplicidad: texto plano. En producción usar hash.
    string fullName;

    static User fromCsvLine(const string &line);
    string toCsvLine() const;
};