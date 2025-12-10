#pragma once
#include <string>
#include <vector>
#include "User.h"
#include "TimeEntry.h"

using namespace std;

class CsvStorage
{
public:
    explicit CsvStorage(const string &usersPath, const string &entriesPath);

    vector<User> loadUsers() const;
    bool authenticate(const string &username, const string &password, User &outUser) const;
    bool addUser(const User &user);

    vector<TimeEntry> loadEntries() const;
    bool addEntry(const TimeEntry &entry);
    vector<TimeEntry> findEntriesByUserAndWeek(const string &username, int year, int isoWeek) const;
    vector<TimeEntry> findEntriesByUser(const string &username) const;

private:
    string usersPath_;
    string entriesPath_;
};