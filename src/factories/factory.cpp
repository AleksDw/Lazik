#include "factory.h"
#include "../stb_image.h"

Factory::Factory(
    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
    std::unordered_map<unsigned int, RenderComponent>& renderComponents,
    std::unordered_map<unsigned int, HitBoxComponent>& renderComponentsHitbox,
    std::unordered_map<unsigned int, TransformComponent>& transformComponents,
    std::unordered_map<unsigned int, TransformHitBoxComponent>& transformComponentsHitbox
    ):
physicsComponents(physicsComponents),
renderComponents(renderComponents),
renderComponentsHitbox(renderComponentsHitbox),
transformComponents(transformComponents),
transformComponentsHitbox(transformComponentsHitbox)
{
}

Factory::~Factory() {
    glDeleteBuffers(VBOs.size(), VBOs.data());
    glDeleteVertexArrays(VAOs.size(), VAOs.data());
    glDeleteTextures(textures.size(), textures.data());
}

unsigned int Factory::make_camera(glm::vec3 position, glm::vec3 eulers) {

    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;

    transformComponents[entities_made] = transform;

    return entities_made++;
}

void Factory::make_cube(glm::vec3 position, glm::vec3 eulers,
    glm::vec3 eulerVelocity) {

    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;

    PhysicsComponent physics;
    physics.velocity = { 0.0f, 0.0f, 0.0f };
    physics.eulerVelocity = eulerVelocity;
    physicsComponents[entities_made] = physics;

    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    RenderComponent render = make_obj_mesh("../../../models/Rover_test.obj", preTransform);
    render.material = make_texture("../../../img/metal_metalness.jpg");
    renderComponents[entities_made++] = render;
}
//unsigned int Factory::make_ramp(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
//{
//    TransformComponent transform;
//    TransformComponent hitbox;
//    hitbox.position = position;
//    hitbox.eulers = eulers;
//    transform.position = position;
//    transform.eulers = eulers;
//    transformComponents[entities_made] = transform;
//    transformComponentsHitbox[entities_made] = hitbox;
//
//    glm::mat4 preTransform = glm::mat4(1.0f);
//    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    preTransform = glm::rotate(preTransform, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//    RenderComponent render = make_obj_mesh("../../../models/Rover_body.obj", preTransform);
//    RenderComponent renderhitbox = make_obj_mesh("../../../models/hitbox.obj", preTransform);
//    render.material = make_texture("../../../img/Body_BaseColor.png");
//    renderhitbox.material = make_texture("../../../img/Body_BaseColor.png");
//    renderComponents[entities_made] = render;
//    renderComponentsHitbox[entities_made] = renderhitbox;
//    entities_made++;
//}

unsigned int Factory::make_bum(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    TransformComponent transform;
    TransformHitBoxComponent hitbox;
    hitbox.position = position;
    hitbox.eulers = eulers;
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;
    transformComponentsHitbox[entities_made] = hitbox;

    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    RenderComponent render = make_obj_mesh("../../../models/bum.obj", preTransform);
    HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/bum.obj", preTransform);
    render.material = make_texture("../../../img/Body_BaseColor.png");
    renderComponents[entities_made] = render;
    renderComponentsHitbox[entities_made] = renderhitbox;
    
    return entities_made++;
}
unsigned int Factory::make_tree1(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    TransformComponent transform;
    TransformHitBoxComponent hitbox;
    hitbox.position = position;
    hitbox.eulers = eulers;
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;
    transformComponentsHitbox[entities_made] = hitbox;

    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    RenderComponent render = make_obj_mesh("../../../models/tree_1.obj", preTransform);
    HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/bum.obj", preTransform);
    render.material = make_texture("../../../img/tree_diffuse.jpg");
    renderComponents[entities_made] = render;
    renderComponentsHitbox[entities_made] = renderhitbox;

    return entities_made++;
}
unsigned int Factory::make_tree2(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    TransformComponent transform;
    TransformHitBoxComponent hitbox;
    hitbox.position = position;
    hitbox.eulers = eulers;
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;
    transformComponentsHitbox[entities_made] = hitbox;

    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    RenderComponent render = make_obj_mesh("../../../models/tree_2.obj", preTransform);
    HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/bum.obj", preTransform);
    render.material = make_texture("../../../img/tree_diffuse.jpg");
    renderComponents[entities_made] = render;
    renderComponentsHitbox[entities_made] = renderhitbox;

    return entities_made++;
}

