# jeux d'echeque
projet de jeux d'echeque

## Comment **compiler**:
### produire l'executable:
```make echecs``` 
### debug **Flag**
dans la variable debug du makefile est stoquer les différent flag suivant
- **INFO_ON** *message d'infomation pour l'utilisateur*
- **WARN_ON** *événement lier au fonctionement interne*
- **DEBUG_ON** *message de debug général*
- **DEBUG_EMP** *savior le coup trouver pour la solution empirique pour tester l'echeque*
- **VERBEUX_ON** *message de debug redondant*


## Comment **executer** le programe:
`./echecs` *(lancer une partie)*
## Comment **rejouer** une partie:
- **manuelement**```./echecs < parties/pat.auchan```
- **simplement** ```make pat``` *(executable a jour)*
 
 
 les test sont contenue dans le dossier *parties* est on comme extantion *.auchan*


## utilitaire :
### faire tout les test:
make produit les test est l'executable peut prendre 30seconde
```make```
### rejouer un test valgrind
```make r[noms du test]```
utilise des cache générée par make (plus rapide)
### raport lcov:
```make lcov``` permet d'avoir une estimation réel du nombre de ligne executer par le programe
### netoyer le repertoire
```make clean```
### forcer recompilation
en cas de changent de flag
```make r```

## Difficulter rencontrée
- constructueur des piece oneline qui stoque la chaine de caractere
- pour lester la mise en echeque j'ai du faire des constructeur pour dupliquer mon object compliquer car celuit cis contien d'autre object qui a leur tour doive être dupliquer
- fuite mémoire grace a l'outille **valgrind**
- comprendre par le débugue que le rois n'a pas le droit de manger quand il est en echeque

# Mode MULTIJOUEUR en LIGNE
- ```./server.sh``` lance le serveur
- ```./client.sh [ADDRESS]``` lance la partie (defaut utilise localhost)