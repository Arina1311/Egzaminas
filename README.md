# Egzaminas
# Programos tikslas ir veikimas
Programos tiklas yra apdoroti tekstą lietuvių kalba ir iš jo abecelės tvarka išrinkti tuos žodžius kurie pasikartoja daugiau, nei vieną kartą. Be to, programa parodo kokioje eilutėje buvo rastas žodis ir kiek kartų jis pasikartojo joje. Taip pat, jei tekste yra aptinkamos URL nuorodos, programa surašo ir pateikia naudotojui sąrašą unikalių domenų. <br>
Programa yra lengva naudojimui, reikia pateikti tik vieno failo pavadinimą, kurį norime apdoroti. Programa iš karto sukuria tris failus: *"Nuorodos.txt"*, *"BendrasPasikartojimai.txt"* bei *"EilutesIrPasikartojimai.txt"*.

# Programos rezultatų aprašymas
## Žodžių pasikartojimas
Programa naudoja asociatyvų konteinerį **map**, kad galėtų surašyti žodžius ir jų pasikartojimų skaičių, išvedimas į failą *"BendrasPasikartojimai.txt"* atrodo taip:<br><br>
<img width="501" alt="Снимок экрана 2023-12-28 в 11 38 39" src="https://github.com/Arina1311/Egzaminas/assets/144428021/6a30a4a0-8fac-4285-9839-a1f20e08ddbf"><br>
## Žodžių pasikartojimas eilutėse
Programa naudoja asociatyvų konteinerį **map**, kuris turi raktą ir reikšmes. Šioje programoje, reikėjo, kad **map** konteinėris savyje turėtų dar vieną **map** konteinėrį, kad galėtume surašyti žodį, pateikti eilutes, kuriuose jis pasikartoja ir kiek kartų pasikartoja skaičių. Kaip rezultatas, išvedimas į failą *"EilutesIrPasikartojimai.txt"* atrodo taip:<br><br>
<img width="842" alt="Снимок экрана 2023-12-28 в 11 39 10" src="https://github.com/Arina1311/Egzaminas/assets/144428021/98e8766c-db09-4ae7-851b-c56bcfaf11a6"><br>
## Domenai
Programoje, kad galėtume iš ilgų URL adresų gauti sutrumpintus ir unikalius domenus, buvo naudojamas konteineris **set** ir **regex** struktūros ir funkcijos. Apsirašę paiešką URL adresų, kurie bendrai prasideda: http, https arba ftp, pagal tokią pradžią buvo ieškomi URL adresai tekste. Vėliau šie adresai buvo perduodami į funkciją, kuri ištraukia domeną ir gražiną į programą, papildydama konteinerį **set**. Po to, kai nuoroda buvo apdorota, ji buvo ištrinama iš teksto. Išvedimas atrodo taip:<br><br>
<img width="381" alt="Снимок экрана 2023-12-28 в 11 39 23" src="https://github.com/Arina1311/Egzaminas/assets/144428021/b4e1ac3b-0c93-4e24-b74e-1ed03281b1da"><br>


