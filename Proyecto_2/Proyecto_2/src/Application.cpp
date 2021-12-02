#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Penrose.h"


void framebuffer_size_callback( GLFWwindow *window, int width, int height );
void processInput( GLFWwindow *window );

int main( void ){
    GLFWwindow *window;

    /* Initialize the library */
    if( !glfwInit() )
        return -1;

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 4 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow( 920, 920, "Proyecto_1", NULL, NULL );
    if( !window ){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    glfwSwapInterval( 1 );

    // Se debe poner después del make context eso marca la documentación
    if( glewInit() != GLEW_OK )
        std::cout << "Error!" << std::endl;

    std::cout << glGetString( GL_VERSION ) << std::endl;

    {
        float tillingDiameter = 1.0f;
        Penrose p( 2, Coordinate( 0.0, -0.0 ), 36, tillingDiameter );

        p.execute();

        float *vertices = p.GetVerticesWithColors();
        int numVertices = p.GetNumTriangles() * 18;

        VertexArray va;

        VertexBuffer vb( vertices, numVertices * sizeof( float ) );

        VertexBufferLayout layout;
        layout.Push<float>( 3 );
        layout.Push<float>( 3 );
        va.AddBuffer( vb, layout );
        va.Bind();

        Shader shader( "res/shaders/animation_1.shader" );
        shader.Bind();

        va.UnBind();
        shader.UnBind();
        vb.UnBind();

        Renderer renderer;


        glPolygonMode( GL_FRONT, GL_FILL );
        
        time_t seconds;
        seconds = time( NULL );
        int passed_seconds;
        float translation = 0.01;
        float r = 0.001;
        float scale = 1.0;
        /* Loop until the user closes the window */
        while( !glfwWindowShouldClose( window ) ){
            /* Render here */
            renderer.Clear();


            processInput( window );
            shader.Bind();

            vb.Bind();
            va.Bind();
            GLCall( glDrawArrays( GL_TRIANGLES, 0, numVertices ) );

            glm::mat4 trans = glm::mat4( 1.0f );

            //std::cout << "time" << passed_seconds % 20 << std::endl;

            shader.SetUniformsMat4( "transform", trans, 1 );
            shader.SetUniformFloat( "time", 0 );

            /* Swap front and back buffers */
            GLCall( glfwSwapBuffers( window ) );

            /* Poll for and process events */
            GLCall( glfwPollEvents() );

        }
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame andreact accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput( GLFWwindow *window ){
    if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
        glfwSetWindowShouldClose( window, true );
    if( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS ){
        GLCall( glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ) );
        std::cout << "w press" << std::endl;
    }
    if( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS ){
        GLCall( glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ) );
        std::cout << "S press" << std::endl;
    }
    if( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS ){
        GLCall( glPolygonMode( GL_FRONT_AND_BACK, GL_POINT ) );
        std::cout << "a press" << std::endl;
    }
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback( GLFWwindow *window, int width, int height ){
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport( 0, 0, width, height );
}