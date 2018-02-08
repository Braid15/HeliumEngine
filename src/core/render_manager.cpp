#include "render_manager.h"
#include "window_manager.h"
#include "shader.h"
#include "math/math.h"
#include "input_manager.h"
#include "graphics/simple_renderer_2d.h"

namespace HeliumEngine {

    RenderManager RenderManager::_singleton;

    RenderManager& RenderManager::get_singleton() {
        return _singleton;
    }

    void RenderManager::submit(ARenderComponent* render_component) {
        assert(_renderer);
        _renderer->submit(render_component);
    }

    bool RenderManager::initialize() {
        //glViewport(0, 0, WindowManager::get_singleton().get_width(), WindowManager::get_singleton().get_height());

        set_renderer(new SimpleRenderer2D());

        return true;
    }

    void RenderManager::shutdown() {
        if (_renderer) {
            _renderer->shutdown();
            delete _renderer;
        }
        _renderer = nullptr;
    }

    void RenderManager::draw_line(uint32 start_x, uint32 start_y, uint32 end_x, uint32 end_y) {
    }

    // Only initializes values. Ctor should not do anything else
    RenderManager::RenderManager() {
        _renderer = nullptr;
    }

    void RenderManager::set_renderer(IRenderer* renderer) {
        if (_renderer) {
            _renderer->shutdown();
            delete _renderer;
        }
        _renderer = renderer;
        _renderer->initialize();
    }

    void RenderManager::add_render_component(ARenderComponent* const component) {
        // @TODO: Optimize this. This will eventually need to be changed if different data
        //        structure is going to be used
        std::list<ARenderComponent*>::iterator iter = _render_components.begin();
        std::list<ARenderComponent*>::iterator end  = _render_components.end();

        while (iter != end) {
            if (component == *iter) {
                std::cout << "[RenderManager] Attempting to double register render component\n";
                return;
            }
            iter++;
        }
        _render_components.push_back(component);

        #ifdef _DEBUG
        std::cout << "[RenderManager] RenderComponent count: " << _render_components.size() << "\n";
        #endif
    }

    void RenderManager::remove_render_component(ARenderComponent* const component) {
         std::list<ARenderComponent*>::iterator iter = _render_components.begin();
         std::list<ARenderComponent*>::iterator end  = _render_components.end();       

         while (iter != end) {
             if (component == *iter) {
                 _render_components.remove(component);

                 #ifdef _DEBUG
                 std::cout << "[RenderManager] RenderComponent count: " << _render_components.size() << "\n";
                 #endif

                 return;
             }
             iter++;
         }

         std::cout << "[RenderManager] Could not find render component to remove\n";
    }

    void RenderManager::render_begin() {
        assert(_renderer);
        const vec4& color = WindowManager::get_singleton().get_background_color();
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);

        _renderer->render_begin();
    }

    void RenderManager::render() {
        assert(_renderer);

        std::list<ARenderComponent*>::iterator iter = _render_components.begin();
        std::list<ARenderComponent*>::iterator end  = _render_components.end();       
        while (iter != end) {
            if ((*iter)->is_visible() && (*iter)->is_enabled()) {
                (*iter)->on_render_begin();
                _renderer->submit(*iter);
                (*iter)->on_render_end();
            }
            iter++;
        }
        _renderer->render_submissions();
    }

    void RenderManager::render_end() {
        assert(_renderer);
        _renderer->render_end();
    }

    void RenderManager::render_present() {
        glfwSwapBuffers(&WindowManager::get_singleton().get_glfw_window());
    }
}