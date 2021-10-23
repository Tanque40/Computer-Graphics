#include "Renderer.h"
#include <iostream>

void GLClearError(){
    while( glGetError() != GL_NO_ERROR );
}

bool GLLogCall( const char *function, const char *file, int line ){
    while( GLenum error = glGetError() ){
        std::cout << "[OpenGl Error] ( " << error << " )" << function << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const{
    //GLCall( glClearColor( 0.804, 0.141, 0.557, 1.0f ) );
    GLCall( glClearColor( 0.388, 0.878, 0.157, 1.0f ) );
    GLCall( glClear( GL_COLOR_BUFFER_BIT ) );
}

void Renderer::Draw( const VertexArray &va, const IndexBuffer &ib, const Shader &shader ) const{

    shader.Bind();
    
    va.Bind();
    ib.Bind();

    GLCall( glDrawElements( GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr ) );

}
