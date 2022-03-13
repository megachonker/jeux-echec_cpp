#include "colision.hh"
#include <iostream>




/**
 * @brief verifie les piece ayant des colision
 * 
 *      slidecheque pourait retourner une carte des collision est apres on verrifie si la piece dedant donc on fait le call de la map si elle existe pas !     
 * 
 *      pour plus de lisibilitée j'ai 2 énume qui veule dire les meme chause utile ?
 * @param source 
 * @param direction 
 * @return true 
 * @return false 
 */
bool Colision::slidecheck(Piece * source,Square const position_dst){

        //choix bonne piece
        switch (source->get_type())
        {
        case tour:      return  slidecheck(source,position_dst,lignecolone    );
        case fou:       return  slidecheck(source,position_dst,diagonal       );
        case dame:      return  slidecheck(source,position_dst,diagonal       ) 
                        ||      slidecheck(source,position_dst,lignecolone    );
        default: return true;
        }
        return true;
}

/**
 * @brief vérifie si le déplacemetn est possible sans colision
 * 
 * vérifie si la colymap est bonne puis vérifie le masque avec la position de destination si elle n'es pas bonne le regenère 
 * 
 * @param source 
 * @param position_dst 
 * @param look 
 * @return true 
 * @return false 
 */
bool Colision::slidecheck(Piece *source,Square position_dst,direction const look){
        if (!source->colisionvalide)
                gen_colimap(source,look);
        
        if (source->get_colision(position_dst)){
                std::cout << "collision avec une piece !" << std::endl;
                return false;
        }
        
        return true;
}

/**
 * @brief génère une carte des colision est raporte s'il y a eux colision
 * 
 * @param source 
 * @param look 
 * @return true 
 * @return false 
 */
void Colision::gen_colimap(Piece * source,direction look) {/////////////manque la colimap
        Square decalage = look==lignecolone ? Square(1,0) : Square(1,1);
        Square virtual_case = source->get_pos();

        slide(virtual_case,decalage);
        virtual_case.inv();
        slide(virtual_case,decalage);
        virtual_case.swap();
        slide(virtual_case,decalage);
}


/**
 * @brief va avancer la piece j'usqua une colision
 * 
 * @param origine enplacement pour tester
 * @param decalage direction du déplacement
 * @return true pas de colision
 * @return false il y a eux une colision
 */
void Colision::slide(Square origine,Square decalage){
        //tan que la position a tester est dans le jeux decheque
        int flag=true;
        while (flag){
                // colisionmap_map[]++++++++++++++ faire le masque
                if (origine.inside())
                        flag=true;
                if (est_case_vide(origine))
                        flag=false;
                origine+=decalage;
        }
}
