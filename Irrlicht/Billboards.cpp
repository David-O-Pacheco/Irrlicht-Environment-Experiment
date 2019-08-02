#include "Billboards.h"




Billboards::Billboards(io::path textureString, dimension2d<f32> size, vector3df position, IVideoDriver* driver, ISceneManager* manager) {

	auto billboard = manager->addBillboardSceneNode(NULL, size, position);
	billboard->setMaterialTexture(0, driver->getTexture(textureString));
	billboard->setMaterialFlag(EMF_LIGHTING, false);
	billboard->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);

}

Billboards::Billboards() {
	//Incase array of billboards isn't full
}

