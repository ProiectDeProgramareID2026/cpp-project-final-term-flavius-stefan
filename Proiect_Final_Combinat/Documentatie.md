# Documentația proiectului — Rezervare Săli de Ședință

> Acest fișier este o **schiță**. Completați secțiunile marcate cu „..." și
> exportați apoi în PDF (din Word/Google Docs, sau direct dacă scrieți în Markdown).

## 1. Descrierea proiectului
Aplicația permite gestionarea sălilor de ședință și a rezervărilor:
adăugarea/ștergerea sălilor (nume + capacitate), afișarea sălilor și a
rezervărilor, căutarea sălilor (după nume, capacitate, disponibilitate),
rezervarea unei săli (cu dată și interval orar) și anularea unei rezervări.
Datele sunt salvate în fișiere text.

## 2. Echipa și împărțirea sarcinilor
- **Persoana A — Modulul Săli:** clasa `Sala`, clasa `GestionarSali`, comenzile
  de săli din linia de comandă, opțiunile de meniu pentru săli.
- **Persoana B — Modulul Rezervări:** clasa `Rezervare`, clasa `GestionarRezervari`,
  relația de asociere între clase, comenzile de rezervări, dispecerul `main`.
- **Comun:** `Repository.h` (clasă template) și `Utils.h` (culori + validări).

## 3. Arhitectura aplicației (clase)
- `Sala` — modelează o sală (nume, capacitate). Metoda `getTip()` decide MICĂ/MARE.
- `Rezervare` — modelează o rezervare (sală, dată, interval orar).
- `Repository<T>` — **clasă template** care încarcă/salvează un `std::vector<T>`
  din/în fișier. E folosită identic pentru `Sala` și `Rezervare`.
- `GestionarSali` — logica de business pentru săli; conține un `Repository<Sala>`.
- `GestionarRezervari` — logica pentru rezervări; conține un `Repository<Rezervare>`
  **și o referință către `GestionarSali`** (relație de asociere).

(Recomandare: adăugați o diagramă simplă a claselor — săgeată „conține" /
„folosește" între `GestionarRezervari` → `GestionarSali`.)

## 4. Cerințe tehnice — unde sunt îndeplinite
| Cerință | Unde în cod |
|---------|-------------|
| Clase și obiecte | `Sala`, `Rezervare`, `GestionarSali`, `GestionarRezervari` |
| Documentarea codului | comentarii în toate fișierele `.h` / `.cpp` |
| Clean code | separare pe fișiere, denumiri clare, getteri, încapsulare |
| Lucrul cu fișiere | `Repository::incarca()` / `salveaza()` → `Sali.txt`, `Rezervari.txt` |
| STL (containere) | `std::vector` în `Repository` |
| Supraîncărcarea operatorilor | `operator<<` pentru `Sala` și `Rezervare` |
| Template | `Repository<T>` (folosit pentru ambele tipuri) |
| Asociere / moștenire | `GestionarRezervari` ține o referință `GestionarSali&` |
| Funcționalități conform descrierii | meniu + comenzi CLI complete |
| Preluare/validare argumente CLI | `ruleazaComanda()` + validări din `Utils.h` |

## 5. Validări implementate
- Capacitate: număr întreg pozitiv (`esteIntreg`).
- Dată: format `zz/ll/aaaa`, zi 1–31, lună 1–12 (`esteDataValida`).
- Interval orar: format `HH:MM-HH:MM`, ore/minute valide, start < final (`esteIntervalValid`).
- Număr corect de argumente pentru fiecare comandă; sală inexistentă; dublă rezervare.

## 6. Exemple de utilizare
(Copiați aici câteva comenzi din `README.md` + capturi de ecran cu rezultatul.)

## 7. Concluzii
...
