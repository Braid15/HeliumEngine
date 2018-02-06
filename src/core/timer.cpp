#include "timer.h"
#include "_glfw_glew_include.h"

namespace HeliumEngine {

    float32 Timer::_cycles_per_second = 0.0f;

    uint64 Timer::seconds_to_cycles(float32 seconds) {
        return (uint64)(seconds * _cycles_per_second);
    }

    float32 Timer::cycles_to_seconds(uint64 cycles) {
        return (float32)(cycles / _cycles_per_second);
    }

    void Timer::initialize() {
        _cycles_per_second = (float32)glfwGetTimerFrequency();
    }

    Timer::Timer(float32 start_time) {
        _time_cycles = seconds_to_cycles(start_time);
        _time_scale  = 1.0f;
        _paused      = false;
    }

    uint64 Timer::get_time_cycles() const {
        return _time_cycles;
    }

    float32 Timer::get_delta_seconds(const Timer& other) {
        uint64 delta_time = _time_cycles - other._time_cycles;
        return cycles_to_seconds(delta_time);
    }

    void Timer::update(float32 frame_time) {
        if (!_paused) {
            uint64 scaled_cycles = seconds_to_cycles(frame_time * _time_scale);
            _time_cycles += scaled_cycles;
        }
    }

    void Timer::set_paused(bool paused) {
        _paused = paused;
    }

    bool Timer::is_paused() const {
        return _paused;
    }

    void Timer::set_time_scale(float32 scale) {
        _time_scale = scale;
    }

    float32 Timer::get_time_scale() const {
        return _time_scale;
    }

    void Timer::single_step() {
        if (_paused) {
            uint64 scaled_cycles = seconds_to_cycles((1.0f/30.0f) * _time_scale);
            _time_cycles += scaled_cycles;
        }
    }

    void Timer::reset(bool reset_time_scale, bool set_paused) {
        _time_cycles = 0;

        if (reset_time_scale) {
            _time_scale = 1.0f;
        }

        if (set_paused) {
            _paused = true;
        }
    }
}