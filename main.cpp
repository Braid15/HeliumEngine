#ifdef _DEBUG
#include "S:\SDKs\Visual_Leak_Detector\include\vld.h"
#endif

#include "src/helium_engine.h"

using namespace HeliumEngine;

vec4 color(0.8, 0.2, 0.6, 1.0);
vec2 pos(-0.5, -0.5);
vec2 size(0.2, 0.3);
Shader* shader = nullptr;
RenderComponent2D* renderable;
vec2 mouse_pos;
vec2 dir(0, 0);
GameObject* obj = nullptr;

class TestApp : public GameApp {

public:
    bool initialize() override {
        shader = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
        renderable = new RenderComponent2D(pos, size, color, shader);

        obj = GameObject::create();
        return true;
    }

    void shutdown() override {
        delete obj;
        delete renderable;
    }

    void handle_input(InputData& input) override {
        if (input.key_released()) {
            dir.x = 0;
            dir.y = 0;
        }

        if (input.key_pressed(KEY_W)) {

            dir.x = 0;
            dir.y = 1;
        } 

        if (input.key_pressed(KEY_A)) {

            dir.x = -1;
            dir.y = 0;
        }

        if (input.key_pressed(KEY_D)) {
            dir.x = 1;
            dir.y = 0;
        }

        if (input.key_pressed(KEY_S)) {
            dir.x = 0;
            dir.y = -1;
        }

        if (input.mouse_click_down(MOUSE_BUTTON_LEFT)) {
            renderable->set_position(pixel_point_to_gl_coordinate(input.mouse_position()));
        }

        if (input.key_pressed(KEY_SPACE)) {
        }

        mouse_pos = input.mouse_position();
    }

    void update() override {
        if (obj) {
            obj->update();
        }
        if (shader) {
            shader->enable();
            shader->set_uniform("light_pos", pixel_point_to_gl_coordinate(mouse_pos));
            shader->disable();
        }

        vec2 p(renderable->get_position());
        // p += dir * 0.2f is because of gl coordinates and not using dt
        // because of a fixed timestep
        renderable->set_position(p += dir * 0.02f);
    }
};

int main() {
    Application::start(new TestApp());

    #ifdef _DEBUG
    system("PAUSE");
    #endif

    return Application::get_exit_code();
}

