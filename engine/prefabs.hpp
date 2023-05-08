#include "raylib.h"
#include "entt/entt.hpp"
#include "components.hpp"
#include "systems.hpp"
#include <string>

#ifndef PREFABS_HPP
#define PREFABS_HPP

// Create an entity with a transform, sprite, box collider, box area, and a velocity.
entt::entity create_sprite_entity(entt::registry &registry, const char* resource_name = "", float x = 0, float y = 0, float z = 0)
{
    auto entity = registry.create();
    registry.emplace<BDTransform>(entity, x, y, z);
    registry.emplace<Sprite>(entity, resource_name);
    auto tex = registry.ctx().get<TextureCache>().load_resource(resource_name);
    registry.emplace<Velocity>(entity);
    registry.emplace<BoxCollider>(entity, Rectangle{(float)(x - tex.width / 2), (float)(y - tex.height / 2), (float)tex.width, (float)tex.height});
    registry.emplace<BoxArea>(entity, Rectangle{(float)(x - tex.width / 2), (float)(y - tex.height / 2), (float)tex.width, (float)tex.height});
    auto name = std::to_string(registry.alive()+1);
    registry.emplace<Name>(entity, name);
    sort_sprites_by_z(registry);
    return entity;
}

// Create and add the camera to the registry's context
void add_camera(entt::registry &registry) {
    registry.ctx().emplace<Camera2D>(Vector2{0, 0}, Vector2{0, 0}, 0.f, 1.f);
}


#endif