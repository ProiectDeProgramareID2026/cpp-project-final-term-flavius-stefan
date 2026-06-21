#ifndef GESTIONAR_SALI_H
#define GESTIONAR_SALI_H
//  GestionarSali.h - clasa care gestioneaza toate salile (logica de business)
//  Responsabil: PERSOANA A
//  Foloseste Repository<Sala> pentru lucrul cu fisierul Sali.txt.


#include "Sala.h"
#include "Repository.h"
#include <string>
#include <vector>

class GestionarSali {
private:
    Repository<Sala> repo;   // compozitie: gestionarul "contine" depozitul de sali

public:
    GestionarSali(const std::string& numeFisier = "Sali.txt");

    // Returneaza true daca sala a fost adaugata (false daca exista deja / date invalide).
    bool adaugaSala(const std::string& nume, int capacitate);

    // Returneaza true daca sala a fost gasita si stearsa.
    bool stergeSala(const std::string& nume);

    void afiseazaToate() const;

    // Cauta o sala dupa nume; returneaza pointer la sala sau nullptr daca nu exista.
    const Sala* cautaDupaNume(const std::string& nume) const;

    // Afiseaza salile a caror capacitate este in intervalul [minim, maxim].
    void cautaDupaCapacitate(int minim, int maxim) const;

    // Acces la lista completa (folosit de GestionarRezervari prin asociere).
    const std::vector<Sala>& toateSalile() const;
};

#endif // GESTIONAR_SALI_H
