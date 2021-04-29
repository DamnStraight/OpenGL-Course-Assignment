#pragma once

#include <vector>

#include "Entity.h"
#include "cugl.h"

using std::vector;
using glm::mat4;
using glm::mat3x2;
using glm::vec3;
using glm::vec2;
using cugl::Quaternion;

class EntityGroup {

private:
    vec3 pos, rot, scaleXYZ;
    Quaternion qRot;
    mat3x2 shear;
    vector<Entity*> entities;
    vector<EntityGroup*> childrenGroups;

public:
    EntityGroup();
    ~EntityGroup();
    explicit EntityGroup(const EntityGroup * src, bool copyTransform);

    EntityGroup * add(Entity * entity);
    EntityGroup * add(EntityGroup * group);
    EntityGroup * remove(Entity * entity);
    EntityGroup * remove(EntityGroup * group);

    EntityGroup * translate(const vec3 & translation);
    EntityGroup * rotate(const vec3 & rotation);
    EntityGroup * rotate(const Quaternion & rotation);
    EntityGroup * scale(const vec3 & scale);
    EntityGroup * scale(float scale);
    EntityGroup * shearX(const vec2 & shear);
    EntityGroup * shearY(const vec2 & shear);
    EntityGroup * shearZ(const vec2 & shear);

    EntityGroup * set_translation(const vec3 & translation);
    EntityGroup * set_rotation(const vec3 & rotation);
    EntityGroup * set_scale(const vec3 & scale);
    EntityGroup * set_scale(float scale);
    EntityGroup * set_shearX(const vec2 & shear);
    EntityGroup * set_shearY(const vec2 & shear);
    EntityGroup * set_shearZ(const vec2 & shear);

    mat4 create_transform() const;

    inline const vector<Entity*> & get_entities() const {
        return entities;
    }

    inline const vector<EntityGroup*> & get_children_groups() const {
        return childrenGroups;
    }

};
