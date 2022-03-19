#include <iostream>
#include <string>
#include "jeu.hh"
#include "square.hh"
#include "echiquier.hh"

#include "macro.hh"
using namespace std;

//--------------------------------------------------------------
int main() {
    Jeu monjeu;  // initialise le jeu
    bool stop(false);
    monjeu.affiche();
    string mouvement;
    do
    {
        mouvement.clear();    
        cout <<  couleur_to_str(monjeu.get_couleur()) << ": Coup (eg. a1a8) ? ";
        cin >> mouvement;
        //catch le ctrl+d
        if (mouvement == "/quit" || mouvement.empty())
            break;

        //check syntaxe
        if(!saisie_correcte(mouvement)){
            if (saisie_correcte_grandroque(mouvement))
                {/* code pour troquer */}
            else if (saisie_correcte_petitroque(mouvement))
                {/* code */}
            else{
                INFO("erreur sintaxe du coup");
                continue;
            }
        }
        //lower case
        mouvement[0] = tolower(mouvement[0]);
        mouvement[2] = tolower(mouvement[2]);
        // découper case origine et destination
        string orig = mouvement.substr(0, 2);
        string dest = mouvement.substr(2, 2);
        if(monjeu.deplace(orig, dest)==true)
            monjeu.affiche();

    } while (!stop);

    return 0;
}