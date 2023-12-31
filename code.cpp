#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <cctype>
#include <regex>
#include <locale>
#include <codecvt>
#include <string>
#include "Funkcijos.h"

using namespace std;

string mazosiosRaides(const string& zodis) {
    string rezultatas = zodis;
    for (char& c : rezultatas) {
        c = tolower(c);
    }
    return rezultatas;
}

string pasalintiSkyrybosIrSkaicius(const string& zodis) {
    string rezultatas;
    for (char c : zodis) {
        if (isalpha(c) || c == '.' || static_cast<unsigned char>(c) > 127) {
            rezultatas += c;
        }
    }
    return rezultatas;
}

string isgautiDomena(const string& url) {
    regex domenoRegex("https?://([^/?#]+)");
    smatch atitikmuo;
    if (regex_search(url, atitikmuo, domenoRegex)) {
        return atitikmuo[1];
    }
    return "";
}

int main() {
    setlocale(LC_ALL, "lt_LT.UTF-8");

    /*
    Skaitymas is failo
    */
    string failoVardas;
    cout << "Iveskite failo pavadinima: ";
    cin >> failoVardas;

    ifstream ivestiesFailas(failoVardas, ios::in);

    if (!ivestiesFailas.is_open()) {
        cerr << "Klaida atidarant faila." << endl;
        return 1;
    }

    set<string> visiURL; // saugo unikalius domenus

    regex urlRegex("(https?|ftp)://[^\\s/$.?#].[^\\s]*"); 

    string eilute;
    while (getline(ivestiesFailas, eilute)) {
        smatch urlAtitikmuo;                                    //tikrina atitikmeni su urlRegex
        while (regex_search(eilute, urlAtitikmuo, urlRegex)) {
            string url = urlAtitikmuo[0];
            string domenas = isgautiDomena(url);
            if (!domenas.empty()) {
                visiURL.insert(domenas);
                eilute = regex_replace(eilute, regex(url), ""); //iskirpame is eilutes url pakeisdami i tuscias
            }
            eilute = urlAtitikmuo.suffix().str();               //gražina teksto dalį, kuri seka po paskutinio rasto atitikimo ir konvertuoja i string
        }
    }

    ivestiesFailas.close();

    Nuorodos("Nuorodos.txt", visiURL);
   
    /*
    Vel atidarome musu skaitymo faila
    */
    ivestiesFailas.open(failoVardas);

    if (!ivestiesFailas.is_open()) {
        cerr << "Klaida atidarant faila." << endl;
        return 1;
    }

    map<string, map<int, int> > zodziuPasikartojimai;

    int eilutesNumeris = 1;

    while (getline(ivestiesFailas, eilute)) {
        istringstream iss(eilute);
        string zodis;

        while (iss >> zodis) {
            string apdorotasZodis = pasalintiSkyrybosIrSkaicius(mazosiosRaides(zodis));

            if (!apdorotasZodis.empty() && apdorotasZodis.back() == '.') {
                apdorotasZodis.pop_back();
            }

            if (!apdorotasZodis.empty() && visiURL.find(apdorotasZodis) == visiURL.end() &&
                apdorotasZodis.find("www") == string::npos && apdorotasZodis.find("http") == string::npos) {
                zodziuPasikartojimai[apdorotasZodis][eilutesNumeris]++;
            }
        }

        eilutesNumeris++;
    }

    ivestiesFailas.close();

    BendrasPasikartojimas ("BendrasPasikartojimai.txt", zodziuPasikartojimai);

    EilutesIrPasikartojimai ("EilutesIrPasikartojimai.txt", zodziuPasikartojimai);

    cout << "Rezultatai eksportuoti i EilutesIrPasikartojimai.txt, BendrasPasikartojimai.txt ir Nuorodos.txt" << endl;

    return 0;
}
