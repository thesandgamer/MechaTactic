#include "Engine.h"

//++ToDo: Faire en sorte de passer le jeu en 3d:
// Enlever le contr�le au joueur quand une unit� s'active
// Camera 3d: controllable(pour l'instant utiliser camear free)
// Dessin du chemin que le mecha va emprinter: 
    // Indicateur du mecha selectionn�
    // Indicateur de la case sur laquelle est la souris(mettre �a dans curseur)
    // Dessiner un chemin de cases en cases sur lequels va aller le m�cha
// Ui qui montre notre team et quand on clique dessus �a les s�l�ctionne et focus la cam dessus

// En plus:
// Faire en sorte que les mechas attatquent
// Faire une IA pour les mechas ennemis
// Am�liorer le A* pour le rendre mieux
// Faire une map plus grande avec de la hauteur(map g�n�r�e proc�duralement), et avec un A* pas en grille


//++ToDo:
//  Cr�er un syst�me pour permettre de mettre en lumi�re des cases:
//      Les cases sur lesquelles le mecha va se d�placer
//      Les cases d'attaque possible
//      ??NotNow?? les cases de d�placement possible
//

//++ToDo:
// Faire en sorte que les m�cha puissen se d�placer et utiliser une cap�cit�e
// Faire un syst�me de vie
//


/*
 Si on clique avec une capacit� hors d'une bonne case d�s�l�ctionne la capacit�
 Si on d�s�l�ctionne capacit� repase en mode mouvement
 Si clique sur case pas acessible en mode d�placement d�s�l�ctionne le m�cha
 Mecha reste s�l�ctionn� quand finit d�placement mais peut plus bouger

Selected: 
	Affiche son ui en bas � gauche
	Entour� de vert 
	Barre de vie s'affiche en dessus

Selected et peut bouger:
	Pareil s�l�cted 
	Zone o� peut se d�placer

Hover(tant que hover)
	Zone o� peut se d�placer en plus clair
	Pareil selected

Hover et peut bouger
	Pareil Hover et seletec peut bouger
	
	
Selected et peut rien faire:
	Pareil s�l�cted
	Turn over marqu� dans UI
	Boutons gris�
*/
/*
* Life Manager C++:
Le rendre le plus ind�pendant possible

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

