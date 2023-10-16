#include "MushMech.h"

#include "Utility.h"

MushMech::MushMech() : MechaParent()
{

}


MushMech::MushMech(Vector3 positionP) : MechaParent(positionP)
{
	
	model = Utility::GetInstance()->ChampiModel;
	texture = Utility::GetInstance()->champiTexture;

	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}


MushMech::~MushMech()
{
}
