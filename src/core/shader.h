#pragma once

#include <helium_std.h>

namespace HeliumEngine {

    class Shader {
    private:
        uint32 _program_handle;
        std::string _vertex_shader_code;
        std::string _fragment_shader_code;
        std::string _vertex_shader_path;
        std::string _fragment_shader_path;
        std::string _error_string;
    public:
        Shader();
        explicit Shader(const char* vertex_path, const char* fragment_path);
        Shader(const Shader&) = delete;
        ~Shader();

        Shader& operator=(const Shader&) = delete;

        const std::string& get_vertex_shader_path() const;
        void set_vertex_shader_path(const char* path);
        void set_vertex_shader_path(const std::string& path);

        const std::string& get_fragment_shader_path() const;
        void set_fragment_shader_path(const char* path);
        void set_fragment_shader_path(const std::string& path);

        const std::string& get_vertex_shader_code() const;
        void set_vertex_shader_code(const char* code);
        void set_vertex_shader_code(const std::string& code);

        const std::string& get_fragment_shader_code() const;
        void set_fragment_shader_code(const char* code);
        void set_fragment_shader_code(const std::string& code);

        // Error string gets cleared after this is called
        std::string get_error_string();

        bool compile();
        void destroy();
        void bind() const;
        void unbind() const;

        bool set_int32_uniform(const char* uniform, const int32& value);
        bool set_float32_uniform(const char* uniform, const float32& value);

    private:
        enum class ErrorType : uint8 {
            compile,
            link
        };

        bool load_shader_code();
        void set_error_string(const std::string& error);
        bool error_encountered(uint32 id, ErrorType type);
        bool load_file_contents(const std::string& path, std::string* contents_reciever);
    };
}