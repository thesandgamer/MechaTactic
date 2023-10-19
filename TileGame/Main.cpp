#include "Engine.h"

//++ToDo: Faire en sorte de passer le jeu en 3d:
// Enlever le contrôle au joueur quand une unité s'active
// Camera 3d: controllable(pour l'instant utiliser camear free)
// Dessin du chemin que le mecha va emprinter: 
    // Indicateur du mecha selectionné
    // Indicateur de la case sur laquelle est la souris(mettre ça dans curseur)
    // Dessiner un chemin de cases en cases sur lequels va aller le mécha
// Ui qui montre notre team et quand on clique dessus ça les séléctionne et focus la cam dessus

// En plus:
// Faire en sorte que les mechas attatquent
// Faire une IA pour les mechas ennemis
// Améliorer le A* pour le rendre mieux
// Faire une map plus grande avec de la hauteur(map générée procéduralement), et avec un A* pas en grille


//++ToDo:
//  Créer un système pour permettre de mettre en lumière des cases:
//      Les cases sur lesquelles le mecha va se déplacer
//      Les cases d'attaque possible
//      ??NotNow?? les cases de déplacement possible
//

//++ToDo:
// Faire en sorte que les mécha puissen se déplacer et utiliser une capâcitée
// Faire un système de vie
//


/*
 Si on clique avec une capacité hors d'une bonne case déséléctionne la capacité
 Si on déséléctionne capacité repase en mode mouvement
 Si clique sur case pas acessible en mode déplacement déséléctionne le mécha
 Mecha reste séléctionné quand finit déplacement mais peut plus bouger

Selected: 
	Affiche son ui en bas à gauche
	Entouré de vert 
	Barre de vie s'affiche en dessus

Selected et peut bouger:
	Pareil sélécted 
	Zone où peut se déplacer

Hover(tant que hover)
	Zone où peut se déplacer en plus clair
	Pareil selected

Hover et peut bouger
	Pareil Hover et seletec peut bouger
	
	
Selected et peut rien faire:
	Pareil sélécted
	Turn over marqué dans UI
	Boutons grisé
*/
/*
* Life Manager C++:
Le rendre le plus indépendant possible

Vie Maximum
Vie current
Armure
f TakeDamages
f Death
e onDeath

Damage Manager:
f MakeDamages(LifeManager& toDamages,DamageData data)

str DamageData:
Damages to make
Armor reducing(in %)

*/



int main(int argc, char** args)
{
    Engine engine;
	engine.run();
	return 0;


}

