#include "raylib.h"
#include "entt/entt.hpp"
#include "components.hpp"
#include "systems.hpp"
#include <string>

#ifndef PREFABS_HPP
#define PREFABS_HPP

entt::entity create_sprite_entity(entt::registry &registry, const char* path, float x = 0, float y = 0, float z = 0)
{
    auto entity = registry.create();
    registry.emplace<BDTransform>(entity, x, y, z);
    registry.emplace<Sprite>(entity, path);
    auto tex = registry.ctx().get<TextureCache>().load_resource(path);
    registry.emplace<Velocity>(entity);
    registry.emplace<BoxCollider>(entity, Rectangle{(float)(x - tex.width / 2), (float)(y - tex.height / 2), (float)tex.width, (float)tex.height});
    registry.emplace<BoxArea>(entity, Rectangle{(float)(x - tex.width / 2), (float)(y - tex.height / 2), (float)tex.width, (float)tex.height});

    sort_sprites_by_z(registry);

    return entity;
}

#endif