<?php
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL &~ E_NOTICE &~ E_DEPRECATED);

    require '../vendor/autoload.php' ;
    include 'mongo.php';

    $flag=$_REQUEST['flag'];

    switch($flag)
    {
    case 1:

    echo "<h4>Dane wejściowe</h4>
    n -  liczba elementów w sortowanym zbiorze<br>
    t[] -  zbiór n-elementowy, który będzie sortowany. Elementy zbioru mają indeksy od 1 do n.
    <br>
    <h2>Lista kroków</h2>
    K1 - Dla j=1,2,..,n-1:<br>
    Wykonuj krok K2<br>
    K2 - Dla i=1,2,..,n-1:<br>
    Jeśli t[i]>d[i+1]<br>
    to swap(t[i],t[i+1])<br>
    <button onclick='hideAlgorithm(".$flag.")'>Ukryj pseudokod</button>";

        break;

    case 2:

        echo "<h4>Dane wejściowe</h4>
        n -  liczba elementów w sortowanym zbiorze<br>
        t[] -  zbiór n-elementowy, który będzie sortowany. Elementy zbioru mają indeksy od 1 do n.
        <h4>Dane wejściowe</h4>
        x - zawiera wybrany ze zbioru element.
        <br>
        <h2>Lista kroków</h2>
        K1 - Dla j=n-1,n-2,..,1:<br>
        wykonuj kroki K2..K4<br>
        K2 - x = t[j], i = j+1<br>
        Dopóki (i &#8804 n) oraz (x > t[i]):<br>
        wykonuj t[i-1] = t[i], i = i+1<br>
        K4 - t[i-1] = x<br>
        <button onclick='hideAlgorithm(".$flag.")'>Ukryj pseudokod</button>";
        break;

        case 3:

            echo "<h4>Dane wejściowe</h4>
            n -  liczba elementów w sortowanym zbiorze<br>
            t[] -  zbiór n-elementowy, który będzie sortowany. Elementy zbioru mają indeksy od 1 do n.
            <h4>Dane pomocnicze</h4>
            x - zawiera wybrany ze zbioru element.
            p - pozycja elementu minimalnego w zbiorze t[]
            <br>
            <h2>Lista kroków</h2>
            K1 - dla j=1,2,..,n-1:<br>
            wykonuj kroki K2..K4
            K2 - p = j<br>
            K3 - Dla i = j + 1, j + 2,..,n<br>
            jeśli t[i] < t[p]<br>
            to p=i<br>
            K4 - swap(t[j],t[p])<br>
            <button onclick='hideAlgorithm(".$flag.")'>Ukryj pseudokod</button>";
            break;

        case 4:

            echo "<h2>Specyfikacja algorytmu scalania</h2><br>
            <b>Scalaj(i<sub>p</sub>,i<sub>s</sub>,i<sub>k</sub>)</b>
            <h4>Dane wejściowe</h4>
            t[] - scalany zbiór<br>
            i<sub>p</sub> - indeks pierwszego elemenu w młodszym podzbiorze<br>
            i<sub>s</sub> - indeks pierwszego elementu w satrszym podzbiorze<br>
            i<sub>k</sub> - indeks ostatniego elementu w starszym podzbiorze
            <h4>Dane pomocnicze</h4>
            p[] - zbiór pomocniczy, który zawiera tyle samo elementów co zbiór t[]<br>
            i<sub>1</sub> - indeks elementów w młodszej połowie zbioru t[]<br>
            i<sub>2</sub> - indeks elementów w starszej połowe zbioru t[]
            <h2> Lista kroków</h2>
            K1 - i<sub>1</sub>=i<sub>p</sub>, i<sub>2</sub> = i<sub>2</sub>, i = i<sub>p</sub><br>
            K2 - Dla i=i<sub>p</sub>, i<sub>p</sub> + 1,...,i<sub>k</sub><br>
            Jeśli (i<sub>1</sub> = i<sub>s</sub>) lub (i<sub>2</sub> < i<sub>k</sub>
            oraz t[i<sub>1</sub>] > t[i<sub>2</sub>])<br>
            to p[i] = t[i<sub>1</sub>], i<sub>1</sub> = i<sub>1</sub> + 1<br>
            K3 - Dla i = i<sub>p</sub>, i<sub>p</sub>+1,...,i<sub>k</sub><br>
            t[i] = p[i]<br>
            <br>
            <h2>Specyfikacja algorytmu sortującego</h2>
            <b>SortowaniePrzezScalanie(i<sub>p</sub>,i<sub>k</sub>)</b><br>
            <h4>Dane wejściowe</h4>
            t[] - sortowany zbiór<br>
            i<sub>p</sub> - indeks pierwszego elementu w młodszym podzbiorze<br>
            i<sub>k</sub> - indeks ostatniego elementu w starszym podzbiorze<br>
            <h4>Zmienne pomocnicze</h4>
            i<sub>s</sub> - indeks pierwszego elementu w starszym podzbiorze<br>
            <h2>Lista kroków</h2>
            K1 - i<sub>s</sub> = (i<sub>p</sub> + i<sub>k</sub> + 1) / 2<br>
            K2 - Jeśli i<sub>s</sub> - i<sub>p</sub> > 1 to SortujPrzezScalanie(i<sub>p</sub>,i<sub>s</sub> -1)<br>
            K3 - Jeśli i<sub>k</sub> - i<sub>s</sub> > 0 to SortujPrzezScalanie(i<sub>s</sub>,i<sub>k</sub>)<br>
            K4 - Scalaj(i<sub>p</sub,i<sub>s</sub>,i<sub>k</sub><br>
            <button onclick='hideAlgorithm(".$flag.")'>Ukryj pseudokod</button>";
            break;

        case 5:
            echo "<h2>Specyfikacja algorytmu 'Quick sort'</h2>
            <b>QuickSort(l,p)</b>
            <h4>Dane wejściowe</h4>
            t[] - Zbiór do posortowania<br>
            l - indeks pierwszego elementu w zbiorze<br>
            p - indeks ostatniego elementu w zbiorze
            <h4>Zmienne pomocnicze</h4>
            piwot - element podziałowy
            <h2>Lista kroków</h2>
            K1 - i = (l+p)/2
            K2 - piwot - t[i], t[i] = t[p], j = lewy<br>
            K3 - Dla i=l, l+1,...,p-1<br>
            wykonuj kroki K4...K5<br>
            K4 - Jeśli t[i] > piwot to 'continue'<br>
            K5 - swap(t[i],t[j]), j = j+1<br>
            K6 - t[p] = t[j], t[j] = piwot<br>
            K7 - Jeśli l < j-1 to QuickSort(l,j-1)<br>
            K8 - Jeśli j+1 < p to QuickSort(j+1,p)<br>
            <button onclick='hideAlgorithm(".$flag.")'>Ukryj pseudokod</button>";
            break;
           
        case 6:

            echo "<h2>Algorytm budowania kopca</h2>
            <h4>Dane wejściowe</h4>
            t[] = Zbiór zawierający elementy do wstawienia do kopca. Numeracja elementów zaczyna się od 1<br>
            n - ilość elementów w zbiorze
            <h4>Zmienne pomocnicze</h4>
            i - iterator umieszczający kolejne elementy w kopcu, i=2,3,...,n<br>
            j,k - indeksy elementów leżących na ścieżce od wstawianego elementu do korzenia<br>
            x - przechowuje tymczasowo element wstawiany do kopca<br>
            <h2>Lista kroków</h2>
            K1 - dla i = 2,3,...,n<br>
            Wykonuj kroki K2...K5<br>
            K2 - j = i, k = j/2<br>
            K3 - x = t[i]<br>
            K4 - Dopóki (k > 0) oraz (t[k] < x)<br>
            wykonuj:<br>
            t[j] = t[k]<br>
            j = k<br>
            k = j/2<br>
            K5 - t[j] = x<br>

            <h2>Algorytm rozbioru kopca</h2>
            <h4>Dane wejściowe</h4>
            t[] = Zbiór zawierający elementy do wstawienia do kopca. Numeracja elementów zaczyna się od 1<br>
            n - ilość elementów w zbiorze
            <h4>Zmienne pomocnicze</h4>
            i - iterator umieszczający kolejne elementy w kopcu, i=n,n-1,...,2<br>
            j,k - indeksy elementów leżących na ścieżce w dół do korzenia<br>
            m - indeks większego z dwóch elementów potomnych<br>
            <h2>Lista kroków</h2>
            K1 - Dla i = n,n-1,...,2:<br>
            Wykonuj kroki K2...K8<br>
            K2 - swap(t[1],t[i])<br>
            K3 - j = 1, k = 2<br>
            K4 - Dopóki k < i<br>
            Wykonuj kroki K5 - K8<br>
            K5 - Jeśli (k + 1 < i) oraz (t[k+i) > t[k] to m = k+1<br>
            inaczej m = k<br>
            K6 - Jeśli t[m] &#8804 t[j] to wyjdź z pętli K4<br>
            K7 - swap(t[j],t[m])<br>
            K8 - j = m, k = j+1<br>
            
            <h2>Algorytm sortowania przez kopcowanie</h2>
            <h2>Lista kroków</h2>
            K1 - Stwórz kopiec<br>
            K2 - Rozbierz kopiec<br>
            <button onclick='hideAlgorithm(".$flag.")'>Ukryj pseudokod</button>";
            break;

        default:
            break;
    }

?>