#ifndef REZERVARE_H
#define REZERVARE_H

//  Rezervare.h - clasa care modeleaza o rezervare a unei sali
//  Responsabil: PERSOANA B


#include <string>
#include <iostream>

class Rezervare {
private:
    std::string numeSala;      // numele salii rezervate
    std::string data;          // data rezervarii (zz/ll/aaaa)
    std::string intervalOrar;  // intervalul orar (HH:MM-HH:MM)

public:
    // Constructori
    Rezervare();
    Rezervare(std::string numeSala, std::string data, std::string intervalOrar);

    // Getteri
    const std::string& getNumeSala() const;
    const std::string& getData() const;
    const std::string& getIntervalOrar() const;

    // Lucrul cu fisiere: format pe o linie -> "numeSala data interval"
    void scrieInFisier(std::ostream& out) const;
    bool citesteDinFisier(std::istream& in);

    // Supraincarcarea operatorului << pentru afisare formatata.
    friend std::ostream& operator<<(std::ostream& out, const Rezervare& r);
};

#endif // REZERVARE_H
