#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
using namespace std;

void framebuffer_size_callback( GLFWwindow *window, int width, int height );
void processInput( GLFWwindow *window );

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.9f, 0.2f, 1.0f);\n"
"}\n\0";

int main(){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#ifdef __APPLE__
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL );
    if( window == NULL ){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if( !gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress ) ){
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
    glCompileShader( vertexShader );
    // check for shader compile errors
    int success;
    char infoLog[ 512 ];
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if( !success ){
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL );
    glCompileShader( fragmentShader );
    // check for shader compile errors
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    if( !success ){
        glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );
    // check for linking errors
    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
    if( !success ){
        glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = { //Para un rombo
        -0.03f, 0.02f, 0.0f, // left  
         0.03f, 0.02f, 0.0f, // right 
         0.0f, 0.07f, 0.0f,  // top   
         0.0f, -0.03f, 0.0f  // bottom   
    };
    float new_vertices[] = {
        vertices[ 0 ] * cos( 36 ) + vertices[ 1 ] * sin( 36 )+0.1, -vertices[ 0 ] * sin( 36 ) + vertices[ 1 ] * cos( 36 )+0.1, 0.0f, //left rotada
        vertices[ 3 ] * cos( 36 ) + vertices[ 4 ] * sin( 36 )+0.1, -vertices[ 3 ] * sin( 36 ) + vertices[ 4 ] * cos( 36 ) + 0.1, 0.0f, //right rotada
        vertices[ 6 ] * cos( 36 ) + vertices[ 7 ] * sin( 36 )+0.1, -vertices[ 6 ] * sin( 36 ) + vertices[ 7 ] * cos( 36 ) + 0.1, 0.0f, //top rotada
        vertices[ 9 ] * cos( 36 ) + vertices[ 10 ] * sin( 36 )+0.1, -vertices[ 9 ] * sin( 36 ) + vertices[ 10 ] * cos( 36 ) + 0.1, 0.0f, //bottom rotada
    };
    float all_vertices[ 24 ];

    for( int i = 0; i < 24; i++ ){
        if( i < 12 ){
            all_vertices[ i ] = vertices[i];
        } else{
            all_vertices[ i ] = new_vertices[ i % 12];
        }
        printf( "%f\n", all_vertices[ i ] );
    }


    // Indices para poder dibujar con triangulos algunas cosas
    unsigned int indices[] = {
        0, 2, 3, //bottom triangle
        1, 2, 3, // top triangle
        4, 6, 7, //bottom triangle
        5, 6, 7, // top triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    glGenBuffers( 1, &EBO );
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( all_vertices ), all_vertices, GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void * ) 0 );
    glEnableVertexAttribArray( 0 );

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray( 0 );


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while( !glfwWindowShouldClose( window ) ){
        // input
        // -----
        processInput( window );

        // render
        // ------
        glClearColor( 0.0f, 0.0f, 0.5f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        // draw our first triangle
        glUseProgram( shaderProgram );
        glBindVertexArray( VAO ); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements( GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0 );
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    glDeleteProgram( shaderProgram );

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput( GLFWwindow *window ){
    if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
        glfwSetWindowShouldClose( window, true );
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback( GLFWwindow *window, int width, int height ){
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport( 0, 0, width, height );
}