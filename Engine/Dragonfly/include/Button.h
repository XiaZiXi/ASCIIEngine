#pragma once
#include "ViewObject.h"
#include "EventMouse.h"
#include "Color.h"

namespace df {
	class Button : public ViewObject {
	private:
		Color highlightColor;
		Color buttonColor;
		int buttonCountdown;
		int buttonCooldown;
	public:
		Button();
		Color getButtonColor() const;
		void setButtonColor(Color new_color);
		Color getHighlightColor() const;
		void setHighlightColor(Color new_color);
		bool mouseOverButton(Vector pos) const;
		virtual void callback(int id) = 0;
		int eventHandler(const Event *p_e);
	};
}
