// =============================================================================
//  GestionarSali.cpp - implementarea logicii de gestionare a salilor
//  Responsabil: PERSOANA A


#include "GestionarSali.h"
#include "Utils.h"
#include <iostream>

GestionarSali::GestionarSali(const std::string& numeFisier) : repo(numeFisier) {
    repo.incarca();   // la pornire incarcam salile existente din fisier
}

bool GestionarSali::adaugaSala(const std::string& nume, int capacitate) {
    if (capacitate <= 0) return false;          // capacitate invalida
    if (cautaDupaNume(nume) != nullptr) return false;  // sala exista deja
    repo.adauga(Sala(nume, capacitate));
    repo.salveaza();
    return true;
}

bool GestionarSali::stergeSala(const std::string& nume) {
    const std::vector<Sala>& sali = repo.getToate();
    for (std::size_t i = 0; i < sali.size(); ++i) {
        if (sali[i].getNume() == nume) {
            repo.stergeLaIndex(i);
            repo.salveaza();
            return true;
        }
    }
    return false;
}

void GestionarSali::afiseazaToate() const {
    std::cout << GREEN << "\n--- Lista Sali de Sedinta ---\n" << RESET;
    if (repo.esteGol()) {
        std::cout << YELLOW << "Nu exista nicio sala inregistrata.\n" << RESET;
        return;
    }
    for (const Sala& s : repo.getToate()) {
        std::cout << "- " << s << "\n";   // foloseste operator<< definit pentru Sala
    }
}

const Sala* GestionarSali::cautaDupaNume(const std::string& nume) const {
    for (const Sala& s : repo.getToate()) {
        if (s.getNume() == nume) return &s;
    }
    return nullptr;
}

void GestionarSali::cautaDupaCapacitate(int minim, int maxim) const {
    std::cout << GREEN << "\n--- Sali cu capacitate intre " << minim
              << " si " << maxim << " ---\n" << RESET;
    bool gasit = false;
    for (const Sala& s : repo.getToate()) {
        if (s.getCapacitate() >= minim && s.getCapacitate() <= maxim) {
            std::cout << "- " << s << "\n";
            gasit = true;
        }
    }
    if (!gasit) {
        std::cout << YELLOW << "Nicio sala nu corespunde criteriilor.\n" << RESET;
    }
}

const std::vector<Sala>& GestionarSali::toateSalile() const {
    return repo.getToate();
}
