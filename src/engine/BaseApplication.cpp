#include "BaseApplication.h"
#include <windows.h>

void glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

    printf("!!! Debug callback !!!\n"); 
    printf("Debug message: id %d, %s\n", id, message);

    printf("Message source: "); 
    switch (source) 
    {
    case GL_DEBUG_SOURCE_API: printf("API\n"); break; 
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM: printf("Window System\n"); break; 
    case GL_DEBUG_SOURCE_SHADER_COMPILER : printf("Shader Compiler\n"); break; 
    case GL_DEBUG_SOURCE_THIRD_PARTY: printf("Third Party\n"); break; 
    case GL_DEBUG_SOURCE_APPLICATION: printf("Application\n"); break; 
    case GL_DEBUG_SOURCE_OTHER: printf("Other\n"); break;
    }

    printf("Error type: "); 
    switch (type) 
    {
    case GL_DEBUG_TYPE_ERROR: printf("Error\n"); break; 
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR : printf("Deprecated Behaviour\n"); break; 
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: printf("Undefined Behaviour\n"); break; 
    case GL_DEBUG_TYPE_PORTABILITY: printf("Portability\n"); break; 
    case GL_DEBUG_TYPE_PERFORMANCE: printf("Performance\n"); break; 
    case GL_DEBUG_TYPE_MARKER: printf("Marker\n"); break; 
    case GL_DEBUG_TYPE_PUSH_GROUP: printf("Push Group\n"); break; 
    case GL_DEBUG_TYPE_POP_GROUP: printf("Pop Group\n"); break; 
    case GL_DEBUG_TYPE_OTHER: printf("Other\n"); break;
    }
    
    printf("Severity: "); 
    switch (severity) 
    {
    case GL_DEBUG_SEVERITY_HIGH: printf("High\n"); break;
    case GL_DEBUG_SEVERITY_MEDIUM: printf("Medium\n"); break; 
    case GL_DEBUG_SEVERITY_LOW: printf("Low\n"); break; 
    case GL_DEBUG_SEVERITY_NOTIFICATION: printf("Notification\n"); break;
    }
}

BaseApplication::BaseApplication()
{
    /* Initialize the library */
    if (!glfwInit())
        ASSERT(false);//return -1;

#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif // DEBUG
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        ASSERT(false);//return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // disable vsync

    GLenum err = glewInit();

    if (err != GLEW_OK) {
        std::cout << glewGetErrorString(err) << std::endl;
        ASSERT(false);//return -1;
    }

#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif // DEBUG

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //std::cout << glGetString(GL_VERSION) << std::endl;
}

BaseApplication::~BaseApplication()
{
    glfwTerminate();
    //return 0;
}

void BaseApplication::Run()
{
    GLfloat verts[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f,  3.0f, 0.0f, 2.0f,
         3.0f, -1.0f, 2.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2
    };

    VertexArray va;
    VertexBuffer vb(verts, 3 * 4 * sizeof(GLfloat));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 3);

    Shader shader("res/shaders/default.shader");
    shader.Bind();

    m_texture = new Texture(256, 256);
    m_texture->Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    Start();

    double lastFrameTime = glfwGetTime();
    double deltaTime = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_window))
    {
        double currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        if (deltaTime < 1.0 / 60.0)
            Sleep((1.0 / 30.0 - deltaTime) * 1000);

        /* Render here */
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Update();

        Draw();

        m_texture->ApplyTextureChanges();
        renderer.Draw(va, ib, shader);

        OnImGui();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    Quit();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}