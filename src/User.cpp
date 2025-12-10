#include "User.h"
#include <sstream>

using namespace std;

static string trim(const string &s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

User User::fromCsvLine(const string &line)
{
    stringstream ss(line);
    string username, password, fullName;
    getline(ss, username, ',');
    getline(ss, password, ',');
    getline(ss, fullName, ',');
    User u;
    u.username = trim(username);
    u.password = trim(password);
    u.fullName = trim(fullName);
    return u;
}

string User::toCsvLine() const
{
    return username + "," + password + "," + fullName;
}