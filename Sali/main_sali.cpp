//  main_sali.cpp - APLICATIE DE SINE STATATOARE pentru gestionarea salilor
//  Responsabil: PERSOANA A
//
//  Acesta este modulul dezvoltat si testat independent de Persoana A.
//  Produce executabilul "gestionare_sali".


#include "GestionarSali.h"
#include "Utils.h"

#include <iostream>
#include <string>

void afiseazaUtilizare(const std::string& prog) {
    std::cout << BLUE << "\nUtilizare: " << RESET << prog << " <comanda> [argumente]\n\n";
    std::cout << CYAN << "Comenzi pentru sali:\n" << RESET;
    std::cout << "  adauga-sala <nume> <capacitate>    Adauga o sala noua\n";
    std::cout << "  sterge-sala <nume>                 Sterge o sala\n";
    std::cout << "  listeaza-sali                      Afiseaza toate salile\n";
    std::cout << "  cauta-sala <nume>                  Cauta o sala dupa nume\n";
    std::cout << "  cauta-capacitate <min> <max>       Cauta sali dupa capacitate\n";
    std::cout << "  --help                             Afiseaza acest mesaj\n";
}

int eroareArgumente(const std::string& mesaj, const std::string& prog) {
    std::cout << RED << "Eroare: " << mesaj << "\n" << RESET;
    afiseazaUtilizare(prog);
    return 1;
}

// Preluare si validare a argumentelor din linia de comanda (PERSOANA A).
int ruleazaComanda(int argc, char* argv[], GestionarSali& gs) {
    const std::string prog = argv[0];
    const std::string comanda = argv[1];

    if (comanda == "--help" || comanda == "-h" || comanda == "ajutor") {
        afiseazaUtilizare(prog);
        return 0;
    }
    if (comanda == "adauga-sala") {
        if (argc != 4) return eroareArgumente("'adauga-sala' necesita: <nume> <capacitate>.", prog);
        int capacitate;
        if (!esteIntreg(argv[3], capacitate) || capacitate <= 0)
            return eroareArgumente("capacitatea trebuie sa fie un numar intreg pozitiv.", prog);
        if (gs.adaugaSala(argv[2], capacitate))
            std::cout << GREEN << "Sala '" << argv[2] << "' a fost adaugata.\n" << RESET;
        else
            std::cout << RED << "Sala exista deja sau capacitatea este invalida.\n" << RESET;
        return 0;
    }
    if (comanda == "sterge-sala") {
        if (argc != 3) return eroareArgumente("'sterge-sala' necesita: <nume>.", prog);
        if (gs.stergeSala(argv[2]))
            std::cout << GREEN << "Sala '" << argv[2] << "' a fost stearsa.\n" << RESET;
        else
            std::cout << YELLOW << "Sala '" << argv[2] << "' nu a fost gasita.\n" << RESET;
        return 0;
    }
    if (comanda == "listeaza-sali") {
        if (argc != 2) return eroareArgumente("'listeaza-sali' nu accepta argumente.", prog);
        gs.afiseazaToate();
        return 0;
    }
    if (comanda == "cauta-sala") {
        if (argc != 3) return eroareArgumente("'cauta-sala' necesita: <nume>.", prog);
        const Sala* s = gs.cautaDupaNume(argv[2]);
        if (s != nullptr) std::cout << "- " << *s << "\n";
        else std::cout << YELLOW << "Sala '" << argv[2] << "' nu a fost gasita.\n" << RESET;
        return 0;
    }
    if (comanda == "cauta-capacitate") {
        if (argc != 4) return eroareArgumente("'cauta-capacitate' necesita: <min> <max>.", prog);
        int minim, maxim;
        if (!esteIntreg(argv[2], minim) || !esteIntreg(argv[3], maxim))
            return eroareArgumente("min si max trebuie sa fie numere intregi.", prog);
        if (minim > maxim) return eroareArgumente("min nu poate fi mai mare decat max.", prog);
        gs.cautaDupaCapacitate(minim, maxim);
        return 0;
    }
    return eroareArgumente("comanda necunoscuta '" + comanda + "'.", prog);
}

int main(int argc, char* argv[]) {
    GestionarSali gestionarSali("Sali.txt");
    if (argc > 1) return ruleazaComanda(argc, argv, gestionarSali);
    afiseazaUtilizare(argv[0]);
    return 0;
}
