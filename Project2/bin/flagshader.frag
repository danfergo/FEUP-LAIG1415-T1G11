uniform sampler2D baseImage;
varying float coordY;
void main()
{
	float attenuation = (coordY+1.0)*0.6 + 0.4; // values between 0.4 and 1
	vec4 original_text = texture2D(baseImage,gl_TexCoord[0].st);
	gl_FragColor = vec4(original_text.xyz*attenuation,1.0);
}
