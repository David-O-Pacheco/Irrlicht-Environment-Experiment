#pragma once
#include <string>
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;


class Models {
public:

	IMesh* model;
	IMeshSceneNode* modelNode;

	Models(io::path meshString, io::path textureString, vector3df position, vector3df rotation, vector3df scale, IVideoDriver* driver, ISceneManager* manager);

	Models();

private:

};