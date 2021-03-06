/****
Compenents Present in Scene 3

#####Ready Features

1. City Model
2. CubeMap (SkyBox -> Sky and Cloud)
3.Grass Instancing
4.CityLight Instancing
5.Bench Instancing
6. Palm Tree Instancing

######Upcoming Features

1.Shadow
2.Fog
3.Low Poly Water
****/
#include <C:\glm\glm.hpp>
#include <C:\glm\gtc\matrix_transform.hpp>
#include <C:\glm\gtc\type_ptr.hpp>

#include "Camera_2.h"

#define MODEL_X_TRANSLATE		0.0f	//X-translation of MODEL
#define MODEL_Y_TRANSLATE		-1.0f	//Y-translation of MODEL
#define MODEL_Z_TRANSLATE		-20.0f	//Z-translation of MODEL

Camera camera;

enum
{
	HAD_ATTRIBUTE_POSITION = 0,
	HAD_ATTRIBUTE_COLOR,
	HAD_ATTRIBUTE_NORMAL,
	HAD_ATTRIBUTE_TEXTURE0,
};

FILE *gpFile;

GLuint g_Scene3_Vbo_Position, g_Scene3_Vbo_Normal, g_Scene3_Vbo_Instance;

struct Model
{
	GLuint Vao;
	std::vector<float> gv_vertices;
	std::vector<float> gv_textures;
	std::vector<float> gv_normals;
	int count_of_vertices;

	
};

Model g_Scene3_CityModel;
Model g_Scene3_GrassModel;
Model g_Scene3_SkyBoxModel;
//Instancing
Model g_Scene3_CityLightModel;
Model g_Scene3_PalmTreeModel;
Model g_Scene3_BenchModel;


struct Shader
{
	GLuint gVertexShaderObject;
	GLuint gFragmentShaderObject;
	GLuint gShaderProgramObject;
};

Shader g_Scene3_CityModelShader;
Shader g_Scene3_GrassShader;
Shader g_Scene3_SkyBoxShader;
Shader g_Scene3_InstanceShader;



//**********City Model******************


//uniforms 
GLuint g_Scene3_CityModel_ModelMatrixUniform, g_Scene3_CityModel_ViewMatrixUniform, g_Scene3_CityModel_ProjectionMatrixUniform;
GLuint g_Scene3_CityModel_LKeyPressedUniform;

GLuint g_Scene3_CityModel_LaUniform, g_Scene3_CityModel_LdUniform, g_Scene3_CityModel_LsUniform;
GLuint g_Scene3_CityModel_LightPositionUniform;

GLuint g_Scene3_CityModel_KaUniform, g_Scene3_CityModel_KdUniform, g_Scene3_CityModel_KsUniform;
GLuint g_Scene3_CityModel_MaterialShininessUniform;

glm::mat4 g_Scene3_CityModel_PerspectiveProjectionMatrix;

bool gbLight = false;

//Light Values
GLfloat lightAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat lightPosition[] = { -324.0f,205.0f,-365.0f,0.0f };

GLfloat materialAmbient[] = { 0.25f,0.25f,0.25f,1.0f };
GLfloat materialDiffuse[] = { 0.4f,0.4f,0.4f,1.0f };
GLfloat materialSpecular[] = { 0.774597f,0.774597f,0.774597f,1.0f };
GLfloat materialShininess = 0.6f * 128.0f;


//Functions
//init, uninit, draw
void Init_Scene3(void);
//CityModel
void Scene3_initializeCityModel(void);
//GRASS
void Scene3_initializeGrass(void);
//SkyBox
void Scene3_initializeSkyBox(void);
unsigned int loadCubemap(std::vector<std::string> faces);

typedef struct                                      // Create A Structure
{
	GLubyte *imageData;                             // Image Data (Up To 32 Bits)
	GLuint  bpp;                                    // Image Color Depth In Bits Per Pixel
	GLuint  width;                                  // Image Width
	GLuint  height;                                 // Image Height
	GLuint  texID;                                  // Texture ID Used To Select A Texture
} TextureImage;

TextureImage    textures[6];

TextureImage* LoadTGA(TextureImage *texture, const char *filename, int num);


//Instancing
GLuint g_Scene3_Instance_ModelMatrixUniform, g_Scene3_Instance_ViewMatrixUniform, g_Scene3_Instance_ProjectionMatrixUniform;
GLuint g_Scene3_Instance_LKeyPressedUniform, g_Scene3_Instance_LaUniform, g_Scene3_Instance_LdUniform, g_Scene3_Instance_LsUniform;
GLuint g_Scene3_Instance_LightPositionUniform, g_Scene3_Instance_KaUniform, g_Scene3_Instance_KdUniform, g_Scene3_Instance_KsUniform, g_Scene3_Instance_MaterialShininessUniform;

//CITYLIGHT Instancing
const int g_CityLight_InstanceCount = 8;

void Scene3_initializeInstancingFeature(void);
void Scene3_initializeCityLightInstancing(void);

float CITYLIGHT_X_TRANSLATE = -430.0f; //for actual grass
float CITYLIGHT_Y_TRANSLATE = -1.0f;
float CITYLIGHT_Z_TRANSLATE = -920.0f;

//Bench Instancing
const int g_Bench_InstanceCount = 3;
void Scene3_initializeBenchInstancing(void);

//Palm Tree
const int g_PalmTree_InstanceCount = 3;
void Scene3_initializePalmTreeInstancing(void);

void Init_Scene3()
{
	g_Scene3_CityModel.count_of_vertices = LoadMeshData("resources/CityModel/cityModel.obj", g_Scene3_CityModel.gv_vertices, g_Scene3_CityModel.gv_textures, g_Scene3_CityModel.gv_normals);
	Scene3_initializeCityModel();

	//SkyBox
	Scene3_initializeSkyBox();

	//Grass Instancing
	Scene3_initializeGrass();

	//CityLight Instancing
	g_Scene3_CityLightModel.count_of_vertices = LoadMeshData("resources/StreetLight/street_light.obj", g_Scene3_CityLightModel.gv_vertices, g_Scene3_CityLightModel.gv_textures, g_Scene3_CityLightModel.gv_normals);

	Scene3_initializeInstancingFeature();
	Scene3_initializeCityLightInstancing();

	//Bench
	g_Scene3_BenchModel.count_of_vertices = LoadMeshData("resources/Bench/Bench.obj", g_Scene3_BenchModel.gv_vertices, g_Scene3_BenchModel.gv_textures, g_Scene3_BenchModel.gv_normals);
	Scene3_initializeBenchInstancing();

	//Palm Tree
	g_Scene3_PalmTreeModel.count_of_vertices = LoadMeshData("resources/PalmTree/PalmTree.obj", g_Scene3_PalmTreeModel.gv_vertices, g_Scene3_PalmTreeModel.gv_textures, g_Scene3_PalmTreeModel.gv_normals);
	Scene3_initializePalmTreeInstancing();

}
//********************GRASS**********************

