#include "application.h"

//-------------------------------------------------------------------------------------
Application::Application() 
{
    openglInit();
    mainShader.shaderInit("../../src/shaders/3.3.shader.vs", "../../src/shaders/3.3.shader.fs");
    graphicResourcesInit();
}
//-------------------------------------------------------------------------------------
Application::~Application(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
}
//-------------------------------------------------------------------------------------
void Application::openglInit(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "window", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLFW window");
    }
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this); // window user pointer set to object, so that the static glfw functions can use nonstatic vars

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD"); 
    }

    glEnable(GL_DEPTH_TEST);  
}
//-------------------------------------------------------------------------------------
void Application::graphicResourcesInit(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attrib
    // ---------------
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attrib
    // --------------------
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture 
    // -------------------------
    loadTexture(texture1, "../../assets/textures/jude-al-safadi-mIwTJNB4x80-unsplash.jpg");
    loadTexture(texture2, "../../assets/textures/WIN_512.jpg");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    mainShader.use(); 
    mainShader.setInt("texture1", 0);
    mainShader.setInt("texture2", 1);

    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    mainShader.setMat4("projection", projection);
}
//-------------------------------------------------------------------------------------
void Application::run(){
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
   while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0213769420f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // bind Texture
        // ------------
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        // activate shader
        // ---------------
        mainShader.use();

        glUniform1f(glGetUniformLocation(mainShader.ID, "winOpacity"), opacityValue);

        // pass projection matrix to shader 
        // --------------------------------
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        mainShader.setMat4("projection", projection);

        // camera/view transformation
        // --------------------------
        glm::mat4 view = camera.GetViewMatrix();
        mainShader.setMat4("view", view);

        // rendering
        // ---------
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i; 
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
            mainShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glfw: swap buffers and poll IO events 
        // -------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
//-------------------------------------------------------------------------------------
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    auto application = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (application) application->onFramebufferSize(width,height);
}
//-------------------------------------------------------------------------------------
void Application::mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    auto application = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (application) application->onMouseMove(xposIn,yposIn);
}
//-------------------------------------------------------------------------------------
void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    auto application = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (application) application->onScroll(static_cast<float>(yoffset));
}
//-------------------------------------------------------------------------------------
void Application::onFramebufferSize(int width, int height) {
    glViewport(0, 0, width, height);
}
//-------------------------------------------------------------------------------------
void Application::onMouseMove(double xpos, double ypos) {
    if (firstMouse) {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoff = static_cast<float>(xpos) - lastX;
    float yoff = lastY - static_cast<float>(ypos);
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    camera.ProcessMouseMovement(xoff, yoff);
}
//-------------------------------------------------------------------------------------
void Application::onScroll(double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
//-------------------------------------------------------------------------------------
void Application::processInput(GLFWwindow *window){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);    
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            if(camera.MovementSpeed < 8.5f) camera.MovementSpeed+=6.0f;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
            if(camera.MovementSpeed > 2.5f) camera.MovementSpeed-=6.0f;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            if(opacityValue<1.0) opacityValue += 0.005; 
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            if(opacityValue>0.0) opacityValue -= 0.01; 

}
//-------------------------------------------------------------------------------------