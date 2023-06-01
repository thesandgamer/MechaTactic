#include "TreeMech.h"

#include "Utility.h"

TreeMech::TreeMech() : MechaParent()
{

}

TreeMech::TreeMech(Vector3 positionP) : MechaParent(positionP)
{
	
	model = Utility::GetInstance()->TreeModel;
	//texture = Utility::GetInstance()->treeTexture;

	//model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

TreeMech::~TreeMech()
{
	
}
