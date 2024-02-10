#include <algorithm>
#include <string>

#include "Point.hpp"
#include "Slider.hpp"

Slider::Slider(float x, float y, float w, float h) :
	ImageButton("stage-select/slider.png", "stage-select/slider-blue.png", x, y),
	Bar("stage-select/bar.png", x, y, w, h),
	End1("stage-select/end.png", x, y + h / 2, 0, 0, 0.5, 0.5),
	End2("stage-select/end.png", x + w, y + h / 2, 0, 0, 0.5, 0.5) {
	Position.x += w;
	Position.y += h / 2;
	Anchor = Engine::Point(0.5, 0.5);
}
// TODO 4 (0/6): Finish the 6 functions below and ensure it can control both BGM and SFX volume.
//               The slider shouldn't be dragged outside the bar, and you should also keep the mouse-in / mouse-out effect.
void Slider::Draw() const {
    Engine::ImageButton::Draw();
    Bar.Draw();
    End1.Draw();
    End2.Draw();
	// TODO 4 (1/6): Draw all components.
}
void Slider::SetOnValueChangedCallback(std::function<void(float value)> onValueChangedCallback) {
    OnValueChangedCallback = onValueChangedCallback;
	// TODO 4 (2/6): Set the function pointer. Can imitate ImageButton's 'SetOnClickCallback'.
}
void Slider::SetValue(float value) {
    if(Down == true){
        this->value = value;
        OnValueChangedCallback(value);
    }
	// TODO 4 (3/6): Call 'OnValueChangedCallback' when value changed. Can imitate ImageButton's 'OnClickCallback'.
	//               Also move the slider along the bar, to the corresponding position.
}
void Slider::OnMouseDown(int button, int mx, int my) {
    if(button & 1){
        if(mx >= End1.Position.x && mx <= End2.Position.x && mouseIn){
            Down = !Down;
        }else{
            Down = false;
        }
    }
	// TODO 4 (4/6): Set 'Down' to true if mouse is in the slider.
}
void Slider::OnMouseUp(int button, int mx, int my) {
    if(!(button & 1)) Down = false;
	// TODO 4 (5/6): Set 'Down' to false.
}
void Slider::OnMouseMove(int mx, int my) {
    if(mx >= End1.Position.x && mx <= End2.Position.x){
        Engine::ImageButton::OnMouseMove(mx, my);
        if(Down){
            float val = (mx-Bar.Position.x)/Bar.GetBitmapWidth();
            Position.x = mx;
            SetValue(val);
        }
    }
	// TODO 4 (6/6): Clamp the coordinates and calculate the value. Call 'SetValue' when you're done.
}
