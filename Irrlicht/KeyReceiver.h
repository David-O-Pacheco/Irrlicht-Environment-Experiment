#include <irrlicht.h>
using namespace irr;

class KeyEventReceiver : public IEventReceiver {
public:

	KeyEventReceiver() {
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; i++) {

			KeyIsDown[i] = false;

		}
	}

	virtual bool IsKeyDown(EKEY_CODE keyCode) const {

		return KeyIsDown[keyCode];
	}

	virtual bool OnEvent(const SEvent &event) {
		if (event.EventType == EET_KEY_INPUT_EVENT) KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

private:

	bool KeyIsDown[KEY_KEY_CODES_COUNT];

};
