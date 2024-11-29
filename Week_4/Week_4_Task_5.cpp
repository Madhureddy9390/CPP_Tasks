#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>
using namespace std;
// Singleton: HMISystem to manage HMI state
class HMISystem {
    static HMISystem* instance;
    string mode = "Day";
    HMISystem() {}
public:
    static HMISystem* getInstance() {
        if (!instance) {
            instance = new HMISystem();
        }
        return instance;
    }
    string getMode(){ 
        return mode; 
    }
    void setMode(const string& newMode)
    {
        mode = newMode; 
    }
};
HMISystem* HMISystem::instance = nullptr;
// Factory: Create different control types
class Control {
public:
    virtual void render() = 0;
};
class Button : public Control { 
    void render() override { 
        cout << "Rendering Button\n"; 
    } 
};
class Slider : public Control {
    void render() override {
        cout << "Rendering Slider\n"; 
    } 
};
class ControlFactory {
public:
    static unique_ptr<Control> createControl(const string& type) {
        if (type == "Button") return make_unique<Button>();
        if (type == "Slider") return make_unique<Slider>();
        return nullptr;
    }
};
// Observer: Notify widgets on mode change
class Widget {
public:
    virtual void update(const string& mode) = 0;
};
class ButtonWidget : public Widget {
    void update(const string& mode) override { cout << "ButtonWidget updated to " << mode << " mode\n"; }
};
class SliderWidget : public Widget {
    void update(const string& mode) override { cout << "SliderWidget updated to " << mode << " mode\n"; }
};
class WidgetManager {
    vector<Widget*> widgets;
public:
    void subscribe(Widget* w) { widgets.push_back(w); }
    void notify(const string& mode) {
        for (auto w : widgets) w->update(mode);
    }
};
// Strategy: Define rendering behaviors
class RenderStrategy {
public:
    virtual void render() = 0;
};
class Render2D : public RenderStrategy { void render() override { cout << "Rendering in 2D\n"; } };
class Render3D : public RenderStrategy { void render() override { cout << "Rendering in 3D\n"; } };
class Renderer {
    RenderStrategy* strategy;
public:
    void setStrategy(RenderStrategy* s) { strategy = s; }
    void render() { if (strategy) strategy->render(); }
};
int main() {
    // Singleton
    auto hmi = HMISystem::getInstance();
    cout << "Current HMI Mode: " << hmi->getMode() << endl;
    hmi->setMode("Night");
    // Factory
    auto button = ControlFactory::createControl("Button");
    auto slider = ControlFactory::createControl("Slider");
    button->render();
    slider->render();
    // Observer
    WidgetManager wm;
    ButtonWidget bw; SliderWidget sw;
    wm.subscribe(&bw);
    wm.subscribe(&sw);
    wm.notify(hmi->getMode());
    // Strategy
    Renderer renderer;
    Render2D r2d; Render3D r3d;
    renderer.setStrategy(&r2d);
    renderer.render();
    renderer.setStrategy(&r3d);
    renderer.render();
    return 0;
}
