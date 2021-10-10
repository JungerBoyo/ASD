##<header> ZADANIE 2_0</header>

1. Wczytywanie zmiennych z pliku na liste przy jednoczesnym sortowaniu danych rosnąco

*      Złożoność :: kwadratowa => O((n*(n+1))/2)  [zakładając że w najgorszym wypadku dane są unikalne i posortowane malejąco]



2. Znajdywanie w posortowanej liście najdłużeszego podciągu takich samych danych

*      Złożoność :: liniowa => O(2*n)
<br />

    Czyli :: O((n*(n+1))/2 + 2*n)
<br /><br />
<table>
   <thead>
      <tr>
         <th>Testy</th>
         <th>Test1</th>
         <th>Test2</th>
         <th>Test3</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Liczba danych</td>
         <td>20</td>
         <td>40</td>
         <td>1000</td>
      </tr>
      <tr>
         <td>Czas wykonania [ms]</td>
         <td>0.079&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.022&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>4.125&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
      </tr>
   </tbody>
</table>


  <br />

##<header> ZADANIE 2_1 </header>

1. Wczytywanie zmiennych z pliku do dynamicznej tablicy przy jednoczesnym sprawdzaniu
czy dana wartość pojawiła się jeśli tak inkremetnacja liczby całkowitej powiązanej z tą daną
jeśli nie dodanie nowej wartości do tablicy

*      Złożoność :: kwadratowa => O(~(n*(n+1))/2)  [zakładając że w najgorszym wypadku wszystkie dane są unikalne]

2. Szukanie max
*      Złożoność :: liniowa => O(n)
<br />

     Czyli :: O((n*(n+1))/2 + n)
<br /><br />



<table>
   <thead>
      <tr>
         <th>Testy</th>
         <th>Test1</th>
         <th>Test2</th>
         <th>Test3</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Liczba danych</td>
         <td>20</td>
         <td>40</td>
         <td>1000</td>
      </tr>
      <tr>
         <td>Czas wykonania [ms]</td>
         <td>0.027&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.013&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.627&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
      </tr>
   </tbody>
</table>

##<header> ZADANIE 2_2 </header>

1. Wczytywanie danych na tablicę dynamiczną i szukanie max

*      Złożoność :: linionwa => O(n)  [zakładając że w najgorszym wypadku wszystkie dane są unikalne]

2. Wykorzystanie tablicy o indeksach wartościowanych w zakresie danych liczb binarnych do inkremetnacji 
wartości im przypisanych sum
*      Złożoność :: liniowa => O(n)

3! Alokacja tablicy o zakresie [0, maksymalna wartość spośród danych]
*      Złożoność pamięciowa :: O(2^25 * 4)
<br />

     Czyli :: O((n*(n+1))/2 + n)
<br /><br />



<table>
   <thead>
      <tr>
         <th>Testy</th>
         <th>Test1</th>
         <th>Test2</th>
         <th>Test3</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Liczba danych</td>
         <td>20</td>
         <td>40</td>
         <td>1000</td>
      </tr>
      <tr>
         <td>Czas wykonania [ms]</td>
         <td>0.008&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.01&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.181&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
      </tr>
   </tbody>
</table>

