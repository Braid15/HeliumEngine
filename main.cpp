#ifdef _DEBUG
#include "S:\SDKs\Visual_Leak_Detector\include\vld.h"
#endif

#include "src/helium_engine.h"

using namespace HeliumEngine;

vec4 color(0.8, 0.2, 1.0, 1.0);
vec2 pos(0.0, 0.0);
vec2 size(0.2, 0.3);
Shader* shader = nullptr;
vec2 mouse_pos;
vec2 dir(0, 0);

class TestGameObject : public GameObject {
protected:
    void on_initialize() {
        attach_component(new RenderComponent2D(pos, size, color, shader));
    }

    void on_start() {
        get_component<Transform>()->get_position().x = -0.5;
        get_component<Transform>()->get_position().y = -0.5;
    }

    void on_update() {
        vec2 p = get_component<Transform>()->get_position();

        // p += dir * 0.2f is because of gl coordinates and not using dt
        // because of a fixed timestep
        get_component<Transform>()->set_position(p += dir * 0.02f);
    }

};

TestGameObject* game_object = nullptr;

class TestApp : public GameApp {

public:
    bool initialize() override {
        shader = new Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag");

        game_object = GameObject::create<TestGameObject>();

        if (!game_object->initialize()) {
            std::cout << "obj init failed\n";
        }

        return true;
    }

    void shutdown() override {
        delete game_object;
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
            // Need to do this just by setting game objects position
            //renderable->set_position(pixel_point_to_gl_coordinate(input.mouse_position()));
        }

        if (input.key_pressed(KEY_SPACE)) {
            game_object->set_enabled(!game_object->is_enabled());
        }

        mouse_pos = input.mouse_position();
    }

    void update() override {
        if (game_object) {
            game_object->update();
        }
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