#include "ktx_loading_header.h"

GLuint g_Scene3_Grass_MVPMatrix;
GLuint g_Scene3_Grass_Rotation;


GLuint g_Scene3_Texture_grass_color;
GLuint g_Scene3_Texture_grass_length;
GLuint g_Scene3_Texture_grass_orientation;
GLuint g_Scene3_Texture_grass_bend;

float GRASS_X_TRANSLATE = -204.0f;//-445.0f; //for actual grass
float GRASS_Y_TRANSLATE = -1.0f;
float GRASS_Z_TRANSLATE = -750.0f;

void Scene3_initializeGrass(void)
{
	void uninitialize(int);

	//Vertex Shader
	g_Scene3_GrassShader.gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
		"#version 450" \
		"\n" \
		// Incoming per vertex position:
		"in vec4 vVertex;" \

		// Output varyings:
		"out vec4 color;"\

		"uniform mat4 mvpMatrix;"\
		"uniform float rotation_increment;"\

		"layout(binding = 0) uniform sampler1D grass_palette_texture;"\
		"layout(binding = 1) uniform sampler2D grass_length_texture;"\
		"layout(binding = 2) uniform sampler2D grass_orientation_texture;"\
		"layout(binding = 3) uniform sampler2D grass_color_texture;"\
		"layout(binding = 4) uniform sampler2D grass_bend_texture;"\

		"int random(int seed, int iterations)"\
		"{"\
		"int value = seed;"\
		"int n;"

		"for (n = 0; n < iterations; n++)"\
		"{"\
		"value = ((value >> 7) ^ (value << 9)) * 15485863;"\
		"}"\

		"return(value);"\
		"}"\

		"vec4 random_vector(int seed)"\
		"{"\
		"int r = random(gl_InstanceID, 4);"\
		"int g = random(r, 2);"\
		"int b = random(g, 2);"\
		"int a = random(b, 2);"\

		"return(vec4(float(r & 0x3FF) / 1024.0,"\
		"float(g & 0x3FF) / 1024.0,"\
		"float(b & 0x3FF) / 1024.0,"\
		"float(a & 0x3FF) / 1024.0));"\
		"}"\

		"mat4 construct_rotation_matrix(float angle)"\
		"{"\
		"float st = sin(angle + rotation_increment);"\
		"float ct = cos(angle + rotation_increment);"\

		"return(mat4(vec4(ct, 0.0, st, 0.0),"\
		"vec4(0.0, 1.0, 0.0, 0.0),"\
		"vec4(-st, 0.0, ct, 0.0),"\
		"vec4(0.0, 0.0, 0.0, 1.0)));"\
		"}"\

		"void main(void)"\
		"{"\
		"vec4 offset = vec4(float(gl_InstanceID >> 10) - 512.0,"\
		"0.0f,"\
		"float(gl_InstanceID & 0x3FF) - 512.0,"\
		"0.0f);"\

		"int number_1 = random(gl_InstanceID, 3);"\
		"int number_2 = random(number_1, 2);"\

		"offset += vec4(float(number_1 & 0xFF) / 256.0,"\
		"0.0f,"\
		"float(number_2 & 0xFF) / 256.0,"\
		"0.0f);"\

		//float angle = float(random(number_2, 2) & 0x3FF) / 1024.0;

		"vec2 texcoord = offset.xz / 1024.0 + vec2(0.5);"\

		// float bend_factor = float(random(number_2, 7) & 0x3FF) / 1024.0;
		"float bend_factor = texture(grass_bend_texture, texcoord).r * 2.0;"\
		"float bend_amount = cos(vVertex.y);"\

		"float angle = texture(grass_orientation_texture, texcoord).r * 2.0 * 3.141592;"\
		"mat4 rot = construct_rotation_matrix(angle);"\
		"vec4 position = (rot * (vVertex + vec4(0.0, 0.0, bend_amount * bend_factor, 0.0))) + offset;"\

		"position *= vec4(1.0, texture(grass_length_texture, texcoord).r * 0.9 + 0.3, 1.0, 1.0);"\

		"gl_Position = mvpMatrix * position;"\
		// (rot * position);

		// color = vec4(random_vector(gl_InstanceID).xyz * vec3(0.1, 0.5, 0.1) + vec3(0.1, 0.4, 0.1), 1.0);
		// color = texture(grass_orientation_texture, texcoord);
		"color = texture(grass_palette_texture, texture(grass_color_texture, texcoord).r) + vec4(random_vector(gl_InstanceID).xyz * vec3(0.1, 0.5, 0.1), 1.0);"\
		"}";

	glShaderSource(g_Scene3_GrassShader.gVertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	glCompileShader(g_Scene3_GrassShader.gVertexShaderObject);
	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(g_Scene3_GrassShader.gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_GrassShader.gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_GrassShader.gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Vertex Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Fragment Shader
	g_Scene3_GrassShader.gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 450" \
		"\n" \

		"in vec4 color;"\

		"out vec4 output_color;"\

		"void main(void)"\
		"{"\
		"output_color = color;"\
		"}";

	glShaderSource(g_Scene3_GrassShader.gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	glCompileShader(g_Scene3_GrassShader.gFragmentShaderObject);

	glGetShaderiv(g_Scene3_GrassShader.gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_GrassShader.gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_GrassShader.gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Shader Program
	g_Scene3_GrassShader.gShaderProgramObject = glCreateProgram();

	glAttachShader(g_Scene3_GrassShader.gShaderProgramObject, g_Scene3_GrassShader.gVertexShaderObject);

	glAttachShader(g_Scene3_GrassShader.gShaderProgramObject, g_Scene3_GrassShader.gFragmentShaderObject);

	glBindAttribLocation(g_Scene3_GrassShader.gShaderProgramObject, HAD_ATTRIBUTE_POSITION, "vVertex");

	//glBindAttribLocation(gShaderProgramObject, HAD_ATTRIBUTE_NORMAL, "vNormal");

	glLinkProgram(g_Scene3_GrassShader.gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;

	glGetProgramiv(g_Scene3_GrassShader.gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_Scene3_GrassShader.gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(g_Scene3_GrassShader.gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	g_Scene3_Grass_MVPMatrix = glGetUniformLocation(g_Scene3_GrassShader.gShaderProgramObject, "mvpMatrix");
	g_Scene3_Grass_Rotation = glGetUniformLocation(g_Scene3_GrassShader.gShaderProgramObject, "rotation_increment");

	glActiveTexture(GL_TEXTURE1);
	g_Scene3_Texture_grass_length = load("resources/Grass/grass_length.ktx", 0);
	glActiveTexture(GL_TEXTURE2);
	g_Scene3_Texture_grass_orientation = load("resources/Grass/grass_orientation.ktx", 0);
	glActiveTexture(GL_TEXTURE3);
	g_Scene3_Texture_grass_color = load("resources/Grass/grass_color.ktx", 0);
	glActiveTexture(GL_TEXTURE4);
	g_Scene3_Texture_grass_bend = load("resources/Grass/grass_bend.ktx", 0);


	static const GLfloat grass_blade[] =
	{
		-0.3f, 0.0f,
		0.3f, 0.0f,
		-0.20f, 1.0f,
		0.1f, 1.3f,
		-0.05f, 2.3f,
		0.0f, 3.3f
	};

	glGenVertexArrays(1, &g_Scene3_GrassModel.Vao);
	glBindVertexArray(g_Scene3_GrassModel.Vao);

	glGenBuffers(1, &g_Scene3_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grass_blade), grass_blade, GL_STATIC_DRAW);


	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

}

//***********************SKYBOX***********************
GLuint g_Scene3_SkyBox_ProjectionUniform;
GLuint g_Scene3_SkyBox_ModelMatrixUniform;
GLuint g_Scene3_SkyBox_ViewUniform;
GLuint g_Scene3_SkyBox_Uniform;


GLuint g_Scene3_CubemapTexture;

void Scene3_initializeSkyBox(void)
{
	fopen_s(&gpFile, "Log.txt", "a+");

	fprintf(gpFile, "In LoadSkyBoxShader \n");
	fclose(gpFile);
	void uninitialize(int);
	//VERTEX SHADER
	g_Scene3_SkyBoxShader.gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertextShaderSourceCodeSkyBox =
		"#version 460" \
		"\n" \
		"out VS_OUT" \
		"{" \
		"vec3    tc;" \
		"} vs_out;" \
		"uniform mat4 model_matrix;" \
		"uniform mat4 view_matrix;" \
		"void main(void)" \
		"{" \
		"vec3[4] vertices = vec3[4](vec3(-1.0, -1.0, 1.0)," \
		"vec3(1.0, -1.0, 1.0)," \
		"vec3(-1.0, 1.0, 1.0)," \
		"vec3(1.0, 1.0, 1.0)); "\

		"vs_out.tc = mat3(view_matrix * model_matrix) * vertices[gl_VertexID];" \
		"gl_Position = vec4(vertices[gl_VertexID], 1.0);" \
		"}";


	glShaderSource(g_Scene3_SkyBoxShader.gVertexShaderObject, 1, (const GLchar**)&vertextShaderSourceCodeSkyBox, NULL);

	//compile shader
	glCompileShader(g_Scene3_SkyBoxShader.gVertexShaderObject);

	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(g_Scene3_SkyBoxShader.gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_SkyBoxShader.gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_SkyBoxShader.gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Vertex Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);


				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}
	//FRAGMENT SHADER

	g_Scene3_SkyBoxShader.gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCodeSkyBox =
		"#version 460"\
		"\n" \
		"uniform samplerCube tex_cubemap;" \
		"in VS_OUT" \
		"{" \
		"vec3    tc;" \
		"} fs_in;" \
		"layout (location = 0) out vec4 color;" \
		"void main(void)" \
		"{" \
		//"color = texture(tex_cubemap, vec3(fs_in.tc.x, -fs_in.tc.y, fs_in.tc.z));" 
		"color = texture(tex_cubemap, fs_in.tc);" \
		"}";

	glShaderSource(g_Scene3_SkyBoxShader.gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCodeSkyBox, NULL);

	glCompileShader(g_Scene3_SkyBoxShader.gFragmentShaderObject);

	glGetShaderiv(g_Scene3_SkyBoxShader.gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_SkyBoxShader.gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_SkyBoxShader.gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);


				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Shader Program

	g_Scene3_SkyBoxShader.gShaderProgramObject = glCreateProgram();

	glAttachShader(g_Scene3_SkyBoxShader.gShaderProgramObject, g_Scene3_SkyBoxShader.gVertexShaderObject);

	glAttachShader(g_Scene3_SkyBoxShader.gShaderProgramObject, g_Scene3_SkyBoxShader.gFragmentShaderObject);

	//glBindAttribLocation(gShaderProgramObjectSkyBox, MALATI_ATTRIBUTE_VERTEX, "aPos");
	//glBindAttribLocation(gShaderProgramObjectSkyBox, MALATI_ATTRIBUTE_TEXTURE0, "vTexture0_Coord");

	glLinkProgram(g_Scene3_SkyBoxShader.gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(g_Scene3_SkyBoxShader.gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_Scene3_SkyBoxShader.gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength>0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(g_Scene3_SkyBoxShader.gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				fclose(gpFile);


				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	g_Scene3_SkyBox_ModelMatrixUniform = glGetUniformLocation(g_Scene3_SkyBoxShader.gShaderProgramObject, "model_matrix");
	g_Scene3_SkyBox_ViewUniform = glGetUniformLocation(g_Scene3_SkyBoxShader.gShaderProgramObject, "view_matrix");
	g_Scene3_SkyBox_Uniform = glGetUniformLocation(g_Scene3_SkyBoxShader.gShaderProgramObject, "tex_cubemap");


	glGenVertexArrays(1, &g_Scene3_SkyBoxModel.Vao);
	glBindVertexArray(g_Scene3_SkyBoxModel.Vao);
	glBindVertexArray(0);

	std::vector<std::string> Faces
	{
		"resources/RotateMirMar/right.tga",
		"resources/RotateMirMar/left.tga",
		"resources/RotateMirMar/new_up.tga",
		"resources/RotateMirMar/dwn.tga",
		"resources/RotateMirMar/front.tga",
		"resources/RotateMirMar/bck.tga",
	};

	g_Scene3_CubemapTexture = loadCubemap(Faces);

}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In loadCubemap....\n");
	fclose(gpFile);
	TextureImage* LoadTGA(TextureImage *texture, const char *filename, int i);
	bool returnType = false;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		TextureImage* textureIm = LoadTGA(&textures[i], faces[i].c_str(), i);
		if (textureIm->imageData)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textureIm->width, textureIm->height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureIm->imageData);
		}
		else
		{
			fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "CubeMap texture failed to load..\n");
			fclose(gpFile);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	/*glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);*/


	return textureID;
}

TextureImage* LoadTGA(TextureImage *texture, const char *filename, int num)                 // Loads A TGA File Into Memory
{
	void _check_gl_error();

	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA : FileName : %s\n", filename);
	fclose(gpFile);

	GLubyte     TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };           // Uncompressed TGA Header
	GLubyte     TGAcompare[12];                         // Used To Compare TGA Header
	GLubyte     header[6];                          // First 6 Useful Bytes From The Header
	GLuint      bytesPerPixel;                          // Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint      imageSize;                          // Used To Store The Image Size When Setting Aside Ram
	GLuint      temp;                               // Temporary Variable
	GLuint      type = GL_RGBA;                           // Set The Default GL Mode To RBGA (32 BPP)
	FILE *file = NULL;
	fopen_s(&file, filename, "rb");                     // Open The TGA File

	if (file == NULL ||                               // Does File Even Exist?
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||  // Are There 12 Bytes To Read?
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||  // Does The Header Match What We Want?
		fread(header, 1, sizeof(header), file) != sizeof(header))            // If So Read Next 6 Header Bytes
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "Does File EVen Exist..\n");
		fclose(gpFile);

		if (file == NULL)                           // Did The File Even Exist? *Added Jim Strong*
		{
			fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "No..File Not Exists..\n");
			fclose(gpFile);
			return NULL;                           // Return False
		}
		else
		{
			fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "Any Other thing Failed\n");
			fclose(gpFile);
			fclose(file);                           // If Anything Failed, Close The File
			return NULL;                           // Return False
		}
	}
	texture->width = header[1] * 256 + header[0];                   // Determine The TGA Width  (highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];                   // Determine The TGA Height (highbyte*256+lowbyte)
	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA 100\n");
	fclose(gpFile);
	if (texture->width <= 0 ||                      // Is The Width Less Than Or Equal To Zero
		texture->height <= 0 ||                      // Is The Height Less Than Or Equal To Zero
		(header[4] != 24 && header[4] != 32))                   // Is The TGA 24 or 32 Bit?
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "In LoadTGA 1\n");
		fclose(gpFile);
		fclose(file);                               // If Anything Failed, Close The File
		return NULL;                               // Return False
	}
	texture->bpp = header[4];                            // Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel = texture->bpp / 8;                        // Divide By 8 To Get The Bytes Per Pixel
	imageSize = texture->width*texture->height*bytesPerPixel;           // Calculate The Memory Required For The TGA Data
	texture->imageData = (GLubyte *)malloc(imageSize);             // Reserve Memory To Hold The TGA Data
	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA 101\n");
	fclose(gpFile);
	if (texture->imageData == NULL ||                      // Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file) != imageSize)        // Does The Image Size Match The Memory Reserved?
	{
		fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "In LoadTGA 500\n");
		fclose(gpFile);
		if (texture->imageData != NULL)                     // Was Image Data Loaded
		{
			fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "In LoadTGA 501\n");
			fclose(gpFile);
			free(texture->imageData);                    // If So, Release The Image Data
		}
		fclose(file);                               // Close The File
		return NULL;                               // Return False
	}
	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA 102\n");
	fclose(gpFile);
	for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)              // Loop Through The Image Data
	{   // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)

		temp = texture->imageData[i];                      // Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];            // Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;                    // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	return texture;                                    // Texture Building Went Ok, Return True
}

