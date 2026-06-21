#ifndef UTILS_H
#define UTILS_H
//  Utils.h - functii ajutatoare folosite in tot proiectul
//  (culori pentru consola, validari de input, curatare ecran)
//  Modul comun: validarea capacitatii apartine Persoanei A,
//  validarea datei si a intervalului orar apartine Persoanei B.


#include <string>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cctype>

// --- Culori ANSI pentru consola---
inline constexpr const char* RESET   = "\033[0m";
inline constexpr const char* RED     = "\033[31m";
inline constexpr const char* GREEN   = "\033[32m";
inline constexpr const char* YELLOW  = "\033[33m";
inline constexpr const char* BLUE    = "\033[34m";
inline constexpr const char* MAGENTA = "\033[35m";
inline constexpr const char* CYAN    = "\033[36m";

// Curata ecranul, portabil intre Windows si Linux/Mac.
inline void curataEcran() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

// Asteapta apasarea tastei Enter (folosit in meniul interactiv).
inline void asteaptaEnter() {
    std::cout << "\nApasa Enter pentru a continua...";
    std::cin.get();
}

// Citeste o optiune intreaga din consola, ignorand input gresit (litere etc.).
inline int citesteOptiune() {
    int valoare;
    while (!(std::cin >> valoare)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << RED << "Introdu un numar valid: " << RESET;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valoare;
}

// --- VALIDARI ---

// Verifica daca un text reprezinta un numar intreg si il converteste.
inline bool esteIntreg(const std::string& text, int& rezultat) {
    if (text.empty()) return false;
    std::size_t start = 0;
    if (text[0] == '+' || text[0] == '-') start = 1;
    if (start == text.size()) return false;
    for (std::size_t i = start; i < text.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(text[i]))) return false;
    }
    rezultat = std::stoi(text);
    return true;
}

// Verifica formatul unei date: zz/ll/aaaa (ex: 25/12/2025).
inline bool esteDataValida(const std::string& data) {
    if (data.size() != 10) return false;
    if (data[2] != '/' || data[5] != '/') return false;
    for (int i : {0, 1, 3, 4, 6, 7, 8, 9}) {
        if (!std::isdigit(static_cast<unsigned char>(data[i]))) return false;
    }
    int zi   = (data[0] - '0') * 10 + (data[1] - '0');
    int luna = (data[3] - '0') * 10 + (data[4] - '0');
    return zi >= 1 && zi <= 31 && luna >= 1 && luna <= 12;
}

// Verifica formatul unui interval orar: HH:MM-HH:MM (ex: 10:00-12:00).
inline bool esteIntervalValid(const std::string& interval) {
    if (interval.size() != 11) return false;
    if (interval[2] != ':' || interval[5] != '-' || interval[8] != ':') return false;
    for (int i : {0, 1, 3, 4, 6, 7, 9, 10}) {
        if (!std::isdigit(static_cast<unsigned char>(interval[i]))) return false;
    }
    int oraStart = (interval[0] - '0') * 10 + (interval[1] - '0');
    int minStart = (interval[3] - '0') * 10 + (interval[4] - '0');
    int oraEnd   = (interval[6] - '0') * 10 + (interval[7] - '0');
    int minEnd   = (interval[9] - '0') * 10 + (interval[10] - '0');
    if (oraStart > 23 || oraEnd > 23 || minStart > 59 || minEnd > 59) return false;
    // ora de inceput trebuie sa fie inaintea celei de final
    return (oraStart * 60 + minStart) < (oraEnd * 60 + minEnd);
}

#endif // UTILS_H
