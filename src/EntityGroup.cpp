#include "EntityGroup.h"

#include <glm/gtx/transform2.hpp>

EntityGroup::EntityGroup(bool hasToRotate) :
        pos(0, 0, 0),
        rot(0, 0, 0),
        scaleXYZ(1, 1, 1),
        shear(0),
        makeRotate(hasToRotate)
{}

EntityGroup::EntityGroup(const EntityGroup * src, bool copyTransform) :
        pos(copyTransform ? src->pos : vec3(0, 0, 0)),
        rot(copyTransform ? src->rot : vec3(0, 0, 0)),
        scaleXYZ(copyTransform ? src->scaleXYZ : vec3(1, 1, 1)),
        shear(copyTransform ? src->shear : mat3x2(0)),
        entities(src->entities) {
    for (const EntityGroup * group : src->childrenGroups) {
        childrenGroups.push_back(new EntityGroup(group, true));
    }
}

EntityGroup::~EntityGroup() {
    for (const EntityGroup * group : childrenGroups) {
        delete group;
    }
}

EntityGroup * EntityGroup::add(const Entity * entity) {
    if (entity == nullptr)
        return this;
    entities.push_back(entity);
    return this;
}


EntityGroup * EntityGroup::add(const EntityGroup * group) {
    childrenGroups.push_back(group);
    return this;
}


EntityGroup * EntityGroup::remove(const Entity * entity) {
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (*it == entity) {
            entities.erase(it);
            return this;
        }
    }
    return this;
}

EntityGroup * EntityGroup::remove(const EntityGroup * group) {
    for (auto it = childrenGroups.begin(); it != childrenGroups.end(); ++it) {
        if (*it == group) {
            childrenGroups.erase(it);
            return this;
        }
    }
    return this;
}

EntityGroup * EntityGroup::translate(const vec3 & translation) {
    pos += translation;
    return this;
}

EntityGroup * EntityGroup::rotate(const vec3 & rotation) {
    rot += rotation;
    return this;
}

EntityGroup * EntityGroup:: scale(const vec3 & scale) {
    scaleXYZ *= scale;
    return this;
}

EntityGroup * EntityGroup::scale(float scale) {
    scaleXYZ *= scale;
    return this;
}

EntityGroup * EntityGroup::shearX(const vec2 & shearX) {
    shear[0][0] += shearX.x;
    shear[0][1] += shearX.y;
    return this;
}

EntityGroup * EntityGroup::shearY(const vec2 & shearY) {
    shear[1][0] += shearY.x;
    shear[1][1] += shearY.y;
    return this;
}

EntityGroup * EntityGroup::shearZ(const vec2 & shearZ) {
    shear[2][0] += shearZ.x;
    shear[2][1] += shearZ.y;
    return this;
}

EntityGroup * EntityGroup::set_translation(const vec3 & translation) {
    pos = vec3(translation);
    return this;
}

EntityGroup * EntityGroup::set_rotation(const vec3 & rotation) {
    rot = vec3(rotation);
    return this;
}

EntityGroup * EntityGroup::set_scale(const vec3 & scale) {
    scaleXYZ = vec3(scale);
    return this;
}

EntityGroup * EntityGroup::set_scale(float scale) {
    scaleXYZ = vec3(scale, scale, scale);
    return this;
}

EntityGroup * EntityGroup::set_shearX(const vec2 & shearX) {
    shear[0] = shearX;
    return this;
}

EntityGroup * EntityGroup::set_shearY(const vec2 & shearY) {
    shear[1] = shearY;
    return this;
}

EntityGroup * EntityGroup::set_shearZ(const vec2 & shearZ) {
    shear[2] = shearZ;
    return this;
}

mat4 EntityGroup::create_transform() {
    mat4 matrix = glm::translate(mat4(1.0f), pos);
    matrix = glm::shearX3D(matrix, shear[0][0], shear[0][1]);
    matrix = glm::shearY3D(matrix, shear[1][0], shear[1][1]);
    matrix = glm::shearZ3D(matrix, shear[2][0], shear[2][1]);
    matrix = glm::rotate(matrix, rot.x * glm::pi<float>() / 180.0f, vec3(1, 0, 0));
    matrix = glm::rotate(matrix, (makeRotate ? ++rot.y : rot.y) * glm::pi<float>() / 180.0f, vec3(0, 1, 0));
    matrix = glm::rotate(matrix, rot.z * glm::pi<float>() / 180.0f, vec3(0, 0, 1));
    matrix = glm::scale(matrix, scaleXYZ);
    return matrix;
}
