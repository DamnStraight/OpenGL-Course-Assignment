#include <cmath>
#include <cstdlib>
#include <ctime>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Line.h"
#include "Grid.h"
#include "AssetLoader.h"
#include "EntityRenderer.h"
#include "EntityManager.h"
#include "PointLight.h"

#include "cugl.h"

using glm::vec3;
using glm::vec4;
using std::vector;

// When debugging, the code will execute from "out/build/x64-Debug/". That last folder will have the name of your configuration.
// We need to go three levels back to the root directory and into "src" before we can see the "Shaders" folder.
// The build directory might be different with other IDEs and OS, just add a preprocessor conditional statement for your case when you encounter it.
// Vertex Shader file path
static const char * vertex_path = "Shaders/shader.vert";
// Fragment Shader file path
static const char * fragment_path = "Shaders/shader.frag";

// Shadow Map Shader vertex file path
static const char * shadow_vertex_path = "Shaders/omni_shadow_map.vert";
// Shadow Map Shader fragment file path
static const char * shadow_fragment_path = "Shaders/omni_shadow_map.frag";
// Shadow Map Shader geometry file path
static const char * shadow_geometry_path = "Shaders/omni_shadow_map.geom";

void create_entities(AssetLoader & loader, EntityManager & entityManager, EntityGroup ** groups) {
    const Mesh * cubeMesh_letter = loader.load_mesh("cube.obj");
    const Texture * cubeTexture_letter = loader.load_texture_2d("Cardboard.jpg");
    const Mesh* cubeMesh_digit = loader.load_mesh("cube.obj");
    const Texture* cubeTexture_digit = loader.load_texture_2d("Metal-Finish.jpg");

    TexturedMesh * cube_letter = new TexturedMesh(cubeMesh_letter, cubeTexture_letter);
    TexturedMesh* cube_digit = new TexturedMesh(cubeMesh_digit, cubeTexture_digit, new Material(3.0f, 30.0f));

    // LETTER S
    Entity * s_1 = (new Entity(cube_letter))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(2, 2.5f, 0));

    Entity * s_2 = (new Entity(cube_letter))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(2, 5.5f, 0));

    Entity * s_3 = (new Entity(cube_letter))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(2, 8.5f, 0));

    Entity * s_4 = (new Entity(cube_letter))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(3.25f, 4, 0));

    Entity * s_5 = (new Entity(cube_letter))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(0.75f, 7, 0));

    EntityGroup * letter_s = (new EntityGroup())
            ->add(s_1)
            ->add(s_2)
            ->add(s_3)
            ->add(s_4)
            ->add(s_5);

    // LETTER C

    Entity * c_1 = (new Entity(cube_letter))
            ->scale(vec3(0.7f, 5, 1))
            ->translate(vec3(0, 5.5f, 0));

    Entity * c_2 = (new Entity(cube_letter))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 2.5f, 0));

    Entity * c_3 = (new Entity(cube_letter))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 8.5f, 0));

    EntityGroup * letter_c = (new EntityGroup())
            ->translate(vec3(5, 0, 0))
            ->add(c_1)
            ->add(c_2)
            ->add(c_3);

    // LETTER N
    Entity * n_1 = (new Entity(cube_letter))
            ->scale(vec3(0.7f, 6, 1))
            ->translate(vec3(0, 5, 0));

    Entity * n_2 = (new Entity(cube_letter))
            ->scale(vec3(3, 1, 1))
            ->translate(vec3(1.5f, 8.5f, 0));

    Entity * n_3 = (new Entity(cube_letter))
            ->scale(vec3(0.7f, 6, 1))
            ->translate(vec3(3, 5, 0));

    EntityGroup * letter_n = (new EntityGroup())
            ->translate(vec3(10, 0, 0))
            ->add(n_1)
            ->add(n_2)
            ->add(n_3);

    // LETTER M
    Entity * m_1 = (new Entity(cube_letter))
            ->scale(vec3(0.7f, 6, 1))
            ->translate(vec3(0, 5, 0));

    Entity * m_2 = (new Entity(cube_letter))
            ->scale(vec3(6, 1, 1))
            ->translate(vec3(3, 8.5f, 0));

    Entity * m_3 = (new Entity(cube_letter))
            ->scale(vec3(0.7f, 6, 1))
            ->translate(vec3(3, 5, 0));

    Entity * m_5 = (new Entity(cube_letter))
            ->scale(vec3(0.7f, 6, 1))
            ->translate(vec3(6, 5, 0));

    EntityGroup * letter_m = (new EntityGroup())
            ->translate(vec3(16, 0, 0))
            ->add(m_1)
            ->add(m_2)
            ->add(m_3)
            ->add(m_5);

    // LETTER I
    Entity * i_1 = (new Entity(cube_letter))
        ->scale(vec3(0.7f, 7, 1))
        ->translate(vec3(0, 5.5f, 0));

    EntityGroup * letter_i = (new EntityGroup())
            ->translate(vec3(25, 0, 0))
            ->add(i_1);

    // NUMBER 2
    Entity * nb2_1 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 2.5f, 0));

    Entity * nb2_2 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 5.5f, 0));

    Entity * nb2_3 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 8.5f, 0));

    Entity * nb2_4 = (new Entity(cube_digit))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(1.25f, 7, 0));

    Entity * nb2_5 = (new Entity(cube_digit))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(-1.25f, 4, 0));

    EntityGroup * number_2 = (new EntityGroup())
            ->translate(vec3(30, 0, 0))
            ->add(nb2_1)
            ->add(nb2_2)
            ->add(nb2_3)
            ->add(nb2_4)
            ->add(nb2_5);

    // NUMBER 4
    Entity * nb4_1 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(0, 5.5f, 0));


    Entity * nb4_3 = (new Entity(cube_digit))
            ->scale(vec3(0.6f, 7, 1))
            ->translate(vec3(1.25f, 5.5f, 0));

    Entity * nb4_4 = (new Entity(cube_digit))
            ->scale(vec3(0.6f, 3.5f, 1))
            ->translate(vec3(-1.25f, 7.25f, 0));

    EntityGroup * number_4 = (new EntityGroup())
            ->translate(vec3(35, 0, 0))
            ->add(nb4_1)
            ->add(nb4_3)
            ->add(nb4_4);

    // NUMBER 6
    Entity * nb6_1 = (new Entity(cube_digit))
            ->scale(vec3(0.7f, 5, 1))
            ->translate(vec3(0, 5.5f, 0));

    Entity * nb6_2 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 2.5f, 0));

    Entity * nb6_3 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 5.5f, 0));

    Entity * nb6_4 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 8.5f, 0));

    Entity * nb6_5 = (new Entity(cube_digit))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(2.5f, 4, 0));

    EntityGroup * number_6 = (new EntityGroup())
            ->translate(vec3(40, 0, 0))
            ->add(nb6_1)
            ->add(nb6_2)
            ->add(nb6_3)
            ->add(nb6_4)
            ->add(nb6_5);

    // NUMBER 7
    Entity * nb7_1 = (new Entity(cube_digit))
            ->scale(vec3(0.6f, 6.5f, 1))
            ->translate(vec3(1.5f, 5, 0))
            ->rotate(vec3(0, 0, -20));

    Entity * nb7_2 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 8.5f, 0));

    EntityGroup * number_7 = (new EntityGroup())
            ->translate(vec3(45, 0, 0))
            ->add(nb7_1)
            ->add(nb7_2);

    // NUMBER 8
    Entity * nb8_1 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 2.5f, 0));

    Entity * nb8_2 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 5.5f, 0));

    Entity * nb8_3 = (new Entity(cube_digit))
            ->scale(vec3(2.5f, 1, 1))
            ->translate(vec3(1.25f, 8.5f, 0));

    Entity * nb8_4 = (new Entity(cube_digit))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(2.5f, 4, 0));

    Entity * nb8_5 = (new Entity(cube_digit))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(2.5f, 7, 0));

    Entity * nb8_6 = (new Entity(cube_digit))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(0, 4, 0));

    Entity * nb8_7 = (new Entity(cube_digit))
            ->scale(vec3(0.6f, 2, 1))
            ->translate(vec3(0, 7, 0));

    EntityGroup * number_8 = (new EntityGroup())
            ->translate(vec3(50, 0, 0))
            ->add(nb8_1)
            ->add(nb8_2)
            ->add(nb8_3)
            ->add(nb8_4)
            ->add(nb8_5)
            ->add(nb8_6)
            ->add(nb8_7);

    EntityGroup * cristian = (new EntityGroup())
            ->translate(vec3(-8, 0, 0))
            ->add((new EntityGroup(letter_c, false))
                ->translate(vec3(0.5f, 0, 1.2f))
                ->rotate(vec3(0, 20, 0))
            )
            ->add((new EntityGroup(letter_n, false))
                ->translate(vec3(4.25f, 0, 0))
                ->rotate(vec3(0, 10, 0))
            )
            ->add((new EntityGroup(number_4, false))
                ->translate(vec3(10, 0, -0.2f))
                ->rotate(vec3(0, -10, 0))
            )
            ->add((new EntityGroup(number_7, false))
                ->translate(vec3(12.5f, 0, 0.5f))
                ->rotate(vec3(0, -20, 0))
            );

    EntityGroup * mahdi = (new EntityGroup())
            ->translate(vec3(-8.75f, 0, 0))
            ->add((new EntityGroup(letter_m, false))
                ->translate(vec3(0.5f, 0, 2.6f))
                ->rotate(vec3(0, 20, 0))
            )
            ->add((new EntityGroup(letter_i, false))
                ->translate(vec3(8.5f, 0, 0))
                ->rotate(vec3(0, 10, 0))
            )
            ->add((new EntityGroup(number_2, false))
                ->translate(vec3(11.5f, 0, 0.2f))
                ->rotate(vec3(0, -10, 0))
            )
            ->add((new EntityGroup(number_6, false))
                ->translate(vec3(14.5f, 0, 1))
                ->rotate(vec3(0, -20, 0))
            );

    EntityGroup * mahdi2 = (new EntityGroup())
            ->translate(vec3(-8.75f, 0, 0))
            ->add((new EntityGroup(letter_m, false))
                ->translate(vec3(0.5f, 0, 3.5f))
                ->rotate(vec3(0, 30, 0))
            )
            ->add((new EntityGroup(letter_i, false))
                ->translate(vec3(8.5f, 0, 0))
                ->rotate(vec3(0, 10, 0))
            )
            ->add((new EntityGroup(number_2, false))
                ->translate(vec3(11.5f, 0, 0))
                ->rotate(vec3(0, -10, 0))
            )
            ->add((new EntityGroup(number_6, false))
                ->translate(vec3(14.5f, 0, 1))
                ->rotate(vec3(0, -25, 0))
            );

    EntityGroup * steven = (new EntityGroup())
            ->translate(vec3(-8.25f, 0, 0))
            ->add((new EntityGroup(letter_s, false))
                ->translate(vec3(0, 0, 1.5f))
                ->rotate(vec3(0, 20, 0))
            )
            ->add((new EntityGroup(letter_n, false))
                ->translate(vec3(4.5f, 0, 0))
                ->rotate(vec3(0, 10, 0))
            )
            ->add((new EntityGroup(number_4, false))
                ->translate(vec3(10, 0, -0.4f))
                ->rotate(vec3(0, -8, 0))
            )
            ->add((new EntityGroup(number_8, false))
                ->translate(vec3(12.5f, 0, 0.1f))
                ->rotate(vec3(0, -20, 0))
            );

    EntityGroup * steven2 = (new EntityGroup())
            ->translate(vec3(-8.25f, 0, 0))
            ->add((new EntityGroup(letter_s, false))
                          ->translate(vec3(0, 0, 1.5f))
                          ->rotate(vec3(0, 20, 0))
            )
            ->add((new EntityGroup(letter_n, false))
                          ->translate(vec3(4.5f, 0, 0))
                          ->rotate(vec3(0, 10, 0))
            )
            ->add((new EntityGroup(number_4, false))
                          ->translate(vec3(10, 0, -0.4f))
                          ->rotate(vec3(0, -8, 0))
            )
            ->add((new EntityGroup(number_8, false))
                          ->translate(vec3(12.5f, 0, 0.1f))
                          ->rotate(vec3(0, -20, 0))
            );


    EntityGroup * cristianPosition = (new EntityGroup())
            ->translate(vec3(-40, 0, -10))
            ->rotate(vec3(0, 60, 0))
            ->add(cristian);
    EntityGroup * mahdiPosition = (new EntityGroup())
            ->translate(vec3(-40, 0, 10))
            ->rotate(vec3(0, 120, 0))
            ->add(mahdi);
    EntityGroup * mahdi2Position = (new EntityGroup())
            ->add(mahdi2)
            ->translate(vec3(0, 0, 15.0f));
    EntityGroup * stevenPosition = (new EntityGroup())
            ->translate(vec3(40, 0, 10))
            ->rotate(vec3(0, 240, 0))
            ->add(steven);
    EntityGroup * steven2Position = (new EntityGroup())
            ->translate(vec3(40, 0, -10))
            ->rotate(vec3(0, 300, 0))
            ->add(steven2);

    groups[0] = mahdi2Position;
    groups[1] = cristianPosition;
    groups[2] = mahdiPosition;
    groups[3] = stevenPosition;
    groups[4] = steven2Position;

    // Add names
    entityManager.add(cristianPosition);
    entityManager.add(mahdiPosition);
    entityManager.add(stevenPosition);
    entityManager.add(steven2Position);
    entityManager.add(mahdi2Position);

    delete letter_c;
    delete letter_i;
    delete letter_m;
    delete letter_n;
    delete letter_s;
    delete number_2;
    delete number_4;
    delete number_6;
    delete number_7;
    delete number_8;

}

