#include "CsvStorage.h"
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

CsvStorage::CsvStorage(const string &usersPath, const string &entriesPath)
    : usersPath_(usersPath), entriesPath_(entriesPath) {}

vector<User> CsvStorage::loadUsers() const
{
    vector<User> users;
    ifstream in(usersPath_);
    if (!in.is_open())
        return users;
    string line;
    if (in.peek() == ifstream::traits_type::eof())
        return users;
    getline(in, line);
    if (line.find("username,password,fullName") == string::npos)
    {
        users.push_back(User::fromCsvLine(line));
    }
    while (getline(in, line))
    {
        if (line.empty())
            continue;
        users.push_back(User::fromCsvLine(line));
    }
    return users;
}

bool CsvStorage::authenticate(const string &username, const string &password, User &outUser) const
{
    auto users = loadUsers();
    for (const auto &u : users)
    {
        if (u.username == username && u.password == password)
        {
            outUser = u;
            return true;
        }
    }
    return false;
}

bool CsvStorage::addUser(const User &user)
{
    bool newFile = !filesystem::exists(usersPath_);
    ofstream out(usersPath_, ios::app);
    if (!out.is_open())
        return false;
    if (newFile)
    {
        out << "username,password,fullName\n";
    }
    out << user.toCsvLine() << "\n";
    return true;
}

vector<TimeEntry> CsvStorage::loadEntries() const
{
    vector<TimeEntry> entries;
    ifstream in(entriesPath_);
    if (!in.is_open())
        return entries;
    string line;
    if (in.peek() == ifstream::traits_type::eof())
        return entries;
    getline(in, line);
    if (line.find("username,year,isoWeek,hours,comment") == string::npos)
    {
        entries.push_back(TimeEntry::fromCsvLine(line));
    }
    while (getline(in, line))
    {
        if (line.empty())
            continue;
        entries.push_back(TimeEntry::fromCsvLine(line));
    }
    return entries;
}

bool CsvStorage::addEntry(const TimeEntry &entry)
{
    bool newFile = !filesystem::exists(entriesPath_);
    ofstream out(entriesPath_, ios::app);
    if (!out.is_open())
        return false;
    if (newFile)
    {
        out << "username,year,isoWeek,hours,comment\n";
    }
    out << entry.toCsvLine() << "\n";
    return true;
}

vector<TimeEntry> CsvStorage::findEntriesByUserAndWeek(const string &username, int year, int isoWeek) const
{
    vector<TimeEntry> result;
    auto entries = loadEntries();
    for (const auto &e : entries)
    {
        if (e.username == username && e.year == year && e.isoWeek == isoWeek)
        {
            result.push_back(e);
        }
    }
    return result;
}

vector<TimeEntry> CsvStorage::findEntriesByUser(const string &username) const
{
    vector<TimeEntry> result;
    auto entries = loadEntries();
    for (const auto &e : entries)
    {
        if (e.username == username)
        {
            result.push_back(e);
        }
    }
    return result;
}