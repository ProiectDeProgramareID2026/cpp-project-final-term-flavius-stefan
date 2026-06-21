#ifndef SALA_H
#define SALA_H

//  Sala.h - clasa care modeleaza o sala de sedinta
//  Responsabil: PERSOANA A


#include <string>
#include <iostream>

class Sala {
private:
    std::string nume;     // numele salii (fara spatii, ex: Sala_Mare)
    int capacitate;       // numarul de locuri

public:
    // Constructori
    Sala();
    Sala(std::string nume, int capacitate);

    // Getteri (acces controlat la datele private => incapsulare)
    const std::string& getNume() const;
    int getCapacitate() const;

    // Returneaza tipul salii in functie de capacitate: "MICA" (<=20) sau "MARE".
    std::string getTip() const;

    // Lucrul cu fisiere: format simplu pe o linie -> "nume capacitate"
    void scrieInFisier(std::ostream& out) const;   // serializare
    bool citesteDinFisier(std::istream& in);        // deserializare (false la final)

    // Supraincarcarea operatorului << pentru afisare formatata (cu culori).
    friend std::ostream& operator<<(std::ostream& out, const Sala& s);
};

#endif // SALA_H
