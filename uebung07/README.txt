Übung 07

Contributors:
Rayk Kretzschmar
Bohdan Babii


Exercise 7.1
AXPY.cpp kompilieren und ausführen
Daten werden in output.csv gespeichert
plot_axpy_times.py für die Visualisierung nutzen

Für größere Vektorgrößen zeigen die gemessenen Speed-ups, dass sie oft nicht ideal sind und 
hinter den theoretisch erwarteten Speed-ups zurückbleiben. Dies liegt an verschiedenen Faktoren wie:

Overhead der Parallelisierung: Der Overhead durch das Verwalten der Threads und die Synchronisation 
kann die Geschwindigkeit verringern.

Lastverteilung: Ungleichmäßige Lastverteilung kann dazu führen, dass einige Threads länger arbeiten 
als andere, was die Gesamtausführungszeit verlängert.

Speicherzugriff: Der Zugriff auf den Hauptspeicher kann zu Engpässen führen, insbesondere wenn mehrere 
Threads gleichzeitig darauf zugreifen.

Die Ergebnisse verdeutlichen, dass parallele Algorithmen erhebliche Leistungssteigerungen bieten 
können, insbesondere bei sehr großen Vektoren. Allerdings gibt es praktische Grenzen und Overheads, 
die berücksichtigen werden müssen, um die Effizienz der Parallelisierung zu maximieren.



Exercise 7.2
pnorm.cpp kompilieren und ausführen
Daten werden in pnorm.csv gespeichert
plot_pnorm_times.py für die Visualisierung nutzen

Es war unklar welche Werte für p zu nutzen waren. Daher haben wir es
für p=1, 2 und infinity jeweils einmal laufen lassen.

In der Visualisierung können die Unterschiede angesehen werden.

Bei größeren Vektorgrößen (ab n >= 100000) zeigen parallele Berechnungen signifikante 
Leistungsverbesserungen. Mit zunehmender Anzahl von Threads nähern sich die tatsächlichen 
Geschwindigkeitssteigerungen den idealen theoretischen Geschwindigkeitssteigerungen an. 
Dieser Trend ist besonders bei einer höheren Anzahl von Threads deutlich. Allerdings 
zeigt die inf-Norm durchweg geringere Geschwindigkeitssteigerungen aufgrund der inhärenten 
Komplexität der Parallelisierung der Max-Operation und der damit verbundenen Overheads.