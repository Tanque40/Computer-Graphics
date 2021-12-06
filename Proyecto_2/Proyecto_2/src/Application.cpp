#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

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
#include "Texture.h"

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
    window = glfwCreateWindow( 1080, 810, "Proyecto_1", NULL, NULL );
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
        float tillingDiameter = 2.0f;
        Penrose p(1, Coordinate( 0.0, -0.0 ), 36, tillingDiameter );

        p.execute();
        p.DoIt3D();

        //float *vertices = p.GetVerticesWithColors();
        float *vertices = p.GetVerticesWithTextureCoords();
        //int numVertices = p.GetNumTriangles() * 18;
        int numVertices = p.GetNumTriangles() * 18;
        
        int numIndices = p.GetNumTriangles() * 3;

        unsigned int *indices = new unsigned int[ numIndices ];
        for( int i = 0; i < numIndices; i++ ){
            indices[ i ] = i;
        }

        IndexBuffer ib( indices, numIndices );

        /*std::cout << "vertices:" << std::endl;
        for( int i = 0; i < numVertices; i += 6 ){
            std::cout << 
                vertices[i] << ", " <<
                vertices[ i + 1 ] << ", " <<
                vertices[ i + 2 ] << ", " <<
                vertices[ i + 3 ] << ", " <<
                vertices[ i + 4 ] << ", " <<
                vertices[ i + 5 ] << " "
                << std::endl;;
        }*/

        std::cout << "tringulos: " << p.GetNumTriangles() << std::endl;
        GLCall( glEnable( GL_BLEND ) );
        GLCall( glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ) );

        VertexArray va;

        VertexBuffer vb( vertices, numVertices * sizeof( float ) );

        VertexBufferLayout layout;
        layout.Push<float>( 3 );
        layout.Push<float>( 2 );
        layout.Push<float>( 1 );
        va.AddBuffer( vb, layout );
        va.Bind();

        Shader shader( "res/shaders/project_2.shader" );
        shader.Bind();

        Texture texture_1( "res/textures/end_stone.png" );
        Texture texture_2( "res/textures/nether_brick.png" );
        

        GLuint m_texture_1 = texture_1.GetM_RendererID();
        GLuint m_texture_2 = texture_2.GetM_RendererID();
        GLCall( glBindTextureUnit( 1, m_texture_1 ) );
        GLCall( glBindTextureUnit( 0, m_texture_2 ) );
        int samplers[ 2 ] = { 0, 1 };
        shader.Setuniforms1iv( "u_Textures", 2, samplers );
        



        va.UnBind();
        shader.UnBind();
        vb.UnBind();

        Renderer renderer;


        glPolygonMode( GL_FRONT, GL_FILL );
        

        // Setup ImGui binding
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init( window, true );

        // Setup style
        ImGui::StyleColorsDark();

        // Variables
        // for projection
        float xmin = -4.0f;
        float xmax = 4.0f;
        float ymin = -3.0f;
        float ymax = 3.0f;
        float zmin = -3.0f;
        float zmax = 3.0f;

        // for view
        glm::vec3 cameraPos = glm::vec3( 0.0f, 0.0f, 1.0f );
        glm::vec3 cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
        glm::vec3 cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f );

        //for Model
        glm::vec3 translate_Vector( -1.5f, 0.0f, 0.0f );
        float rotate_angle = 0.0f;
        glm::vec3 rotate_Vector(1.0f, 0.0f, 0.0f);
        glm::vec3 scale_Vector( 1.0, 1.0, 1.0 );


        /* Loop until the user closes the window */
        while( !glfwWindowShouldClose( window ) ){
            /* Render here */
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();

            processInput( window );
            shader.Bind();
            

            vb.Bind();
            va.Bind();

            {   
                // Projection
                glm::mat4 projection = glm::ortho( xmin, xmax, ymin, ymax, zmin, zmax );

                // View
                glm::mat4 view = glm::lookAt( cameraPos, cameraPos + cameraFront, cameraUp );

                // Model
                glm::mat4 model = glm::mat4( 1.0f );
                model = glm::translate( model, translate_Vector );
                model = glm::rotate( model, rotate_angle, rotate_Vector );
                model = glm::scale( model, scale_Vector );

                // Set uniforms
                shader.SetuniformsMat4f( "projection", projection );
                shader.SetuniformsMat4f( "view", view );
                shader.SetuniformsMat4f( "model", model );
                shader.SetUniformFloat( "time", 0 );
                

                // Renderer
                //GLCall( glDrawArrays( GL_TRIANGLES, 0, numVertices ) );
                renderer.Draw( va, ib, shader );
            }

            // 1. Show a simple window.
            // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
            ImGui::Begin( "Controles" );
            {

                ImGui::Text( "Proyecto 2" );
                ImGui::TextWrapped( "En este menu se pueden controlar algunos aspectos generales del proyecto como el uso de proyeccion, vista y modelo." );
                ImGui::TextWrapped( "Al igual que manejaremos la direcciones de la luz y la ubicacion de la misma." );

                if( ImGui::CollapsingHeader( "Modelo" ) ){
                    // translate
                    ImGui::SliderFloat3( "Vector de Transacion: ", &translate_Vector.x, xmin, xmax );

                    //rotate
                    ImGui::SliderAngle( "Angulo de rotacion", &rotate_angle );
                    ImGui::SliderFloat3( "Vector de Rotacion", &rotate_Vector.x, 0.0f, 1.0f);
                    
                    //scale
                    ImGui::SliderFloat3( "Escalado", &scale_Vector.x, xmin, xmax );

                }

                if( ImGui::CollapsingHeader( "Vista" ) ){
                    
                    ImGui::SliderFloat3( "CameraPos", &cameraPos.x, xmin, xmax );
                    ImGui::SliderFloat3( "CameraFront", &cameraFront.x, xmin, xmax );
                    ImGui::SliderFloat3( "CameraUp", &cameraUp.x, -1.0f, 1.0f );

                }

                if( ImGui::CollapsingHeader( "Proyeccion" ) ){
                    
                    ImGui::SliderFloat( "X_Min", &xmin, -10.0f, 0.0f );
                    ImGui::SliderFloat( "X_Max", &xmax, 0.0f, 10.0f );
                    ImGui::SliderFloat( "Y_Min", &ymin, -10.0f, 0.0f );
                    ImGui::SliderFloat( "Y_Max", &ymax, 0.0f, 10.0f );
                    ImGui::SliderFloat( "Z_Min", &zmin, -10.0f, 0.0f );
                    ImGui::SliderFloat( "Z_Max", &zmax, 0.0f, 10.0f );

                }

                ImGui::Text( "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate );

            }
            ImGui::End();

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData( ImGui::GetDrawData() );

            /* Swap front and back buffers */
            GLCall( glfwSwapBuffers( window ) );

            /* Poll for and process events */
            GLCall( glfwPollEvents() );

        }
    }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

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