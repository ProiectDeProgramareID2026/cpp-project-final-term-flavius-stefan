// =============================================================================
//  main.cpp - punctul de intrare al aplicatiei
//
//  Doua moduri de utilizare:
//   1) Cu argumente din linia de comanda  -> executa o singura comanda (PERSOANA B)
//   2) Fara argumente                     -> porneste meniul interactiv
//
//  Preluarea si validarea argumentelor din linia de comanda: PERSOANA B.
//  Optiunile de meniu pentru sali apartin Persoanei A, cele de rezervari Persoanei B.
// =============================================================================

#include "GestionarSali.h"
#include "GestionarRezervari.h"
#include "Utils.h"

#include <iostream>
#include <string>

//  MOD LINIE DE COMANDA (PERSOANA B)


// Afiseaza modul de utilizare (lista de comenzi disponibile).
void afiseazaUtilizare(const std::string& numeProgram) {
    std::cout << BLUE << "\nUtilizare: " << RESET << numeProgram
              << " <comanda> [argumente]\n\n";
    std::cout << CYAN << "Comenzi pentru sali:\n" << RESET;
    std::cout << "  adauga-sala <nume> <capacitate>    Adauga o sala noua\n";
    std::cout << "  sterge-sala <nume>                 Sterge o sala\n";
    std::cout << "  listeaza-sali                      Afiseaza toate salile\n";
    std::cout << "  cauta-sala <nume>                  Cauta o sala dupa nume\n";
    std::cout << "  cauta-capacitate <min> <max>       Cauta sali dupa capacitate\n\n";
    std::cout << CYAN << "Comenzi pentru rezervari:\n" << RESET;
    std::cout << "  rezerva <nume> <data> <interval>   data=zz/ll/aaaa  interval=HH:MM-HH:MM\n";
    std::cout << "  anuleaza <numar>                   Anuleaza o rezervare dupa numar\n";
    std::cout << "  listeaza-rezervari                 Afiseaza toate rezervarile\n";
    std::cout << "  disponibile <data>                 Sali libere la o anumita data\n\n";
    std::cout << "  --help                             Afiseaza acest mesaj\n";
}

// Mic ajutor: afiseaza o eroare de argumente si returneaza cod de eroare.
int eroareArgumente(const std::string& mesaj, const std::string& numeProgram) {
    std::cout << RED << "Eroare: " << mesaj << "\n" << RESET;
    afiseazaUtilizare(numeProgram);
    return 1;
}

// Interpreteaza comanda primita si o executa. Returneaza 0 (succes) sau 1 (eroare).
int ruleazaComanda(int argc, char* argv[], GestionarSali& gs, GestionarRezervari& gr) {
    const std::string prog = argv[0];
    const std::string comanda = argv[1];

    if (comanda == "--help" || comanda == "-h" || comanda == "ajutor") {
        afiseazaUtilizare(prog);
        return 0;
    }

    // ---- Comenzi sali ----
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
        if (minim > maxim)
            return eroareArgumente("min nu poate fi mai mare decat max.", prog);
        gs.cautaDupaCapacitate(minim, maxim);
        return 0;
    }

    // ---- Comenzi rezervari ----
    if (comanda == "rezerva") {
        if (argc != 5) return eroareArgumente("'rezerva' necesita: <nume> <data> <interval>.", prog);
        if (!esteDataValida(argv[3]))
            return eroareArgumente("data invalida. Format corect: zz/ll/aaaa (ex: 25/12/2025).", prog);
        if (!esteIntervalValid(argv[4]))
            return eroareArgumente("interval invalid. Format corect: HH:MM-HH:MM (ex: 10:00-12:00).", prog);
        if (gr.adaugaRezervare(argv[2], argv[3], argv[4]))
            std::cout << GREEN << "Rezervare creata pentru '" << argv[2] << "'.\n" << RESET;
        else
            std::cout << RED << "Sala inexistenta sau deja rezervata in acea zi.\n" << RESET;
        return 0;
    }

    if (comanda == "anuleaza") {
        if (argc != 3) return eroareArgumente("'anuleaza' necesita: <numar>.", prog);
        int numar;
        if (!esteIntreg(argv[2], numar) || numar <= 0)
            return eroareArgumente("numarul rezervarii trebuie sa fie un intreg pozitiv.", prog);
        if (gr.anuleazaRezervare(static_cast<std::size_t>(numar)))
            std::cout << GREEN << "Rezervarea " << numar << " a fost anulata.\n" << RESET;
        else
            std::cout << YELLOW << "Nu exista o rezervare cu numarul " << numar << ".\n" << RESET;
        return 0;
    }

    if (comanda == "listeaza-rezervari") {
        if (argc != 2) return eroareArgumente("'listeaza-rezervari' nu accepta argumente.", prog);
        gr.afiseazaToate();
        return 0;
    }

    if (comanda == "disponibile") {
        if (argc != 3) return eroareArgumente("'disponibile' necesita: <data>.", prog);
        if (!esteDataValida(argv[2]))
            return eroareArgumente("data invalida. Format corect: zz/ll/aaaa.", prog);
        gr.afiseazaDisponibile(argv[2]);
        return 0;
    }

    return eroareArgumente("comanda necunoscuta '" + comanda + "'.", prog);
}

//  MOD INTERACTIV (MENIU)
//  Optiunile de sali = PERSOANA A, optiunile de rezervari = PERSOANA B.


int main(int argc, char* argv[]) {
    // Cele doua gestionare; rezervarile primesc o referinta catre sali (ASOCIERE).
    GestionarSali gestionarSali("Sali.txt");
    GestionarRezervari gestionarRezervari(gestionarSali, "Rezervari.txt");

    if (argc > 1) {
        // Exista argumente -> mod linie de comanda.
        return ruleazaComanda(argc, argv, gestionarSali, gestionarRezervari);
    }

    // Fara argumente -> afisam modul de utilizare.
    afiseazaUtilizare(argv[0]);
    return 0;
}
