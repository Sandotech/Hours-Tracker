#include "User.h"
#include <sstream>

using namespace std;

static string trim(const string &s)
{
    size_t startPos = s.find_first_not_of(" \t\r\n");
    size_t endPos = s.find_last_not_of(" \t\r\n");
    if (startPos == string::npos)
        return "";
    return s.substr(startPos, endPos - startPos + 1);
}

User User::fromCsvLine(const string &line)
{
    stringstream lineStream(line);
    string rawUsername, rawPassword, rawFullName;
    getline(lineStream, rawUsername, ',');
    getline(lineStream, rawPassword, ',');
    getline(lineStream, rawFullName, ',');
    User userObj;
    userObj.username = trim(rawUsername);
    userObj.password = trim(rawPassword);
    userObj.fullName = trim(rawFullName);
    return userObj;
}

string User::toCsvLine() const
{
    return username + "," + password + "," + fullName;
}