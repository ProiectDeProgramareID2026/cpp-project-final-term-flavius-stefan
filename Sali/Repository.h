#ifndef REPOSITORY_H
#define REPOSITORY_H
//  Repository.h - CLASA TEMPLATE generica pentru lucrul cu fisiere.
//
//  Acelasi cod este folosit atat pentru Sala, cat si pentru Rezervare,
//  evitand duplicarea logicii de citire/scriere in fisier.
//
//  Tipul T trebuie sa ofere metodele:
//     - bool citesteDinFisier(std::istream&)
//     - void scrieInFisier(std::ostream&) const
//
//  Foloseste containerul STL std::vector pentru stocarea elementelor.


#include <string>
#include <vector>
#include <fstream>
#include <utility>

template <typename T>
class Repository {
private:
    std::string numeFisier;
    std::vector<T> elemente;   // container STL

public:
    Repository(std::string numeFisier)
        : numeFisier(std::move(numeFisier)) {}

    // Incarca toate elementele din fisier in memorie.
    void incarca() {
        elemente.clear();
        std::ifstream in(numeFisier);
        if (!in.is_open()) return;  // fisierul poate sa nu existe inca - normal
        T temp;
        while (temp.citesteDinFisier(in)) {
            elemente.push_back(temp);
        }
    }

    // Salveaza toate elementele din memorie in fisier (suprascrie continutul).
    void salveaza() const {
        std::ofstream out(numeFisier);
        for (const T& element : elemente) {
            element.scrieInFisier(out);
        }
    }

    void adauga(const T& element) {
        elemente.push_back(element);
    }

    bool stergeLaIndex(std::size_t index) {
        if (index >= elemente.size()) return false;
        elemente.erase(elemente.begin() + static_cast<long>(index));
        return true;
    }

    const std::vector<T>& getToate() const { return elemente; }
    std::size_t dimensiune() const { return elemente.size(); }
    bool esteGol() const { return elemente.empty(); }
};

#endif // REPOSITORY_H