void Scene3_initializeInstancingFeature()
{
	void uninitialize(int);

	g_Scene3_InstanceShader.gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertextShaderSourceCode =
		"#version 400" \
		"\n" \
		"layout(location = 0) in vec3 vPosition;" \
		"layout(location = 1) in vec3 vNormal;" \
		"layout(location = 2) in vec3 aOffset;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_lighting_enabled;" \
		"uniform vec4 u_light_position;" \
		"out vec3 transformed_normals;" \
		"out vec3 light_direction;" \
		"out vec3 viewer_vector;" \

		//"uniform mat4 mvpMatrix;" 
		"void main(void)" \
		"{" \
		"if(u_lighting_enabled==1)" \
		"{" \
		"vec4 eye_coordinates = u_view_matrix*u_model_matrix* vec4(vPosition, 1.0);" \
		"transformed_normals = mat3(u_view_matrix*u_model_matrix)*vNormal;" \
		"light_direction = vec3(u_light_position)-eye_coordinates.xyz;" \
		"viewer_vector = -eye_coordinates.xyz;" \
		"}" \
		//	"gl_Position = u_projection_matrix*u_view_matrix*u_model_matrix*vPosition;" 

		//"gl_Position = mvpMatrix * vec4(aPos.x + aOffset.x, aPos.y, aPos.z + aOffset.y, 1.0f);" 
		//"gl_Position = mvpMatrix * vec4(aPos + aOffset, 1.0f);" 
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vec4(vPosition.x + aOffset.x, vPosition.y + aOffset.y, vPosition.z + aOffset.z, 1.0f);" \
		"}";
	glShaderSource(g_Scene3_InstanceShader.gVertexShaderObject, 1, (const GLchar **)&vertextShaderSourceCode, NULL);

	//compile shader
	glCompileShader(g_Scene3_InstanceShader.gVertexShaderObject);

	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(g_Scene3_InstanceShader.gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_InstanceShader.gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_InstanceShader.gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Vertex Shader of CityLight Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}
	//FRAGMENT SHADER

	g_Scene3_InstanceShader.gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 400" \
		"\n" \
		"in vec3 transformed_normals;" \
		"in vec3 light_direction;" \
		"in vec3 viewer_vector;" \
		"out vec4 FragColor;" \
		"uniform vec3 u_La;" \
		"uniform vec3 u_Ld;" \
		"uniform vec3 u_Ls;" \
		"uniform vec3 u_Ka;" \
		"uniform vec3 u_Kd;" \
		"uniform vec3 u_Ks;" \
		"uniform float u_material_shininess;" \
		"uniform int u_lighting_enabled;" \

		"void main()" \
		"{" \
		"vec3 phong_ads_color;" \
		"if(u_lighting_enabled == 1)" \
		"{" \
		"vec3 normalized_transformed_normals = normalize(transformed_normals);" \
		"vec3 normalized_light_direction = normalize(light_direction);" \
		"vec3 normalized_viewer_vector = normalize(viewer_vector);" \
		"vec3 ambient = u_La * u_Ka;" \
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);" \
		"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;" \
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);" \
		"vec3 specular = u_Ls * u_Ks * pow(max(dot(reflection_vector,normalized_viewer_vector),0.0),u_material_shininess);" \
		"phong_ads_color = ambient + diffuse + specular;" \
		"}" \
		"else" \
		"{" \
		"phong_ads_color = vec3(1.0f,1.0f,1.0f);" \
		"}" \
		"FragColor = vec4(phong_ads_color,1.0);" \

		//		"FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0);" 
		"}";
	glShaderSource(g_Scene3_InstanceShader.gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	glCompileShader(g_Scene3_InstanceShader.gFragmentShaderObject);

	glGetShaderiv(g_Scene3_InstanceShader.gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_InstanceShader.gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_InstanceShader.gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader of CityLight Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Shader Program

	g_Scene3_InstanceShader.gShaderProgramObject = glCreateProgram();

	glAttachShader(g_Scene3_InstanceShader.gShaderProgramObject, g_Scene3_InstanceShader.gVertexShaderObject);

	glAttachShader(g_Scene3_InstanceShader.gShaderProgramObject, g_Scene3_InstanceShader.gFragmentShaderObject);
	glBindAttribLocation(g_Scene3_InstanceShader.gShaderProgramObject, 0, "vPosition"); //aOffset
	glBindAttribLocation(g_Scene3_InstanceShader.gShaderProgramObject, 1, "vNormal"); //aOffset

	glBindAttribLocation(g_Scene3_InstanceShader.gShaderProgramObject, 2, "aOffset");

	glLinkProgram(g_Scene3_InstanceShader.gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(g_Scene3_InstanceShader.gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_Scene3_InstanceShader.gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength>0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(g_Scene3_InstanceShader.gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//g_Scene3_CityLight_MVPUniform = glGetUniformLocation(g_Scene3_CityLight_ShaderProgramObject, "mvpMatrix");

	g_Scene3_Instance_ModelMatrixUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_model_matrix");
	g_Scene3_Instance_ViewMatrixUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_view_matrix");
	g_Scene3_Instance_ProjectionMatrixUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_projection_matrix");

	g_Scene3_Instance_LKeyPressedUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_lighting_enabled");

	g_Scene3_Instance_LaUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_La");
	g_Scene3_Instance_LdUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_Ld");
	g_Scene3_Instance_LsUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_Ls");

	g_Scene3_Instance_LightPositionUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_light_position");

	g_Scene3_Instance_KaUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_Ka");
	g_Scene3_Instance_KdUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_Kd");
	g_Scene3_Instance_KsUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_Ks");

	g_Scene3_Instance_MaterialShininessUniform = glGetUniformLocation(g_Scene3_InstanceShader.gShaderProgramObject, "u_material_shininess");


}

void Scene3_initializeCityLightInstancing()
{
	//new addition
	glm::vec3 translations[g_CityLight_InstanceCount];
	int index = 0;
	float offset = 0.1f;

	translations[0] = { 0.0f , 0.0f , -140.0f };
	translations[1] = { 0.0f , 0.0f, -100.0f };
	translations[2] = { 0.0f, 0.0f , -60.0f };
	translations[3] = { 0.0f, 0.0f , -20.0f };
	translations[4] = { 0.0f , 0.0f , 20.0f };
	translations[5] = { 0.0f , 0.0f, 60.0f };
	translations[6] = { 0.0f, 0.0f , 100.0f };
	translations[7] = { 0.0f, 0.0f , 140.0f };

	glGenBuffers(1, &g_Scene3_Vbo_Instance);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Instance);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * g_CityLight_InstanceCount, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenVertexArrays(1, &g_Scene3_CityLightModel.Vao);
	glBindVertexArray(g_Scene3_CityLightModel.Vao);

	glGenBuffers(1, &g_Scene3_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Position);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_CityLightModel.gv_vertices.size() * sizeof(float), &g_Scene3_CityLightModel.gv_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(MALATI_ATTRIBUTE_VERTEX, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenBuffers(1, &g_Scene3_Vbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Normal);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_CityLightModel.gv_normals.size() * sizeof(float), &g_Scene3_CityLightModel.gv_normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(MALATI_ATTRIBUTE_VERTEX, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Instance);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(2, 1);// tell OpenGL this is an instanced vertex attribute.

	glBindVertexArray(0);

}

void Scene3_initializeBenchInstancing()
{
	//new addition
	glm::vec3 translations[g_Bench_InstanceCount];
	int index = 0;
	float offset = 0.1f;

	translations[0] = { 0.0f , 0.0f , -1000.0f };
	translations[1] = { 0.0f , 0.0f, -200.0f };
	translations[2] = { 0.0f, 0.0f , 1000.0f };
	//translations[3] = { 0.0f, 0.0f , 800.0f };

	glGenBuffers(1, &g_Scene3_Vbo_Instance);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Instance);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * g_Bench_InstanceCount, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenVertexArrays(1, &g_Scene3_BenchModel.Vao);
	glBindVertexArray(g_Scene3_BenchModel.Vao);

	glGenBuffers(1, &g_Scene3_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Position);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_BenchModel.gv_vertices.size() * sizeof(float), &g_Scene3_BenchModel.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(MALATI_ATTRIBUTE_VERTEX, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_Scene3_Vbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Normal);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_BenchModel.gv_normals.size() * sizeof(float), &g_Scene3_BenchModel.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(MALATI_ATTRIBUTE_VERTEX, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Instance);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(2, 1);// tell OpenGL this is an instanced vertex attribute.

	glBindVertexArray(0);
}

void Scene3_initializePalmTreeInstancing()
{
	//new addition
	glm::vec3 translations[g_PalmTree_InstanceCount];
	int index = 0;
	float offset = 0.1f;

	translations[0] = { 0.0f , 0.0f , -1000.0f };
	translations[1] = { 0.0f , 0.0f, -200.0f };
	translations[2] = { 0.0f, 0.0f , 1000.0f };
	//translations[3] = { 0.0f, 0.0f , 800.0f };

	glGenBuffers(1, &g_Scene3_Vbo_Instance);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Instance);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * g_PalmTree_InstanceCount, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenVertexArrays(1, &g_Scene3_PalmTreeModel.Vao);
	glBindVertexArray(g_Scene3_PalmTreeModel.Vao);

	glGenBuffers(1, &g_Scene3_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Position);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_PalmTreeModel.gv_vertices.size() * sizeof(float), &g_Scene3_PalmTreeModel.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(MALATI_ATTRIBUTE_VERTEX, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_Scene3_Vbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Normal);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_PalmTreeModel.gv_normals.size() * sizeof(float), &g_Scene3_PalmTreeModel.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(MALATI_ATTRIBUTE_VERTEX, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Instance);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(2, 1);// tell OpenGL this is an instanced vertex attribute.

	glBindVertexArray(0);

}

void Scene3_initializeCityModel(void)
{
	void uninitialize(int);
	//Vertex Shader
	g_Scene3_CityModelShader.gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
		"#version 450" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_lighting_enabled;" \
		"uniform vec4 u_light_position;" \
		"out vec3 transformed_normals;" \
		"out vec3 light_direction;" \
		"out vec3 viewer_vector;" \
		"void main(void)" \
		"{" \
		"if(u_lighting_enabled==1)" \
		"{" \
		"vec4 eye_coordinates = u_model_matrix*vPosition;" \
		"transformed_normals = mat3(u_model_matrix)*vNormal;" \
		"light_direction = vec3(u_light_position)-eye_coordinates.xyz;" \
		"viewer_vector = -eye_coordinates.xyz;" \
		"}" \
		"gl_Position = u_projection_matrix*u_view_matrix*u_model_matrix*vPosition;" \
		"}";

	glShaderSource(g_Scene3_CityModelShader.gVertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	glCompileShader(g_Scene3_CityModelShader.gVertexShaderObject);
	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(g_Scene3_CityModelShader.gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_CityModelShader.gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_CityModelShader.gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Vertex Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Fragment Shader
	g_Scene3_CityModelShader.gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 450" \
		"\n" \
		"in vec3 transformed_normals;" \
		"in vec3 light_direction;" \
		"in vec3 viewer_vector;" \
		"out vec4 FragColor;" \
		"uniform vec3 u_La;" \
		"uniform vec3 u_Ld;" \
		"uniform vec3 u_Ls;" \
		"uniform vec3 u_Ka;" \
		"uniform vec3 u_Kd;" \
		"uniform vec3 u_Ks;" \
		"uniform float u_material_shininess;" \
		"uniform int u_lighting_enabled;" \
		"void main(void)" \
		"{" \
		"vec3 phong_ads_color;" \
		"if(u_lighting_enabled == 1)" \
		"{" \
		"vec3 normalized_transformed_normals = normalize(transformed_normals);" \
		"vec3 normalized_light_direction = normalize(light_direction);" \
		"vec3 normalized_viewer_vector = normalize(viewer_vector);" \
		"vec3 ambient = u_La * u_Ka;" \
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);" \
		"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;" \
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);" \
		"vec3 specular = u_Ls * u_Ks * pow(max(dot(reflection_vector,normalized_viewer_vector),0.0),u_material_shininess);" \
		"phong_ads_color = ambient + diffuse + specular;" \
		"}" \
		"else" \
		"{" \
		"phong_ads_color = vec3(1.0f,1.0f,1.0f);" \
		"}" \
		"FragColor = vec4(phong_ads_color,1.0);" \
		"}";

	glShaderSource(g_Scene3_CityModelShader.gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	glCompileShader(g_Scene3_CityModelShader.gFragmentShaderObject);

	glGetShaderiv(g_Scene3_CityModelShader.gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_CityModelShader.gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_CityModelShader.gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Shader Program
	g_Scene3_CityModelShader.gShaderProgramObject = glCreateProgram();

	glAttachShader(g_Scene3_CityModelShader.gShaderProgramObject, g_Scene3_CityModelShader.gVertexShaderObject);

	glAttachShader(g_Scene3_CityModelShader.gShaderProgramObject, g_Scene3_CityModelShader.gFragmentShaderObject);

	glBindAttribLocation(g_Scene3_CityModelShader.gShaderProgramObject, HAD_ATTRIBUTE_POSITION, "vPosition");

	glBindAttribLocation(g_Scene3_CityModelShader.gShaderProgramObject, HAD_ATTRIBUTE_NORMAL, "vNormal");

	glLinkProgram(g_Scene3_CityModelShader.gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;

	glGetProgramiv(g_Scene3_CityModelShader.gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_Scene3_CityModelShader.gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(g_Scene3_CityModelShader.gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	g_Scene3_CityModel_ModelMatrixUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_model_matrix");
	g_Scene3_CityModel_ViewMatrixUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_view_matrix");
	g_Scene3_CityModel_ProjectionMatrixUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_projection_matrix");

	g_Scene3_CityModel_LKeyPressedUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_lighting_enabled");

	g_Scene3_CityModel_LaUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_La");
	g_Scene3_CityModel_LdUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_Ld");
	g_Scene3_CityModel_LsUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_Ls");

	g_Scene3_CityModel_LightPositionUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_light_position");

	g_Scene3_CityModel_KaUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_Ka");
	g_Scene3_CityModel_KdUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_Kd");
	g_Scene3_CityModel_KsUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_Ks");

	g_Scene3_CityModel_MaterialShininessUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_material_shininess");

	//VAO
	glGenVertexArrays(1, &g_Scene3_CityModel.Vao);
	glBindVertexArray(g_Scene3_CityModel.Vao);

	glGenBuffers(1, &g_Scene3_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Position);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_CityModel.gv_vertices.size() * sizeof(float), &g_Scene3_CityModel.gv_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_Scene3_Vbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Normal);
	//glBufferData(GL_ARRAY_BUFFER, gv_normals_road.size() * sizeof(float), &gv_normals_road[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_CityModel.gv_normals.size() * sizeof(float), &g_Scene3_CityModel.gv_normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Uninitialize_Scene3(void);
void Uninitialize_CityModelShader(void);
void Uninitialize_GrassShader(void);
void Uninitialize_SkyBoxShader(void);
void Uninitialize_CityLightShader(void);
void Uninitialize_BenchShader(void);
void Uninitialize_InstanceShader(void);
void Uninitialize_PalmTreeShader(void);


void Uninitialize_Scene3()
{
	if (g_Scene3_Vbo_Position)
	{
		glDeleteBuffers(1, &g_Scene3_Vbo_Position);
		g_Scene3_Vbo_Position = 0;
	}

	if (g_Scene3_Vbo_Normal)
	{
		glDeleteBuffers(1, &g_Scene3_Vbo_Normal);
		g_Scene3_Vbo_Normal = 0;
	}

	if (g_Scene3_Vbo_Instance)
	{
		glDeleteBuffers(1, &g_Scene3_Vbo_Instance);
		g_Scene3_Vbo_Instance = 0;
	}

	Uninitialize_CityLightShader();
	Uninitialize_BenchShader();
	Uninitialize_InstanceShader();

	Uninitialize_GrassShader();

	Uninitialize_SkyBoxShader();

	Uninitialize_CityModelShader();

	

}

void Uninitialize_CityLightShader(void)
{
	if (g_Scene3_CityLightModel.Vao)
	{
		glDeleteVertexArrays(1, &g_Scene3_CityLightModel.Vao);
		g_Scene3_CityLightModel.Vao = 0;
	}
}

void Uninitialize_BenchShader(void)
{
	if (g_Scene3_BenchModel.Vao)
	{
		glDeleteVertexArrays(1, &g_Scene3_BenchModel.Vao);
		g_Scene3_BenchModel.Vao = 0;
	}
}

void Uninitialize_InstanceShader(void)
{
	//Detach Shader 
	glDetachShader(g_Scene3_InstanceShader.gShaderProgramObject, g_Scene3_InstanceShader.gVertexShaderObject);
	glDetachShader(g_Scene3_InstanceShader.gShaderProgramObject, g_Scene3_InstanceShader.gFragmentShaderObject);

	//Delete Shader
	glDeleteShader(g_Scene3_InstanceShader.gVertexShaderObject);
	g_Scene3_InstanceShader.gVertexShaderObject = 0;

	glDeleteShader(g_Scene3_InstanceShader.gFragmentShaderObject);
	g_Scene3_InstanceShader.gFragmentShaderObject = 0;

	//Delete Program
	glDeleteProgram(g_Scene3_InstanceShader.gShaderProgramObject);
	g_Scene3_InstanceShader.gShaderProgramObject = 0;

	//Stray call to glUseProgram(0)
	glUseProgram(0);
}
void Uninitialize_CityModelShader(void)
{
	if (g_Scene3_CityModel.Vao)
	{
		glDeleteVertexArrays(1, &g_Scene3_CityModel.Vao);
		g_Scene3_CityModel.Vao = 0;
	}

	//Detach Shader 
	glDetachShader(g_Scene3_CityModelShader.gShaderProgramObject, g_Scene3_CityModelShader.gVertexShaderObject);
	glDetachShader(g_Scene3_CityModelShader.gShaderProgramObject, g_Scene3_CityModelShader.gFragmentShaderObject);

	//Delete Shader
	glDeleteShader(g_Scene3_CityModelShader.gVertexShaderObject);
	g_Scene3_CityModelShader.gVertexShaderObject = 0;

	glDeleteShader(g_Scene3_CityModelShader.gFragmentShaderObject);
	g_Scene3_CityModelShader.gFragmentShaderObject = 0;

	//Delete Program
	glDeleteProgram(g_Scene3_CityModelShader.gShaderProgramObject);
	g_Scene3_CityModelShader.gShaderProgramObject = 0;

	//Stray call to glUseProgram(0)
	glUseProgram(0);
}

void Uninitialize_GrassShader()
{
	if (g_Scene3_GrassModel.Vao)
	{
		glDeleteVertexArrays(1, &g_Scene3_GrassModel.Vao);
		g_Scene3_GrassModel.Vao = 0;
	}

	//Detach Shader 
	glDetachShader(g_Scene3_GrassShader.gShaderProgramObject, g_Scene3_GrassShader.gVertexShaderObject);
	glDetachShader(g_Scene3_GrassShader.gShaderProgramObject, g_Scene3_GrassShader.gFragmentShaderObject);

	//Delete Shader
	glDeleteShader(g_Scene3_GrassShader.gVertexShaderObject);
	g_Scene3_GrassShader.gVertexShaderObject = 0;

	glDeleteShader(g_Scene3_GrassShader.gFragmentShaderObject);
	g_Scene3_GrassShader.gFragmentShaderObject = 0;

	//Delete Program
	glDeleteProgram(g_Scene3_GrassShader.gShaderProgramObject);
	g_Scene3_GrassShader.gShaderProgramObject = 0;

	//Stray call to glUseProgram(0)
	glUseProgram(0);

}

void Uninitialize_SkyBoxShader(void)
{
	if (g_Scene3_SkyBoxModel.Vao)
	{
		glDeleteVertexArrays(1, &g_Scene3_SkyBoxModel.Vao);
		g_Scene3_SkyBoxModel.Vao = 0;
	}

	//Detach Shader 
	glDetachShader(g_Scene3_SkyBoxShader.gShaderProgramObject, g_Scene3_SkyBoxShader.gVertexShaderObject);
	glDetachShader(g_Scene3_SkyBoxShader.gShaderProgramObject, g_Scene3_SkyBoxShader.gFragmentShaderObject);

	//Delete Shader
	glDeleteShader(g_Scene3_SkyBoxShader.gVertexShaderObject);
	g_Scene3_SkyBoxShader.gVertexShaderObject = 0;

	glDeleteShader(g_Scene3_SkyBoxShader.gFragmentShaderObject);
	g_Scene3_SkyBoxShader.gFragmentShaderObject = 0;

	//Delete Program
	glDeleteProgram(g_Scene3_SkyBoxShader.gShaderProgramObject);
	g_Scene3_SkyBoxShader.gShaderProgramObject = 0;

	//Stray call to glUseProgram(0)
	glUseProgram(0);
}

void Draw_Scene3(void);
void DrawSkyBox(void);
void DrawCityModel(void);
void DrawGrassInstancing(void);
void DrawInstancingShader(void);


void Draw_Scene3(void)
{
	DrawSkyBox();

	DrawCityModel();

	DrawGrassInstancing();

	DrawInstancingShader();
}

void DrawSkyBox()
{
	glm::mat4 modelMatrix = glm::mat4();
	glm::mat4 viewMatrix = glm::mat4();


	glUseProgram(g_Scene3_SkyBoxShader.gShaderProgramObject);
	glDisable(GL_DEPTH_TEST);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));
	glUniformMatrix4fv(g_Scene3_SkyBox_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	viewMatrix = camera.GetViewMatrix();
	glUniformMatrix4fv(g_Scene3_SkyBox_ViewUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform1i(g_Scene3_SkyBox_Uniform, 0);

	glBindVertexArray(g_Scene3_SkyBoxModel.Vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_Scene3_CubemapTexture);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(0);
}

void DrawCityModel(void)
{
	//Use Shader Program Object
	glUseProgram(g_Scene3_CityModelShader.gShaderProgramObject);

	if (gbLight == true)
	{
		glUniform1i(g_Scene3_CityModel_LKeyPressedUniform, 1);

		glUniform3fv(g_Scene3_CityModel_LaUniform, 1, lightAmbient);
		glUniform3fv(g_Scene3_CityModel_LdUniform, 1, lightDiffuse);
		glUniform3fv(g_Scene3_CityModel_LsUniform, 1, lightSpecular);
		glUniform4fv(g_Scene3_CityModel_LightPositionUniform, 1, lightPosition);

		glUniform3fv(g_Scene3_CityModel_KaUniform, 1, materialAmbient);
		glUniform3fv(g_Scene3_CityModel_KdUniform, 1, materialDiffuse);
		glUniform3fv(g_Scene3_CityModel_KsUniform, 1, materialSpecular);
		glUniform1f(g_Scene3_CityModel_MaterialShininessUniform, materialShininess);
	}
	else
	{
		glUniform1i(g_Scene3_CityModel_LKeyPressedUniform, 0);
	}

	glm::mat4 viewMatrix = glm::mat4();
	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	
	viewMatrix = camera.GetViewMatrix();

	glUniformMatrix4fv(g_Scene3_CityModel_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(g_Scene3_CityModel_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(g_Scene3_CityModel_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_Scene3_CityModel_PerspectiveProjectionMatrix));

	glBindVertexArray(g_Scene3_CityModel.Vao);
	glDrawArrays(GL_TRIANGLES, 0, g_Scene3_CityModel.gv_vertices.size());
	glBindVertexArray(0);

	glUseProgram(0);
}

void DrawGrassInstancing(void)
{
	//Grass Instancing
	glUseProgram(g_Scene3_GrassShader.gShaderProgramObject);

	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(GRASS_X_TRANSLATE, GRASS_Y_TRANSLATE, GRASS_Z_TRANSLATE));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.03f, 0.1f, 0.5f));

	glm::mat4 viewMatrix = glm::mat4();
	viewMatrix = camera.GetViewMatrix();

	glm::mat4 MVPMatrix = g_Scene3_CityModel_PerspectiveProjectionMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv(g_Scene3_Grass_MVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

	glBindVertexArray(g_Scene3_GrassModel.Vao);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, 1024 * 1024);

	glBindVertexArray(0);

	glUseProgram(0);

}

void DrawInstancingShader()
{
	//Instancing
	glUseProgram(g_Scene3_InstanceShader.gShaderProgramObject);

	if (gbLight == true)
	{
		glUniform1i(g_Scene3_Instance_LKeyPressedUniform, 1);

		glUniform3fv(g_Scene3_Instance_LaUniform, 1, lightAmbient);
		glUniform3fv(g_Scene3_Instance_LdUniform, 1, lightDiffuse);
		glUniform3fv(g_Scene3_Instance_LsUniform, 1, lightSpecular);
		glUniform4fv(g_Scene3_Instance_LightPositionUniform, 1, lightPosition);

		glUniform3fv(g_Scene3_Instance_KaUniform, 1, materialAmbient);
		glUniform3fv(g_Scene3_Instance_KdUniform, 1, materialDiffuse);
		glUniform3fv(g_Scene3_Instance_KsUniform, 1, materialSpecular);
		glUniform1f(g_Scene3_Instance_MaterialShininessUniform, materialShininess);
	}
	else
	{
		glUniform1i(g_Scene3_Instance_LKeyPressedUniform, 0);
	}

	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-185.0f, -1.3f, -900.0f));
	//X - Pos : -185.000000, Y - Pos : 0.000000, Z - Pos : -835.000000

	modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(g_Scene3_Instance_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glm::mat4 viewMatrix = glm::mat4();
	viewMatrix = camera.GetViewMatrix();

	glUniformMatrix4fv(g_Scene3_Instance_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(g_Scene3_Instance_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_Scene3_CityModel_PerspectiveProjectionMatrix));

	//****************CITY LIGHT (on road opposite to grass)***************
	glBindVertexArray(g_Scene3_CityLightModel.Vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, g_Scene3_CityLightModel.gv_vertices.size(), g_CityLight_InstanceCount);
	glBindVertexArray(0);

	modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(2.4f, -1.3f, -270.0f));

//	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 0.5f, 1.0f));

	glUniformMatrix4fv(g_Scene3_Instance_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	viewMatrix = glm::mat4();
	viewMatrix = camera.GetViewMatrix();

	glUniformMatrix4fv(g_Scene3_Instance_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(g_Scene3_Instance_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_Scene3_CityModel_PerspectiveProjectionMatrix));

	//****************CITY LIGHT (on road after bridge crossing)*******************
	glBindVertexArray(g_Scene3_CityLightModel.Vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, g_Scene3_CityLightModel.gv_vertices.size(), 6);
	glBindVertexArray(0);


	modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-200.0f, -3.0f, -800.0f));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.03f));

	glUniformMatrix4fv(g_Scene3_Instance_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	//***************BENCHES (Placed On Grass)
	glBindVertexArray(g_Scene3_BenchModel.Vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, g_Scene3_BenchModel.gv_vertices.size(), g_Bench_InstanceCount);
	glBindVertexArray(0);
	glUseProgram(0);

	/*
	modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-200.0f, -3.0f, -800.0f));

	//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.03f));

	glUniformMatrix4fv(g_Scene3_Instance_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	//***************Palm Tree (Placed On Grass)
	glBindVertexArray(g_Scene3_PalmTreeModel.Vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, g_Scene3_PalmTreeModel.gv_vertices.size(), g_PalmTree_InstanceCount);
	glBindVertexArray(0);
	glUseProgram(0);
	*/
	
}