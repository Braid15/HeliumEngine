#pragma once

#include <helium_std.h>

namespace HeliumEngine {

    // Based off of Clock clas in Game Engine Architecture. P.358

    class Timer {
    private:
        uint64 _time_cycles;
        float32 _time_scale;
        bool _paused;

        static float32 _cycles_per_second;

        static uint64 seconds_to_cycles(float32 seconds);

        // Only use to convert small durations
        static float32 cycles_to_seconds(uint64 cycles);

    public:
        static void initialize();

        explicit Timer(float32 start_time = 0.0f);

        uint64 get_time_cycles() const;

        float32 get_delta_seconds(const Timer& other);

        void update(float32 frame_time);

        void set_paused(bool paused);

        bool is_paused() const;

        void set_time_scale(float32 scale);

        float32 get_time_scale() const;

        void single_step();

        void reset(bool reset_time_scale=false, bool set_paused=false);
    };
}