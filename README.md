# ProjecteAlgoritmia-8

---

**Projecte de l'assignatura d'Algoritmia, Q2 2022/23**

Integrants del grup:

- Lluis Llull  `lluis.llull.riera@estudiantat.upc.edu`

- Miquel Muñoz `miquel.munoz.garcia-ramos@estudiantat.upc.edu`

- Marti Recalde `marti.recalde@estudiantat.upc.edu`

- Iván Serrano `ivan.serrano.hernandez@estudiantat.upc.edu`

---

### Usage

Per compilar tots els fitxers.

```bash
make
```

Per netejar d'executables i outputs.

```bash
make clean
```

X: IC | LT

*Usage* del programa per executar els algorismes voraços.

```bash
./difusioX                     # for manual input
./difusioX  graph_name         # input graph from file
./difusioX  graph_name test    # test propagation
```

*Usage* del programa per executar els algorismes voraços.

```bash
./greedyX                    # for manual input
./greedyX graph_name         # input graph from file
./greedyX graph_name test    # test propagation
```

*Usage* del programa per executar l'algorisme de cerca local.

```bash
./localSearchX                    # for manual input
./localSearchx graph_name         # input graph from file
./localSearchX graph_name test    # test propagation
```

*Usage* del programa per executar l'algorisme de *simulated annealing*.

```bash
./metaheuristicX                    # for manual input
./metaheuristicX  graph_name         # input graph from file
./metaheuristicX  graph_name test    # test propagation
```

Totes les sortides dels algorismes es redirigeixen a un fitxer de text pla, on es mostren els resultats i les mètriques de l'execució (temps i nombre d'iteracions).

Per comoditat tots els executables tenen una opció per probar la propagació.