unsigned int Factory::make_rover(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    // cialo
    TransformComponent transform;
    TransformHitBoxComponent hitbox;
    hitbox.position = position;
    hitbox.eulers = eulers;
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;
    transformComponentsHitbox[entities_made] = hitbox;

    PhysicsComponent physics;
    physics.velocity = { 0.0f, 0.0f, 0.0f };
    physics.eulerVelocity = eulerVelocity;
    physicsComponents[entities_made] = physics;

    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    RenderComponent render = make_obj_mesh("../../../models/Rover_body.obj", preTransform);
    HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/hitbox.obj", preTransform);
    render.material = make_texture("../../../img/Body_BaseColor.png");

    renderComponents[entities_made] = render;
    renderComponentsHitbox[entities_made] = renderhitbox;
    entities_made++;
    
    // prawy przod
    transform.position.x = position.x;
    transform.position.y = position.y;
    transform.position.z = position.z;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;

    physics.velocity = { 0.0f, 0.0f, 0.0f };
    physics.eulerVelocity = eulerVelocity;
    physicsComponents[entities_made] = physics;

    preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    render = make_obj_mesh("../../../models/Rover_wheel_right.obj", preTransform);
    render.material = make_texture("../../../img/Wheel_BaseColor.png");
    renderComponents[entities_made] = render;
    entities_made++;

    // prawy tyl
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;

    physics.velocity = { 0.0f, 0.0f, 0.0f };
    physics.eulerVelocity = eulerVelocity;
    physicsComponents[entities_made] = physics;

    preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    render = make_obj_mesh("../../../models/Rover_wheel_right.obj", preTransform);
    renderComponents[entities_made] = render;
    entities_made++;

    // lewo przod
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;

    physics.velocity = { 0.0f, 0.0f, 0.0f };
    physics.eulerVelocity = eulerVelocity;
    physicsComponents[entities_made] = physics;

    preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    render = make_obj_mesh("../../../models/Rover_wheel.obj", preTransform);
    render.material = make_texture("../../../img/Wheel_BaseColor.png");
    renderComponents[entities_made] = render;
    entities_made++;

    // lewy tyl
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;

    physics.velocity = { 0.0f, 0.0f, 0.0f };
    physics.eulerVelocity = eulerVelocity;
    physicsComponents[entities_made] = physics;

    preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    render = make_obj_mesh("../../../models/Rover_wheel.obj", preTransform);
    render.material = make_texture("../../../img/Wheel_BaseColor.png");
    renderComponents[entities_made] = render;
    entities_made++;

	return entities_made++;
}

unsigned int Factory::make_bullet(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    PhysicsComponent physics;
    physics.velocity = { 0.0f, 0.0f, 0.0f };
    physics.eulerVelocity = eulerVelocity;
    physicsComponents[entities_made] = physics;

    TransformComponent transform;
    TransformHitBoxComponent hitbox;
    hitbox.position = position;
    hitbox.eulers = eulers;
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;

    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    RenderComponent render = make_obj_mesh("../../../models/bum.obj", preTransform);
    render.material = make_texture("../../../img/Body_BaseColor.png");
    renderComponents[entities_made] = render;

    return entities_made++;
}


void Factory::make_terrain(glm::vec3 position, glm::vec3 eulers)
{
    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;

    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    RenderComponent render = make_obj_mesh("../../../models/terrain.obj", preTransform);
    render.material = make_texture("../../../img/rock_face_diff_4k.jpg");
    renderComponents[entities_made++] = render;
}
HitBoxComponent Factory::make_obj_coliderbox(const char* filepath, glm::mat4 preTransform) {
    std::vector<glm::vec3> v; // Store only vertices

    std::string line;
    std::vector<std::string> words;

    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open OBJ file: " + std::string(filepath));
    }

    // Read the OBJ file line by line
    while (std::getline(file, line)) {
        words = split(line, " ");

        // Process vertex lines
        if (!words[0].compare("v")) {
            v.push_back(read_vec3(words, preTransform, 1.0f));
        }
    }
    file.close();


    HitBoxComponent render;
    render.vertexCount = v.size(); // Number of vertices
    render.vertices = v; // Assuming RenderComponent has a `vertices` field for debugging

    return render;
}


