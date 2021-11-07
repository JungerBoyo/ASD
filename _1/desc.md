##<header> Rozwiązanie naiwne </header>

W rozwiązaniu naiwnym, najpierw wczytuje się wartość 
danej na std::bitset, następnie przeszukiwana jest tablica
dotychczasowych bitsetów, jeśli wartość wystąpiła inkrementuje 
się przyporządkowaną jej sume, o 1 i sprawdza czy jest
większa od dotychczasowej wartości maksymalnej, jeśli 
jest większa przypisuje się nową wartość maksymalną.
Jeśli wartość nie wystąpiła, dodaje się ją do tablicy.


*      T(N) =  ~N(25 + N/2 + 1) = N^2/2 + 26n  [zakładając najgorszy przypadek - wszystkie dane są unikalne i długości 25 bitów]
*      Złożoność :: kwadratowa => O(N^2)
<br />


###<header> Testy </header>
<table>
   <thead>
      <tr>
         <th>Testy</th>
         <th>Mały1</th>
         <th>Mały2</th>
         <th>Średni</th>
         <th>Duży</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Liczba danych</td>
         <td>20</td>
         <td>40</td>
         <td>1000</td>
         <td>1000000&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
      </tr>
      <tr>
         <td>Czas wykonania(debugmode)</td>
         <td>0.01ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.03ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.741ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>6.7min</td>
      </tr>
      <tr>
         <td>Czas wykonania(releasemode)</td>
         <td>0.011ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.007ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.128ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>15.614s</td>
      </tr>
      <tr>
        <td>Zużycie pamięci</td>
        <td> ~250B   </td>
        <td> ~500B   </td>
        <td> ~12kB   </td>
        <td> ~12MB   </td>
      </tr>
   </tbody>
</table>

##<header> Rozwiązanie szybkie</header>
<br /><br />
W rozwiązaniu szybkim najpierw wczytuje się elementy do tablicy jednocześnie szukając pośród
nich minimum oraz maksimum. Następnie deklaruje się drugą tablice której indeksami są wartości
danych z pierwszej tablicy. Podczas jej deklaracji pod uwagę brana jest wcześniej znaleziona wartość
minimum oraz maksimum aby możliwie zmniejszyć jej zakres a tym samym zużycie pamięci. Druga pętla 
algorytmu iteruje po danych z pierwszej tablicy, i traktując je jako indeksy drugiej inkrementuje 
wartości drugiej tablicy jednocześnie sprawdzając czy wartość jest większa od dotychczasowego maksimum, jeśli
tak następuje aktualizacja zmiennej max.

*      T(N) = N(25 + 2) + N = 29n  [zakładając najgorszy przypadek - wszystkie dane są długości 25 bitów]
*      Złożoność :: liniowa => O(N)


<br />

###<header> Testy</header>
<table>
   <thead>
      <tr>
         <th>Testy</th>
         <th>Mały1</th>
         <th>Mały2</th>
         <th>Średni</th>
         <th>Duży</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>Liczba danych</td>
         <td>20</td>
         <td>40</td>
         <td>1000</td>
         <td>1000000&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
      </tr>
      <tr>
         <td>Czas wykonania(debugmode)</td>
         <td>0.009ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.008ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.132ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>322.758ms</td>
      </tr>
      <tr>
         <td>Czas wykonania(releasemode)</td>
         <td>0.005ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.005ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>0.082ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
         <td>130.894ms</td>
      </tr>
      <tr>
        <td>Zużycie pamięci</td>
        <td>  ~144B  </td>
        <td>  ~220B  </td>
        <td>  ~4.5kB </td>
        <td>  ~4.8MB </td>
      </tr>
   </tbody>
</table>
