#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void generateTexture(unsigned int *texture, std::string path);

unsigned int loadCubemap(std::vector<std::string> faces);

bool keyValue = false;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    // 编译着色器
    // -------------------------
    Shader modelShader(FileSystem::getPath("Shaders/1.model_loading.vs").c_str(),
            FileSystem::getPath("Shaders/1.model_loading.fs").c_str());
    Shader ourShader(FileSystem::getPath("Shaders/f.vs").c_str(),
                       FileSystem::getPath("Shaders/f.fs").c_str());
    Shader lightShader(FileSystem::getPath("Shaders/light.vs").c_str(),
                       FileSystem::getPath("Shaders/light.fs").c_str());
    Shader skyboxShader(FileSystem::getPath("Shaders/skybox.vs").c_str(),
                       FileSystem::getPath("Shaders/skybox.fs").c_str());
    Shader darkLightShader(FileSystem::getPath("Shaders/light.vs").c_str(),
                       FileSystem::getPath("Shaders/darkLight.fs").c_str());

    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    float skyboxVertices[] = {
            // positions
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
    };

    // 光源位置
    glm::vec3 pointLightPositions[] = {
            glm::vec3(0.7f, 2.2f, 1.0f),
//            glm::vec3(2.3f, -3.3f, -4.0f),
//            glm::vec3(-4.0f, 2.0f, -12.0f),
//            glm::vec3(0.0f, 2.0f, -3.0f)
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    std::vector<std::string> faces{
        FileSystem::getPath("Res/textures/skybox/orbital-element_lf.tga"),
        FileSystem::getPath("Res/textures/skybox/orbital-element_rt.tga"),
        FileSystem::getPath("Res/textures/skybox/orbital-element_up.tga"),
        FileSystem::getPath("Res/textures/skybox/orbital-element_dn.tga"),
        FileSystem::getPath("Res/textures/skybox/orbital-element_ft.tga"),
        FileSystem::getPath("Res/textures/skybox/orbital-element_bk.tga")
    };
    unsigned int cubemapTexture = loadCubemap(faces);

    unsigned int texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9, texture10, texture11, texture12, texture13;
    generateTexture(&texture1, FileSystem::getPath("Res/textures/my/ground.jpg"));
    generateTexture(&texture2, FileSystem::getPath("Res/textures/my/container.jpg"));
    generateTexture(&texture3, FileSystem::getPath("Res/textures/my/bed.jpg"));
    generateTexture(&texture4, FileSystem::getPath("Res/textures/my/pillow.jpg"));
    generateTexture(&texture5, FileSystem::getPath("Res/textures/my/window.jpg"));
    generateTexture(&texture6, FileSystem::getPath("Res/textures/my/wall.jpg"));
    generateTexture(&texture7, FileSystem::getPath("Res/textures/my/computer.jpg"));
    generateTexture(&texture8, FileSystem::getPath("Res/textures/my/bracket.jpg"));
    generateTexture(&texture9, FileSystem::getPath("Res/textures/my/outlet.jpg"));
    generateTexture(&texture10, FileSystem::getPath("Res/textures/my/material.jpg"));
    generateTexture(&texture11, FileSystem::getPath("Res/textures/my/desk.jpg"));
    generateTexture(&texture12, FileSystem::getPath("Res/textures/my/keyboard.png"));
    generateTexture(&texture13, FileSystem::getPath("Res/textures/my/gold.jpg"));

    ourShader.setInt("material.diffuse", 0);
    ourShader.setInt("material.specular", 1);

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);


    // 加载模型
    // -----------
    Model planet(FileSystem::getPath("Res/objects/planet/planet.obj"));
    Model floor(FileSystem::getPath("Res/objects/floor/floor.obj"));
    Model wall(FileSystem::getPath("Res/objects/bricks/bricks.obj"));
    Model house(FileSystem::getPath("Res/objects/cottage/cottage.obj"));

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();
        ourShader.setVec3("viewPos", camera.Position);
        ourShader.setFloat("material.shininess", 32.0f);

        // directional light
        ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        ourShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        ourShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light
        for (int i = 0; i < 1; ++i) {
            ourShader.setVec3("pointLights["+ to_string(i) +"].position", pointLightPositions[i]);
            ourShader.setVec3("pointLights["+ to_string(i) +"].ambient", 0.05f, 0.05f, 0.05f);
            ourShader.setVec3("pointLights["+ to_string(i) +"].diffuse", 0.8f, 0.8f, 0.8f);
            ourShader.setVec3("pointLights["+ to_string(i) +"].specular", 1.0f, 1.0f, 1.0f);
            ourShader.setFloat("pointLights["+ to_string(i) +"].constant", 1.0f);
            ourShader.setFloat("pointLights["+ to_string(i) +"].linear", 0.09);
            ourShader.setFloat("pointLights["+ to_string(i) +"].quadratic", 0.032);
        }

        // spotLight
        ourShader.setVec3("spotLight.position", camera.Position);
        ourShader.setVec3("spotLight.direction", camera.Front);
        ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        ourShader.setFloat("spotLight.constant", 1.0f);
        ourShader.setFloat("spotLight.linear", 0.09);
        ourShader.setFloat("spotLight.quadratic", 0.032);
        ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        glm::mat4 lightColor = glm::mat4(1.0f);
        ourShader.setMat4("lightColor", lightColor);

        glBindVertexArray(VAO);
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glm::mat4 ground = glm::mat4(1.0f);
//        ground = glm::scale(ground, glm::vec3(3, 0.2, 3));
//        ourShader.setMat4("model", ground);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindTexture(GL_TEXTURE_2D, 0);
//
//        glBindTexture(GL_TEXTURE_2D, texture6);
//        glm::mat4 left = glm::mat4(1.0f);
//        left = glm::translate(left, glm::vec3(-1.5, 1.5, 0));
//        left = glm::rotate(left, glm::radians(90.0f), glm::vec3(0, 0, 1));
//        left = glm::scale(left, glm::vec3(3, 0.2, 3));
//        ourShader.setMat4("model", left);
//        glDrawArrays(GL_TRIANGLES, 0, 36);

