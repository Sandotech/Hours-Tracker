#include "CsvStorage.h"
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

CsvStorage::CsvStorage(const std::string &usersPath, const std::string &entriesPath)
    : usersPath_(usersPath), entriesPath_(entriesPath) {}

std::vector<User> CsvStorage::loadUsers() const
{
    std::vector<User> users;
    std::ifstream in(usersPath_);
    if (!in.is_open())
        return users;
    std::string line;
    // Saltar encabezado si existe
    if (in.peek() == std::ifstream::traits_type::eof())
        return users;
    std::getline(in, line);
    if (line.find("username,password,fullName") == std::string::npos)
    {
        // La primera línea es un usuario real, procesarla
        users.push_back(User::fromCsvLine(line));
    }
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;
        users.push_back(User::fromCsvLine(line));
    }
    return users;
}

bool CsvStorage::authenticate(const std::string &username, const std::string &password, User &outUser) const
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
    bool newFile = !std::filesystem::exists(usersPath_);
    std::ofstream out(usersPath_, std::ios::app);
    if (!out.is_open())
        return false;
    if (newFile)
    {
        out << "username,password,fullName\n";
    }
    out << user.toCsvLine() << "\n";
    return true;
}

std::vector<TimeEntry> CsvStorage::loadEntries() const
{
    std::vector<TimeEntry> entries;
    std::ifstream in(entriesPath_);
    if (!in.is_open())
        return entries;
    std::string line;
    if (in.peek() == std::ifstream::traits_type::eof())
        return entries;
    std::getline(in, line);
    if (line.find("username,year,isoWeek,hours,comment") == std::string::npos)
    {
        entries.push_back(TimeEntry::fromCsvLine(line));
    }
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;
        entries.push_back(TimeEntry::fromCsvLine(line));
    }
    return entries;
}

bool CsvStorage::addEntry(const TimeEntry &entry)
{
    bool newFile = !std::filesystem::exists(entriesPath_);
    std::ofstream out(entriesPath_, std::ios::app);
    if (!out.is_open())
        return false;
    if (newFile)
    {
        out << "username,year,isoWeek,hours,comment\n";
    }
    out << entry.toCsvLine() << "\n";
    return true;
}

std::vector<TimeEntry> CsvStorage::findEntriesByUserAndWeek(const std::string &username, int year, int isoWeek) const
{
    std::vector<TimeEntry> result;
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

std::vector<TimeEntry> CsvStorage::findEntriesByUser(const std::string &username) const
{
    std::vector<TimeEntry> result;
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