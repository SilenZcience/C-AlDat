# Anforderungen an die Testfälle

Schreiben Sie Ihre Testfälle in die Dateien in ```testcases/```. Die Testfälle
sollen das Format
```
<Anzahl Schlüssel n>
<Schlüssel 1>
<Schlüssel 2>
...
<Schlüssel n>
```
haben. Jeder Schlüssel ist eine ganze Zahl

## Testfälle

Finden Sie Testfälle gemäß der unten beschriebenen Laufzeitanforderungen.
**Gewertet werden die Laufzeiten auf dem Server!**

## InsertionSort

- ```insertionsort1.in```: Finden Sie eine Eingabe mit genau 1.000.000 Schlüsseln, auf denen InsertionSort maximal 150ms läuft.
- ```insertionsort2.in```: Finden Sie eine Eingabe mit 100.000 Schlüsseln, auf denen InsertionSort mindestens 2500ms, aber maximal 3500ms läuft

## SelectionSort

- ```selectionsort1.in```: Finden Sie eine Eingabe mit einer Schlüsselanzahl ihrer Wahl, auf denen SelectionSort
mindestens 800ms, aber höchstens 1200ms läuft.
- ```selectionsort2.in```: Finden Sie eine Eingabe mit einer Schlüsselanzahl ihrer Wahl, auf denen SelectionSort
mindestens 2000ms, aber höchstens 3000ms läuft.

## MergeSort

- ```mergesort1.in```: Finden Sie eine Eingabe mit genau 1.000.000 Schlüsseln, auf denen MergeSort länger als 210ms läuft (maximal 500ms).
- ```mergesort2.in```: Finden Sie eine Eingabe mit einer genau 1.000.000 Schlüsseln, auf denen MergeSort höchstens 190ms läuft.

## QuickSort
- ```quicksort1.in```: Finden Sie eine Eingabe mit 75.000 Schlüsseln, auf der QuickSort mindestens 1000ms, aber höchstens 200ms läuft.
- ```quicksort2.in```: Finden Sie eine Eingabe mit 1.000.000 Schlüsseln, auf denen QuickSort maximal 400ms läuft.



