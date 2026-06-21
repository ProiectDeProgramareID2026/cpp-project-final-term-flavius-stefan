// =============================================================================
//  Rezervare.cpp - implementarea clasei Rezervare
//  Responsabil: PERSOANA B


#include "Rezervare.h"
#include "Utils.h"
#include <iomanip>
#include <utility>

Rezervare::Rezervare() : numeSala(""), data(""), intervalOrar("") {}

Rezervare::Rezervare(std::string numeSala, std::string data, std::string intervalOrar)
    : numeSala(std::move(numeSala)),
      data(std::move(data)),
      intervalOrar(std::move(intervalOrar)) {}

const std::string& Rezervare::getNumeSala() const {
    return numeSala;
}

const std::string& Rezervare::getData() const {
    return data;
}

const std::string& Rezervare::getIntervalOrar() const {
    return intervalOrar;
}

void Rezervare::scrieInFisier(std::ostream& out) const {
    out << numeSala << "|" << data << "|" << intervalOrar << "\n";
}

bool Rezervare::citesteDinFisier(std::istream& in) {
    // Citim numeSala pana la '|' (permite spatii in nume), apoi data si intervalul.
    if (!std::getline(in, numeSala, '|')) return false;
    if (!std::getline(in, data, '|')) return false;
    return static_cast<bool>(std::getline(in, intervalOrar));
}

std::ostream& operator<<(std::ostream& out, const Rezervare& r) {
    out << std::left << std::setw(20) << r.numeSala << " | "
        << YELLOW << std::setw(12) << r.data << RESET << " | "
        << GREEN  << std::setw(13) << r.intervalOrar << RESET;
    return out;
}
