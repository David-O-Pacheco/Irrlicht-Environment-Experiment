#pragma once
#include <string>
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;


class Billboards {
public:


	Billboards(io::path textureString, dimension2d<f32> size, vector3df position, IVideoDriver* driver, ISceneManager* manager);

	Billboards();

private:

};