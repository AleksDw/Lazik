﻿#include "factory.h"
#include "../stb_image.h"
#include <array>

Factory::Factory(
    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
    std::unordered_map<unsigned int, RenderComponent>& renderComponents,
    std::unordered_map<unsigned int, HitBoxComponent>& renderComponentsHitbox,
    std::unordered_map<unsigned int, HitBoxComponentTerrain>& renderComponentsHitboxTerrain,
    std::unordered_map<unsigned int, TransformComponent>& transformComponents,
    std::unordered_map<unsigned int, TransformHitBoxComponent>& transformComponentsHitbox
    ):
physicsComponents(physicsComponents),
renderComponents(renderComponents),
renderComponentsHitbox(renderComponentsHitbox),
renderComponentsHitboxTerrain(renderComponentsHitboxTerrain),
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

    HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/wall_col_y.obj", preTransform);
    renderComponentsHitbox[entities_made] = renderhitbox;
    
    return entities_made++;
}
unsigned int Factory::make_bum2(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
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

    HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/wall_col_x.obj", preTransform);
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
    HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/tree_hitBox.obj", preTransform);
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
    HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/tree_hitBox.obj", preTransform);
    render.material = make_texture("../../../img/tree_diffuse.jpg");
    renderComponents[entities_made] = render;
    renderComponentsHitbox[entities_made] = renderhitbox;

    return entities_made++;
}

unsigned int Factory::make_rockWalls(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
{
    TransformComponent transform;
    TransformHitBoxComponent hitbox;
    hitbox.position = {38.0f,0.0f,0.0f};
    hitbox.eulers = eulers;
    transform.position = position;
    transform.eulers = eulers;
    transformComponents[entities_made] = transform;
    transformComponentsHitbox[entities_made] = hitbox;

    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    preTransform = glm::rotate(preTransform, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    RenderComponent render = make_obj_mesh("../../../models/rock_walls.obj", preTransform);
    render.material = make_texture("../../../img/rock_face_diff_4k.jpg");
    //HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/wall_col_x.obj", preTransform);
    
    renderComponents[entities_made] = render;
    //renderComponentsHitbox[entities_made] = renderhitbox;

    return entities_made++;
}
unsigned int Factory::make_rocks1(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
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

    RenderComponent render = make_obj_mesh("../../../models/small_rock_group_1.obj", preTransform);
    HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/small_rock_group_col.obj", preTransform);
    render.material = make_texture("../../../img/rock_face_diff_4k.jpg");
    renderComponents[entities_made] = render;
    renderComponentsHitbox[entities_made] = renderhitbox;

    return entities_made++;
}
unsigned int Factory::make_rocks2(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity)
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

    RenderComponent render = make_obj_mesh("../../../models/small_rock_group_2.obj", preTransform);
    HitBoxComponent renderhitbox = make_obj_coliderbox("../../../models/small_rock_group_2_col.obj", preTransform);
    render.material = make_texture("../../../img/rock_face_diff_4k.jpg");
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

    RenderComponent render = make_obj_mesh("../../../models/throw_rock.obj", preTransform);
    render.material = make_texture("../../../img/rock_face_diff_4k.jpg");
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
    HitBoxComponentTerrain renderhitbox = loadObjAsTriangle("../../../models/terrain.obj", preTransform);
    render.material = make_texture("../../../img/rock_face_diff_4k.jpg");

    renderComponents[entities_made++] = render;
    renderComponentsHitboxTerrain[0] = renderhitbox;
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

HitBoxComponentTerrain Factory::loadObjAsTriangle(const char* filepath, glm::mat4 preTransform)
{
    // Temporary storage for raw vertices and triangles
    std::vector<glm::vec3> tempVertices;
    std::vector<std::array<glm::vec3, 3>> tempTriangles;

    // Open the file
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open OBJ file: " + std::string(filepath));
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Tokenize the line
        std::vector<std::string> tokens = split(line, " ");
        if (tokens.empty()) continue;

        const std::string& prefix = tokens[0];

        // Handle "v" lines (vertices)
        if (prefix == "v")
        {
            // Parse the vertex and apply preTransform
            glm::vec3 raw = read_vec3(tokens, glm::mat4(1.0f), 1.0f);
            glm::vec4 transformed = preTransform * glm::vec4(raw, 1.0f);
            tempVertices.push_back(glm::vec3(transformed));
        }

        // Handle "f" lines (faces with at least 3 vertices)
        else if (prefix == "f")
        {
            if (tokens.size() < 4) {
                // Skip if fewer than 3 indices are present
                continue;
            }

            // Parse vertex indices from the face line
            auto parseIndex = [&](const std::string& s) {
                size_t slashPos = s.find('/');
                if (slashPos == std::string::npos) {
                    return static_cast<unsigned int>(std::stoi(s)) - 1; // Convert OBJ 1-based to 0-based
                }
                else {
                    return static_cast<unsigned int>(std::stoi(s.substr(0, slashPos))) - 1;
                }
                };

            // Extract first three vertices (v1, v2, v3) and store as a triangle
            unsigned int i1 = parseIndex(tokens[1]);
            unsigned int i2 = parseIndex(tokens[2]);
            unsigned int i3 = parseIndex(tokens[3]);

            if (i1 < tempVertices.size() && i2 < tempVertices.size() && i3 < tempVertices.size()) {
                tempTriangles.push_back(std::array<glm::vec3, 3>{ tempVertices[i1], tempVertices[i2], tempVertices[i3] });
            }
        }
    }

    file.close();

    // Fill the HitBoxComponentTerrain structure
    HitBoxComponentTerrain terrain;
    terrain.vertexCount = static_cast<unsigned int>(tempVertices.size());
    terrain.vertices = std::move(tempVertices);
    terrain.triangleCount = static_cast<unsigned int>(tempTriangles.size());
    terrain.triangles = std::move(tempTriangles);

    return terrain;
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

void Factory::read_corner2(std::string description,
    std::vector<glm::vec3>& v,
    std::vector<glm::vec2>& vt,
    std::vector<glm::vec3>& vn,
    std::vector<float>& vertices)
{
    // E.g. description = "31158/12151/10395"
    std::vector<std::string> v_vt_vn = split(description, "/");

    // position
    glm::vec3 pos = v[std::stoi(v_vt_vn[0]) - 1];
    vertices.push_back(pos.x);
    vertices.push_back(pos.y);
    vertices.push_back(pos.z);

    // texture coordinate
    if (v_vt_vn.size() > 1 && !v_vt_vn[1].empty()) {
        glm::vec2 texcoord = vt[std::stoi(v_vt_vn[1]) - 1];
        vertices.push_back(texcoord.x);
        vertices.push_back(texcoord.y);
    }
    else {
        // no texture => push default or 0,0
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
    }

    // normal
    if (v_vt_vn.size() > 2 && !v_vt_vn[2].empty()) {
        glm::vec3 normal = vn[std::stoi(v_vt_vn[2]) - 1];
        vertices.push_back(normal.x);
        vertices.push_back(normal.y);
        vertices.push_back(normal.z);
    }
    else {
        // no normal => push default or 0,0,1
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
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