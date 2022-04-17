# jeux d'echeque
projet de jeux d'echeque

## Comment **compiler**:
### produire l'executable:
```make echecs``` 


## Comment **executer** le programe:
`./echecs` *(lancer une partie)*
## Comment **rejouer** une partie:
- **manuelement**```./echecs < parties/pat.auchan```
- **simplement** ```make pat``` *(executable a jour)*
 
 
 les test sont contenue dans le dossier *parties* est on comme extantion *.auchan*


## utilitaire :
### faire tout les test:
make produit les test est l'executable
```make```
### rejouer un valgrind
```make r[noms du test]```
utilise des cache générée par make (plus rapide)
### raport lcov:
```make lcov``` permet d'avoir une estimation réel du nombre de ligne executer par le programe
### netoyer le repertoire
```make clean```
## Difficulter rencontrée
- constructueur des piece oneline qui stoque la chaine de caractere
- pour lester la mise en echeque j'ai du faire des constructeur pour dupliquer mon object compliquer car celuit cis contien d'autre object qui a leur tour doive être dupliquer
- fuite mémoire grace a l'outille **valgrind**

# Mode MULTIJOUEUR en LIGNE
- ```./server.sh``` lance le serveur
- ```./client.sh [ADDRESS]``` lance la partie (defaut utilise localhost)