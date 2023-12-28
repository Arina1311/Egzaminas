#ifndef ISVEDIMAS_H
#define ISVEDIMAS_H

#include <list>
#include <string>
#include <set> 
#include <map>

using namespace std;

void Nuorodos(const string& failoPavadinimas, set<string>  visiURL);
void BendrasPasikartojimas (const string& failoPavadinimas, map<string, map<int, int> >& zodziuPasikartojimai);
void EilutesIrPasikartojimai (const string& failoPavadinimas, map<string, map<int, int> >& zodziuPasikartojimai);

#endif
