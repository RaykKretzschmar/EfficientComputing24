Rayk Kretzschmar
Bohdan Babii

- Programm compilieren und dann mit einem Argument für i ausführen
- Das Programm erstellt einen Vektor mit Länge n = 1024 * i und eine Matrix mit der Größe nXn und führt eine Matrix-Vektor-Multiplikation durch mit randomisierten Werten.

i = 1
Matrix size (n): 1024 x 1024
mit Transponierter Matrix: 
Execution time: 0.010727 seconds
ohne Transponierte Matrix: 
Execution time: 0.007063 seconds

i = 4
Matrix size (n): 4096 x 4096
mit Transponierter Matrix: 
Execution time: 0.359750 seconds
ohne Transponierte Matrix: 
Execution time: 0.058360 seconds

i = 8
Matrix size (n): 8192 x 8192
mit Transponierter Matrix: 
Execution time: 1.123960 seconds
ohne Transponierte Matrix: 
Execution time: 0.231570 seconds

i = 16
Matrix size (n): 16384 x 16384
mit Transponierter Matrix: 
Execution time: 4.021603 seconds
ohne Transponierte Matrix: 
Execution time: 0.954313 seconds


Erklärung:
Der Unterschied in den Ausführungszeiten zwischen dem transponierten Matrix-Vektor-Produkt und 
dem regulären Matrix-Vektor-Produkt liegt hauptsächlich am Zugriffsmuster auf den Speicher.

Das reguläre Matrix-Vektor-Produkt hat ein sequentielles und zusammenhängendes Zugriffsmuster auf 
den Speicher, was cache-freundlich ist und zu guter Leistung führt.

Im Gegensatz dazu hat das transponierte Matrix-Vektor-Produkt ein nicht sequentielles und 
nicht zusammenhängendes Zugriffsmuster auf den Speicher, was zu schlechter Cache-Lokalität, 
mehr Cache-Misses und langsamerer Ausführung führt.

Wenn die Matrixgröße zunimmt, wird der Unterschied in den Ausführungszeiten noch deutlicher, 
weil die Häufigkeit und Kosten von Cache-Misses zunehmen.