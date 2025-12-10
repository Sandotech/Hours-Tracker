#include "TimeEntry.h"
#include <sstream>
#include <iomanip>

using namespace std;

static string trim(const string &s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

TimeEntry TimeEntry::fromCsvLine(const string &line)
{
    stringstream ss(line);
    string username, yearStr, weekStr, hoursStr, comment;
    getline(ss, username, ',');
    getline(ss, yearStr, ',');
    getline(ss, weekStr, ',');
    getline(ss, hoursStr, ',');
    getline(ss, comment, ',');
    TimeEntry e;
    e.username = trim(username);
    e.year = stoi(trim(yearStr));
    e.isoWeek = stoi(trim(weekStr));
    e.hours = stoi(trim(hoursStr));
    e.comment = trim(comment);
    return e;
}

string TimeEntry::toCsvLine() const
{
    stringstream ss;
    ss << username << "," << year << "," << isoWeek << "," << hours << "," << comment;
    return ss.str();
}

static int isoWeekNumber(tm tm)
{
    tm.tm_hour = 12;
    tm.tm_min = 0;
    tm.tm_sec = 0;

    std::time_t t = std::mktime(&tm);
    std::tm *ptm = std::localtime(&t);
    int wday = ptm->tm_wday;
    int isoWday = (wday == 0) ? 7 : wday;
    int deltaToThursday = 4 - isoWday;
    t += deltaToThursday * 24 * 60 * 60;
    std::tm thursday = *std::localtime(&t);
    int y = thursday.tm_year + 1900;

    std::tm firstJan{};
    firstJan.tm_year = y - 1900;
    firstJan.tm_mon = 0;
    firstJan.tm_mday = 1;
    firstJan.tm_hour = 12;
    firstJan.tm_min = 0;
    firstJan.tm_sec = 0;
    std::mktime(&firstJan);
    int firstWday = firstJan.tm_wday;
    int firstIsoWday = (firstWday == 0) ? 7 : firstWday;
    int daysToFirstThursday = (4 - firstIsoWday + 7) % 7;
    std::time_t firstThursdayTime = std::mktime(&firstJan) + daysToFirstThursday * 24 * 60 * 60;
    std::tm firstThursday = *std::localtime(&firstThursdayTime);

    int diffDays = static_cast<int>(std::difftime(std::mktime(&thursday), std::mktime(&firstThursday)) / (24 * 60 * 60));
    int week = 1 + diffDays / 7;
    return week;
}

int TimeEntry::currentYear()
{
    std::time_t t = std::time(nullptr);
    std::tm *ptm = std::localtime(&t);
    return ptm->tm_year + 1900;
}

int TimeEntry::currentIsoWeek()
{
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    return isoWeekNumber(tm);
}