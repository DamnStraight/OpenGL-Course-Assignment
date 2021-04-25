#include <glm/gtc/type_ptr.hpp>
#include "EntityRenderer.h"
#include <glm/gtx/string_cast.hpp>

#include "cugl.h"

cugl::Vector axis; // Vector pointing at viewer in earth's frame
cugl::Quaternion ori; // Orientation of the earth
double earthRotation = 0;
const double DIR_STEP = 0.01;

//glLoadIdentity();
//ori.apply();

void changeDir(double dir)
{
    // Rotate the earth about an axis pointing towards the viewer
    axis = cugl::Vector(0, sin(earthRotation), cos(earthRotation));
    cugl::Quaternion d(axis, DIR_STEP * dir);
    ori = d * ori;
}

EntityRenderer::EntityRenderer(const Shader & shader) : shader(shader) {}

void EntityRenderer::render(const Camera & camera, const map<const TexturedMesh*, vector<const Entity*>> & entities) {

    // Enable shader, load view matrix
    shader.use_shader();
    glUniformMatrix4fv(shader.get_view_location(), 1, GL_FALSE, glm::value_ptr(camera.calculate_view_matrix()));

    for (const auto & entry : entities) {
        const Mesh * mesh = entry.first->get_mesh();
        const Texture * texture = entry.first->get_texture();
        const Material * material = entry.first->get_material();

        // Bind VAO and enable attributes
        glBindVertexArray(mesh->get_vao());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        // Bind texture
        texture->bind_to_unit(0);

        // Load material vars
        material->use_material(shader.get_specular_intensity_location(), shader.get_shininess_location());

        //

        changeDir(-1);

        float ** test = ori.get_matrix();

        glm::mat4 bbb = glm::make_mat4x4(*test);

        //std::cout << glm::to_string(bbb) << std::endl;
        //


        // This for-loop can easily be instanced to reduce it to one render call
        for (const Entity * entity : entry.second) {
            // Load model matrix then render
            glUniformMatrix4fv(shader.get_model_location(), 1, GL_FALSE, glm::value_ptr(entity->create_transform()));
            //glUniformMatrix4fv(shader.get_model_location(), 1, GL_FALSE, glm::value_ptr(entity->create_transform(bbb)));
            mesh->render_mesh();
        }

        for (int i = 0; i < 4; i++)
            delete [] test[i];

        delete[] test;

        // Disable attributes
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);

    }

    // Unbind VAO
    glBindVertexArray(0);

}

void EntityRenderer::render(const Camera & camera, const vector<const EntityGroup *> & entityGroups) {
    // Enable shader, load view matrix
    shader.use_shader();
    glUniformMatrix4fv(shader.get_view_location(), 1, GL_FALSE, glm::value_ptr(camera.calculate_view_matrix()));

    for (const EntityGroup * group : entityGroups) {
        render(mat4(1.0f), group);
    }

    // Unbind VAO
    glBindVertexArray(0);
}

void EntityRenderer::render(const mat4 & parentTransform, const EntityGroup * group) {

    // Transform for the group
    mat4 groupTransform = group->create_transform();

    //
    //

    changeDir(-1);

    float ** test = ori.get_matrix();

    glm::mat4 bbb = glm::make_mat4x4(*test);

    //

    //

    // If entities are present in this group, render them
    const vector<const Entity*>& groupEntities = group->get_entities();
    if (!groupEntities.empty()) {
        for (const Entity * entity : groupEntities) {
            const Mesh * mesh = entity->get_mesh()->get_mesh();
            const Texture * texture = entity->get_mesh()->get_texture();
            const Material * material = entity->get_mesh()->get_material();

            // Bind VAO and enable attributes
            glBindVertexArray(mesh->get_vao());
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glEnableVertexAttribArray(3);

            // Bind texture
            texture->bind_to_unit(0);

            // Load material vars
            material->use_material(shader.get_specular_intensity_location(), shader.get_shininess_location());

            // Load model matrix then render
            mat4 transform = parentTransform * groupTransform * entity->create_transform();
            glUniformMatrix4fv(shader.get_model_location(), 1, GL_FALSE, glm::value_ptr(transform));
            mesh->render_mesh();

            // Disable attributes
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
            glDisableVertexAttribArray(3);

        }
    }

    for (int i = 0; i < 4; i++)
        delete [] test[i];

    delete[] test;

    // Render children groups, applying this groups transform to them
    for (const EntityGroup * child : group->get_children_groups()) {
        render(parentTransform * groupTransform, child);
    }

}