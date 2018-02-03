#include "shader.h"
#include "_glfw_glew_include.h"

namespace HeliumEngine {

    Shader::Shader() : _program_handle(0) 
    {}

    Shader::Shader(const char* vertex_path, const char* fragment_path) : _program_handle(0),
        _vertex_shader_path(vertex_path), _fragment_shader_path(fragment_path)
    {}

    Shader::~Shader() {
        destroy();
    }

    const std::string& Shader::get_vertex_shader_path() const {
        return _vertex_shader_path;
    }

    void Shader::set_vertex_shader_path(const char* path) {
        _vertex_shader_path = std::string(path);
    }

    void Shader::set_vertex_shader_path(const std::string& path) {
        _vertex_shader_path = path;
    }

    const std::string& Shader::get_fragment_shader_path() const {
        return _fragment_shader_path;
    }

    void Shader::set_fragment_shader_path(const char* path) {
        _fragment_shader_path = std::string(path);
    }

    void Shader::set_fragment_shader_path(const std::string& path) {
        _fragment_shader_path = path;
    }

    const std::string& Shader::get_vertex_shader_code() const {
        return _vertex_shader_code;
    }

    void Shader::set_vertex_shader_code(const char* code) {
        _vertex_shader_code = std::string(code);
    }

    void Shader::set_vertex_shader_code(const std::string& code) {
        _vertex_shader_code = code;
    }

    const std::string& Shader::get_fragment_shader_code() const {
        return _fragment_shader_code;
    }

    void Shader::set_fragment_shader_code(const char* code) {
        _fragment_shader_code = std::string(code);
    }

    void Shader::set_fragment_shader_code(const std::string& code) {
        _fragment_shader_code = code;
    }

    std::string Shader::get_error_string() {
        std::string error_string = _error_string;
        _error_string.clear();
        return error_string;
    }

    bool Shader::compile() {
        if (!load_shader_code()) return false;

        bool success = true;

        GLuint vertex_shader    = glCreateShader(GL_VERTEX_SHADER);
        const char* vertex_code = _vertex_shader_code.c_str();
        glShaderSource(vertex_shader, 1, &vertex_code, NULL);
        glCompileShader(vertex_shader);

        if (error_encountered(vertex_shader, ErrorType::compile)) {
            success = false;
        }

        GLuint fragment_shader    = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragment_code = _fragment_shader_code.c_str();
        glShaderSource(fragment_shader, 1, &fragment_code, NULL);
        glCompileShader(fragment_shader);

        if (error_encountered(fragment_shader, ErrorType::compile)) {
            success = false;
        }
        
        _program_handle = glCreateProgram();
        glAttachShader(_program_handle, vertex_shader);
        glAttachShader(_program_handle, fragment_shader);
        glLinkProgram(_program_handle);

        if (error_encountered(_program_handle, ErrorType::link)) {
            success = false;
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return success;
    }

    void Shader::destroy() {
        glDeleteProgram(_program_handle);
    }

    void Shader::bind() const {
        glUseProgram(_program_handle);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    bool Shader::set_int32_uniform(const char* uniform, const int32& value) {
        uint32 location = glGetUniformLocation(_program_handle, uniform);

        if (location < 0) {
            set_error_string("Unable to find int32 uniform: " + std::string(uniform));
            return false;
        }

        glUniform1i(location, value);
        return true;
    }

    bool Shader::set_float32_uniform(const char* uniform, const float32& value) {
        uint32 location = glGetUniformLocation(_program_handle, uniform);

        if (location < 0) {
            set_error_string("Unable to find float32 uniform: " + std::string(uniform));
            return false;
        }

        glUniform1f(location, value);
        return true;
    }

    bool Shader::load_shader_code() {
        bool has_code  = !(_vertex_shader_code.empty() && _fragment_shader_code.empty());

        if (has_code) return true;

        bool has_paths = !(_vertex_shader_path.empty() && _fragment_shader_path.empty());

        if (!has_code && !has_paths) return false;

        if (_vertex_shader_code.empty() && !_vertex_shader_path.empty()) {
            if (!load_file_contents(_vertex_shader_path, &_vertex_shader_code)) return false;
        }

        if (_fragment_shader_code.empty() && !_fragment_shader_path.empty()) {
            if (!load_file_contents(_fragment_shader_path, &_fragment_shader_code)) return false;
        }

        return !(_vertex_shader_code.empty() && _fragment_shader_code.empty());
    }

    void Shader::set_error_string(const std::string& error) {
        _error_string = "[Shader Error] " + error;
    }

    bool Shader::error_encountered(uint32 id, ErrorType type) {
        #define log_size 1024

        int32 result;
        char log_info[log_size];

        bool was_error = false;

        switch (type) {
            case ErrorType::compile: {
                glGetShaderiv(id, GL_COMPILE_STATUS, &result);

                if (result) break;

                glGetShaderInfoLog(id, log_size, NULL, log_info);
                set_error_string(std::string(log_info));
                was_error = true;
                break;
            }
            
            case ErrorType::link: {
                glGetProgramiv(id, GL_LINK_STATUS, &result);

                if (result) break;

                glGetProgramInfoLog(id, log_size, NULL, log_info);
                set_error_string(std::string(log_info));
                was_error = true;
                break;
            }

            default:
                break;
        }

        #undef log_size


        return was_error;
    }

    bool Shader::load_file_contents(const std::string& path, std::string* contents_reciever) {
        std::ifstream file;
        std::stringstream stream;

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            file.open(path);
            stream << file.rdbuf();
            file.close();
            *contents_reciever = stream.str();
        } catch (std::ifstream::failure e) {
            set_error_string(std::string(e.what()) + " : " + path);
            return false;
        }

        return true;
    }
}