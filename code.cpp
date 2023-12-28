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

using namespace std;

string mazosiosRaides(const string& eilute) {
    string rezultatas = eilute;
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

    string failoVardas;
    cout << "Iveskite failo pavadinima: ";
    cin >> failoVardas;

    ifstream ivestiesFailas(failoVardas, ios::in);

    if (!ivestiesFailas.is_open()) {
        cerr << "Klaida atidarant faila." << endl;
        return 1;
    }

    set<string> visiURL;

    regex urlRegex("(https?|ftp)://[^\\s/$.?#].[^\\s]*");

    string eilute;
    while (getline(ivestiesFailas, eilute)) {
        smatch urlAtitikmuo;
        while (regex_search(eilute, urlAtitikmuo, urlRegex)) {
            string url = urlAtitikmuo[0];
            string domenas = isgautiDomena(url);
            if (!domenas.empty()) {
                visiURL.insert(domenas);
                eilute = regex_replace(eilute, regex(url), "");
            }
            eilute = urlAtitikmuo.suffix().str();
        }
    }

    ivestiesFailas.close();

    ofstream urlFailas("Nuorodos.txt");

    if (!urlFailas.is_open()) {
        cerr << "Klaida atidarant nuorodu faila." << endl;
        return 1;
    }

    for (const string& domenas : visiURL) {
        urlFailas << domenas << endl;
    }

    urlFailas.close();

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

    ofstream outputFile("BendrasPasikartojimai.txt");
    if (!outputFile.is_open()) {
        cerr << "Nepavyko atidaryti rezultato failo!" << endl;
        return 1;
    }

    outputFile <<left<<setw(30)<<"| Zodis"<<setw(80)<<"| Pasikartojimai tekste"<<endl;
    outputFile <<"---------------------------------------------------------------------------------------------------------"<<endl;
    for (const auto &pora : zodziuPasikartojimai) {
    if (pora.second.size() > 1 && !any_of(pora.first.begin(), pora.first.end(), ::isdigit)) {
        outputFile << left << setw(30) << "| " + pora.first << setw(80) << "| " + to_string(pora.second.size()) << endl;
    }
}


    outputFile.close();

    ofstream rezultatuFailas("EilutesIrPasikartojimai.txt");

    if (!rezultatuFailas.is_open()) {
        cerr << "Klaida atidarant rezultatu faila." << endl;
        return 1;
    }

    rezultatuFailas << left << setw(30) << "| Žodis" << left << setw(80) << "| Eilutes numeris (Pasikartojimai)" << endl;
    rezultatuFailas << left << setfill('-') << left << setw(110) << " " << setfill(' ') << endl;

    for (const auto& irasas : zodziuPasikartojimai) {
        const string& zodis = irasas.first;
        const map<int, int>& pasikartojimai = irasas.second;

        if (pasikartojimai.size() > 1 && !any_of(zodis.begin(), zodis.end(), ::isdigit)) {
            stringstream eiluciuNumeriaiSrautas;
            for (const auto& eilutesirasas : pasikartojimai) {
                eiluciuNumeriaiSrautas << eilutesirasas.first << " (" << eilutesirasas.second << "); ";
            }

            string eiluciuNumeriai = eiluciuNumeriaiSrautas.str();
            eiluciuNumeriai.pop_back();

            rezultatuFailas << left << setw(30) << "| " + zodis << left << setw(80) << "| " + eiluciuNumeriai << endl;
        }
    }

    rezultatuFailas.close();

    cout << "Rezultatai eksportuoti i EilutesIrPasikartojimai.txt, BendrasPasikartojimai.txt ir Nuorodos.txt" << endl;

    return 0;
}
