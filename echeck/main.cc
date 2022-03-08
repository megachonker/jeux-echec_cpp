#include <iostream>
#include <string>
#include "jeu.hh"
#include "square.hh"
#include "echiquier.hh"

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
        if (mouvement != "/quit" && !mouvement.empty()) {
            //lower case
            mouvement[0] = tolower(mouvement[0]);
            mouvement[2] = tolower(mouvement[2]);

            //check syntaxe
            if(!saisie_correcte(mouvement)){
                if (saisie_correcte_petitroque(mouvement))
                    {/* code pour troquer */}
                else{
                    cout << "erreur sintaxe du coup" << endl;
                    continue;
                }
            }
            // découper case origine et destination
            string orig = mouvement.substr(0, 2);
            string dest = mouvement.substr(2, 2);
            if(monjeu.deplace(orig, dest)==true)
                monjeu.affiche();
        }
        else stop=true;
    } while (!stop);

    return 0;
}