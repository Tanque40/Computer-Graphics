#shader vertex
#version 410 core

layout( location = 0 ) in vec3 aPos;   // the position variable has attribute position 0
layout( location = 1 ) in vec3 aColor; // the color variable has attribute position 1

out  VS_OUT{
    vec3 ourColor; // output a color to the fragment shader
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4( aPos, 1.0 );
    vs_out.ourColor = aColor; // set ourColor to the input color we got from the vertex data
}





#shader fragment
#version 410 core

out vec4 FragColor;
in vec3 OurColor;

void main(){
    FragColor = vec4( OurColor, 1.0 );
}





#shader geometry
#version 410 core
layout( triangles ) in;
layout( triangle_strip, max_vertices = 3 ) out;

in VS_OUT{
    vec3 ourColor;
} gs_in[];

out vec3 OurColor;

uniform float time;

vec4 explode( vec4 position, vec3 normal ){
    float magnitude = 0.4;
    vec3 direction = normal * ( ( sin( time ) + 1.0 ) / 2.0 ) * magnitude;
    return position + vec4( direction, 0.0 );
}

vec3 GetNormal(){
    vec3 a = vec3( gl_in[ 0 ].gl_Position );
    vec3 b = vec3( gl_in[ 1 ].gl_Position );
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
    OurColor = gs_in[ 0 ].ourColor;
    EmitVertex();
    gl_Position = explode( gl_in[ 1 ].gl_Position, normal );
    OurColor = gs_in[ 1 ].ourColor;
    EmitVertex();
    gl_Position = explode( gl_in[ 2 ].gl_Position, normal );
    OurColor = gs_in[ 2 ].ourColor;
    EmitVertex();
    EndPrimitive();
}