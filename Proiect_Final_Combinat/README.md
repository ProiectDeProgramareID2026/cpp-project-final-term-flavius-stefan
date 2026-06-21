# Rezervare Săli de Ședință (C++)

Aplicație pentru gestionarea sălilor de ședință și a rezervărilor.
Transpunere în C++ (OOP) a proiectului original scris în C.

## Compilare

### Varianta 1 — g++ direct (terminal)
```bash
g++ -std=c++17 main.cpp Sala.cpp Rezervare.cpp GestionarSali.cpp GestionarRezervari.cpp -o rezervari
```

### Varianta 2 — CMake (CLion / VS Code)
Există `CMakeLists.txt`. Deschideți folderul în CLion sau:
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Rulare

### Mod interactiv (meniu)
```bash
./rezervari
```

### Mod linie de comandă (preluare + validare argumente)
```bash
./rezervari adauga-sala Sala_Mica 15
./rezervari adauga-sala Sala_Mare 150
./rezervari listeaza-sali
./rezervari cauta-sala Sala_Mare
./rezervari cauta-capacitate 30 100
./rezervari sterge-sala Sala_Mica

./rezervari rezerva Sala_Mare 25/12/2025 10:00-12:00
./rezervari listeaza-rezervari
./rezervari disponibile 25/12/2025
./rezervari anuleaza 1

./rezervari --help
```

Datele se salvează automat în `Sali.txt` și `Rezervari.txt` (create la prima rulare).

## Structura fișierelor

| Fișier | Conținut | Responsabil |
|--------|----------|-------------|
| `Sala.h` / `Sala.cpp` | Clasa `Sala` | Persoana A |
| `GestionarSali.h` / `.cpp` | Logica sălilor | Persoana A |
| `Rezervare.h` / `Rezervare.cpp` | Clasa `Rezervare` | Persoana B |
| `GestionarRezervari.h` / `.cpp` | Logica rezervărilor + asociere | Persoana B |
| `Repository.h` | Clasă template pentru fișiere (comun) | Comun |
| `Utils.h` | Culori, validări, ajutor (comun) | Comun |
| `main.cpp` | Argumente linie comandă + meniu | Persoana B (meniu săli: A) |
