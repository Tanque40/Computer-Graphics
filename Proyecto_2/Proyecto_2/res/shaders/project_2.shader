#shader vertex
#version 410 core

layout( location = 0 ) in vec3 aPos;   // the position variable has attribute position 0
layout( location = 1 ) in vec2 texCoord; // the texture variable has attribute position 1
layout( location = 2 ) in float o_TexIndex; // the texture index variable has attribute position 2

out  VS_OUT{
    vec2 ourTexture; // output a texture to the fragment shader
    float v_TexIndex;
} vs_out;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4( aPos, 1.0 );
    vs_out.ourTexture = texCoord; // set ourColor to the input color we got from the vertex data
    vs_out.v_TexIndex = o_TexIndex;
}


#shader geometry
#version 410 core
layout( triangles ) in;
layout( triangle_strip, max_vertices = 3 ) out;

in VS_OUT{
    vec2 ourTexture;
    float v_TexIndex;
} gs_in[];

out vec2 OurTexture;
out float g_TexIndex;

uniform float time;

vec4 explode( vec4 position, vec3 normal ){
    float magnitude = 0.8;
    vec3 direction = normal * ( ( sin( time ) + 1.0 ) / 2.0 ) * magnitude;
    return position + vec4( direction, 0.0 );
}

vec3 GetNormal(){
    vec3 a = vec3( gl_in[ 0 ].gl_Position ) - vec3( gl_in[ 1 ].gl_Position );
    vec3 b = vec3( gl_in[ 2 ].gl_Position ) - vec3( gl_in[ 1 ].gl_Position );
    vec3 c = a + b;
    return normalize( c );
}

void main(){
    vec3 normal;

    if( time == 0 ){
        normal = vec3( 0.0, 0.0, 0.0 );
    } else{

        normal = GetNormal();
    }

    gl_Position = explode( gl_in[ 0 ].gl_Position, normal );
    OurTexture = gs_in[ 0 ].ourTexture;
    g_TexIndex = gs_in[ 0 ].v_TexIndex;
    EmitVertex();
    gl_Position = explode( gl_in[ 1 ].gl_Position, normal );
    OurTexture = gs_in[ 1 ].ourTexture;
    g_TexIndex = gs_in[ 1 ].v_TexIndex;
    EmitVertex();
    gl_Position = explode( gl_in[ 2 ].gl_Position, normal );
    OurTexture = gs_in[ 2 ].ourTexture;
    g_TexIndex = gs_in[ 2 ].v_TexIndex;
    EmitVertex();
    EndPrimitive();

}


#shader fragment
#version 410 core

layout( location = 0 ) out vec4 color;

in vec2 OurTexture;

in float g_TexIndex;


uniform sampler2D u_Textures[2];

void main(){
    
    int index = int( g_TexIndex );
    vec4 texColor = texture( u_Textures[index], OurTexture );
    color = texColor;
}
