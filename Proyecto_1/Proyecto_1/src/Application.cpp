#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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
        float tillingDiameter = 0.3;
        Penrose p( 6, Coordinate( 0.0, -0.0 ), 36, tillingDiameter);

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
        shader.Bind();

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
            
            vb.Bind();
            va.Bind();
            GLCall( glDrawArrays( GL_TRIANGLES, 0, numVertices ) );
            
            glm::mat4 trans = glm::mat4( 1.0f );
            
            passed_seconds = time( NULL ) - seconds;
            //std::cout << "time" << passed_seconds % 20 << std::endl;

            if( passed_seconds % 40 < 5  ){

                shader.SetUniformFloat( "time", 0 );
                trans = glm::translate( trans, glm::vec3( -1.0, 1.0, 0.0f ) );
                trans = glm::rotate( trans, -1 * ( float ) glfwGetTime(), glm::vec3( 0.0, 0.0, 1.0 ) );
                shader.SetUniformsMat4( "transform", trans, 1 );    

            } else if( passed_seconds % 40 < 10 ){

                shader.SetUniformFloat( "time", 0 );
                trans = glm::translate( trans, glm::vec3( -1.0 + translation, 1.0 - translation, 0.0f ) );
                trans = glm::scale( trans, glm::vec3( scale, scale, 0.0f ) );
                trans = glm::rotate( trans, -1 * ( float ) glfwGetTime(), glm::vec3( 0.0, 0.0, 1.0 ) );
                shader.SetUniformsMat4( "transform", trans, 1 );
                if( translation <= 1.0 ){
                    translation += 0.004;
                }

                if( scale <= 3.3 ){
                    scale += 0.0075;
                }

            } else if( passed_seconds % 40 < 15 ){

                shader.SetUniformFloat( "time", 0 );
                trans = glm::scale( trans, glm::vec3( scale, scale, 0.0f ) );
                trans = glm::rotate( trans, -1 * ( float ) glfwGetTime() * r, glm::vec3( 0.0, 0.0, 1.0 ) );
                shader.SetUniformsMat4( "transform", trans, 1 );
                if( r <= 3.0 ){
                    r += 0.01;
                }

                if( scale > 0.1 ){
                    scale -= 0.01;
                }

            } else if( passed_seconds % 40 < 20 ){

                shader.SetUniformFloat( "time", glfwGetTime() );
                trans = glm::scale( trans, glm::vec3( scale, scale, 0.0f ) );
                shader.SetUniformsMat4( "transform", trans, 0 );

                if( scale < 2 ){
                    scale += 0.1;
                }

            } else if( passed_seconds % 40 < 25 ){

                shader.SetUniformFloat( "time", glfwGetTime() );
                trans = glm::scale( trans, glm::vec3( scale, scale, 0.0f ) );
                shader.SetUniformsMat4( "transform", trans, 0 );

                if( scale > 0.1 ){
                    scale -= 0.01;
                }

            } else if( passed_seconds % 40 < 30 ){

                shader.SetUniformFloat( "time", 0 );
                trans = glm::scale( trans, glm::vec3( scale, scale, 0.0f ) );
                trans = glm::rotate( trans, -1 * ( float ) glfwGetTime() * r, glm::vec3( 0.0, 0.0, 1.0 ) );
                shader.SetUniformsMat4( "transform", trans, 1 );
                if( r > 1.0 ){
                    r -= 0.01;
                }

                if( scale < 3.3 ){
                    scale += 0.01;
                }

            } else if( passed_seconds % 40 < 35 ){

                shader.SetUniformFloat( "time", 0 );
                trans = glm::translate( trans, glm::vec3( -1.0 + translation, 1.0 - translation, 0.0f ) );
                trans = glm::scale( trans, glm::vec3( scale, scale, 0.0f ) );
                trans = glm::rotate( trans, -1 * ( float ) glfwGetTime(), glm::vec3( 0.0, 0.0, 1.0 ) );
                shader.SetUniformsMat4( "transform", trans, 1 );
                if( translation > 0.0 ){
                    translation -= 0.004;
                }

                if( scale > 1.0 ){
                    scale -= 0.0075;
                }

            } else if( passed_seconds % 40 < 40 ){

                shader.SetUniformFloat( "time", 0 );
                trans = glm::translate( trans, glm::vec3( -1.0, 1.0, 0.0f ) );
                trans = glm::rotate( trans, -1 * ( float ) glfwGetTime(), glm::vec3( 0.0, 0.0, 1.0 ) );
                shader.SetUniformsMat4( "transform", trans, 1 );
            
            }
           

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
void processInput( GLFWwindow * window ){
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
void framebuffer_size_callback( GLFWwindow * window, int width, int height ){
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport( 0, 0, width, height );
}