//        glm::mat4 right = glm::mat4(1.0f);
//        right = glm::translate(right, glm::vec3(1.5, 1.5, 0));
//        right = glm::rotate(right, glm::radians(90.0f), glm::vec3(0, 0, 1));
//        right = glm::scale(right, glm::vec3(3, 0.2, 3));
//        ourShader.setMat4("model", right);
//        glDrawArrays(GL_TRIANGLES, 0, 36);

//        glm::mat4 top = glm::mat4(1.0f);
//        top = glm::translate(top, glm::vec3(0, 3, 0));
//        top = glm::scale(top, glm::vec3(3, 0.2, 3));
//        ourShader.setMat4("model", top);
//        glDrawArrays(GL_TRIANGLES, 0, 36);

//        glm::mat4 back = glm::mat4(1.0f);
//        back = glm::translate(back, glm::vec3(0, 1.5, -1.6));
//        back = glm::rotate(back, glm::radians(90.0f), glm::vec3(1, 0, 0));
//        back = glm::scale(back, glm::vec3(3, 0.2, 3));
//        ourShader.setMat4("model", back);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, texture11);
        glm::mat4 desk = glm::mat4(1.0f);
        desk = glm::translate(desk, glm::vec3(-1.2, 0.5, 0.5));
        desk = glm::rotate(desk, glm::radians(90.0f), glm::vec3(0, 1, 0));
        desk = glm::scale(desk, glm::vec3(1.2, 0.1, 0.5));
        ourShader.setMat4("model", desk);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, texture11);
        glm::mat4 leftLeg = glm::mat4(1.0f);
        leftLeg = glm::translate(leftLeg, glm::vec3(-1.2, 0.25, 0.9));
        leftLeg = glm::rotate(leftLeg, glm::radians(90.0f), glm::vec3(1, 0, 0));
        leftLeg = glm::scale(leftLeg, glm::vec3(0.5, 0.3, 0.4));
        ourShader.setMat4("model", leftLeg);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 rightLeg = glm::mat4(1.0f);
        rightLeg = glm::translate(rightLeg, glm::vec3(-1.2, 0.25, 0.1));
        rightLeg = glm::rotate(rightLeg, glm::radians(90.0f), glm::vec3(1, 0, 0));
        rightLeg = glm::scale(rightLeg, glm::vec3(0.5, 0.3, 0.4));
        ourShader.setMat4("model", rightLeg);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, texture3);
        glm::mat4 bed = glm::mat4(1.0f);
        bed = glm::translate(bed, glm::vec3(-0.5, 0.2, -0.9));
        bed = glm::scale(bed, glm::vec3(2, 0.3, 1));
        ourShader.setMat4("model", bed);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, texture4);
        glm::mat4 pillow = glm::mat4(1.0f);
        pillow = glm::translate(pillow, glm::vec3(-1.3, 0.4, -0.9));
        pillow = glm::scale(pillow, glm::vec3(0.2, 0.1, 0.6));
        ourShader.setMat4("model", pillow);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

