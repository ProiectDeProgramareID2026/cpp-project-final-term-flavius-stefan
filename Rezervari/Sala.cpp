//  Sala.cpp - implementarea clasei Sala
//  Responsabil: PERSOANA A

#include "Sala.h"
#include "Utils.h"
#include <iomanip>
#include <utility>

Sala::Sala() : nume(""), capacitate(0) {}

Sala::Sala(std::string nume, int capacitate)
    : nume(std::move(nume)), capacitate(capacitate) {}

const std::string& Sala::getNume() const {
    return nume;
}

int Sala::getCapacitate() const {
    return capacitate;
}

std::string Sala::getTip() const {
    return (capacitate <= 20) ? "MICA" : "MARE";
}

void Sala::scrieInFisier(std::ostream& out) const {
    out << nume << " " << capacitate << "\n";
}

bool Sala::citesteDinFisier(std::istream& in) {
    // Daca citirea reuseste (sunt date valide), returneaza true.
    return static_cast<bool>(in >> nume >> capacitate);
}

std::ostream& operator<<(std::ostream& out, const Sala& s) {
    out << std::left << std::setw(20) << s.nume << " | ";
    if (s.capacitate >= 100) {
        out << BLUE << s.capacitate << RESET << " locuri";
    } else if (s.capacitate <= 20) {
        out << RED << s.capacitate << RESET << " locuri";
    } else {
        out << s.capacitate << " locuri";
    }
    return out;
}
