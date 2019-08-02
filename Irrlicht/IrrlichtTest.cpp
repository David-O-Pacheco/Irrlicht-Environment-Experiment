#include <irrlicht.h>
// #include "Collision.h"
#include "Billboards.h"
#include "Models.h"
#include "KeyReceiver.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

#pragma comment(lib, "irrlicht.lib")

Billboards billboard[10];
Models model[15];
// CollisionDetection colision[15];

//Main function
int main(void) {

	//Get KeyEventReiver class from header file. This allows us to use the KeyDown events.
	KeyEventReceiver ker;

	//Set speed of skybox rotation. This allows us to add moving clouds
	int cloudSpeed = 1;
	//Declared and set to true everytime W,A,S or D is pressed. We then use this to display coordinates or check for collisions only when a key is pressed.
	bool KeyDown = true;

	//Create device with custom parameters.
	IrrlichtDevice *device = createDevice(EDT_DIRECT3D9, dimension2d<u32>(1280, 920), 32, false, false, true, &ker);
	if (device == nullptr) return -1;

	//Declare video driver and scene manager. This then allows us to use and manipulate certain things in our scene. We'll be using these two variables later on.
	IVideoDriver *driver = device->getVideoDriver();
	ISceneManager *manager = device->getSceneManager();

	//Get FPS. This will then be used to compare to latest FPS. At a later stage, anytime the FPS variables don't match, it will update it on screen.
	s32 fpsThen = driver->getFPS();

	//Here we set the window caption to "Irrlicht Game" and the cursor visibility to false. Self explanatory.
	device->setWindowCaption(L"Irrlicht Game");
	device->getCursorControl()->setVisible(false);

	//Here we create a terrain scene node which we can then add a texture to it, a heightmap, a detailmap and lastly, change the parameters so we get high mountains/hills.
	ITerrainSceneNode *terrain = manager->addTerrainSceneNode("media/textures/heightmap2.png", 0, 1, vector3df(-6000, 0.0f, -6000), vector3df(0.0f, 0.0f, 0.0f), vector3df(150, 20.4f, 150), SColor(255,255,255,255), 5, ETPS_17, 4);
	
	//Here we set the texture for terrain. We also set a material flag for lighting as our scene/environment still doesn't have a light implemented into it. This "Material Flag" allows us to see the texture without problems.
	terrain->setMaterialTexture(0, driver->getTexture("media/textures/grass.jpg"));
	terrain->setMaterialFlag(EMF_LIGHTING, false);
	// L
	terrain->setMaterialTexture(1, driver->getTexture("media/textures/detailmap.jpg"));
	terrain->setMaterialType(EMT_DETAIL_MAP);

	//These two cameras are First Person and Third Person cameras. At a later stage we use them to move them around or set them to a specific location.
	ICameraSceneNode *FPSCam = manager->addCameraSceneNodeFPS(0, 100);
	ICameraSceneNode *TPSCam = manager->addCameraSceneNode();

	//Here we are creating a cube which will temporarily act as our player model. At a later stage within this code, we set the camera as a parent to the player to both move together.
	IMeshSceneNode *Player = manager->addCubeSceneNode(100);

	//Here we declare static text to go onto your User Interface. We use these later on to set them to coordinates/fps count, etc..
	IGUIStaticText *FPSText = device->getGUIEnvironment()->addStaticText(L"FPSTEXT", rect<s32>(10, 10, 100, 100), false, true);
	IGUIStaticText *POSXT = device->getGUIEnvironment()->addStaticText(L"POSx: ", rect<s32>(10, 30, 100, 100), false, true);
	IGUIStaticText *POSYT = device->getGUIEnvironment()->addStaticText(L"POSy: ", rect<s32>(10, 50, 100, 100), false, true);
	IGUIStaticText *POSZT = device->getGUIEnvironment()->addStaticText(L"POSz: ", rect<s32>(10, 70, 100, 100), false, true);
	IGUIStaticText *ROTX = device->getGUIEnvironment()->addStaticText(L"ROT: ", rect<s32>(10, 90, 100, 100), false, true);


	billboard[0] = Billboards("media/textures/billboard_tree1.png", dimension2d<f32>(1300, 1000), vector3df(2790, 400, 2740), driver, manager);
	billboard[1] = Billboards("media/textures/billboard_tree2.png", dimension2d<f32>(1300, 1000), vector3df(2790, 400, 2340), driver, manager);
	billboard[2] = Billboards("media/textures/billboard_tree2.png", dimension2d<f32>(1600, 1300), vector3df(3990, 500, 8990), driver, manager);
	billboard[3] = Billboards("media/textures/fire.png", dimension2d<f32>(650, 500), vector3df(23881, 170, 18972), driver, manager);
	billboard[4] = Billboards("media/textures/fire.png", dimension2d<f32>(850, 700), vector3df(11063, 3000, 14050), driver, manager);
	billboard[5] = Billboards("media/textures/billboard_building1.png", dimension2d<f32>(1500, 3000), vector3df(6943, 5032, -4210), driver, manager);
	billboard[6] = Billboards("media/textures/billboard_building2.png", dimension2d<f32>(1500, 3000), vector3df(8437, 4572, -4524), driver, manager);
	billboard[7] = Billboards("media/textures/billboard_building3.png", dimension2d<f32>(1500, 3000), vector3df(13310, 3085, -1390), driver, manager);
	billboard[8] = Billboards("media/textures/billboard_building4.png", dimension2d<f32>(1500, 3000), vector3df(13150, 3987, 1335), driver, manager);
	billboard[9] = Billboards("media/textures/billboard_building5.png", dimension2d<f32>(1500, 3700), vector3df(13609, 5056, -587), driver, manager);

	model[0] = Models("media/models/building1.obj", "media/textures/building1.jpg", vector3df(25571, 240, 11720), vector3df(0, 0, 0), vector3df(10, 10, 10), driver, manager);
	model[1] = Models("media/models/building2.obj", "media/textures/building2.jpg", vector3df(13757, 240, 8814), vector3df(0, 120, 0), vector3df(10, 10, 10), driver, manager);
	model[2] = Models("media/models/building3.obj", "media/textures/building3.jpg", vector3df(21685, 0, 19701), vector3df(0, -90, 0), vector3df(10, 10, 10), driver, manager);
	model[3] = Models("media/models/building4.obj", "media/textures/building4.jpg", vector3df(11033, 800, 13000), vector3df(0, 180, 0), vector3df(8, 8, 8), driver, manager);
	model[4] = Models("media/models/building5.obj", "media/textures/building5.jpg", vector3df(26000, 0, 20847), vector3df(0, -45, 0), vector3df(8, 8, 8), driver, manager);
	model[5] = Models("media/models/tree.obj", "media/textures/tree1.jpg", vector3df(19444, 240, 11337), vector3df(0 ,0, 0), vector3df(10, 10, 10), driver, manager);
	model[6] = Models("media/models/tree2.obj", "media/textures/tree2.jpg", vector3df(13309, 500, 12481), vector3df(0, 0, 0), vector3df(15, 15, 15), driver, manager);
	model[7] = Models("media/models/tree2.obj", "media/textures/tree2.jpg", vector3df(20676, 0, 19545), vector3df(0, 90, 0), vector3df(10, 10, 10), driver, manager);
	model[8] = Models("media/models/bush.obj", "media/textures/bush.jpg", vector3df(19361, 240, 11068), vector3df(0, 180, 0), vector3df(15, 15, 15), driver, manager);
	model[9] = Models("media/models/car.obj", "media/textures/car.jpg", vector3df(24520, 240, 11061), vector3df(0, 180, 0), vector3df(10, 10, 10), driver, manager);
	model[10] = Models("media/models/car.obj", "media/textures/car2.jpg", vector3df(23961, 0, 19402), vector3df(0, 0, 0), vector3df(10, 10, 10), driver, manager);
	model[11] = Models("media/models/hospital_vehicle.obj", "media/textures/hospital_vehicle.jpg", vector3df(11346, 800, 16061), vector3df(0, 270, 0), vector3df(10, 10, 10), driver, manager);
	model[12] = Models("media/models/street_lamp.obj", "media/textures/street_lamp.jpg", vector3df(23881, 0, 18972), vector3df(0, 180, 0), vector3df(10, 10, 10), driver, manager);
	model[13] = Models("media/models/traffic_lights.obj", "media/models/traffic_lights.jpg", vector3df(2199, 0, 6650), vector3df(0, 90, 0), vector3df(10, 10, 10), driver, manager);
	model[14] = Models("media/models/broken_bench.obj", "media/textures/broken_bench.jpg", vector3df(4332, 0, 8724), vector3df(0, 197, 0), vector3df(10, 10, 10), driver, manager);

	//Declaring and obtaining skybox textures which we then combine together to make the skybox.
	ITexture *skybox_up = driver->getTexture("media/textures/skybox_up.png");
	ITexture *skybox_down = driver->getTexture("media/textures/skybox_down.png");
	ITexture *skybox_left = driver->getTexture("media/textures/skybox_left.png");
	ITexture *skybox_right = driver->getTexture("media/textures/skybox_right.png");
	ITexture *skybox_forward = driver->getTexture("media/textures/skybox_forward.png");
	ITexture *skybox_back = driver->getTexture("media/textures/skybox_back.png");
	// L
	ISceneNode *skybox = manager->addSkyBoxSceneNode(skybox_up, skybox_down, skybox_left, skybox_right, skybox_forward, skybox_back);

	//Here we set custom parameters to the FPS camera.
	FPSCam->setPosition(vector3df(18971, 395, 10311));
	FPSCam->setTarget(vector3df(3670, 255.0f, 6320));
	FPSCam->setFarValue(42000.0f);

	//Here we only set the render distance of the Third Person camera. The position and target are constantly changing depending on player movement at a later stage.
	TPSCam->setFarValue(42000.0f);

	//Although player does not have a texture set to it, this material flag allows us to see the default "texture" or colour of the model/shape.
	Player->setMaterialFlag(EMF_LIGHTING, false);

	/*   This sets the scale of the terrrain texture. The higher the number, the higher the quality will be as it wraps the same texture to fill the entire terrain.
	This number isn't very high which in turn has less cost in performance when rendering.   */
	terrain->scaleTexture(10.0f, 10.0f);

	//This sets the rotation of the skybox to 0,0,0 just to make sure that when the rest of the code runs, we don't run into problems.
	skybox->setRotation(vector3df(0,0,0));

	//This is a variable which states where the skybox should rotate to. At a later stage, we compare both positions (Current Pos and This pos) and reset the rotation so it goes on an infinite loop.
	vector3df skyBoxLastPos = vector3df(0, 360, 0);
	vector3df sBox = skybox->getRotation();
	vector3df camRotation;

	//Get current time. This is later on used to calculate elapsed frames so we can have smooth movement and skybox rotation (consistent to the frame rate).
	u32 lastFrameTime = device->getTimer()->getTime();

	//These steps create and define parameters for the terrain's collision.
	ITriangleSelector *terSelector = manager->createTerrainTriangleSelector(terrain, 0);
	terrain->setTriangleSelector(terSelector);
	// L
	ISceneNodeAnimator *anim = manager->createCollisionResponseAnimator(terSelector, FPSCam, vector3df(100,100,100), vector3df(0,-0.5f,0), vector3df(0,50,0));

	//This declares a variable which later on is used to store the players old position.
	vector3df playerPosThen = vector3df(3610, 150.05, 1740);

	//If sceneAnimator is correctly declared, it adds the animator to FPSCam so we can have collision detection against the terrain.
	if (anim) {

		terSelector->drop();
		FPSCam->addAnimator(anim);
		anim->drop();

	}

	//This sets the camera to be a parent of the player. That way both items move together within the scene.
	Player->setParent(FPSCam);

	//Set the main camera to be FPSCam
	manager->setActiveCamera(FPSCam);

	//This is the main update loop. We use this to render each frame onto the screen while also testing certain variables for movement, updating User Interface text boxes, etc..
	while (device->run()) {

		//Every frame, it gets the camera rotation so we can later on test if it has reached its' final destination.
		camRotation = FPSCam->getRotation();

		//Calculates the current frame time. We mostly use elapsed for movement and skybox rotation.
		u32 currentTime = device->getTimer()->getTime();
		u32 elapsed = currentTime - lastFrameTime;

		lastFrameTime = currentTime;

		//Every frame get the current FPS so we can then compare if the FPS has changed. If it has, we'll then update the FPS on screen.
		s32 fpsNow = driver->getFPS();
		// L
		if (fpsNow != fpsThen) {
			stringw fpsMsg = "FPS: ";
			fpsMsg += fpsNow;
			FPSText->setText(fpsMsg.c_str());

			fpsThen = fpsNow;
		}

		//Test for key input "Escape". If said key is pressed, stop running the program and exit with code 0 (no errors).
		if (ker.IsKeyDown(KEY_ESCAPE)) {
			driver->drop();

			return 0;
		}

		//If key "1" is pressed, change from FPS camera to TPS camera.
		if (ker.IsKeyDown(KEY_KEY_1)) {
			manager->setActiveCamera(FPSCam);
		}
		else if (ker.IsKeyDown(KEY_KEY_2)) {
			manager->setActiveCamera(TPSCam);
		}

		//These variables get the position of both "billTreePos" and "Camera position" so we can then use them to test at a later stage.
		vector3df buildingPos = model[0].modelNode->getAbsolutePosition();
		vector3df cameraPosition = FPSCam->getAbsolutePosition();
		vector3df camPos;
		//This is supposed to calculate the distance between the player and the billboard and then then test it against certain coordinates (I'll have to revisit this or change at a later to actually work properly)
	
		if (buildingPos - cameraPosition <= (buildingPos - cameraPosition) / 2) {
			device->setWindowCaption(L"INSIDE RENDERING SCOPE");
		}
		else {
			device->setWindowCaption(L"NOT WITHIN THE RENDERING SCOPE");
		}

		//This gets the rotation of the camera and then displays it on the screen as a static text.
		stringw rotX = "ROT: ";
		rotX += camRotation.Y;
		ROTX->setText(rotX.c_str());

		/*   This tests the rotation of the camera and if it's rotated upwards, the skybox starts moving. 
		Otherwise, if the player is looking down, the skybox stops moving. At a later stage I'm going to make it so the skybox stops rendering when it is not being used  .*/
		if (camRotation.X > 175 && camRotation.X < 360 || camRotation.X > 0 && camRotation.X < 5) {

			if (skybox->getRotation() != skyBoxLastPos) {

				sBox.Y += cloudSpeed * (elapsed / 1000.0f);

			}
			else if (skybox->getRotation() == skyBoxLastPos) {
				skybox->setRotation(vector3df(0, 0, 0));
			}

			skybox->setRotation(sBox);

		}

		//This test for keyboard inputs for movement. If a player presses W,A,S or D, it will move depending on the frames per second.
		if (ker.IsKeyDown(KEY_KEY_W)) {

			if (camRotation.Y > 330 && camRotation.Y < 360 || camRotation.Y > 0 && camRotation.Y < 30) cameraPosition.Z += 400.0f * (elapsed / 1000.0f); // #1
			if (camRotation.Y > 30 && camRotation.Y < 60) {cameraPosition.X += 200.0f * (elapsed / 1000.0f); cameraPosition.Z += 200.0f * (elapsed / 1000.0f);} // #1.5
			if (camRotation.Y > 60 && camRotation.Y < 120) cameraPosition.X += 400.0f * (elapsed / 1000.0f); // #2
			if (camRotation.Y > 120 && camRotation.Y < 150) { cameraPosition.X += 200.0f * (elapsed / 1000.0f); cameraPosition.Z -= 200.0f * (elapsed / 1000.0f); } // #2.5
			if (camRotation.Y > 150 && camRotation.Y < 210) cameraPosition.Z -= 400.0f * (elapsed / 1000.0f); // #3
			if (camRotation.Y > 210 && camRotation.Y < 240) { cameraPosition.X -= 200.0f * (elapsed / 1000.0f); cameraPosition.Z -= 200.0f * (elapsed / 1000.0f); } // #3.5
			if (camRotation.Y > 240 && camRotation.Y < 300) cameraPosition.X -= 400.0f * (elapsed / 1000.0f); // #4
			if (camRotation.Y > 300 && camRotation.Y < 330) { cameraPosition.X -= 200.0f * (elapsed / 1000.0f); cameraPosition.Z += 200.0f * (elapsed / 1000.0f); } // #4.5

			KeyDown = true;
		}
		else if (ker.IsKeyDown(KEY_KEY_S)) {

			if (camRotation.Y > 330 && camRotation.Y < 360 || camRotation.Y > 0 && camRotation.Y < 30) cameraPosition.Z -= 400.0f * (elapsed / 1000.0f); // #1
			if (camRotation.Y > 30 && camRotation.Y < 60) { cameraPosition.X -= 200.0f * (elapsed / 1000.0f); cameraPosition.Z -= 200.0f * (elapsed / 1000.0f); } // #1.5
			if (camRotation.Y > 60 && camRotation.Y < 120) cameraPosition.X -= 400.0f * (elapsed / 1000.0f); // #2
			if (camRotation.Y > 120 && camRotation.Y < 150) { cameraPosition.X -= 200.0f * (elapsed / 1000.0f); cameraPosition.Z += 200.0f * (elapsed / 1000.0f); } // #2.5
			if (camRotation.Y > 150 && camRotation.Y < 210) cameraPosition.Z += 400.0f * (elapsed / 1000.0f); // #3
			if (camRotation.Y > 210 && camRotation.Y < 240) { cameraPosition.X += 200.0f * (elapsed / 1000.0f); cameraPosition.Z += 200.0f * (elapsed / 1000.0f); } // #3.5
			if (camRotation.Y > 240 && camRotation.Y < 300) cameraPosition.X += 400.0f * (elapsed / 1000.0f); // #4
			if (camRotation.Y > 300 && camRotation.Y < 330) { cameraPosition.X += 200.0f * (elapsed / 1000.0f); cameraPosition.Z -= 200.0f * (elapsed / 1000.0f); } // #4.5
			KeyDown = true;

		}

		if (ker.IsKeyDown(KEY_KEY_A)) {

			if (camRotation.Y > 330 && camRotation.Y < 360 || camRotation.Y > 0 && camRotation.Y < 30) cameraPosition.X -= 400.0f * (elapsed / 1000.0f); // #1
			if (camRotation.Y > 30 && camRotation.Y < 60) { cameraPosition.X -= 200.0f * (elapsed / 1000.0f); cameraPosition.Z += 200.0f * (elapsed / 1000.0f); } // #1.5
			if (camRotation.Y > 60 && camRotation.Y < 120) cameraPosition.Z += 400.0f * (elapsed / 1000.0f); // #2
			if (camRotation.Y > 120 && camRotation.Y < 150) { cameraPosition.X += 200.0f * (elapsed / 1000.0f); cameraPosition.Z += 200.0f * (elapsed / 1000.0f); } // #2.5
			if (camRotation.Y > 150 && camRotation.Y < 210) cameraPosition.X += 400.0f * (elapsed / 1000.0f); // #3
			if (camRotation.Y > 210 && camRotation.Y < 240) { cameraPosition.X += 200.0f * (elapsed / 1000.0f); cameraPosition.Z -= 200.0f * (elapsed / 1000.0f); } // #3.5
			if (camRotation.Y > 240 && camRotation.Y < 300) cameraPosition.Z -= 400.0f * (elapsed / 1000.0f); // #4
			if (camRotation.Y > 300 && camRotation.Y < 330) { cameraPosition.X -= 200.0f * (elapsed / 1000.0f); cameraPosition.Z -= 200.0f * (elapsed / 1000.0f); } // #4.5
			KeyDown = true;

		}
		else if (ker.IsKeyDown(KEY_KEY_D)) {

			if (camRotation.Y > 330 && camRotation.Y < 360 || camRotation.Y > 0 && camRotation.Y < 30) cameraPosition.X += 400.0f * (elapsed / 1000.0f); // #1
			if (camRotation.Y > 30 && camRotation.Y < 60) { cameraPosition.X += 200.0f * (elapsed / 1000.0f); cameraPosition.Z -= 200.0f * (elapsed / 1000.0f); } // #1.5
			if (camRotation.Y > 60 && camRotation.Y < 120) cameraPosition.Z -= 400.0f * (elapsed / 1000.0f); // #2
			if (camRotation.Y > 120 && camRotation.Y < 150) { cameraPosition.X -= 200.0f * (elapsed / 1000.0f); cameraPosition.Z -= 200.0f * (elapsed / 1000.0f); } // #2.5
			if (camRotation.Y > 150 && camRotation.Y < 210) cameraPosition.X -= 400.0f * (elapsed / 1000.0f); // #3
			if (camRotation.Y > 210 && camRotation.Y < 240) { cameraPosition.X -= 200.0f * (elapsed / 1000.0f); cameraPosition.Z += 200.0f * (elapsed / 1000.0f); } // #3.5
			if (camRotation.Y > 240 && camRotation.Y < 300) cameraPosition.Z += 400.0f * (elapsed / 1000.0f); // #4
			if (camRotation.Y > 300 && camRotation.Y < 330) { cameraPosition.X += 200.0f * (elapsed / 1000.0f); cameraPosition.Z += 200.0f * (elapsed / 1000.0f); } // #4.5
			KeyDown = true;

		}

		//If space key is pressed, make the player jump.
		if (ker.IsKeyDown(KEY_SPACE)) {

			cameraPosition.Y += 400.0f * (elapsed / 1000.0f);
		}

		//Purely for testing, I added these two buttons to change the speed of the skybox rotation to show that it is actually moving.
		if (ker.IsKeyDown(KEY_KEY_C)) {
			cloudSpeed = 100;
		}
		else if (ker.IsKeyDown(KEY_KEY_V)) {
			cloudSpeed = 1;

		}

		//If a key is pressed, this piece of code runs. Only when the player is moving, it will display the coordinates. Also, only when moving will the collision detection happen. This is so it's not constantly running.
		if (KeyDown) {
			stringw posX = "POSx: ";
			stringw posY = "POSy: ";
			stringw posZ = "POSz: ";

			posX += cameraPosition.X;
			posY += cameraPosition.Y;
			posZ += cameraPosition.Z;

			//colision[0] = CollisionDetection(device, Player, model[0].modelNode);
			//colision[1] = CollisionDetection(device, Player, model[1].modelNode);
			//colision[2] = CollisionDetection(device, Player, model[2].modelNode);
			//colision[3] = CollisionDetection(device, Player, model[3].modelNode);
			//colision[4] = CollisionDetection(device, Player, model[4].modelNode);
			//colision[5] = CollisionDetection(device, Player, model[5].modelNode);
			//colision[6] = CollisionDetection(device, Player, model[6].modelNode);
			//colision[7] = CollisionDetection(device, Player, model[7].modelNode);
			//colision[8] = CollisionDetection(device, Player, model[8].modelNode);
			//colision[9] = CollisionDetection(device, Player, model[9].modelNode);
			//colision[10] = CollisionDetection(device, Player, model[10].modelNode);
			//colision[11] = CollisionDetection(device, Player, model[11].modelNode);
			//colision[12] = CollisionDetection(device, Player, model[12].modelNode);
			//colision[13] = CollisionDetection(device, Player, model[13].modelNode);
			//colision[14] = CollisionDetection(device, Player, model[14].modelNode);


			FPSCam->setPosition(cameraPosition);

			//int i = 0;

			//for (; i < 14; i++) {

			//	if (isCollisionDetected(Player, model[i].modelNode)) {

			//		FPSCam->setPosition(playerPosThen);
			//		device->setWindowCaption(L"COLLISION DETECTED ***** ***** ***** ***** ***** *****");
			//	}
			//	else if (!isCollisionDetected(Player, model[i].modelNode)) {
			//		playerPosThen = cameraPosition;


			//		FPSCam->setPosition(cameraPosition);
			//		device->setWindowCaption(L"COLLISION NOT DETECTED");
			//	}

			//}

			//i = 0;


			POSXT->setText(posX.c_str());
			POSYT->setText(posY.c_str());
			POSZT->setText(posZ.c_str());

			KeyDown = false;

		}

		TPSCam->setTarget(cameraPosition);
		TPSCam->setPosition(vector3df(cameraPosition.X, cameraPosition.Y + 100, cameraPosition.Z - 200));


		//This piece of code starts the scene and renders everything within manager and GUI.
		driver->beginScene(true, true, SColor(255,200,101,140));

		manager->drawAll();
		device->getGUIEnvironment()->drawAll();

		driver->endScene();

	}

	//If main loop stops, it will exit the program with code 0 (no errors).
	device->drop();

	return 0;

}

