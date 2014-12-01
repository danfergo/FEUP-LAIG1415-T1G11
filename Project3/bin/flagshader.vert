uniform int time;
uniform int wind;
uniform float pi;
varying float coordY;

void main() 
{
	vec4 wave_vertex = gl_Vertex;
	float y_coord = gl_Vertex.x + 0.001*float(time);
	wave_vertex.y = sin(2.0*float(wind)*mod(y_coord,2.0*pi));
	gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*wave_vertex;
	coordY = wave_vertex.y;

	gl_TexCoord[0] = gl_MultiTexCoord0;
}