
//  main_rezervari.cpp - APLICATIE DE SINE STATATOARE pentru rezervari
//  Responsabil: PERSOANA B
//
//  Modulul de rezervari FOLOSESTE modulul de sali (relatie de asociere):
//  o rezervare are sens doar pentru o sala existenta. De aceea programul
//  incarca si salile din Sali.txt (modulul Persoanei A).
//  Produce executabilul "gestionare_rezervari".


#include "GestionarSali.h"
#include "GestionarRezervari.h"
#include "Utils.h"

#include <iostream>
#include <string>

void afiseazaUtilizare(const std::string& prog) {
    std::cout << BLUE << "\nUtilizare: " << RESET << prog << " <comanda> [argumente]\n\n";
    std::cout << CYAN << "Comenzi pentru rezervari:\n" << RESET;
    std::cout << "  rezerva <nume> <data> <interval>   data=zz/ll/aaaa  interval=HH:MM-HH:MM\n";
    std::cout << "  anuleaza <numar>                   Anuleaza o rezervare dupa numar\n";
    std::cout << "  listeaza-rezervari                 Afiseaza toate rezervarile\n";
    std::cout << "  disponibile <data>                 Sali libere la o anumita data\n";
    std::cout << "  sali                               Afiseaza salile disponibile (din modulul A)\n";
    std::cout << "  --help                             Afiseaza acest mesaj\n";
    std::cout << YELLOW << "\nFara argumente: porneste meniul interactiv.\n" << RESET;
}

int eroareArgumente(const std::string& mesaj, const std::string& prog) {
    std::cout << RED << "Eroare: " << mesaj << "\n" << RESET;
    afiseazaUtilizare(prog);
    return 1;
}

// Preluare si validare a argumentelor din linia de comanda (PERSOANA B).
int ruleazaComanda(int argc, char* argv[], GestionarSali& gs, GestionarRezervari& gr) {
    const std::string prog = argv[0];
    const std::string comanda = argv[1];

    if (comanda == "--help" || comanda == "-h" || comanda == "ajutor") {
        afiseazaUtilizare(prog);
        return 0;
    }
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
    if (comanda == "sali") {
        if (argc != 2) return eroareArgumente("'sali' nu accepta argumente.", prog);
        gs.afiseazaToate();  // doar citire, din modulul Persoanei A
        return 0;
    }
    return eroareArgumente("comanda necunoscuta '" + comanda + "'.", prog);
}

// Meniu interactiv pentru rezervari (PERSOANA B).
void meniuInteractiv(GestionarSali& gs, GestionarRezervari& gr) {
    int optiune;
    do {
        curataEcran();
        std::cout << BLUE << "Gestionare Rezervari (Persoana B)\n" << RESET;
        std::cout << "<><><><><><><><><><><><><><><><><>\n";
        std::cout << CYAN << "1." << RESET << " Rezerva o sala\n";
        std::cout << CYAN << "2." << RESET << " Anulare rezervare\n";
        std::cout << CYAN << "3." << RESET << " Vizualizare rezervari\n";
        std::cout << CYAN << "4." << RESET << " Vizualizare sali disponibile (pe data)\n";
        std::cout << CYAN << "5." << RESET << " Vizualizare toate salile (modulul A)\n";
        std::cout << CYAN << "0." << RESET << " Iesire\n";
        std::cout << "Selecteaza optiune: ";
        optiune = citesteOptiune();

        if (optiune == 1) {
            std::string nume, data, interval;
            std::cout << "Numele salii: ";
            std::cin >> nume;
            std::cout << "Data (zz/ll/aaaa): ";
            std::cin >> data;
            std::cout << "Interval (HH:MM-HH:MM): ";
            std::cin >> interval;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (!esteDataValida(data)) std::cout << RED << "Data invalida.\n" << RESET;
            else if (!esteIntervalValid(interval)) std::cout << RED << "Interval invalid.\n" << RESET;
            else if (gr.adaugaRezervare(nume, data, interval)) std::cout << GREEN << "Rezervare salvata.\n" << RESET;
            else std::cout << RED << "Sala inexistenta sau deja rezervata in acea zi.\n" << RESET;
            asteaptaEnter();
        } else if (optiune == 2) {
            gr.afiseazaToate();
            std::cout << "\nNumarul rezervarii de anulat (0 = renunta): ";
            int numar = citesteOptiune();
            if (numar > 0) {
                if (gr.anuleazaRezervare(static_cast<std::size_t>(numar)))
                    std::cout << GREEN << "Rezervare anulata.\n" << RESET;
                else std::cout << YELLOW << "Numar invalid.\n" << RESET;
            }
            asteaptaEnter();
        } else if (optiune == 3) {
            gr.afiseazaToate();
            asteaptaEnter();
        } else if (optiune == 4) {
            std::string data;
            std::cout << "Data (zz/ll/aaaa): ";
            std::cin >> data;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (!esteDataValida(data)) std::cout << RED << "Data invalida.\n" << RESET;
            else gr.afiseazaDisponibile(data);
            asteaptaEnter();
        } else if (optiune == 5) {
            gs.afiseazaToate();
            asteaptaEnter();
        } else if (optiune != 0) {
            std::cout << RED << "Optiune invalida.\n" << RESET;
            asteaptaEnter();
        }
    } while (optiune != 0);
    std::cout << "-- Iesire din modulul de rezervari --\n";
}

int main(int argc, char* argv[]) {
    // ASOCIERE: rezervarile au nevoie de sali => incarcam ambele.
    GestionarSali gestionarSali("Sali.txt");
    GestionarRezervari gestionarRezervari(gestionarSali, "Rezervari.txt");

    if (argc > 1) return ruleazaComanda(argc, argv, gestionarSali, gestionarRezervari);
    meniuInteractiv(gestionarSali, gestionarRezervari);
    return 0;
}
