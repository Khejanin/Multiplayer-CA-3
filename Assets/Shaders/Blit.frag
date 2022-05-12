uniform sampler2D source;

void main()
{
    vec4 sourceFragment = texture2D(source, gl_TexCoord[0].xy);
    gl_FragColor = sourceFragment;
}