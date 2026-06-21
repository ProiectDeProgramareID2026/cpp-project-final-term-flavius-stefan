#ifndef GESTIONAR_REZERVARI_H
#define GESTIONAR_REZERVARI_H

//  GestionarRezervari.h - clasa care gestioneaza rezervarile
//  Responsabil: PERSOANA B
//
//  RELATIE DE ASOCIERE: aceasta clasa pastreaza o referinta catre GestionarSali,
//  pentru ca o rezervare nu are sens fara o sala existenta (verificare existenta
//  sala, aflarea tipului salii, listarea salilor libere).
//
//  Foloseste Repository<Rezervare> pentru lucrul cu fisierul Rezervari.txt.
#include "Rezervare.h"
#include "Repository.h"
#include "GestionarSali.h"
#include <string>

class GestionarRezervari {
private:
    Repository<Rezervare> repo;
    GestionarSali& gestionarSali;   // <-- ASOCIERE intre clase

public:
    GestionarRezervari(GestionarSali& gs, const std::string& numeFisier = "Rezervari.txt");

    // Adauga o rezervare. Esueaza daca sala nu exista sau e deja rezervata in acea zi.
    bool adaugaRezervare(const std::string& numeSala,
                         const std::string& data,
                         const std::string& interval);

    // Anuleaza rezervarea cu numarul dat (numerotare de la 1, asa cum o vede userul).
    bool anuleazaRezervare(std::size_t numar1Based);

    void afiseazaToate() const;
    void afiseazaDisponibile(const std::string& data) const;

    std::size_t numarRezervari() const;
};

#endif // GESTIONAR_REZERVARI_H