//        glBindTexture(GL_TEXTURE_2D, texture5);
////        glm::mat4 win = glm::mat4(1.0f);
////        win = glm::translate(win, glm::vec3(0, 1.5, -1.5));
////        win = glm::scale(win, glm::vec3(1.5, 1.5, 0.1));
////        ourShader.setMat4("model", win);
////        glDrawArrays(GL_TRIANGLES, 0, 36);
////        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, texture7);
        glm::mat4 computer = glm::mat4(1.0f);
        computer = glm::translate(computer, glm::vec3(-1.1, 0.75, 0.5));
        computer = glm::rotate(computer, glm::radians(10.0f), glm::vec3(0, 0, 1));
        computer = glm::scale(computer, glm::vec3(0.02, 0.3, 0.5));
        ourShader.setMat4("model", computer);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, texture8);
        glm::mat4 bracket = glm::mat4(1.0f);
        bracket = glm::translate(bracket, glm::vec3(-1.1, 0.6, 0.5));
        bracket = glm::rotate(bracket, glm::radians(-20.0f), glm::vec3(0, 0, 1));
        bracket = glm::scale(bracket, glm::vec3(0.005, 0.1, 0.1));
        ourShader.setMat4("model", bracket);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 cushion = glm::mat4(1.0f);
        cushion = glm::translate(cushion, glm::vec3(-1.1, 0.55, 0.5));
        cushion = glm::scale(cushion, glm::vec3(0.15, 0.01, 0.15));
        ourShader.setMat4("model", cushion);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, texture9);
        glm::mat4 outlet = glm::mat4(1.0f);
        outlet = glm::translate(outlet, glm::vec3(-1.4, 0.7, 0.7));
        outlet = glm::scale(outlet, glm::vec3(0.01, 0.1, 0.1));
        ourShader.setMat4("model", outlet);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, texture11);
        glm::mat4 tray = glm::mat4(1.0f);
        tray = glm::translate(tray, glm::vec3(-1.2, 0.4, 0.5));
        tray = glm::scale(tray, glm::vec3(0.5, 0.01, 0.5));
        ourShader.setMat4("model", tray);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, texture12);
        glm::mat4 keyboard = glm::mat4(1.0f);
        keyboard = glm::translate(keyboard, glm::vec3(-1.1, 0.41, 0.5));
        keyboard = glm::scale(keyboard, glm::vec3(0.1, 0.01, 0.4));
        ourShader.setMat4("model", keyboard);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, texture13);
        glm::mat4 stool = glm::mat4(1.0f);
        stool = glm::translate(stool, glm::vec3(-0.5, 0.3, 0.5));
        stool = glm::scale(stool, glm::vec3(0.2, 0.02, 0.2));
        ourShader.setMat4("model", stool);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 backup = glm::mat4(1.0f);
        backup = glm::translate(backup, glm::vec3(-0.4, 0.3, 0.5));
        backup = glm::scale(backup, glm::vec3(0.02, 0.4, 0.2));
        ourShader.setMat4("model", backup);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 holder = glm::mat4(1.0f);
        holder = glm::translate(holder, glm::vec3(-0.55, 0.2, 0.5));
        holder = glm::rotate(holder, glm::radians(-20.0f), glm::vec3(0, 0, 1));
        holder = glm::scale(holder, glm::vec3(0.03, 0.2, 0.2));
        ourShader.setMat4("model", holder);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

        // 放置模型
        modelShader.use();
        modelShader.setMat4("projection", projection);
        modelShader.setMat4("view", view);
        // render the loaded model
        glm::mat4 models = glm::mat4(1.0f);
        // translate it down so it's at the center of the scene
        models = glm::translate(models, glm::vec3(0.0f, -1.75f, 0.0f));

        models = glm::rotate(models,  (float)glfwGetTime()/10, glm::vec3(0.0f, 1.0f, 0.0f));
        // it's a bit too big for our scene, so scale it down
        models = glm::scale(models, glm::vec3(3.2f, 3.2f, 3.2f));
        modelShader.setMat4("model", models);
        //  星球
        //planet.Draw(modelShader);
        //地板
        models = glm::mat4(1.0f);
        models = glm::scale(models, glm::vec3(1.5,1.5,1.5));
        modelShader.setMat4("model", models);
        floor.Draw(modelShader);
        // 墙
        models = glm::mat4(1.0f);
        models = glm::rotate(models, (float)glm::radians(-90.0f),glm::vec3(0.0f, 1.0f, 0.0f) );
        models = glm::translate(models, glm::vec3(7.0f, -0.2f, 5.235f));
        models = glm::scale(models, glm::vec3(1.5f,1.5f,1.5f));
        modelShader.setMat4("model", models);
        //wall.Draw(modelShader);

        models = glm::mat4(1.0f);
        models = glm::rotate(models, (float)glm::radians(-90.0f),glm::vec3(0.0f, 1.0f, 0.0f) );
        models = glm::translate(models, glm::vec3(7.0f, -0.2f, -7.235f));
        models = glm::scale(models, glm::vec3(1.5f,1.5f,1.5f));
        modelShader.setMat4("model", models);
        //wall.Draw(modelShader);

        models = glm::mat4(1.0f);
        models = glm::rotate(models, (float)glm::radians(-90.0f),glm::vec3(0.0f, 1.0f, 0.0f) );
        models = glm::translate(models, glm::vec3(-0.25f, 0.0f, 0.0f));
        models = glm::scale(models, glm::vec3(0.2f,0.2f,0.2f));
        modelShader.setMat4("model", models);
        house.Draw(modelShader);

        if (keyValue) {
            darkLightShader.use();
            darkLightShader.setMat4("projection", projection);
            darkLightShader.setMat4("view", view);
            glBindVertexArray(lightVAO);
            for (auto pointLightPosition : pointLightPositions) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, pointLightPosition);
                model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
                darkLightShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        } else {
            lightShader.use();
            lightShader.setMat4("projection", projection);
            lightShader.setMat4("view", view);
            glBindVertexArray(lightVAO);
            for (auto pointLightPosition : pointLightPositions) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, pointLightPosition);
                model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
                lightShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        // change depth function so depth test passes when values are equal to depth buffer's content
        glDepthFunc(GL_LEQUAL);
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        keyValue = !keyValue;
    }


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

void generateTexture(unsigned int *texture, std::string path) {
    int width, height, nrChannels;
    glGenTextures(1, &(*texture));
    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << path << "  : Failed to load texture" << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

unsigned int loadCubemap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                    width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}