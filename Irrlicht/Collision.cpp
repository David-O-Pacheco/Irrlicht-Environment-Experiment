#include "Collision.h"

CollisionDetection::CollisionDetection(IrrlichtDevice* device, IMeshSceneNode* player, IMeshSceneNode* object) {

	aabbox3d<f32> node1_aabb = player->getTransformedBoundingBox();
	aabbox3d<f32> node2_aabb = object->getTransformedBoundingBox();

	if (node1_aabb.intersectsWithBox(node2_aabb)) {
		FPSCam->setPosition(playerPosThen);
		device->setWindowCaption(L"Collision Detected");
	}
	else {
		playerPosThen = FPSCam->getPosition();
		device->setWindowCaption(L"No Collision Detection");
	}
}

CollisionDetection::CollisionDetection() {

}