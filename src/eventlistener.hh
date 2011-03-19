#ifndef ASTEROIDS_EVENTLISTENER_HH
#define ASTEROIDS_EVENTLISTENER_HH

#include <irrlicht.h>

class EventListener : public irr::IEventReceiver {
	public:
		virtual bool OnEvent(const irr::SEvent& event) {
			
			if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
				switch (event.MouseInput.Event) {
					case irr::EMIE_LMOUSE_PRESSED_DOWN:
						KeyIsDown [irr::KEY_LBUTTON] = 1; break;
					case irr::EMIE_MMOUSE_PRESSED_DOWN:
						KeyIsDown [irr::KEY_RBUTTON] = 1; break;
					case irr::EMIE_RMOUSE_PRESSED_DOWN:
						KeyIsDown [irr::KEY_RBUTTON] = 1; break;
					case irr::EMIE_LMOUSE_LEFT_UP:
						KeyIsDown [irr::KEY_LBUTTON] = 0; break;
					case irr::EMIE_MMOUSE_LEFT_UP:
						KeyIsDown [irr::KEY_MBUTTON] = 0; break;
					case irr::EMIE_RMOUSE_LEFT_UP:
						KeyIsDown [irr::KEY_RBUTTON] = 0; break;
				}
			}
			if (event.EventType == irr::EET_KEY_INPUT_EVENT)
				KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			return false;
		}
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const {
			return KeyIsDown[keyCode];
		}

		EventListener() {
			for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
				KeyIsDown[i] = false;
		}
		

		void initMouse(irr::gui::ICursorControl *m) {
			mouse = m;
			mouse->setPosition(irr::core::position2d<irr::f32>(0.5, 0.5));
			mouse->setVisible(false);
			mouseCenter = mouse->getRelativePosition();
		}

		void updateMouse() {
			mouseDelta = mouseCenter - mouse->getRelativePosition();
			mouse->setPosition(mouseCenter);
		}

		irr::core::position2d<irr::f32> getMouseDelta() {
			return mouseDelta;
		}

	private:

		bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];

		irr::gui::ICursorControl *mouse;
		irr::core::position2d<irr::f32> mouseCenter;
		irr::core::position2d<irr::f32> mouseDelta;

};

#endif