RenderComponent Factory::make_obj_mesh(
    const char* filepath, glm::mat4 preTransform) {

    std::vector<glm::vec3> v;
    std::vector<glm::vec2> vt;
    std::vector<glm::vec3> vn;
    std::vector<float> vertices;

    size_t vertexCount = 0;
    size_t texcoordCount = 0;
    size_t normalCount = 0;
    size_t triangleCount = 0;

    std::string line;
    std::vector<std::string> words;

    std::ifstream file;

    file.open(filepath);
    while (std::getline(file, line)) {

        words = split(line, " ");

        if (!words[0].compare("v")) {
            ++vertexCount;
        }

        else if (!words[0].compare("vt")) {
            ++texcoordCount;
        }

        else if (!words[0].compare("vn")) {
            ++normalCount;
        }

        else if (!words[0].compare("f")) {
            triangleCount += words.size() - 3;
        }
    }
    file.close();

    v.reserve(vertexCount);
    vt.reserve(texcoordCount);
    vn.reserve(normalCount);
    //three corners per triangle, 8 floats per corner
    vertices.reserve(triangleCount * 3 * 8);

    file.open(filepath);
    while (std::getline(file, line)) {

        words = split(line, " ");

        if (!words[0].compare("v")) {
            v.push_back(read_vec3(words, preTransform, 1.0f));
        }

        else if (!words[0].compare("vt")) {
            vt.push_back(read_vec2(words));
        }

        else if (!words[0].compare("vn")) {
            vn.push_back(read_vec3(words, preTransform, 0.0f));
        }

        else if (!words[0].compare("f")) {
            read_face(words, v, vt, vn, vertices);
        }
    }
    file.close();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    VAOs.push_back(VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs.push_back(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), 
        vertices.data(), GL_STATIC_DRAW);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
    glEnableVertexAttribArray(0);
    //texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)12);
    glEnableVertexAttribArray(1);
    //normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)20);
    glEnableVertexAttribArray(2);

    RenderComponent render;
    render.VAO = VAO;
    render.vertexCount = vertices.size() / 8;
    return render;
}

glm::vec3 Factory::read_vec3(std::vector<std::string> words,
    glm::mat4 preTransform, float w) {
    return glm::vec3(
        preTransform 
        * glm::vec4(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]), w)
    );
}

glm::vec2 Factory::read_vec2(std::vector<std::string> words) {
    return glm::vec2(std::stof(words[1]), std::stof(words[2]));
}

void Factory::read_face(std::vector<std::string> words, 
    std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, 
    std::vector<glm::vec3>& vn, std::vector<float>& vertices) {
    
    size_t triangleCount = words.size() - 3;

    for (size_t i = 0; i < triangleCount; ++i) {
        read_corner(words[1], v, vt, vn, vertices);
        read_corner(words[2 + i], v, vt, vn, vertices);
        read_corner(words[3 + i], v, vt, vn, vertices);
    }

}

void Factory::read_corner(std::string description, 
    std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, 
    std::vector<glm::vec3>& vn, std::vector<float>& vertices) {
    
    std::vector<std::string> v_vt_vn = split(description, "/");

    //position
    glm::vec3 pos = v[std::stol(v_vt_vn[0]) - 1];
    vertices.push_back(pos[0]);
    vertices.push_back(pos[1]);
    vertices.push_back(pos[2]);

    //tex coord
    glm::vec2 texcoord = vt[std::stol(v_vt_vn[1]) - 1];
    vertices.push_back(texcoord[0]);
    vertices.push_back(texcoord[1]);

    //normal
    glm::vec3 normal = vn[std::stol(v_vt_vn[2]) - 1];
    vertices.push_back(normal[0]);
    vertices.push_back(normal[1]);
    vertices.push_back(normal[2]);

}

unsigned int Factory::make_texture(const char* filename) {

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(
        filename, &width, &height, &channels, STBI_rgb_alpha);

	//make the texture
    unsigned int texture;
	glGenTextures(1, &texture);
    textures.push_back(texture);
    glBindTexture(GL_TEXTURE_2D, texture);
	
    //load data
    glTexImage2D(GL_TEXTURE_2D, 
        0, GL_RGBA, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, data);

    //free data
	stbi_image_free(data);

    //Configure sampler
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}