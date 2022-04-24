#include <iostream>
#include <string>
#include "jeu.hh"
#include "square.hh"
#include "echiquier.hh"

#include "macro.hh"
using namespace std;

int main() {
    Jeu monjeu;  // initialise le jeu
    monjeu.affiche();
    string mouvement;
    do
    {
        cout <<  couleur_to_str(monjeu.get_couleur()) << ": Coup (eg. a1a8) ? ";
        mouvement.clear();    
        cin >> mouvement;


        //Quite catch le ctrl+d
        if (mouvement == "/quit" || mouvement.empty())
            break;

        //Mouvement
        if(saisie_correcte(mouvement)){
            //lower case
            mouvement[0] = tolower(mouvement[0]);
            mouvement[2] = tolower(mouvement[2]);
            // découper case origine et destinationclear
            string orig = mouvement.substr(0, 2);
            string dest = mouvement.substr(2, 2);
            if(monjeu.deplace(orig, dest))
                monjeu.affiche();
        }
        //Grand rock
        else if (saisie_correcte_grandroque(mouvement)){
            monjeu.explain(monjeu.rock(true));
            INFO("vous faite le grand rock");
            monjeu.affiche();
        }
        //Petit rock
        else if (saisie_correcte_petitroque(mouvement)){
            monjeu.explain(monjeu.rock(false));
            INFO("vous faite le petit rock");
            monjeu.affiche();
        }
        //Erreur
        else
            INFO("erreur sintaxe du coup");

    //la partie prend elle fin ?
    } while (monjeu.fin());
    monjeu.print_canonical_position();
    return 0;
}