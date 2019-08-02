#pragma once
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

class CollisionDetection {
public:

	ICameraSceneNode* FPSCam;

	vector3df playerPosThen = vector3df(3610, 150.05, 1740);;

	CollisionDetection(IrrlichtDevice* device, IMeshSceneNode* player, IMeshSceneNode* object);

	CollisionDetection();

private:

};