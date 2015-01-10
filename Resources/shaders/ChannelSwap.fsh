#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;

void main()
{ 
    vec3 normalColor = texture2D(CC_Texture0, v_texCoord).rgb;

  	gl_FragColor = vec4( normalColor.g, normalColor.b, normalColor.r, 1.0 );
  	
  	// this syntax is called swizzling, and achieves the same results
  	// a channel swapping shader is a great opportunity to use swizzling 
  	// https://www.opengl.org/wiki/Data_Type_%28GLSL%29		
  	// gl_FragColor.rgb = normalColor.gbr;
  	// alpha must be set
  	// gl_FragColor.a = 1.0;
}