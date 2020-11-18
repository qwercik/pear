# Język pear

Język Pear jest językiem programowania w logice, inspirowanym językiem Prolog. Głównym celem autora było stworzenie języka, który przy minimalnym stopniu skomplikowania składni, oferowałby rozsądne możliwości.

Programy w *Pear* zbudowane są z modułów. Każdy moduł znajduje się w osobnym pliku, a każdy plik jest zarazem modułem.
```
module(
    author('Autor'),
    description('Opis'),
    def(predykat(argument_1, argument_2, multi(kilka_argumentow), argument_n), warunek),
    query(warunek)
)
```

Minimalna biblioteka standardowa:
    - eval(expression, result) - predykat ewaluuje wyrażenie matematyczne i uzgadnia jego wynik ze zmienną result

    - and(multi(predicates)) - predykat przyjmuje dowolną liczbę argumentów; uruchamia wszystkie wszystkie wywołania predykatów, które do niego przekazano i zwraca prawdę jeżeli wszystkie z nich zwróciły prawdę
    - or(multi(predicates)) - predykat analogiczny do powyższego, ale zwraca prawdę jeżeli dowolny z elementów zwróci prawdę. Jest przyczyną wykonywania nawrotów

    - call(predicate) - wywołuje predykat
    - unify(left, right) - uzgadnia dwa termy
    - functor(expression, name) - nazwa funkcji stanowiącej wyrażenie
    - arity(expression, arity) - arność funkcji stanowiącej wyrażenie
    - argument(expression, n, argument) - uzgadnia zmienną argument z n-tym argumentem funkcji (indeksacja od 0)

    - `is_int(value)` - jest prawdziwa jeżeli wartość jest intem
    - `is_float(value)` - jest prawdziwa, jeżeli wartość jest floatem
    - `is_string(value)` - jest prawdziwa, jeżeli wartość jest stringiem
    - `to_int(value, converted)` - konwertuje wartość do inta
    - `to_float(value, converted)` - konweruje wartość do floata
    - `to_string(value, converted)` - konwertuje wartość do stringa

    - `append(multi(sublists), result)` - scala listy w jedną

