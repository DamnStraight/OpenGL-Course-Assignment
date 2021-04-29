//
// Created by Cristian on 2/15/2021.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cugl.h"
#include "TexturedMesh.h"

using glm::mat4;
using glm::vec3;
using cugl::Quaternion;

class Entity {

private:
    TexturedMesh * mesh;
    vec3 pos, rot, scaleXYZ;
    Quaternion qRot;

public:
    Entity(TexturedMesh * mesh);

    Entity * translate(const vec3 & translation);
    Entity * rotate(const vec3 & rotation);
    Entity * rotate(const Quaternion & rotation);
    Entity * scale(const vec3 & scale);
    Entity * scale(float scale);

    Entity * set_translation(const vec3 & translation);
    Entity * set_rotation(const vec3 & rotation);
    Entity * set_scale(const vec3 & scale);
    Entity * set_scale(float scale);

    inline void set_texture(const Texture* newTexture) { mesh->set_texture(newTexture); }

    mat4 create_transform() const;

    inline const TexturedMesh * get_mesh() const {
        return mesh;
    }

};