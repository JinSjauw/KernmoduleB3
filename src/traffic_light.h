#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/texture2d.hpp>

using namespace godot;

enum TrafficLightState
{
    TRAFFIC_LIGHT_GO = 0,
    TRAFFIC_LIGHT_STOP = 1,
    TRAFFIC_LIGHT_CAUTION = 2,
};

class TrafficLight: public Control
{
    GDCLASS(TrafficLight, Control);

    TextureRect *texture_rect;

    Ref<Texture2D> go_texture;
    Ref<Texture2D> stop_texture;
    Ref<Texture2D> caution_texture;

    TrafficLightState light_state;

    protected:
        static void _bind_methods();
    
    public:
        void set_go_texture(const Ref<Texture2D> &p_texture);
        Ref<Texture2D> get_go_texture() const;

        void set_stop_texture(const Ref<Texture2D> &p_texture);
        Ref<Texture2D> get_stop_texture() const;

        void set_caution_texture(const Ref<Texture2D> &p_texture);
        Ref<Texture2D> get_caution_texture() const;

        void set_light_state(TrafficLightState p_type);
        TrafficLightState get_light_state() const;

        TrafficLight();
};

VARIANT_ENUM_CAST(TrafficLightState);