float frand(float a, float b) {
    float random = ((float) std::rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void omni_shadow_map_pass(Shader * shader, PointLight * light)
{
    shader->use_shader();

    glViewport(0, 0, light->get_shadow_map()->get_shadow_width(), light->get_shadow_map()->get_shadow_height());

    light->get_shadow_map()->write();
    glClear(GL_DEPTH_BUFFER_BIT);

    GLuint uniform_far_plane = shader->get_far_plane_location();
    GLuint uniform_light_pos = shader->get_omni_light_pos_location();

    glUniform3f(uniform_light_pos, light->get_position().x, light->get_position().y, light->get_position().z);
    glUniform1f(uniform_far_plane, light->get_far_plane());
    shader->set_light_matrices(light->calculate_light_transform());
}

int main() {
    // Window creation
    Window main_window(1024, 768);
	int result = main_window.init();
	if (result == 1) {
		// Error creating the GLFW window so terminate early
		return 1;
	}

    // Creates the camera, used as an abstraction to calculate the view matrix
    Camera camera(glm::vec3(0.0f, 80.0f, 100.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -30.0f, 0.4f, 0.2f, &main_window);

    // Load shader programs
	Shader app_shader(vertex_path, fragment_path);
	Shader omni_shadow_shader(shadow_vertex_path, shadow_fragment_path, shadow_geometry_path);

    // Light
    PointLight point_light = PointLight(1024, 1024, 0.1f, 100.0f,
                                        glm::vec3(0.3f, 0.3f, 0.3f),
                                        0.2f, 0.5f,
                                        glm::vec3(0.0, 30.0f, 0.0f),
                                        1.0f, 0.14f, 0.07f);

	// Init entity renderer and manager, create necessary entities
	EntityRenderer entityRenderer(app_shader);
    EntityRenderer shadowRenderer(omni_shadow_shader);

	EntityManager entityManager;

    AssetLoader loader;

    // Specifies the alignment requirements for the start of each pixel row in memory. The allowable values are 1 (byte-alignment), 2 (rows aligned to even-numbered bytes), 4 (word-alignment), and 8 (rows start on double-word boundaries).
    // I think we have to use 1 because our data is held in an array of 1 byte unsigned char type
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load textures
    const Texture * floorTexture = loader.load_texture_2d("Floor-Tiles.jpg");
    const Texture * clothTexture = loader.load_texture_2d("Cloth-Texture.jpg");
    const Texture * metalPillarTexture = loader.load_texture_2d("Metal-Pillars.jpg");
    const Texture * metalHolderTexture = loader.load_texture_2d("Metal-Holder.jpg");

    std::vector<const Texture*> slideShow
    {
        loader.load_texture_2d("CN47_Screenshot.png"),
        loader.load_texture_2d("MI26_Screenshot.png"),
        loader.load_texture_2d("SN48_Screenshot.png")
    };
    size_t currentSlideIndex{ 0u };
    const Texture* currentSlide{ slideShow[currentSlideIndex] };
    double slideShowTimer{ 0.0 };

    Entity* floor = (new Entity(new TexturedMesh(loader.load_mesh("Floor.obj"), floorTexture)));
    Entity* floor_back = (new Entity(new TexturedMesh(loader.load_mesh("Floor_back.obj"), floorTexture)));
    Entity* stage = (new Entity(new TexturedMesh(loader.load_mesh("Stage.obj"), clothTexture)));
    Entity* screen = (new Entity(new TexturedMesh(loader.load_mesh("Screen.obj"), currentSlide)));
    Entity* screen_back = (new Entity(new TexturedMesh(loader.load_mesh("Screen_back.obj"), metalHolderTexture)));
    Entity* pillar1 = (new Entity(new TexturedMesh(loader.load_mesh("Pillar1.obj"), metalPillarTexture)));
    Entity* pillar2 = (new Entity(new TexturedMesh(loader.load_mesh("Pillar2.obj"), metalPillarTexture)));
    Entity* pillarAttach1 = (new Entity(new TexturedMesh(loader.load_mesh("Attach1.obj"), metalHolderTexture)));
    Entity* pillarAttach2 = (new Entity(new TexturedMesh(loader.load_mesh("Attach2.obj"), metalHolderTexture)));
    Entity* pillarAttach3 = (new Entity(new TexturedMesh(loader.load_mesh("Attach3.obj"), metalHolderTexture)));
    Entity* pillarAttach4 = (new Entity(new TexturedMesh(loader.load_mesh("Attach4.obj"), metalHolderTexture)));
    EntityGroup* environment = (new EntityGroup())
        ->add(floor_back)
        ->add(stage)
        ->add(screen)
        ->add(screen_back)
        ->add(pillar1)
        ->add(pillar2)
        ->add(pillarAttach1)
        ->add(pillarAttach2)
        ->add(pillarAttach3)
        ->add(pillarAttach4)
        ->translate(vec3(0, 0, 30));

    entityManager.add(environment);
    entityManager.add(floor);

    // The array of models
    EntityGroup * models[5];
    // The selected model
    EntityGroup* selectedModel;

    create_entities(loader, entityManager, models);

    // The default selected model
    selectedModel = models[0];

    // The window's key states
    bool* keys{ main_window.get_keys() };

	// Creates the X, Y, Z axis lines
	Line line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Line line2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 7.0f),glm::vec3(0.0f, 0.0f, 1.0f));
	Line line3(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Creates the grid
	Grid grid(glm::vec3(0.f, 0.f, 0.f));

    // Enable depth in our view space
    glEnable(GL_DEPTH_TEST);
    
    // So we can actually see the points in Point polygon mode
    glPointSize(3.f);

    // Hide surfaces facing away from camera
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // Set clear color to white
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // For getting back the control of the mouse during runtime
    bool cursor_enabled = false;

    // Key callback
    std::srand(time(nullptr));
    bool textureToggle = true;
    main_window.set_key_callback([&app_shader, selectedModel, &textureToggle, &main_window, &cursor_enabled](int key, int code, int action, int mode) {
        if (key == GLFW_KEY_END && action == GLFW_RELEASE) {
            app_shader.use_shader();
            app_shader.toggle_shadows();
        } else if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
            float x = 0, z = 0;
            do {
                x = (float) std::rand() / ((float) RAND_MAX / 128.0f) - 64.0f;
                z = (float) std::rand() / ((float) RAND_MAX / 128.0f) - 64.0f;
            } while (x > -38.0f && x < 38.0f && z > -40.0f && z < 0.0f);
            selectedModel->set_translation(vec3(x, 0, z));
        } else if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
            textureToggle = !textureToggle;
        } else if (key == GLFW_KEY_SEMICOLON && action == GLFW_RELEASE) {
            selectedModel->shearY(vec2(-0.1f, 0));
        } else if (key == GLFW_KEY_APOSTROPHE && action == GLFW_RELEASE) {
            selectedModel->shearY(vec2(0.1f, 0));
        }// [ - Toggle cursor lock
        else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_RELEASE)
        {
            glfwSetInputMode(main_window.get_instance(), GLFW_CURSOR, cursor_enabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            cursor_enabled = !cursor_enabled;
        }
        // SCALE
        else if (key == GLFW_KEY_I && action == GLFW_RELEASE)
        {
            selectedModel->scale(1.05f);
        }
        else if (key == GLFW_KEY_K && action == GLFW_RELEASE)
        {
            selectedModel->scale(0.95);
        }
    });

    vector<vec4> rotVector;
    for (int i = 0; i < 25; i++) {
        vec4 a(frand(-1, 1), frand(-1, 1), frand(-1, 1), frand(0.01, 0.03));
        rotVector.push_back(a);
    }

	// Loop until window closed
    GLfloat last_time = 0;
	while (!main_window.should_close())
	{
		// Calculate delta time to minimize speed differences on faster CPUs
		GLfloat now = glfwGetTime();
        GLfloat delta_time = now - last_time;
        slideShowTimer += delta_time;
		last_time = now;

        if (slideShowTimer >= 10.0)
        {
            screen->set_texture(slideShow[currentSlideIndex]);

            // This is for circular iteration through the slide show
            if (++currentSlideIndex >= slideShow.size())
            {
                currentSlideIndex = 0u;
            }

            slideShowTimer = 0.0;
        }

		// Get user input events
		glfwPollEvents();

        if (keys[GLFW_KEY_1])
        {
            selectedModel = models[0];
        }
        else if (keys[GLFW_KEY_2])
        {
            selectedModel = models[1];
        }
        else if (keys[GLFW_KEY_3])
        {
            selectedModel = models[2];
        }
        else if (keys[GLFW_KEY_4])
        {
            selectedModel = models[3];
        }
        else if (keys[GLFW_KEY_5])
        {
            selectedModel = models[4];
        }

        // Rotate
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < models[i]->get_children_groups()[0]->get_children_groups().size(); j++) {
                vec4 rot = rotVector[i + (5 * j)];
                models[i]->get_children_groups()[0]->get_children_groups()[j]->rotate(
                        cugl::Quaternion(vec3(rot.x, rot.y, rot.z), rot.w));
            }
        }

		camera.key_controls(main_window.get_keys(), delta_time, selectedModel);
		camera.mouse_controls(main_window.get_x_change(), main_window.get_y_change(), main_window.get_mouse_buttons(), delta_time);

		// Clear window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render shadow maps
		omni_shadow_map_pass(&omni_shadow_shader, &point_light);
		shadowRenderer.render(camera, entityManager);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// End shadows

        app_shader.use_shader();
        glUniform1i(app_shader.get_use_texture_location(), textureToggle);
        glUniform1i(app_shader.get_use_lighting_location(), true);
        entityRenderer.render(camera, entityManager);
        app_shader.set_point_light(point_light);

        glUniformMatrix4fv(app_shader.get_projection_location(), 1, GL_FALSE, glm::value_ptr(camera.calculate_projection()));
        glUniformMatrix4fv(app_shader.get_model_location(), 1, GL_FALSE, glm::value_ptr(mat4(1.0f)));
        glUniform3f(app_shader.get_eye_position_location(),
                    camera.get_camera_position().x,
                    camera.get_camera_position().y,
                    camera.get_camera_position().z);

		// Display the axis lines
        glUniform1i(app_shader.get_use_texture_location(), false);
        glUniform1i(app_shader.get_use_lighting_location(), false);
		line.render();
		line2.render();
		line3.render();

		// Display the grid
		grid.render();

		// Stop the shader
		glUseProgram(0);

		// Display the newly rendered buffer in the window
		main_window.swap_buffers();

	}

	return 0;
}