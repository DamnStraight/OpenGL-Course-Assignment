#include "Entity.h"

Entity::Entity(TexturedMesh * mesh) :
        mesh(mesh),
        pos(0, 0, 0),
        rot(0, 0, 0),
        scaleXYZ(1, 1, 1) {}

Entity * Entity::translate(const vec3 & translation) {
    pos += translation;
    return this;
}

Entity * Entity::rotate(const vec3 & rotation) {
    rot += rotation;
    return this;
}

Entity * Entity::rotate(const Quaternion & rotation) {
    qRot *= rotation;
    return this;
}

Entity * Entity::scale(const vec3 & scale) {
    scaleXYZ *= scale;
    return this;
}

Entity * Entity::scale(float scale) {
    scaleXYZ *= scale;
    return this;
}

Entity * Entity::set_translation(const vec3 & translation) {
    pos = vec3(translation);
    return this;
}

Entity * Entity::set_rotation(const vec3 & rotation) {
    rot = vec3(rotation);
    return this;
}

Entity * Entity::set_scale(const vec3 & scale) {
    scaleXYZ = vec3(scale);
    return this;
}

Entity * Entity::set_scale(float scale) {
    scaleXYZ = vec3(scale, scale, scale);
    return this;
}

mat4 Entity::create_transform() const {
    mat4 matrix = glm::translate(mat4(1.0f), pos);
    matrix = glm::rotate(matrix, rot.x * glm::pi<float>() / 180.0f, vec3(1, 0, 0));
    matrix = glm::rotate(matrix, rot.y * glm::pi<float>() / 180.0f, vec3(0, 1, 0));
    matrix = glm::rotate(matrix, rot.z * glm::pi<float>() / 180.0f, vec3(0, 0, 1));
    mat4 qRotMat;
    qRot.matrix(qRotMat);
    matrix = qRotMat * matrix;
    matrix = glm::scale(matrix, scaleXYZ);
    return matrix;
}
