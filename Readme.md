Alebo o inštalácii editora.

# Prerekvizity #
Qt 4 (qtcore, qtgui), g++, make, svn

# Instalacia #
  * treba stiahnut source kod z "source" tabu cez svn
  * nasledne treba vytvorit Makefile pomocou `qmake -qt=4`
  * `make`
  * potrebujeme este skompilovat wrapper na testovac: `cd testovac && g++ -o wrapper wrapper-mj-${arch}.c` kde $arch je bud x86 alebo amd64
  * nasledne si mozete uzivat pomocou `./editor`

# Kupony #
Ak chcete kupony (a nechcete dojst do ksp a behat okolo matfyzu ci drepovat na T2), tak
nejake kody su v codes.txt, najkratsie su za 100 kreditov a kazde dalsie pismenko zdvojnasobuje hodnotu. Kazdy kupon sa ale da pouzit najviac raz.