#include "Models.h"


Models::Models(io::path meshString, io::path textureString, vector3df position, vector3df rotation, vector3df scale, IVideoDriver* driver, ISceneManager* manager){

	model = manager->getMesh(meshString);
	modelNode = manager->addMeshSceneNode(model);
	modelNode->setMaterialTexture(0, driver->getTexture(textureString));
	modelNode->setMaterialFlag(EMF_LIGHTING, false);
	modelNode->setPosition(vector3df(position));
	modelNode->setRotation(vector3df(rotation));
	modelNode->setScale(vector3df(scale));

}

Models::Models() {
	//Incase the array of models is not full.
}
