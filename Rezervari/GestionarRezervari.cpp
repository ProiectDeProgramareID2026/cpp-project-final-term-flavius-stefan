
//  GestionarRezervari.cpp - implementarea logicii de gestionare a rezervarilor
//  Responsabil: PERSOANA B


#include "GestionarRezervari.h"
#include "Utils.h"
#include <iostream>

GestionarRezervari::GestionarRezervari(GestionarSali& gs, const std::string& numeFisier)
    : repo(numeFisier), gestionarSali(gs) {
    repo.incarca();
}

bool GestionarRezervari::adaugaRezervare(const std::string& numeSala,
                                         const std::string& data,
                                         const std::string& interval) {
    // ASOCIERE: folosim gestionarSali ca sa verificam ca sala chiar exista.
    if (gestionarSali.cautaDupaNume(numeSala) == nullptr) {
        return false;  // sala inexistenta
    }
    // Verificam ca sala nu este deja rezervata in aceeasi zi.
    for (const Rezervare& r : repo.getToate()) {
        if (r.getNumeSala() == numeSala && r.getData() == data) {
            return false;  // deja ocupata
        }
    }
    repo.adauga(Rezervare(numeSala, data, interval));
    repo.salveaza();
    return true;
}

bool GestionarRezervari::anuleazaRezervare(std::size_t numar1Based) {
    if (numar1Based < 1 || numar1Based > repo.dimensiune()) return false;
    repo.stergeLaIndex(numar1Based - 1);
    repo.salveaza();
    return true;
}

void GestionarRezervari::afiseazaToate() const {
    std::cout << BLUE << "\n--- Detalii Rezervari Sali ---\n" << RESET;
    if (repo.esteGol()) {
        std::cout << YELLOW << "Nu exista nicio rezervare inregistrata.\n" << RESET;
        return;
    }
    int index = 1;
    for (const Rezervare& r : repo.getToate()) {
        // ASOCIERE: aflam tipul salii (MICA/MARE) interogand gestionarSali.
        const Sala* sala = gestionarSali.cautaDupaNume(r.getNumeSala());
        std::string tip = (sala != nullptr) ? sala->getTip() : "Necunoscut";

        std::cout << index << ". " << r << " | ";
        if (tip == "MICA")      std::cout << CYAN << tip << RESET;
        else if (tip == "MARE") std::cout << MAGENTA << tip << RESET;
        else                    std::cout << tip;
        std::cout << "\n";
        ++index;
    }
}

void GestionarRezervari::afiseazaDisponibile(const std::string& data) const {
    std::cout << GREEN << "\n--- Sali disponibile pe data de " << data << " ---\n" << RESET;
    bool exista = false;
    // ASOCIERE: parcurgem toate salile (din gestionarSali) si verificam ocuparea lor.
    for (const Sala& s : gestionarSali.toateSalile()) {
        bool ocupata = false;
        for (const Rezervare& r : repo.getToate()) {
            if (r.getNumeSala() == s.getNume() && r.getData() == data) {
                ocupata = true;
                break;
            }
        }
        if (!ocupata) {
            std::cout << "- " << s << " (" << GREEN << "LIBERA" << RESET << ")\n";
            exista = true;
        }
    }
    if (!exista) {
        std::cout << YELLOW << "Nicio sala disponibila pentru aceasta data.\n" << RESET;
    }
}

std::size_t GestionarRezervari::numarRezervari() const {
    return repo.dimensiune();
}
