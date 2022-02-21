#include "jeu.hh"
#include <iostream>
using namespace std;

//--------------------------------------------------------------
int main() {
    Jeu monjeu;  // initialise le jeu
    string mouvement;
    bool stop(false);
    monjeu.affiche();
    do
    {
        cout << "Coup (eg. a1a8) ? ";
        cin >> mouvement;
        if (mouvement != "/quit") {
            // découper case origine et destination
            string orig = mouvement.substr(0, 2);
            string dest = mouvement.substr(2, 2);
            monjeu.deplace("Partie 1", orig, dest);
            monjeu.affiche();
        }
        else stop=true;
    } while (!stop);
}