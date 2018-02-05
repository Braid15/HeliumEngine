#ifdef _DEBUG
#include "S:\SDKs\Visual_Leak_Detector\include\vld.h"
#endif

#include "src/helium_engine.h"

using namespace HeliumEngine;

vec4 color(0.8, 0.2, 0.6, 1.0);
vec2 pos(-0.5, -0.5);
vec2 size(1.0, 1.0);
Shader* shader = nullptr;
RenderComponent2D* renderable;
vec2 mouse_pos;

class TestApp : public GameApp {

public:
    bool initialize() override {
        shader = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
        renderable = new RenderComponent2D(pos, size, color, shader);
        return true;
    }

    void shutdown() override {

        delete renderable;
    }

    void handle_input(InputData& input) override {
        if (input.key_pressed(KEY_W)) {
            std::cout << "key_pressed\n";
        } 
        if (input.key_released(KEY_W)) {
            std::cout << "key_released\n";
        }

        if (input.key_held(KEY_W)) {
            std::cout << "key_held\n";
        }

        if (input.mouse_moved()) {
            std::cout << "mouse_moved\n";
        }

        if (input.button_pressed(MOUSE_BUTTON_LEFT)) {
            std::cout << "mouse button_pressed\n";
        }

        if (input.button_released(MOUSE_BUTTON_LEFT)) {
            std::cout << "mouse button_released\n";
        }

        if (input.button_held(MOUSE_BUTTON_LEFT)) {
            std::cout << "mouse button_held\n";
        }

        if (input.mouse_scroll()) {
            std::cout << "mouse scroll\n";
        }

        if (input.mouse_scroll_up()) {
            std::cout << "mouse scroll up\n";
        }

        if (input.mouse_scroll_down()) {
            std::cout << "mouse scroll down\n";
        }

        if (input.mouse_drag(MOUSE_BUTTON_RIGHT)) {
            std::cout << "mouse drag\n";
        }

        mouse_pos = input.mouse_position();
    }

    void update() override {
        if (shader) {
            shader->enable();
            shader->set_uniform("light_pos", pixel_point_to_gl_coordinate(mouse_pos));
            shader->disable();
        }
    }
};

int main() {
    Application::start(new TestApp());

    #ifdef _DEBUG
    system("PAUSE");
    #endif

    return Application::get_exit_code();
}

