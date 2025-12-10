#pragma once
#include <string>
#include <ctime>

using namespace std;

struct TimeEntry
{
    string username;
    int year;
    int isoWeek; // Semana ISO (1-53)
    int hours;   // Horas trabajadas
    string comment;
    static TimeEntry fromCsvLine(const string &line);
    string toCsvLine() const;

    static int currentYear();
    static int currentIsoWeek();
};