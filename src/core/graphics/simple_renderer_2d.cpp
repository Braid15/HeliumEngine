#include "simple_renderer_2d.h"
#include <core/_glfw_glew_include.h>
#include <core/shader.h>
#include <core/input_manager.h>
#include <core/graphics/render_component.h>

namespace HeliumEngine {

    void SimpleRenderer2D::submit(ARenderComponent* render_component) {
        if (render_component->get_render_type() == RENDER_TYPE_2D) {
            _render_submissions.push_back(render_component);
        }
    }

    void SimpleRenderer2D::render_begin() {

    }

    void SimpleRenderer2D::render_submissions() {
        while (!_render_submissions.empty()) {
            ARenderComponent* component = _render_submissions.front();

            glBindVertexArray(component->get_vao_handle());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, component->get_ibo_handle());

            Shader* shader = component->get_shader();

            if (shader) shader->enable();

            glm::mat4 model(1.0);
            model = glm::translate(model, vec3(component->get_position()));

            component->get_shader()->set_uniform("model_matrix", model);
            glDrawElements(GL_TRIANGLES, component->get_index_count(), GL_UNSIGNED_SHORT, 0);

            if (shader) shader->disable();

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            _render_submissions.pop_front();
        }
    }

    void SimpleRenderer2D::render_end() {

    }

    bool SimpleRenderer2D::initialize() {
        return true;
    }

    void SimpleRenderer2D::shutdown() {
        while (!_render_submissions.empty()) {
            _render_submissions.pop_front();
        }
    }
}