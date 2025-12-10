#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "CsvStorage.h"

using namespace std;

static void printEntries(const vector<TimeEntry> &entries)
{
    if (entries.empty())
    {
        cout << "No hay registros.\n";
        return;
    }
    cout << "Registros:\n";
    for (const auto &e : entries)
    {
        cout << "- Usuario: " << e.username
             << " | Año: " << e.year
             << " | Semana ISO: " << e.isoWeek
             << " | Horas: " << e.hours
             << " | Comentario: " << e.comment << "\n";
    }
}

static int askInt(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        else
        {
            cout << "Entrada inválida. Intenta nuevamente.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main()
{
    const string usersCsv = "users.csv";
    const string entriesCsv = "entries.csv";
    CsvStorage storage(usersCsv, entriesCsv);

    cout << "=== Registro de Horas Freelance (C++) ===\n";
    User currentUser;
    while (true)
    {
        cout << "\n1) Iniciar sesión\n2) Registrar nuevo usuario\n0) Salir\nSelecciona una opción: ";
        int option;
        if (!(cin >> option))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (option == 1)
        {
            string username, password;
            cout << "Usuario: ";
            getline(cin, username);
            cout << "Contraseña: ";
            getline(cin, password);
            if (storage.authenticate(username, password, currentUser))
            {
                cout << "Bienvenido, " << currentUser.fullName << "!\n";
                break;
            }
            else
            {
                cout << "Usuario o contraseña incorrectos.\n";
            }
        }
        else if (option == 2)
        {
            string username, password, fullName;
            cout << "Nuevo usuario: ";
            getline(cin, username);
            cout << "Nueva contraseña: ";
            getline(cin, password);
            cout << "Nombre completo: ";
            getline(cin, fullName);
            User u{username, password, fullName};
            if (storage.addUser(u))
            {
                cout << "Usuario registrado correctamente.\n";
            }
            else
            {
                cout << "Error al registrar usuario.\n";
            }
        }
        else if (option == 0)
        {
            cout << "Hasta luego.\n";
            return 0;
        }
        else
        {
            cout << "Opción inválida.\n";
        }
    }

    // Menú principal
    while (true)
    {
        cout << "\n=== Menú Principal ===\n"
             << "1) Registrar horas de la semana actual\n"
             << "2) Registrar horas de una semana específica\n"
             << "3) Consultar mis registros (todas las semanas)\n"
             << "4) Consultar mis registros por semana\n"
             << "0) Salir\n"
             << "Selecciona una opción: ";
        int option;
        if (!(cin >> option))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (option == 1)
        {
            int year = TimeEntry::currentYear();
            int week = TimeEntry::currentIsoWeek();
            int hours = askInt("Horas trabajadas: ");
            string comment;
            cout << "Comentario: ";
            getline(cin, comment);
            TimeEntry entry{currentUser.username, year, week, hours, comment};
            if (storage.addEntry(entry))
            {
                cout << "Registro guardado para Año " << year << ", Semana " << week << ".\n";
            }
            else
            {
                cout << "Error al guardar el registro.\n";
            }
        }
        else if (option == 2)
        {
            int year = askInt("Año (YYYY): ");
            int week = askInt("Semana ISO (1-53): ");
            int hours = askInt("Horas trabajadas: ");
            string comment;
            cout << "Comentario: ";
            getline(cin, comment);
            TimeEntry entry{currentUser.username, year, week, hours, comment};
            if (storage.addEntry(entry))
            {
                cout << "Registro guardado para Año " << year << ", Semana " << week << ".\n";
            }
            else
            {
                cout << "Error al guardar el registro.\n";
            }
        }
        else if (option == 3)
        {
            auto entries = storage.findEntriesByUser(currentUser.username);
            printEntries(entries);
        }
        else if (option == 4)
        {
            int year = askInt("Año (YYYY): ");
            int week = askInt("Semana ISO (1-53): ");
            auto entries = storage.findEntriesByUserAndWeek(currentUser.username, year, week);
            printEntries(entries);
        }
        else if (option == 0)
        {
            cout << "Hasta luego.\n";
            break;
        }
        else
        {
            cout << "Opción inválida.\n";
        }
    }

    return 0;
}