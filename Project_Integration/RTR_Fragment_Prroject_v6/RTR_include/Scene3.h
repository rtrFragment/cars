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

#pragma once

#include "Common_Header.h"
#include "Camera_2.h"
#include "../RTR_lib/speedometer/speedometer.h"

#define MODEL_X_TRANSLATE 0.0f   //X-translation of MODEL
#define MODEL_Y_TRANSLATE -1.1f  //Y-translation of MODEL
#define MODEL_Z_TRANSLATE -20.0f //Z-translation of MODEL

FRAG_Camera2::Camera Scene3_camera;

Speedometer *speedometer = NULL;

enum
{
	HAD_ATTRIBUTE_POSITION = 0,
	HAD_ATTRIBUTE_COLOR,
	HAD_ATTRIBUTE_NORMAL,
	HAD_ATTRIBUTE_TEXTURE0,
	HAD_ATTRIBUTE_INDICES,
};

//FILE *gpFile;

GLuint g_Scene3_Vbo_Position, g_Scene3_Vbo_Normal, g_Scene3_Vbo_Texture, g_Scene3_Vbo_Instance;

Model g_Scene3_CityModel;
Model g_Scene3_GrassModel;
Model g_Scene3_SkyBoxModel;
Model g_Scene3_HelicopterBodyModel;
Model g_Scene3_HelicopterBladesModel;

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
Shader g_Scene3_DepthShader;

//**********City Model******************

//uniforms
GLuint g_Scene3_CityModel_ModelMatrixUniform, g_Scene3_CityModel_ViewMatrixUniform, g_Scene3_CityModel_ProjectionMatrixUniform;
GLuint g_Scene3_CityModel_LKeyPressedUniform;

GLuint g_Scene3_CityModel_LaUniform, g_Scene3_CityModel_LdUniform, g_Scene3_CityModel_LsUniform;
GLuint g_Scene3_CityModel_LightPositionUniform;

GLuint g_Scene3_CityModel_KaUniform, g_Scene3_CityModel_KdUniform, g_Scene3_CityModel_KsUniform;
GLuint g_Scene3_CityModel_MaterialShininessUniform;

GLuint g_Scene3_CityModel_AlphaUniform, g_Scene3_CityModel_TextureSamplerUniform, g_Scene3_CityModel_TextureActiveUniform;

glm::mat4 g_Scene3_CityModel_PerspectiveProjectionMatrix;

bool g_Scene3_Light = true;

//Light Values
GLfloat g_Scene3_lightAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat g_Scene3_lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat g_Scene3_lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
//GLfloat lightPosition[] = { -324.0f,205.0f,-365.0f,0.0f };

GLfloat g_Scene3_materialAmbient[] = {0.25f, 0.25f, 0.25f, 1.0f};
GLfloat g_Scene3_materialDiffuse[] = {0.4f, 0.4f, 0.4f, 1.0f};
GLfloat g_Scene3_materialSpecular[] = {0.774597f, 0.774597f, 0.774597f, 1.0f};
GLfloat g_Scene3_materialShininess = 0.6f * 128.0f;

//Functions
//init, uninit, draw
void Init_Scene3(void);
//CityModel
//void Scene3_initializeCityModel(void);
//GRASS
void Scene3_initializeGrass(void);
//SkyBox
void Scene3_initializeSkyBox(void);
unsigned int loadCubemap(std::vector<std::string> faces);

typedef struct // Create A Structure
{
	GLubyte *imageData; // Image Data (Up To 32 Bits)
	GLuint bpp;			// Image Color Depth In Bits Per Pixel
	GLuint width;		// Image Width
	GLuint height;		// Image Height
	GLuint texID;		// Texture ID Used To Select A Texture
} TextureImage;

TextureImage textures[6];

TextureImage *LoadTGA(TextureImage *texture, const char *filename, int num);

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
const int g_Bench_InstanceCount = 13;
void Scene3_initializeBenchInstancing(void);

//Palm Tree
const int g_PalmTree_InstanceCount = 20;
void Scene3_initializePalmTreeInstancing(void);

//***********Shadow***************
GLuint g_Scene3_CityModel_LightSpaceMatrixUniform;
GLuint g_Scene3_CityModel_ShadowMapUniform;
GLuint g_Scene3_CityModel_DepthMapFBO;
GLuint g_Scene3_CityModel_DepthMap;

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

//SimpleDepthShader

GLuint glightSpaceMatrixSimpleDepthShaderUniform;
GLuint gmodelSimpleDepthShaderUniform;

void Scene3_initializeDepthShader(void);
void Scene3_GenerateDepthMap(void);

//CityModel with shadow
void Scene3_initializeCityModelWithShadow(void);
void Scene3_initializeHelicopterBody(void);
void Scene3_initializeHelicopterBlades(void);
//float gWidth, gHeight;
/*
float LIGHT_X_TRANSLATE = -324.0f;
float LIGHT_Y_TRANSLATE = 205.0f;
float LIGHT_Z_TRANSLATE = -365.0f;
*/

float LIGHT_X_TRANSLATE = 0.0f;
float LIGHT_Y_TRANSLATE = 76.0f;
float LIGHT_Z_TRANSLATE = 20.0f;

//Camera
int gCameraNumber = 1;
int giCameraMoves = 0;
bool gbIsCameraSet = true;

/******* Low Poly Ocean Start *******/
const int VERTEX_COUNT = 100;
const float OCEAN_SIZE = 0.11f;

GLuint g_Scene3_Ocean_VertexShaderObject;
GLuint g_Scene3_Ocean_GeometryShaderObject;
GLuint g_Scene3_Ocean_FragmentShaderObject;
GLuint g_Scene3_Ocean_ShaderProgramObject;

GLuint g_Scene3_Ocean_VertexArrayObject;
GLuint g_Scene3_Ocean_VertexBufferObject;
GLuint g_Scene3_Ocean_VertexBufferObject_Indices;

GLuint g_Scene3_Ocean_Uniform_ModelMatrix, g_Scene3_Ocean_Uniform_ViewMatrix, g_Scene3_Ocean_Uniform_ProjectionMatrix;
GLuint g_Scene3_Ocean_Uniform_Time, g_Scene3_Ocean_Uniform_Camera_Position;

GLfloat g_Scene3_Ocean_U_Time = 0.0f;

GLfloat g_Scene3_Ocean_MeshVertices[2 * VERTEX_COUNT * VERTEX_COUNT];
GLuint g_Scene3_Ocean_shIndices[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)];

GLfloat fRotation_Angle = 0.0f;

//Helicopter 
GLfloat fRotation_Angle_Blades = 0.0f;
bool isTranslateY = false;
GLfloat fTranslation_In_Y = 0.0f;
bool bIsHelicopterDone = false;

glm::mat4 g_Scene3_Ocean_PerspectiveProjectionMatrix;

/******* Low Poly Ocean End   *******/

/******* Scene 3 Audio Start *******/

/// Take Audio Manager as Scene1_audioManager
// Below Will Be used in Scene3_InitializeAudio Function
SoundSource *g_SS_Scene3_Car = NULL;
SoundSource *g_SS_Scene3_Ambient = NULL; // In The End
SoundSource *g_SS_Scene3_WindSound = NULL;
SoundSource *g_SS_Scene3_Helicopter = NULL;

ALuint g_Scene3_iInTheEnd_Buffer = 0;
ALuint g_Scene3_iSilentSound_Buffer = 0;
ALuint g_Scene3_iCarAcceleration_Start_Buffer = 0;
ALuint g_Scene3_iCarAcceleration_Repeat_Buffer = 0;
ALuint g_Scene3_iCarAcceleration_End_Buffer = 0;
ALuint g_Scene3_iPoliceSiren_Buffer = 0;
ALuint g_Scene3_iCarCrash_Buffer = 0;
ALuint g_Scene3_iHelicopter_Buffer = 0;

bool g_scene3_bPlayInTheEnd = true;
/******* Scene 3 Audio End   *******/


void Init_Scene3()
{
	void Scene3_Ocean_Initialize(void);
	void Scene3_InitializeAudio(void);
	std::vector<Mesh_Data> Scene3_MD_City;
	char Scene3_chMtlPath[256];


	LoadMeshData("RTR_resources/models/Project_Model/Final_Project_Model.obj", g_Scene3_CityModel.gv_vertices, g_Scene3_CityModel.gv_textures, g_Scene3_CityModel.gv_normals, g_Scene3_CityModel.gv_Mesh_Data, g_Scene3_CityModel.chMaterialFileName);

	LoadMaterialData(g_Scene3_CityModel.chMaterialFileName, g_Scene3_CityModel.gv_Material);

	Rearrange_Material_Data(g_Scene3_CityModel.gv_Mesh_Data, g_Scene3_CityModel.gv_Material);

	g_Scene3_CityModel.count_of_vertices = g_Scene3_CityModel.gv_vertices.size();


	//Helicopter Body
	LoadMeshData("RTR_resources/models/Helicopter/Helicopter_Body.obj", g_Scene3_HelicopterBodyModel.gv_vertices, g_Scene3_HelicopterBodyModel.gv_textures, g_Scene3_HelicopterBodyModel.gv_normals, g_Scene3_HelicopterBodyModel.gv_Mesh_Data, g_Scene3_HelicopterBodyModel.chMaterialFileName);

	LoadMaterialData(g_Scene3_HelicopterBodyModel.chMaterialFileName, g_Scene3_HelicopterBodyModel.gv_Material);

	Rearrange_Material_Data(g_Scene3_HelicopterBodyModel.gv_Mesh_Data, g_Scene3_HelicopterBodyModel.gv_Material);

	g_Scene3_HelicopterBodyModel.count_of_vertices = g_Scene3_HelicopterBodyModel.gv_vertices.size();


	//Helicopter Blades
	LoadMeshData("RTR_resources/models/Helicopter/Helicopter_Blades.obj", g_Scene3_HelicopterBladesModel.gv_vertices, g_Scene3_HelicopterBladesModel.gv_textures, g_Scene3_HelicopterBladesModel.gv_normals, g_Scene3_HelicopterBladesModel.gv_Mesh_Data, g_Scene3_HelicopterBladesModel.chMaterialFileName);

	LoadMaterialData(g_Scene3_HelicopterBladesModel.chMaterialFileName, g_Scene3_HelicopterBladesModel.gv_Material);

	Rearrange_Material_Data(g_Scene3_HelicopterBladesModel.gv_Mesh_Data, g_Scene3_HelicopterBladesModel.gv_Material);

	g_Scene3_HelicopterBladesModel.count_of_vertices = g_Scene3_HelicopterBladesModel.gv_vertices.size();

	//Scene3_initializeCityModel();
	// For Shadow
	Scene3_initializeCityModelWithShadow();

	//Helicopter Body
	Scene3_initializeHelicopterBody();

	//Helicopter Blades
	Scene3_initializeHelicopterBlades();

	//SkyBox
	Scene3_initializeSkyBox();

	//Grass Instancing
	Scene3_initializeGrass();

	std::vector<Mesh_Data> Scene3_MD_CityLight;
	//CityLight Instancing
	LoadMeshData("RTR_resources/models/StreetLight/street_light.obj", g_Scene3_CityLightModel.gv_vertices, g_Scene3_CityLightModel.gv_textures, g_Scene3_CityLightModel.gv_normals, Scene3_MD_CityLight, Scene3_chMtlPath);

	g_Scene3_CityLightModel.count_of_vertices = g_Scene3_CityLightModel.gv_vertices.size();

	Scene3_initializeInstancingFeature();
	Scene3_initializeCityLightInstancing();

	//Bench
	std::vector<Mesh_Data> Scene3_MD_Bench;
	LoadMeshData("RTR_resources/models/Bench/Bench.obj", g_Scene3_BenchModel.gv_vertices, g_Scene3_BenchModel.gv_textures, g_Scene3_BenchModel.gv_normals, Scene3_MD_Bench, Scene3_chMtlPath);
	g_Scene3_BenchModel.count_of_vertices = g_Scene3_BenchModel.gv_vertices.size();

	Scene3_initializeBenchInstancing();

	//Palm Tree
	std::vector<Mesh_Data> Scene3_MD_PalmTree;
	LoadMeshData("RTR_resources/models/Tree_obj/Tree.obj", g_Scene3_PalmTreeModel.gv_vertices, g_Scene3_PalmTreeModel.gv_textures, g_Scene3_PalmTreeModel.gv_normals, Scene3_MD_PalmTree, Scene3_chMtlPath);
	g_Scene3_PalmTreeModel.count_of_vertices = g_Scene3_PalmTreeModel.gv_vertices.size();

	Scene3_initializePalmTreeInstancing();

	//Shadow
	Scene3_initializeDepthShader();
	Scene3_GenerateDepthMap();

	speedometer = new Speedometer();
	speedometer->initialize();

	//Camera Position
	Scene3_camera.SetPosition(glm::vec3(-16.799992f, 17.013103f, 438.898560f));
	Scene3_camera.SetFront(glm::vec3(-0.000000f, 0.130526f, -0.991445f));

	Scene3_Ocean_Initialize();
	Scene3_InitializeAudio();
}
//********************GRASS**********************

#include "ktx_loading_header.h"

GLuint g_Scene3_Grass_MVPMatrix;
GLuint g_Scene3_Grass_Rotation;

GLuint g_Scene3_Texture_grass_color;
GLuint g_Scene3_Texture_grass_length;
GLuint g_Scene3_Texture_grass_orientation;
GLuint g_Scene3_Texture_grass_bend;

float GRASS_X_TRANSLATE = -204.0f; //-445.0f; //for actual grass
float GRASS_Y_TRANSLATE = -1.1f;
float GRASS_Z_TRANSLATE = -700.0f;

float GRASS_X_TRANSLATE1 = -50.0f; //-445.0f; //for actual grass
float GRASS_Y_TRANSLATE1 = -2.0f;
float GRASS_Z_TRANSLATE1 = -300.0f;

void Scene3_initializeGrass(void)
{
	void uninitialize(int);

	//Vertex Shader
	g_Scene3_GrassShader.gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
		"#version 450"
		"\n" // Incoming per vertex position:
		"in vec4 vVertex;"

		// Output varyings:
		"out vec4 color;"

		"uniform mat4 mvpMatrix;"
		"uniform float rotation_increment;"

		"layout(binding = 0) uniform sampler1D grass_palette_texture;"
		"layout(binding = 1) uniform sampler2D grass_length_texture;"
		"layout(binding = 2) uniform sampler2D grass_orientation_texture;"
		"layout(binding = 3) uniform sampler2D grass_color_texture;"
		"layout(binding = 4) uniform sampler2D grass_bend_texture;"

		"int random(int seed, int iterations)"
		"{"
		"int value = seed;"
		"int n;"

		"for (n = 0; n < iterations; n++)"
		"{"
		"value = ((value >> 7) ^ (value << 9)) * 15485863;"
		"}"

		"return(value);"
		"}"

		"vec4 random_vector(int seed)"
		"{"
		"int r = random(gl_InstanceID, 4);"
		"int g = random(r, 2);"
		"int b = random(g, 2);"
		"int a = random(b, 2);"

		"return(vec4(float(r & 0x3FF) / 1024.0,"
		"float(g & 0x3FF) / 1024.0,"
		"float(b & 0x3FF) / 1024.0,"
		"float(a & 0x3FF) / 1024.0));"
		"}"

		"mat4 construct_rotation_matrix(float angle)"
		"{"
		"float st = sin(angle + rotation_increment);"
		"float ct = cos(angle + rotation_increment);"

		"return(mat4(vec4(ct, 0.0, st, 0.0),"
		"vec4(0.0, 1.0, 0.0, 0.0),"
		"vec4(-st, 0.0, ct, 0.0),"
		"vec4(0.0, 0.0, 0.0, 1.0)));"
		"}"

		"void main(void)"
		"{"
		"vec4 offset = vec4(float(gl_InstanceID >> 10) - 512.0,"
		"0.0f,"
		"float(gl_InstanceID & 0x3FF) - 512.0,"
		"0.0f);"

		"int number_1 = random(gl_InstanceID, 3);"
		"int number_2 = random(number_1, 2);"

		"offset += vec4(float(number_1 & 0xFF) / 256.0,"
		"0.0f,"
		"float(number_2 & 0xFF) / 256.0,"
		"0.0f);"

		//float angle = float(random(number_2, 2) & 0x3FF) / 1024.0;

		"vec2 texcoord = offset.xz / 1024.0 + vec2(0.5);"

		// float bend_factor = float(random(number_2, 7) & 0x3FF) / 1024.0;
		"float bend_factor = texture(grass_bend_texture, texcoord).r * 2.0;"
		"float bend_amount = cos(vVertex.y);"

		"float angle = texture(grass_orientation_texture, texcoord).r * 2.0 * 3.141592;"
		"mat4 rot = construct_rotation_matrix(angle);"
		"vec4 position = (rot * (vVertex + vec4(0.0, 0.0, bend_amount * bend_factor, 0.0))) + offset;"

		"position *= vec4(1.0, texture(grass_length_texture, texcoord).r * 0.9 + 0.3, 1.0, 1.0);"

		"gl_Position = mvpMatrix * position;" // (rot * position);

		// color = vec4(random_vector(gl_InstanceID).xyz * vec3(0.1, 0.5, 0.1) + vec3(0.1, 0.4, 0.1), 1.0);
		// color = texture(grass_orientation_texture, texcoord);
		"color = texture(grass_palette_texture, texture(grass_color_texture, texcoord).r) + vec4(random_vector(gl_InstanceID).xyz * vec3(0.1, 0.5, 0.1), 1.0);"
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
				//fopen_s(&gpFile, "Log.txt", "a+");
				logError("Vertex Shader Compilation Log : %s\n", szInfoLog);
				//fprintf(gpFile, "Vertex Shader Compilation Log : %s\n", szInfoLog);
				//fclose(gpFile);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Fragment Shader
	g_Scene3_GrassShader.gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 450"
		"\n"

		"in vec4 color;"

		"out vec4 output_color;"

		"void main(void)"
		"{"
		"output_color = color;"
		"}";

	glShaderSource(g_Scene3_GrassShader.gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	glCompileShader(g_Scene3_GrassShader.gFragmentShaderObject);

	glGetShaderiv(g_Scene3_GrassShader.gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_GrassShader.gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_GrassShader.gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				/*fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Fragment Shader Compilation Log : %s\n", szInfoLog);
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
				/*fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Shader Program Link Log : %s\n", szInfoLog);
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
			0.0f, 3.3f};

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
	/*fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadSkyBoxShader \n");
	fclose(gpFile);*/
	logError("In LoadSkyBoxShader \n");

	void uninitialize(int);
	//VERTEX SHADER
	g_Scene3_SkyBoxShader.gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertextShaderSourceCodeSkyBox =
		"#version 460"
		"\n"
		"out VS_OUT"
		"{"
		"vec3    tc;"
		"} vs_out;"
		"uniform mat4 model_matrix;"
		"uniform mat4 view_matrix;"
		"void main(void)"
		"{"
		"vec3[4] vertices = vec3[4](vec3(-1.0, -1.0, 1.0),"
		"vec3(1.0, -1.0, 1.0),"
		"vec3(-1.0, 1.0, 1.0),"
		"vec3(1.0, 1.0, 1.0)); "

		"vs_out.tc = mat3(view_matrix * model_matrix) * vertices[gl_VertexID];"
		"gl_Position = vec4(vertices[gl_VertexID], 1.0);"
		"}";

	glShaderSource(g_Scene3_SkyBoxShader.gVertexShaderObject, 1, (const GLchar **)&vertextShaderSourceCodeSkyBox, NULL);

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
				/*fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Vertex Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Vertex Shader Compilation Log : %s\n", szInfoLog);

				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}
	//FRAGMENT SHADER

	g_Scene3_SkyBoxShader.gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCodeSkyBox =
		"#version 460"
		"\n"
		"uniform samplerCube tex_cubemap;"
		"in VS_OUT"
		"{"
		"vec3    tc;"
		"} fs_in;"
		"layout (location = 0) out vec4 color;"
		"void main(void)"
		"{" //"color = texture(tex_cubemap, vec3(fs_in.tc.x, -fs_in.tc.y, fs_in.tc.z));"
		"color = texture(tex_cubemap, fs_in.tc);"
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
				/*	fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Fragment Shader Compilation Log : %s\n", szInfoLog);

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
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(g_Scene3_SkyBoxShader.gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				/*fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Shader Program Link Log : %s\n", szInfoLog);

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

	std::vector<std::string> Faces{
		"RTR_resources/models/RotateMirMar/right.tga",
		"RTR_resources/models/RotateMirMar/left.tga",
		"RTR_resources/models/RotateMirMar/new_up.tga",
		"RTR_resources/models/RotateMirMar/dwn.tga",
		"RTR_resources/models/RotateMirMar/front.tga",
		"RTR_resources/models/RotateMirMar/bck.tga",
	};

	g_Scene3_CubemapTexture = loadCubemap(Faces);
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	/*fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In loadCubemap....\n");
	fclose(gpFile);*/
	logError("In loadCubemap....\n");
	TextureImage *LoadTGA(TextureImage * texture, const char *filename, int i);
	bool returnType = false;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		TextureImage *textureIm = LoadTGA(&textures[i], faces[i].c_str(), i);
		if (textureIm->imageData)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textureIm->width, textureIm->height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureIm->imageData);
		}
		else
		{
			/*fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "CubeMap texture failed to load..\n");
			fclose(gpFile);*/
			logError("CubeMap texture failed to load..\n");
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

TextureImage *LoadTGA(TextureImage *texture, const char *filename, int num) // Loads A TGA File Into Memory
{
	void _check_gl_error();

	/*fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA : FileName : %s\n", filename);
	fclose(gpFile);*/
	logInfo("In LoadTGA : FileName : %s\n", filename);

	GLubyte TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Uncompressed TGA Header
	GLubyte TGAcompare[12];										  // Used To Compare TGA Header
	GLubyte header[6];											  // First 6 Useful Bytes From The Header
	GLuint bytesPerPixel;										  // Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint imageSize;											  // Used To Store The Image Size When Setting Aside Ram
	GLuint temp;												  // Temporary Variable
	GLuint type = GL_RGBA;										  // Set The Default GL Mode To RBGA (32 BPP)
	FILE *file = NULL;
	fopen_s(&file, filename, "rb"); // Open The TGA File

	if (file == NULL ||															// Does File Even Exist?
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) || // Are There 12 Bytes To Read?
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||				// Does The Header Match What We Want?
		fread(header, 1, sizeof(header), file) != sizeof(header))				// If So Read Next 6 Header Bytes
	{
		/*fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "Does File EVen Exist..\n");
		fclose(gpFile);*/
		logInfo("Does File EVen Exist..\n");

		if (file == NULL) // Did The File Even Exist? *Added Jim Strong*
		{
			/*fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "No..File Not Exists..\n");
			fclose(gpFile);*/
			logError("No..File Not Exists..\n");
			return NULL; // Return False
		}
		else
		{
			/*fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "Any Other thing Failed\n");
			fclose(gpFile);*/
			logError("Any Other thing Failed\n");
			fclose(file); // If Anything Failed, Close The File
			return NULL;  // Return False
		}
	}
	texture->width = header[1] * 256 + header[0];  // Determine The TGA Width  (highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2]; // Determine The TGA Height (highbyte*256+lowbyte)
	/*fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA 100\n");
	fclose(gpFile);*/

	if (texture->width <= 0 ||				  // Is The Width Less Than Or Equal To Zero
		texture->height <= 0 ||				  // Is The Height Less Than Or Equal To Zero
		(header[4] != 24 && header[4] != 32)) // Is The TGA 24 or 32 Bit?
	{
		/*fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "In LoadTGA 1\n");
		fclose(gpFile);*/
		fclose(file); // If Anything Failed, Close The File
		return NULL;  // Return False
	}
	texture->bpp = header[4];										// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel = texture->bpp / 8;								// Divide By 8 To Get The Bytes Per Pixel
	imageSize = texture->width * texture->height * bytesPerPixel;   // Calculate The Memory Required For The TGA Data
	texture->imageData = (GLubyte *)malloc(imageSize);				// Reserve Memory To Hold The TGA Data
																	/*	fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA 101\n");
	fclose(gpFile);*/
	if (texture->imageData == NULL ||								// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file) != imageSize) // Does The Image Size Match The Memory Reserved?
	{
		/*	fopen_s(&gpFile, "Log.txt", "a+");
		fprintf(gpFile, "In LoadTGA 500\n");
		fclose(gpFile);*/
		if (texture->imageData != NULL) // Was Image Data Loaded
		{
			/*	fopen_s(&gpFile, "Log.txt", "a+");
			fprintf(gpFile, "In LoadTGA 501\n");
			fclose(gpFile);*/
			free(texture->imageData); // If So, Release The Image Data
		}
		fclose(file); // Close The File
		return NULL;  // Return False
	}
	/*fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In LoadTGA 102\n");
	fclose(gpFile);*/
	for (GLuint i = 0; i < int(imageSize); i += bytesPerPixel) // Loop Through The Image Data
	{														   // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)

		temp = texture->imageData[i];					   // Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2]; // Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;				   // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	return texture; // Texture Building Went Ok, Return True
}

void Scene3_initializeInstancingFeature()
{
	void uninitialize(int);

	g_Scene3_InstanceShader.gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertextShaderSourceCode =
		"#version 400"
		"\n"
		"layout(location = 0) in vec3 vPosition;"
		"layout(location = 1) in vec3 vNormal;"
		"layout(location = 2) in vec3 aOffset;"
		"uniform mat4 u_model_matrix;"
		"uniform mat4 u_view_matrix;"
		"uniform mat4 u_projection_matrix;"
		"uniform int u_lighting_enabled;"
		"uniform vec3 u_light_position;"
		"out vec3 transformed_normals;"
		"out vec3 light_direction;"
		"out vec3 viewer_vector;"

		//"uniform mat4 mvpMatrix;"
		"void main(void)"
		"{"
		"if(u_lighting_enabled==1)"
		"{"
		"vec4 eye_coordinates = u_view_matrix*u_model_matrix* vec4(vPosition, 1.0);"
		"transformed_normals = mat3(u_view_matrix*u_model_matrix)*vNormal;"
		"light_direction = u_light_position-eye_coordinates.xyz;"
		"viewer_vector = -eye_coordinates.xyz;"
		"}" //	"gl_Position = u_projection_matrix*u_view_matrix*u_model_matrix*vPosition;"

		//"gl_Position = mvpMatrix * vec4(aPos.x + aOffset.x, aPos.y, aPos.z + aOffset.y, 1.0f);"
		//"gl_Position = mvpMatrix * vec4(aPos + aOffset, 1.0f);"
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vec4(vPosition.x + aOffset.x, vPosition.y + aOffset.y, vPosition.z + aOffset.z, 1.0f);"
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
				/*fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Vertex Shader of CityLight Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Vertex Shader of CityLight Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}
	//FRAGMENT SHADER

	g_Scene3_InstanceShader.gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 400"
		"\n"
		"in vec3 transformed_normals;"
		"in vec3 light_direction;"
		"in vec3 viewer_vector;"
		"out vec4 FragColor;"
		"uniform vec3 u_La;"
		"uniform vec3 u_Ld;"
		"uniform vec3 u_Ls;"
		"uniform vec3 u_Ka;"
		"uniform vec3 u_Kd;"
		"uniform vec3 u_Ks;"
		"uniform float u_material_shininess;"
		"uniform int u_lighting_enabled;"

		"void main()"
		"{"
		"vec3 phong_ads_color;"
		"if(u_lighting_enabled == 1)"
		"{"
		"vec3 normalized_transformed_normals = normalize(transformed_normals);"
		"vec3 normalized_light_direction = normalize(light_direction);"
		"vec3 normalized_viewer_vector = normalize(viewer_vector);"
		"vec3 ambient = u_La * u_Ka;"
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);"
		"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;"
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);"
		"vec3 specular = u_Ls * u_Ks * pow(max(dot(reflection_vector,normalized_viewer_vector),0.0),u_material_shininess);"
		"phong_ads_color = ambient + diffuse + specular;"
		"}"
		"else"
		"{"
		"phong_ads_color = vec3(1.0f,1.0f,1.0f);"
		"}"
		"FragColor = vec4(phong_ads_color,1.0);"

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
				/*fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader of CityLight Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Fragment Shader of CityLight Compilation Log : %s\n", szInfoLog);
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
	glBindAttribLocation(g_Scene3_InstanceShader.gShaderProgramObject, 1, "vNormal");   //aOffset

	glBindAttribLocation(g_Scene3_InstanceShader.gShaderProgramObject, 2, "aOffset");

	glLinkProgram(g_Scene3_InstanceShader.gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(g_Scene3_InstanceShader.gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_Scene3_InstanceShader.gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(g_Scene3_InstanceShader.gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				/*fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Shader Program Link Log : %s\n", szInfoLog);
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

	translations[0] = {0.0f, 0.0f, -140.0f};
	translations[1] = {0.0f, 0.0f, -100.0f};
	translations[2] = {0.0f, 0.0f, -60.0f};
	translations[3] = {0.0f, 0.0f, -20.0f};
	translations[4] = {0.0f, 0.0f, 20.0f};
	translations[5] = {0.0f, 0.0f, 60.0f};
	translations[6] = {0.0f, 0.0f, 100.0f};
	translations[7] = {0.0f, 0.0f, 140.0f};

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
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.

	glBindVertexArray(0);
}

void Scene3_initializeBenchInstancing()
{
	//new addition
	glm::vec3 translations[g_Bench_InstanceCount];
	int index = 0;
	float offset = 0.1f;

	translations[0] = {0.0f, 0.0f, -15000.0f};
	translations[1] = {0.0f, 0.0f, -12500.0f};
	translations[2] = {0.0f, 0.0f, -10000.0f};
	translations[3] = {0.0f, 0.0f, -7500.0f};
	translations[4] = {0.0f, 0.0f, -5000.0f};
	translations[5] = {0.0f, 0.0f, -2500.0f};
	translations[6] = {0.0f, 0.0f, 0.0f};
	translations[7] = {0.0f, 0.0f, 2500.0f};
	translations[8] = {0.0f, 0.0f, 5000.0f};
	translations[9] = {0.0f, 0.0f, 7500.0f};
	translations[10] = {0.0f, 0.0f, 10000.0f};
	translations[11] = {0.0f, 0.0f, 12500.0f};
	translations[12] = {0.0f, 0.0f, 15000.0f};

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
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.

	glBindVertexArray(0);
}

void Scene3_initializePalmTreeInstancing()
{
	//new addition
	glm::vec3 translations[g_PalmTree_InstanceCount];
	int index = 0;
	float offset = 0.1f;

	for (int i = 0, z = -100; i < g_PalmTree_InstanceCount - 1; z = z + 10)
	{
		translations[i] = {0.0f, 0.0f, z};
		i++;
	}
	/*translations[0] = { 0.0f , 0.0f , -1000.0f };
	translations[1] = { 0.0f , 0.0f, -200.0f };
	translations[2] = { 0.0f, 0.0f , 1000.0f };
	//translations[3] = { 0.0f, 0.0f , 800.0f };
	*/
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
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.

	glBindVertexArray(0);
}

void Scene3_initializeHelicopterBody(void)
{
	//VAO for Helicopter Body

	glGenVertexArrays(1, &g_Scene3_HelicopterBodyModel.Vao);
	glBindVertexArray(g_Scene3_HelicopterBodyModel.Vao);

	glGenBuffers(1, &g_Scene3_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Position);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_HelicopterBodyModel.gv_vertices.size() * sizeof(float), &g_Scene3_HelicopterBodyModel.gv_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_Scene3_Vbo_Texture);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Texture);
	//glBufferData(GL_ARRAY_BUFFER, gv_normals_road.size() * sizeof(float), &gv_normals_road[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_HelicopterBodyModel.gv_textures.size() * sizeof(float), &g_Scene3_HelicopterBodyModel.gv_textures[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_Scene3_Vbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Normal);
	//glBufferData(GL_ARRAY_BUFFER, gv_normals_road.size() * sizeof(float), &gv_normals_road[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_HelicopterBodyModel.gv_normals.size() * sizeof(float), &g_Scene3_HelicopterBodyModel.gv_normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Scene3_initializeHelicopterBlades(void)
{
	//VAO for Helicopter Blades

	glGenVertexArrays(1, &g_Scene3_HelicopterBladesModel.Vao);
	glBindVertexArray(g_Scene3_HelicopterBladesModel.Vao);

	glGenBuffers(1, &g_Scene3_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Position);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_HelicopterBladesModel.gv_vertices.size() * sizeof(float), &g_Scene3_HelicopterBladesModel.gv_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_Scene3_Vbo_Texture);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Texture);
	//glBufferData(GL_ARRAY_BUFFER, gv_normals_road.size() * sizeof(float), &gv_normals_road[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_HelicopterBladesModel.gv_textures.size() * sizeof(float), &g_Scene3_HelicopterBladesModel.gv_textures[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_Scene3_Vbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Normal);
	//glBufferData(GL_ARRAY_BUFFER, gv_normals_road.size() * sizeof(float), &gv_normals_road[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_HelicopterBladesModel.gv_normals.size() * sizeof(float), &g_Scene3_HelicopterBladesModel.gv_normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Scene3_initializeCityModelWithShadow(void)
{
	void uninitialize(int);
	//Vertex Shader
	g_Scene3_CityModelShader.gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
		"#version 450"
		"\n"
		"in vec4 vPosition;"
		"in vec3 vNormal;"
		"in vec2 vTexture0_Coord;"
		"uniform mat4 u_model_matrix;"
		"uniform mat4 u_view_matrix;"
		"uniform mat4 u_projection_matrix;"
		"uniform int u_lighting_enabled;" //"uniform vec3 u_light_position;"
		"out vec3 transformed_normals;"
		"out vec4 eye_coordinates;" //"out vec3 light_direction;"
		"out vec3 viewer_vector;"
		"out vec2 out_texture0_coord;" //Shadow
		"uniform mat4 u_lightSpace_matrix;"
		"out vec4 FragPosLightSpace;"

		"void main(void)"
		"{"
		"if(u_lighting_enabled==1)"
		"{"
		"eye_coordinates = u_model_matrix*vPosition;"
		"transformed_normals = mat3(u_model_matrix)*vNormal;" //"light_direction = u_light_position-eye_coordinates.xyz;"
		"viewer_vector = -eye_coordinates.xyz;"

		//Shadow
		//"vec3 FragPos = vec3(u_view_matrix*u_model_matrix * vPosition);"
		//	"FragPosLightSpace = u_lightSpace_matrix * vec4(FragPos, 1.0);"
		"FragPosLightSpace = u_lightSpace_matrix * eye_coordinates;"
		"}"
		"gl_Position = u_projection_matrix*u_view_matrix*u_model_matrix*vPosition;"
		"out_texture0_coord = vTexture0_Coord;"
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
				/*fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Vertex Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Vertex Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Fragment Shader
	g_Scene3_CityModelShader.gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 450"
		"\n"
		"in vec3 transformed_normals;" //"in vec3 light_direction;"
		"in vec3 viewer_vector;"
		"in vec4 eye_coordinates;"
		"in vec2 out_texture0_coord;"
		"out vec4 FragColor;"
		"uniform vec3 u_La;"
		"uniform vec3 u_Ld;"
		"uniform vec3 u_Ls;"
		"uniform vec3 u_Ka;"
		"uniform vec3 u_Kd;"
		"uniform vec3 u_Ks;"
		"uniform float u_material_shininess;"
		"uniform int u_lighting_enabled;"
		"uniform vec3 u_light_position;"
		"uniform float u_alpha;"
		"uniform sampler2D u_texture0_sampler;"
		"uniform int u_is_texture;"
		"vec4 Final_Texture;"
		"vec4 Temp_Output;" //Shadow
		"in vec4 FragPosLightSpace;"
		"uniform sampler2D shadowMap;"

		"float ShadowCalculation(vec4 fragPosLightSpace, vec3 light_direction)"
		"{"																 //Perpective Divide
		"vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;" //transform it into [0,1] range
		"projCoords = projCoords * 0.5 + 0.5;"							 //calculate closest depth from light perspective using projCoords as coordinates
		"float closestDepth = texture(shadowMap, projCoords.xy).r;"
		"float currentDepth = projCoords.z;"
		"vec3 normalized_transformed_normals = normalize(transformed_normals);"

		"vec3 normalized_light_direction = normalize(light_direction);"

		"float bias = max(0.05 * (1.0 - dot(normalized_transformed_normals, normalized_light_direction)), 0.05);"
		"float shadow = 0.0;"
		"vec2 texelSize = 1.0 / textureSize(shadowMap, 0);"
		"for(int x = -1; x <= 1; ++x)"
		"{"
		"for(int y = -1; y <= 1; ++y)"
		"{"
		"float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;"
		"shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;"
		"}"
		"}"
		"shadow /= 9.0;"
		"if(projCoords.z > 1.0)"
		"shadow = 0.0;"
		"return shadow;"
		"}"

		"void main(void)"
		"{"
		"vec3 phong_ads_color;"
		"if(u_lighting_enabled == 1)"
		"{"
		"vec3 normalized_transformed_normals = normalize(transformed_normals);"
		"vec3 temp_light_position = u_light_position;"
		"for(int i = 0; i < 2; i++)"
		"{"
		"vec3 light_direction = temp_light_position-eye_coordinates.xyz;"
		"temp_light_position[2] -= 400;"
		"temp_light_position[1] = 200;"
		"vec3 normalized_light_direction = normalize(light_direction);"
		"vec3 normalized_viewer_vector = normalize(viewer_vector);"
		"vec3 ambient = u_La * u_Ka;"
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);"
		"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;"
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);"
		"vec3 specular = u_Ls * u_Ks * pow(max(dot(reflection_vector,normalized_viewer_vector),0.0),u_material_shininess);"

		//Shadow
		"float shadow = ShadowCalculation(FragPosLightSpace, light_direction);"

		"phong_ads_color += ambient +  (1.0 - shadow) * (diffuse + specular);"
		"}"
		"}"
		"else"
		"{"
		"phong_ads_color = vec3(1.0f,1.0f,1.0f);"
		"}"
		"if(u_is_texture == 1)"
		"{"
		"Final_Texture = texture(u_texture0_sampler,out_texture0_coord);"
		"Temp_Output = vec4(phong_ads_color,u_alpha) * Final_Texture;"
		"FragColor = Temp_Output;"
		"}"
		"else"
		"{"
		"FragColor = vec4(phong_ads_color,u_alpha);"
		"}"
		"}";

	glShaderSource(g_Scene3_CityModelShader.gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	glCompileShader(g_Scene3_CityModelShader.gFragmentShaderObject);

	glGetShaderiv(g_Scene3_CityModelShader.gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_CityModelShader.gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_CityModelShader.gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				/*fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Fragment Shader Compilation Log : %s\n", szInfoLog);
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

	glBindAttribLocation(g_Scene3_CityModelShader.gShaderProgramObject, HAD_ATTRIBUTE_TEXTURE0, "vTexture0_Coord");

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
				/*fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Shader Program Link Log : %s\n", szInfoLog);
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

	//for shadow
	g_Scene3_CityModel_LightSpaceMatrixUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_lightSpace_matrix");
	g_Scene3_CityModel_ShadowMapUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "shadowMap");

	g_Scene3_CityModel_AlphaUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_alpha");

	g_Scene3_CityModel_MaterialShininessUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_material_shininess");

	g_Scene3_CityModel_TextureSamplerUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_texture0_sampler");

	g_Scene3_CityModel_TextureActiveUniform = glGetUniformLocation(g_Scene3_CityModelShader.gShaderProgramObject, "u_is_texture");

	//VAO
	glGenVertexArrays(1, &g_Scene3_CityModel.Vao);
	glBindVertexArray(g_Scene3_CityModel.Vao);

	glGenBuffers(1, &g_Scene3_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Position);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_CityModel.gv_vertices.size() * sizeof(float), &g_Scene3_CityModel.gv_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_Scene3_Vbo_Texture);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Vbo_Texture);
	//glBufferData(GL_ARRAY_BUFFER, gv_normals_road.size() * sizeof(float), &gv_normals_road[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, g_Scene3_CityModel.gv_textures.size() * sizeof(float), &g_Scene3_CityModel.gv_textures[0], GL_STATIC_DRAW);
	glVertexAttribPointer(HAD_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_TEXTURE0);
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
	void Scene3_Ocean_UnInitialize(void);
	if (speedometer != NULL)
	{
		delete speedometer;
		speedometer = NULL;
	}

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

	Scene3_Ocean_UnInitialize();
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

void Uninitialize_PalmTreeShader(void)
{
	if (g_Scene3_PalmTreeModel.Vao)
	{
		glDeleteVertexArrays(1, &g_Scene3_PalmTreeModel.Vao);
		g_Scene3_PalmTreeModel.Vao = 0;
	}
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

void Scene3_Update()
{
	void updateCamera(void);
	void Scene3_Ocean_Update(void);
	void Scene3_HelicopterBlades_Update(void);

	if ((g_scene3_bShowScene3==true) & (g_scene3_bPlayInTheEnd == true))
	{
		//g_SS_Scene3_Ambient->play(g_Scene3_iInTheEnd_Buffer);
		g_SS_Scene3_WindSound->play(g_Scene3_iSilentSound_Buffer);
		g_scene3_bPlayInTheEnd = false;
	}

	if (speedometer != NULL)
	{
		speedometer->update();
	}
	updateCamera();

	Scene3_Ocean_Update();

	Scene3_HelicopterBlades_Update();
}

//Camera Update Function

void updateCamera(void)
{
	if (gCameraNumber == 1)
	{
		if (giCameraMoves < 470)
			Scene3_camera.ProcessKeyboard(FRAG_Camera2::FORWARD, deltaTime);
		if (giCameraMoves > 600)
		{
			giCameraMoves = 0;
			gbIsCameraSet = false;
			gCameraNumber++;			
		}

		if (giCameraMoves > 550)
		{
			g_SS_Scene3_WindSound->stop();
			g_SS_Scene3_Ambient->play(g_Scene3_iInTheEnd_Buffer);
			g_SS_Scene3_Ambient->setVolume(0.8f);
			//g_Scene3_iCarAcceleration_Start_Buffer
			g_SS_Scene3_Car->play(g_Scene3_iCarAcceleration_Start_Buffer);
		}
	}
	//Comment all below this for camera facing ocean Start
	else if (gCameraNumber == 2)
	{
		if (gbIsCameraSet == false)
		{
			giCameraMoves = 0;
			gbIsCameraSet = true;
			Scene3_camera.SetPosition(glm::vec3(-40.670250f, 10.522485f, 111.029778f));
			Scene3_camera.SetFront(glm::vec3(0.687855f, 0.031497f, -0.722319f));
		}

		if (giCameraMoves < 700)
			Scene3_camera.ProcessKeyboard(FRAG_Camera2::FORWARD, deltaTime);

		if (10 < giCameraMoves && giCameraMoves < 700)
			Scene3_camera.ProcessKeyboard(FRAG_Camera2::LEFT, deltaTime);

		if (giCameraMoves > 710)
		{
			giCameraMoves = 0;
			gbIsCameraSet = false;
			gCameraNumber++;
		}
	}
	else if (gCameraNumber == 3)
	{
		if (gbIsCameraSet == false)
		{
			giCameraMoves = 0;
			gbIsCameraSet = true;
			Scene3_camera.SetPosition(glm::vec3(27.821997f, 17.694828f, -438.942352f));
			Scene3_camera.SetFront(glm::vec3(-0.668179f, -0.327218f, 0.668181f));
		}

		if (giCameraMoves > 200)
		{
			giCameraMoves = 0;
			gbIsCameraSet = false;
			gCameraNumber++;
		}
	}
	else if (gCameraNumber == 4)
	{
		if (gbIsCameraSet == false)
		{
			giCameraMoves = 0;
			gbIsCameraSet = true;
//			Scene3_camera.SetPosition(glm::vec3(-181.042267f, 1.352625f, -574.238708f));
//			Scene3_camera.SetFront(glm::vec3(-0.017452f, -0.009599f, -0.999802f));

			Scene3_camera.SetPosition(glm::vec3(-182.312881f, 1.352625f, -565.358704f));
			Scene3_camera.SetFront(glm::vec3(-0.000034f, -0.007599f, -0.999437f));

			
		}
		if (giCameraMoves < 550)
			Scene3_camera.ProcessKeyboard(FRAG_Camera2::FORWARD, deltaTime);
		if (giCameraMoves > 550)
		{
			giCameraMoves = 0;
			gbIsCameraSet = false;
			gCameraNumber++;

			// Sam : Car Crash
		}
	}
	else if (gCameraNumber == 5)
	{
		if (gbIsCameraSet == false)
		{
			giCameraMoves = 0;
			gbIsCameraSet = true;
			Scene3_camera.SetPosition(glm::vec3(-209.048843f, 13.932554f, -957.588501f));
			Scene3_camera.SetFront(glm::vec3(0.654204f, -0.573577f, 0.492978f));
		}

		if (giCameraMoves == 100)
		{
			if (isTranslateY == false)
			{
				isTranslateY = true;
				//Helicpter sound
			}

		}

		if (giCameraMoves > 500)
		{
			giCameraMoves = 0;
			gbIsCameraSet = false;
			gCameraNumber++;
		}
	}
	else if (gCameraNumber == 6)
	{
		if (gbIsCameraSet == false)
		{
			giCameraMoves = 0;
			gbIsCameraSet = true;
			Scene3_camera.SetPosition(glm::vec3(44.806740f, 38.181431f, -1911.009033f));
			Scene3_camera.SetFront(glm::vec3(-0.928555f, -0.364877f, 0.068192f));
		}
		if (giCameraMoves < 200)
			Scene3_camera.ProcessKeyboard(FRAG_Camera2::FORWARD, deltaTime);
		if (giCameraMoves > 300)
		{
			giCameraMoves = 0;
			gbIsCameraSet = false;
			gCameraNumber++;
		}
	}
	else if (gCameraNumber == 7)
	{
		if (gbIsCameraSet == false)
		{
			giCameraMoves = 0;
			gbIsCameraSet = true;
			Scene3_camera.SetPosition(glm::vec3(-37.416325f, 7.909022f, -2037.265991f));
			Scene3_camera.SetFront(glm::vec3(-0.074943f, 0.031411f, -0.996693f));
		}
		if (giCameraMoves < 380)
			Scene3_camera.ProcessKeyboard(FRAG_Camera2::FORWARD, deltaTime);
		if (giCameraMoves > 380)
		{
			giCameraMoves = 0;
			gbIsCameraSet = false;
			gCameraNumber++;
		}
	}
	//Comment all above this for camera facing ocean End
	giCameraMoves++;
}

void Draw_Scene3(void);
void DrawSkyBox(void);
void DrawCityModel(void);
void DrawCityModelWithShadowMap(void);
void DrawGrassInstancing(void);
void DrawInstancingShader(void);
void updateCamera(void);

void Draw_Scene3(void)
{
	void Scene3_Ocean_Display(void);
	DrawSkyBox();

	//DrawCityModel();
	DrawCityModelWithShadowMap();

	DrawGrassInstancing();

	DrawInstancingShader();

	if (speedometer != NULL)
	{
		speedometer->display();
	}

	Scene3_Ocean_Display();
}

void Scene3_resize(int width, int height)
{
	if (speedometer != NULL)
	{
		speedometer->resize(width, height);
	}
}

void DrawSkyBox()
{
	glm::mat4 modelMatrix = glm::mat4();
	glm::mat4 viewMatrix = glm::mat4();

	glUseProgram(g_Scene3_SkyBoxShader.gShaderProgramObject);
	glDisable(GL_DEPTH_TEST);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));
	glUniformMatrix4fv(g_Scene3_SkyBox_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	viewMatrix = Scene3_camera.GetViewMatrix();
	glUniformMatrix4fv(g_Scene3_SkyBox_ViewUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform1i(g_Scene3_SkyBox_Uniform, 0);

	glBindVertexArray(g_Scene3_SkyBoxModel.Vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_Scene3_CubemapTexture);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glUseProgram(0);
}

void DrawCityModel(void)
{
	//Use Shader Program Object
	glUseProgram(g_Scene3_CityModelShader.gShaderProgramObject);

	if (g_Scene3_Light == true)
	{
		glUniform1i(g_Scene3_CityModel_LKeyPressedUniform, 1);

		glUniform3fv(g_Scene3_CityModel_LaUniform, 1, g_Scene3_lightAmbient);
		glUniform3fv(g_Scene3_CityModel_LdUniform, 1, g_Scene3_lightDiffuse);
		glUniform3fv(g_Scene3_CityModel_LsUniform, 1, g_Scene3_lightSpecular);
		//glUniform4fv(g_Scene3_CityModel_LightPositionUniform, 1, lightPosition);

		glUniform3fv(g_Scene3_CityModel_KaUniform, 1, g_Scene3_materialAmbient);
		glUniform3fv(g_Scene3_CityModel_KdUniform, 1, g_Scene3_materialDiffuse);
		glUniform3fv(g_Scene3_CityModel_KsUniform, 1, g_Scene3_materialSpecular);
		glUniform1f(g_Scene3_CityModel_MaterialShininessUniform, g_Scene3_materialShininess);
	}
	else
	{
		glUniform1i(g_Scene3_CityModel_LKeyPressedUniform, 0);
	}

	glm::mat4 viewMatrix = glm::mat4();
	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	viewMatrix = Scene3_camera.GetViewMatrix();

	glUniformMatrix4fv(g_Scene3_CityModel_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(g_Scene3_CityModel_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(g_Scene3_CityModel_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_Scene3_CityModel_PerspectiveProjectionMatrix));

	glBindVertexArray(g_Scene3_CityModel.Vao);
	glDrawArrays(GL_TRIANGLES, 0, g_Scene3_CityModel.gv_vertices.size());
	glBindVertexArray(0);

	glUseProgram(0);
}

void DrawCityModelWithShadowMap(void)
{
	void RenderCity(GLuint & NewModel);
	void DrawHelicopterBody(GLuint & NewModel);
	void DrawHelicopterBlades(GLuint & NewModel);

	//Render Depth Map

	glm::vec3 lightPos(LIGHT_X_TRANSLATE, LIGHT_Y_TRANSLATE, LIGHT_Z_TRANSLATE);

	/*float zCoord = 20.0f;
	glm::vec3 lightPosForCity;
	for (int i = 0; i < 5; ++i)
	{
		zCoord -= 100.0f;
		lightPosForCity = glm::vec3(LIGHT_X_TRANSLATE, LIGHT_Y_TRANSLATE, zCoord);
	}
	//glm::vec3 lightPos(0.0f, 20.0f, 20.0f);
	*/

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = -10.0f, far_plane = 100.0f;

	lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);

	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));

	lightSpaceMatrix = lightProjection * lightView;

	// render scene from light's point of view
	glUseProgram(g_Scene3_DepthShader.gShaderProgramObject);

	glUniformMatrix4fv(glightSpaceMatrixSimpleDepthShaderUniform, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, g_Scene3_CityModel_DepthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	glCullFace(GL_FRONT);
	RenderCity(gmodelSimpleDepthShaderUniform);
	DrawHelicopterBody(gmodelSimpleDepthShaderUniform);
	DrawHelicopterBlades(gmodelSimpleDepthShaderUniform);
	glCullFace(GL_BACK);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);

	glViewport(0, 0, currentWidth, currentHeight);
	glClear(GL_DEPTH_BUFFER_BIT);

	//Use Shader Program Object
	glUseProgram(g_Scene3_CityModelShader.gShaderProgramObject);

	if (g_Scene3_Light == true)
	{
		glUniform1i(g_Scene3_CityModel_LKeyPressedUniform, 1);

		glUniform3fv(g_Scene3_CityModel_LaUniform, 1, g_Scene3_lightAmbient);
		glUniform3fv(g_Scene3_CityModel_LdUniform, 1, g_Scene3_lightDiffuse);
		glUniform3fv(g_Scene3_CityModel_LsUniform, 1, g_Scene3_lightSpecular);
		glUniform3fv(g_Scene3_CityModel_LightPositionUniform, 1, glm::value_ptr(lightPos));
		//glUniform4fv(g_Scene3_CityModel_LightPositionUniform, 1, lightPosition);

		glUniform3fv(g_Scene3_CityModel_KaUniform, 1, g_Scene3_materialAmbient);
		glUniform3fv(g_Scene3_CityModel_KdUniform, 1, g_Scene3_materialDiffuse);
		glUniform3fv(g_Scene3_CityModel_KsUniform, 1, g_Scene3_materialSpecular);
		glUniform1f(g_Scene3_CityModel_MaterialShininessUniform, g_Scene3_materialShininess);
		glUniformMatrix4fv(g_Scene3_CityModel_LightSpaceMatrixUniform, 1, GL_FALSE, &lightSpaceMatrix[0][0]);
	}
	else
	{
		glUniform1i(g_Scene3_CityModel_LKeyPressedUniform, 0);
	}

	glm::mat4 viewMatrix = glm::mat4();

	viewMatrix = Scene3_camera.GetViewMatrix();

	glUniformMatrix4fv(g_Scene3_CityModel_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(g_Scene3_CityModel_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_Scene3_CityModel_PerspectiveProjectionMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_Scene3_CityModel_DepthMap);
	RenderCity(g_Scene3_CityModel_ModelMatrixUniform);
	DrawHelicopterBody(g_Scene3_CityModel_ModelMatrixUniform);
	DrawHelicopterBlades(g_Scene3_CityModel_ModelMatrixUniform);
	glUseProgram(0);
}

void RenderCity(GLuint &NewModel)
{
	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = translate(modelMatrix, glm::vec3(MODEL_X_TRANSLATE, MODEL_Y_TRANSLATE, MODEL_Z_TRANSLATE));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(NewModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glBindVertexArray(g_Scene3_CityModel.Vao);
	//glDrawArrays(GL_TRIANGLES, 0, g_Scene3_CityModel.gv_vertices.size());
	for (int i = 0; i < g_Scene3_CityModel.gv_Mesh_Data.size(); i++)
	{
		if (gbLight == true)
		{
			glUniform3fv(g_Scene3_CityModel_KaUniform, 1, g_Scene3_CityModel.gv_Material[g_Scene3_CityModel.gv_Mesh_Data[i].material_index].Ka);
			glUniform3fv(g_Scene3_CityModel_KdUniform, 1, g_Scene3_CityModel.gv_Material[g_Scene3_CityModel.gv_Mesh_Data[i].material_index].Kd);
			glUniform3fv(g_Scene3_CityModel_KsUniform, 1, g_Scene3_CityModel.gv_Material[g_Scene3_CityModel.gv_Mesh_Data[i].material_index].Ks);
			glUniform1f(g_Scene3_CityModel_MaterialShininessUniform, g_Scene3_materialShininess);
			glUniform1f(g_Scene3_CityModel_AlphaUniform, g_Scene3_CityModel.gv_Material[g_Scene3_CityModel.gv_Mesh_Data[i].material_index].d);

			if (g_Scene3_CityModel.gv_Material[g_Scene3_CityModel.gv_Mesh_Data[i].material_index].ismap_Kd == true)
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, g_Scene3_CityModel.gv_Material[g_Scene3_CityModel.gv_Mesh_Data[i].material_index].gTexture);
				glUniform1i(g_Scene3_CityModel_TextureSamplerUniform, 1);
				glUniform1i(g_Scene3_CityModel_TextureActiveUniform, 1);
			}
			else
				glUniform1i(g_Scene3_CityModel_TextureActiveUniform, 0);
		}

		glDrawArrays(GL_TRIANGLES, g_Scene3_CityModel.gv_Mesh_Data[i].vertex_Index, g_Scene3_CityModel.gv_Mesh_Data[i].vertex_Count);
	}
	glBindVertexArray(0);
}

GLfloat gfTranslate_X = -196.0f, gfTranslate_Y = 0.015f, gfTranslate_Z = -945.0f;
void DrawHelicopterBody(GLuint &NewModel)
{
	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = translate(modelMatrix, glm::vec3(gfTranslate_X, 0.015f+ fTranslation_In_Y, gfTranslate_Z));

	if (bIsHelicopterDone)
	{
		modelMatrix = glm::mat4();
		modelMatrix = translate(modelMatrix, glm::vec3(-48.000f, 14.0f, -2190.0f));

		modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		modelMatrix = glm::rotate(modelMatrix, glm::radians(25.0f), glm::vec3(0.0f, 0.0f, -1.0f));

	}
	//modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(NewModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glBindVertexArray(g_Scene3_HelicopterBodyModel.Vao);
	//glDrawArrays(GL_TRIANGLES, 0, g_Scene3_CityModel.gv_vertices.size());
	for (int i = 0; i < g_Scene3_HelicopterBodyModel.gv_Mesh_Data.size(); i++)
	{
		if (gbLight == true)
		{
			glUniform3fv(g_Scene3_CityModel_KaUniform, 1, g_Scene3_HelicopterBodyModel.gv_Material[g_Scene3_HelicopterBodyModel.gv_Mesh_Data[i].material_index].Ka);
			glUniform3fv(g_Scene3_CityModel_KdUniform, 1, g_Scene3_HelicopterBodyModel.gv_Material[g_Scene3_HelicopterBodyModel.gv_Mesh_Data[i].material_index].Kd);
			glUniform3fv(g_Scene3_CityModel_KsUniform, 1, g_Scene3_HelicopterBodyModel.gv_Material[g_Scene3_HelicopterBodyModel.gv_Mesh_Data[i].material_index].Ks);
			glUniform1f(g_Scene3_CityModel_MaterialShininessUniform, g_Scene3_materialShininess);
			glUniform1f(g_Scene3_CityModel_AlphaUniform, g_Scene3_HelicopterBodyModel.gv_Material[g_Scene3_HelicopterBodyModel.gv_Mesh_Data[i].material_index].d);

			if (g_Scene3_HelicopterBodyModel.gv_Material[g_Scene3_HelicopterBodyModel.gv_Mesh_Data[i].material_index].ismap_Kd == true)
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, g_Scene3_HelicopterBodyModel.gv_Material[g_Scene3_HelicopterBodyModel.gv_Mesh_Data[i].material_index].gTexture);
				glUniform1i(g_Scene3_CityModel_TextureSamplerUniform, 1);
				glUniform1i(g_Scene3_CityModel_TextureActiveUniform, 1);
			}
			else
				glUniform1i(g_Scene3_CityModel_TextureActiveUniform, 0);
		}

		glDrawArrays(GL_TRIANGLES, g_Scene3_HelicopterBodyModel.gv_Mesh_Data[i].vertex_Index, g_Scene3_HelicopterBodyModel.gv_Mesh_Data[i].vertex_Count);
	}
	glBindVertexArray(0);
}

void DrawHelicopterBlades(GLuint &NewModel)
{
	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = translate(modelMatrix, glm::vec3(-196.0f, 0.015f+ fTranslation_In_Y, -945.0f));

	if (bIsHelicopterDone)
	{
		modelMatrix = glm::mat4();
		modelMatrix = translate(modelMatrix, glm::vec3(-48.000f, 14.0f, -2190.0f));

		modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(25.0f), glm::vec3(0.0f, 0.0f, -1.0f));

	}
	modelMatrix = glm::rotate(modelMatrix, glm::radians(fRotation_Angle_Blades), glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(NewModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glBindVertexArray(g_Scene3_HelicopterBladesModel.Vao);
	//glDrawArrays(GL_TRIANGLES, 0, g_Scene3_CityModel.gv_vertices.size());
	for (int i = 0; i < g_Scene3_HelicopterBladesModel.gv_Mesh_Data.size(); i++)
	{
		if (gbLight == true)
		{
			glUniform3fv(g_Scene3_CityModel_KaUniform, 1, g_Scene3_HelicopterBladesModel.gv_Material[g_Scene3_HelicopterBladesModel.gv_Mesh_Data[i].material_index].Ka);
			glUniform3fv(g_Scene3_CityModel_KdUniform, 1, g_Scene3_HelicopterBladesModel.gv_Material[g_Scene3_HelicopterBladesModel.gv_Mesh_Data[i].material_index].Kd);
			glUniform3fv(g_Scene3_CityModel_KsUniform, 1, g_Scene3_HelicopterBladesModel.gv_Material[g_Scene3_HelicopterBladesModel.gv_Mesh_Data[i].material_index].Ks);
			glUniform1f(g_Scene3_CityModel_MaterialShininessUniform, g_Scene3_materialShininess);
			glUniform1f(g_Scene3_CityModel_AlphaUniform, g_Scene3_HelicopterBladesModel.gv_Material[g_Scene3_HelicopterBladesModel.gv_Mesh_Data[i].material_index].d);

			if (g_Scene3_HelicopterBladesModel.gv_Material[g_Scene3_HelicopterBladesModel.gv_Mesh_Data[i].material_index].ismap_Kd == true)
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, g_Scene3_HelicopterBladesModel.gv_Material[g_Scene3_HelicopterBladesModel.gv_Mesh_Data[i].material_index].gTexture);
				glUniform1i(g_Scene3_CityModel_TextureSamplerUniform, 1);
				glUniform1i(g_Scene3_CityModel_TextureActiveUniform, 1);
			}
			else
				glUniform1i(g_Scene3_CityModel_TextureActiveUniform, 0);
		}

		glDrawArrays(GL_TRIANGLES, g_Scene3_HelicopterBladesModel.gv_Mesh_Data[i].vertex_Index, g_Scene3_HelicopterBladesModel.gv_Mesh_Data[i].vertex_Count);
	}
	glBindVertexArray(0);
}


void DrawGrassInstancing(void)
{
	//Grass Instancing
	glUseProgram(g_Scene3_GrassShader.gShaderProgramObject);

	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(GRASS_X_TRANSLATE, GRASS_Y_TRANSLATE, GRASS_Z_TRANSLATE));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.03f, 0.1f, 0.4f));

	glm::mat4 viewMatrix = glm::mat4();
	viewMatrix = Scene3_camera.GetViewMatrix();

	glm::mat4 MVPMatrix = g_Scene3_CityModel_PerspectiveProjectionMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv(g_Scene3_Grass_MVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

	glBindVertexArray(g_Scene3_GrassModel.Vao);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, 1024 * 1024);

	glBindVertexArray(0);

	modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(GRASS_X_TRANSLATE1, GRASS_Y_TRANSLATE1, GRASS_Z_TRANSLATE1));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 0.25f, 0.25f));

	MVPMatrix = g_Scene3_CityModel_PerspectiveProjectionMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv(g_Scene3_Grass_MVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

	glBindVertexArray(g_Scene3_GrassModel.Vao);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, 1024 * 1024);

	glBindVertexArray(0);

	glUseProgram(0);
}

void DrawInstancingShader()
{
	//Instancing
	glm::vec3 lightPos(LIGHT_X_TRANSLATE, LIGHT_Y_TRANSLATE, LIGHT_Z_TRANSLATE);

	glUseProgram(g_Scene3_InstanceShader.gShaderProgramObject);

	if (g_Scene3_Light == true)
	{
		glUniform1i(g_Scene3_Instance_LKeyPressedUniform, 1);

		glUniform3fv(g_Scene3_Instance_LaUniform, 1, g_Scene3_lightAmbient);
		glUniform3fv(g_Scene3_Instance_LdUniform, 1, g_Scene3_lightDiffuse);
		glUniform3fv(g_Scene3_Instance_LsUniform, 1, g_Scene3_lightSpecular);
		glUniform3fv(g_Scene3_CityModel_LightPositionUniform, 1, glm::value_ptr(lightPos));

		//glUniform4fv(g_Scene3_Instance_LightPositionUniform, 1, lightPosition);

		glUniform3fv(g_Scene3_Instance_KaUniform, 1, g_Scene3_materialAmbient);
		glUniform3fv(g_Scene3_Instance_KdUniform, 1, g_Scene3_materialDiffuse);
		glUniform3fv(g_Scene3_Instance_KsUniform, 1, g_Scene3_materialSpecular);
		glUniform1f(g_Scene3_Instance_MaterialShininessUniform, g_Scene3_materialShininess);
	}
	else
	{
		glUniform1i(g_Scene3_Instance_LKeyPressedUniform, 0);
	}

	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-185.0f, -1.3f, -700.0f));
	//X - Pos : -185.000000, Y - Pos : 0.000000, Z - Pos : -835.000000

	modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(g_Scene3_Instance_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glm::mat4 viewMatrix = glm::mat4();
	viewMatrix = Scene3_camera.GetViewMatrix();

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
	viewMatrix = Scene3_camera.GetViewMatrix();

	glUniformMatrix4fv(g_Scene3_Instance_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(g_Scene3_Instance_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_Scene3_CityModel_PerspectiveProjectionMatrix));

	//****************CITY LIGHT (on road after bridge crossing)*******************
	glBindVertexArray(g_Scene3_CityLightModel.Vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, g_Scene3_CityLightModel.gv_vertices.size(), 6);
	glBindVertexArray(0);

	modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-200.0f, -1.0f, -700.0f));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01f));

	glUniformMatrix4fv(g_Scene3_Instance_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	//***************BENCHES (Placed On Grass)
	glBindVertexArray(g_Scene3_BenchModel.Vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, g_Scene3_BenchModel.gv_vertices.size(), g_Bench_InstanceCount);
	glBindVertexArray(0);

	modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-190.0f, -1.0f, -680.0f));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 4.0f, 2.0f));

	glUniformMatrix4fv(g_Scene3_Instance_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	//***************Palm Tree (Placed On Grass)
	glBindVertexArray(g_Scene3_PalmTreeModel.Vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, g_Scene3_PalmTreeModel.gv_vertices.size(), g_PalmTree_InstanceCount);
	glBindVertexArray(0);
	glUseProgram(0);
}

//**************************SHADOW MAPPING*******************
void Scene3_initializeDepthShader(void)
{
	void uninitialize(int);

	/*fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In SimpleDepthShaderBuildNCompileShader \n ");
	fclose(gpFile);*/
	logInfo("In SimpleDepthShaderBuildNCompileShader \n ");

	//VERTEX SHADER
	g_Scene3_DepthShader.gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertextShaderSourceCodeSimpleDepthShader =
		"#version 450"
		"\n"
		"layout (location = 0) in vec3 vPosition;"
		"uniform mat4 lightSpaceMatrix;"
		"uniform mat4 model;"
		"void main()"
		"{"
		"gl_Position = lightSpaceMatrix * model * vec4(vPosition, 1.0);"
		"}";

	glShaderSource(g_Scene3_DepthShader.gVertexShaderObject, 1, (const GLchar **)&vertextShaderSourceCodeSimpleDepthShader, NULL);

	//compile shader
	glCompileShader(g_Scene3_DepthShader.gVertexShaderObject);

	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(g_Scene3_DepthShader.gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_DepthShader.gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_DepthShader.gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				/*
				fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Vertex Shader SimpleDepthShader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Vertex Shader SimpleDepthShader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//FRAGMENT SHADER
	g_Scene3_DepthShader.gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCodeSimpleDepthShader =
		"#version 450"
		"\n"
		"void main(void)"
		"{"
		"}";

	glShaderSource(g_Scene3_DepthShader.gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCodeSimpleDepthShader, NULL);

	glCompileShader(g_Scene3_DepthShader.gFragmentShaderObject);

	glGetShaderiv(g_Scene3_DepthShader.gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_DepthShader.gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_DepthShader.gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				/*	fopen_s(&gpFile, "Log.txt", "a+");
				fprintf(gpFile, "Fragment Shader SimpleDepthShader Compilation Log : %s\n", szInfoLog);
				fclose(gpFile);*/
				logError("Fragment Shader SimpleDepthShader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}

	//Shader Program
	g_Scene3_DepthShader.gShaderProgramObject = glCreateProgram();

	glAttachShader(g_Scene3_DepthShader.gShaderProgramObject, g_Scene3_DepthShader.gVertexShaderObject);
	glAttachShader(g_Scene3_DepthShader.gShaderProgramObject, g_Scene3_DepthShader.gFragmentShaderObject);

	glBindAttribLocation(g_Scene3_DepthShader.gShaderProgramObject, HAD_ATTRIBUTE_POSITION, "vPosition");

	glLinkProgram(g_Scene3_DepthShader.gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(g_Scene3_DepthShader.gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_Scene3_DepthShader.gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(g_Scene3_DepthShader.gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				//fprintf(gpFile, "Shader Program Link SimpleDepthShader Log : %s\n", szInfoLog);
				logError("Shader Program Link SimpleDepthShader Log : %s\n", szInfoLog);
				free(szInfoLog);
				uninitialize(1);
				exit(0);
			}
		}
	}
	glightSpaceMatrixSimpleDepthShaderUniform = glGetUniformLocation(g_Scene3_DepthShader.gShaderProgramObject, "lightSpaceMatrix");
	gmodelSimpleDepthShaderUniform = glGetUniformLocation(g_Scene3_DepthShader.gShaderProgramObject, "model");

	/*fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "End of SimpleDepthShaderBuildNCompileShader \n ");
	fclose(gpFile);*/
}

void Scene3_GenerateDepthMap(void)
{
	/*fopen_s(&gpFile, "Log.txt", "a+");
	fprintf(gpFile, "In GenerateDepthMap..\n");
	fclose(gpFile);*/

	//Create a framebuffer object for rendering depth map
	glGenFramebuffers(1, &g_Scene3_CityModel_DepthMapFBO);

	//Create 2D texture that we'll use as framebuffer's depth buffer

	//Create depth texture
	glGenTextures(1, &g_Scene3_CityModel_DepthMap);
	//glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_Scene3_CityModel_DepthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float borderColor[] = {1.0, 1.0, 1.0, 1.0};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, g_Scene3_CityModel_DepthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, g_Scene3_CityModel_DepthMap, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/******* Low Poly Ocean Start *******/

void Scene3_Ocean_Initialize(void)
{
	void Scene3_Ocean_UnInitialize(void);

	// Shader Information End
	// Sam :  All Shaders Code Start

	//***** Vertex Shader *****
	//Create Shader
	g_Scene3_Ocean_VertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	// give source code to shader
	const GLchar *vertexShaderSourceCode = "#version 460 core"
										   "\n"
										   "in vec2 vPosition;"
										   "uniform float u_time;"
										   "const float PI = 3.1415926535897932384626433832795;"
										   "const float amplitude = 0.08f;"
										   "float GenerateHeight()"
										   "{"
										   "	float component1 = sin(2.0f * PI * u_time + ( 16.0f *vPosition.x) )  * amplitude;"
										   "	float component2 = cos(2.0f * PI * u_time + ( 8.0f * vPosition.x * vPosition.y) ) * amplitude;"
										   "	return (component1 + component2);"
										   "}"
										   "void main (void)"
										   "{"
										   "	float height = GenerateHeight();"
										   "	gl_Position =  vec4(vPosition.x,height,vPosition.y,1.0f);"
										   "}";
	glShaderSource(g_Scene3_Ocean_VertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);
	// (u_projection_matrix * u_view_matrix * u_model_matrix) *
	// Compile Source Code
	glCompileShader(g_Scene3_Ocean_VertexShaderObject);
	GLint iInfoLogLength = 0;
	GLint iShaderCompileStatus = 0;
	char *szInfoLog = NULL;
	glGetShaderiv(g_Scene3_Ocean_VertexShaderObject, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_Ocean_VertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_Ocean_VertexShaderObject, GL_INFO_LOG_LENGTH, &written, szInfoLog);
				//fprintf_s(gp_File, "Error : Vertex Shader Compilation Log : %s \n", szInfoLog);
				free(szInfoLog);
				Scene3_Ocean_UnInitialize();
				exit(EXIT_FAILURE);
			}
		}
	}

	//***** Geometry Shader *****
	//Create Shader
	g_Scene3_Ocean_GeometryShaderObject = glCreateShader(GL_GEOMETRY_SHADER);

	// give source code to shader
	const GLchar *geometryShaderSourceCode =
		"#version 460 core"
		"\n"
		"layout(triangles) in;"
		"layout(triangle_strip,max_vertices=3) out;"
		"out vec3 finalColor;"

		"uniform mat4 u_model_matrix;"
		"uniform mat4 u_view_matrix;"
		"uniform mat4 u_projection_matrix;"
		"uniform vec3 u_Camera_Position ;"

		"const vec3 LightDirection= vec3(0.4f,-1.0f,0.8f);"
		"const vec3 normalizedLightDirection = normalize( LightDirection ) ;"
		"const vec3 waterColor = vec3(0.2f,0.4f,0.45f);"
		"const vec3 lightColor = vec3(1.0f,0.6f,0.6f);"
		"const float reflection = 0.5f;"
		"const float shininess = 14.0f;"
		"const float ambientLight = 0.3f;"

		"const float PI = 3.1415926535897932384626433832795;"

		"vec3 CalculateTriangleNormal()"
		"{"
		"	vec3 v3Tangent = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;"
		"	vec3 v3BiTangent = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;"
		"	vec3 v3Normal = cross(v3Tangent,v3BiTangent);"
		"	return normalize(v3Normal) ;"
		"}"

		"vec3 CalculateSpecular(vec4 v4WorldPosition,vec3 v3Normal)"
		"{"
		"	vec3 ViewerVector = normalize(u_Camera_Position - v4WorldPosition.xyz);"
		"	vec3 ReflectedLightDirection = reflect(normalizedLightDirection,v3Normal);"
		"	float specularFactor = dot(ReflectedLightDirection,ViewerVector);"
		"	specularFactor = max(pow(specularFactor,shininess),0.0f);"
		"	return (lightColor * specularFactor * reflection);"
		"}"

		"void main (void)"
		"{"
		"	vec3 normal = CalculateTriangleNormal();"
		"	float fBrightness = max(dot(-normalizedLightDirection,normal),ambientLight); "
		"	vec3 color = waterColor * fBrightness;"

		"	vec4 worldPosition = gl_in[0].gl_Position;"
		"	gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * worldPosition;"
		"	finalColor = color + CalculateSpecular(worldPosition,normal);"
		"	EmitVertex();"

		"	worldPosition = gl_in[1].gl_Position;"
		"	gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * worldPosition;"
		"	finalColor = color + CalculateSpecular(worldPosition,normal);"
		"	EmitVertex();"

		"	worldPosition = gl_in[2].gl_Position;"
		"	gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * worldPosition;"
		"	finalColor = color + CalculateSpecular(worldPosition,normal);"
		"	EmitVertex();"

		"	EndPrimitive();"
		"}";
	glShaderSource(g_Scene3_Ocean_GeometryShaderObject, 1, (const GLchar **)&geometryShaderSourceCode, NULL);

	// Compile Source Code
	glCompileShader(g_Scene3_Ocean_GeometryShaderObject);
	iInfoLogLength = 0;
	iShaderCompileStatus = 0;
	szInfoLog = NULL;
	glGetShaderiv(g_Scene3_Ocean_GeometryShaderObject, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_Ocean_GeometryShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_Ocean_GeometryShaderObject, GL_INFO_LOG_LENGTH, &written, szInfoLog);
				//fprintf_s(gp_File, "Error : Geometry Shader Compilation Log : %s \n", szInfoLog);
				free(szInfoLog);
				Scene3_Ocean_UnInitialize();
				exit(EXIT_FAILURE);
			}
		}
	}

	//***** Fragment Shader *****
	g_Scene3_Ocean_FragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode = "#version 460 core"
											 "\n"
											 "out vec4 FragColor;"
											 "in vec3 finalColor;"
											 "void main (void)"
											 "{"
											 "	FragColor = vec4(finalColor,1.0f);"
											 "}";
	glShaderSource(g_Scene3_Ocean_FragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);
	// 0.2f,0.4f,0.45f
	// Compile Source Code
	glCompileShader(g_Scene3_Ocean_FragmentShaderObject);
	iInfoLogLength = 0;
	iShaderCompileStatus = 0;
	szInfoLog = NULL;
	glGetShaderiv(g_Scene3_Ocean_FragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_Scene3_Ocean_FragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_Scene3_Ocean_FragmentShaderObject, GL_INFO_LOG_LENGTH, &written, szInfoLog);
				//fprintf_s(gp_File, "Error : Fragment Shader Compilation Log : %s \n", szInfoLog);
				free(szInfoLog);
				Scene3_Ocean_UnInitialize();
				exit(EXIT_FAILURE);
			}
		}
	}

	//***** Shader Program *****
	// Create
	g_Scene3_Ocean_ShaderProgramObject = glCreateProgram();
	// Attach Vertex Shader
	glAttachShader(g_Scene3_Ocean_ShaderProgramObject, g_Scene3_Ocean_VertexShaderObject);
	// Attach Fragment Shader
	glAttachShader(g_Scene3_Ocean_ShaderProgramObject, g_Scene3_Ocean_GeometryShaderObject);
	// Attach Fragment Shader
	glAttachShader(g_Scene3_Ocean_ShaderProgramObject, g_Scene3_Ocean_FragmentShaderObject);
	// pre-link Program object with Vertex Sahder position attribute
	glBindAttribLocation(g_Scene3_Ocean_ShaderProgramObject, HAD_ATTRIBUTE_POSITION, "vPosition");
	// link Shader
	glLinkProgram(g_Scene3_Ocean_ShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(g_Scene3_Ocean_ShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	szInfoLog = NULL;
	iInfoLogLength = 0;
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_Scene3_Ocean_ShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(g_Scene3_Ocean_ShaderProgramObject, GL_INFO_LOG_LENGTH, &written, szInfoLog);
				//fprintf_s(gp_File, "Error : Shader Program Link Log : %s \n", szInfoLog);
				free(szInfoLog);
				Scene3_Ocean_UnInitialize();
				exit(EXIT_FAILURE);
			}
		}
	}

	g_Scene3_Ocean_Uniform_ModelMatrix = glGetUniformLocation(g_Scene3_Ocean_ShaderProgramObject, "u_model_matrix");
	g_Scene3_Ocean_Uniform_ViewMatrix = glGetUniformLocation(g_Scene3_Ocean_ShaderProgramObject, "u_view_matrix");
	g_Scene3_Ocean_Uniform_ProjectionMatrix = glGetUniformLocation(g_Scene3_Ocean_ShaderProgramObject, "u_projection_matrix");
	g_Scene3_Ocean_Uniform_Time = glGetUniformLocation(g_Scene3_Ocean_ShaderProgramObject, "u_time");
	g_Scene3_Ocean_Uniform_Camera_Position = glGetUniformLocation(g_Scene3_Ocean_ShaderProgramObject, "u_Camera_Position");
	// **** Verttices, Colors, Shader Attribs, Vbo, Vao Initializations ****

	int iIndex = 0;
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		for (int j = 0; j < VERTEX_COUNT; j++)
		{
			g_Scene3_Ocean_MeshVertices[iIndex++] = j * OCEAN_SIZE;
			g_Scene3_Ocean_MeshVertices[iIndex++] = -i * OCEAN_SIZE;
		}
	}

	iIndex = 0;
	int iFaceCount = 0;

	for (int i = 0, j = 0; j < (6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)); i++, j += 6)
	{
		int topRight = VERTEX_COUNT + i + 1;
		int bottomleft = i;
		int bottomRight = i + 1;
		int topLeft = VERTEX_COUNT + i;

		g_Scene3_Ocean_shIndices[j] = topRight;
		g_Scene3_Ocean_shIndices[j + 1] = bottomleft;
		g_Scene3_Ocean_shIndices[j + 2] = bottomRight;

		g_Scene3_Ocean_shIndices[j + 3] = topRight;
		g_Scene3_Ocean_shIndices[j + 4] = topLeft;
		g_Scene3_Ocean_shIndices[j + 5] = bottomleft;

		iFaceCount += 2;
		if ((iFaceCount / ((VERTEX_COUNT - 1) * 2)) == 1)
		{
			i += 1;
			iFaceCount = 0;
		}
	}

	// vao creation and binding
	glGenVertexArrays(1, &g_Scene3_Ocean_VertexArrayObject);
	glBindVertexArray(g_Scene3_Ocean_VertexArrayObject);

	//vbo creation and binding
	glGenBuffers(1, &g_Scene3_Ocean_VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Ocean_VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, ARRAYSIZE(g_Scene3_Ocean_MeshVertices), g_Scene3_Ocean_MeshVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(HAD_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(HAD_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_Scene3_Ocean_VertexBufferObject_Indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_Scene3_Ocean_VertexBufferObject_Indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(GLuint)) * (6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)), g_Scene3_Ocean_shIndices, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, ARRAYSIZE(g_Scene3_Ocean_shIndices), g_Scene3_Ocean_shIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	glBindVertexArray(0);

	// Sam :  All Shaders Code End

	g_Scene3_Ocean_PerspectiveProjectionMatrix = glm::mat4(1.0f);
}


void Scene3_Ocean_Display(void)
{

	glUseProgram(g_Scene3_Ocean_ShaderProgramObject);

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 rotationMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(-280.0f, -4.0f, 136.0f));

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(0.0f), glm::vec3(-400.0f, -200.0f, 1.0f));
	scaleMatrix = glm::scale(modelMatrix, glm::vec3(100.0f, 1.0f, 200.0f));

	modelMatrix = modelMatrix * rotationMatrix;
	modelMatrix = modelMatrix * scaleMatrix;
	viewMatrix = Scene3_camera.GetViewMatrix();

	glUniformMatrix4fv(g_Scene3_Ocean_Uniform_ModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_Scene3_Ocean_Uniform_ViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_Scene3_Ocean_Uniform_ProjectionMatrix, 1, GL_FALSE, glm::value_ptr(g_Scene3_Ocean_PerspectiveProjectionMatrix));

	glUniform1f(g_Scene3_Ocean_Uniform_Time, g_Scene3_Ocean_U_Time);
	glm::vec3 CameraPos = Scene3_camera.GetCameraPostion();
	glUniform3f(g_Scene3_Ocean_Uniform_Camera_Position, CameraPos.x, CameraPos.y, CameraPos.z);

	glBindVertexArray(g_Scene3_Ocean_VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, g_Scene3_Ocean_VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, _ARRAYSIZE(g_Scene3_Ocean_MeshVertices), g_Scene3_Ocean_MeshVertices, GL_DYNAMIC_DRAW);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_Scene3_Ocean_VertexBufferObject_Indices); //g_Scene3_Ocean_MeshVertices
	glDrawElements(GL_TRIANGLES, (6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)), GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, sizeof(GLushort) * (6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1)), GL_UNSIGNED_SHORT, 0);
	// 58806

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(0);

	glUseProgram(0);
}

void Scene3_HelicopterBlades_Update(void)
{
	fRotation_Angle_Blades = fRotation_Angle_Blades + 10.0f;

	if (fRotation_Angle_Blades >= 360.0f)
	{
		fRotation_Angle_Blades = 0.0f;
	}

	if (isTranslateY)
	{
		fTranslation_In_Y = fTranslation_In_Y + 0.1f;
		if (fTranslation_In_Y >= 50.0f)
		{
			bIsHelicopterDone = true;
			fTranslation_In_Y = 50.0f;
		}
	}
}

void Scene3_Ocean_Update(void)
{
	fRotation_Angle = fRotation_Angle + 0.1f;

	if (fRotation_Angle >= 360.0f)
	{
		fRotation_Angle = 0.0f;
	}

	g_Scene3_Ocean_U_Time = g_Scene3_Ocean_U_Time + 0.005f;
}

void Scene3_Ocean_UnInitialize(void)
{
	if (g_Scene3_Ocean_VertexArrayObject)
	{
		glDeleteVertexArrays(1, &g_Scene3_Ocean_VertexArrayObject);
		g_Scene3_Ocean_VertexArrayObject = 0;
	}

	if (g_Scene3_Ocean_VertexBufferObject)
	{
		glDeleteBuffers(1, &g_Scene3_Ocean_VertexBufferObject);
		g_Scene3_Ocean_VertexBufferObject = 0;
	}

	glDetachShader(g_Scene3_Ocean_ShaderProgramObject, g_Scene3_Ocean_VertexShaderObject);
	glDetachShader(g_Scene3_Ocean_ShaderProgramObject, g_Scene3_Ocean_GeometryShaderObject);
	glDetachShader(g_Scene3_Ocean_ShaderProgramObject, g_Scene3_Ocean_FragmentShaderObject);

	if (g_Scene3_Ocean_VertexShaderObject)
	{
		glDeleteShader(g_Scene3_Ocean_VertexShaderObject);
		g_Scene3_Ocean_VertexShaderObject = 0;
	}

	if (g_Scene3_Ocean_GeometryShaderObject)
	{
		glDeleteShader(g_Scene3_Ocean_GeometryShaderObject);
		g_Scene3_Ocean_GeometryShaderObject = 0;
	}

	if (g_Scene3_Ocean_FragmentShaderObject)
	{
		glDeleteShader(g_Scene3_Ocean_FragmentShaderObject);
		g_Scene3_Ocean_FragmentShaderObject = 0;
	}

	if (g_Scene3_Ocean_ShaderProgramObject)
	{
		glDeleteProgram(g_Scene3_Ocean_ShaderProgramObject);
		g_Scene3_Ocean_ShaderProgramObject = 0;
	}

	//glUseProgram(0);
}

/******* Low Poly Ocean End   *******/

/******* Scene 3 Audio Start *******/

void Scene3_InitializeAudio()
{
	///******* Audio Buffers Start ******
	// initialize In the End Start
	alGenBuffers(1, &g_Scene3_iInTheEnd_Buffer);

	ALenum error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create In The End audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	ALboolean waveDataLoaded = Scene1_audioManager->loadWaveAudio("RTR_resources/audio/InTheEnd.wav", g_Scene3_iInTheEnd_Buffer);

	if (!waveDataLoaded)
	{
		logError("Not able to In The End audio file.\n");
	}

	// initialize In the End END

	// Init Silent Sound Start
	alGenBuffers(1, &g_Scene3_iSilentSound_Buffer);

	error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create Silent Sound audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	waveDataLoaded = Scene1_audioManager->loadWaveAudio("RTR_resources/audio/silence_sound.wav", g_Scene3_iSilentSound_Buffer);

	if (!waveDataLoaded)
	{
		logError("Not able to Silent Sound audio file.\n");
	}
	// Init Silent Sound End

	// Init CarAcceleration_Start_Buffer Start
	alGenBuffers(1, &g_Scene3_iCarAcceleration_Start_Buffer);

	error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create CarAcceleration_Start_Buffer audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	waveDataLoaded = Scene1_audioManager->loadWaveAudio("RTR_resources/audio/CarAcceleration.wav", g_Scene3_iCarAcceleration_Start_Buffer);

	if (!waveDataLoaded)
	{
		logError("Not able to CarAcceleration_Start_Buffer audio file.\n");
	}
	// Init CarAcceleration_Start_Buffer End


	// Init CarAcceleration_Repeat Start
	alGenBuffers(1, &g_Scene3_iCarAcceleration_Repeat_Buffer);

	error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create CarAcceleration_Repeat audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	waveDataLoaded = Scene1_audioManager->loadWaveAudio("RTR_resources/audio/CarAcceleration.wav", g_Scene3_iCarAcceleration_Repeat_Buffer);

	if (!waveDataLoaded)
	{
		logError("Not able to CarAcceleration_Repeat audio file.\n");
	}
	// Init CarAcceleration_Repeat End

	// Init CarAcceleration_End Start
	alGenBuffers(1, &g_Scene3_iCarAcceleration_End_Buffer);

	error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create CarAcceleration_End audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	waveDataLoaded = Scene1_audioManager->loadWaveAudio("RTR_resources/audio/CarAcceleration.wav", g_Scene3_iCarAcceleration_End_Buffer);

	if (!waveDataLoaded)
	{
		logError("Not able to CarAcceleration_End audio file.\n");
	}
	// Init CarAcceleration_End End

	// Init PoliceSiren Start
	alGenBuffers(1, &g_Scene3_iPoliceSiren_Buffer);

	error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create PoliceSiren audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	waveDataLoaded = Scene1_audioManager->loadWaveAudio("RTR_resources/audio/PoliceSiren.wav", g_Scene3_iPoliceSiren_Buffer);

	if (!waveDataLoaded)
	{
		logError("Not able to PoliceSiren audio file.\n");
	}
	// Init PoliceSiren End

	// Init CarCrash Start
	alGenBuffers(1, &g_Scene3_iCarCrash_Buffer);

	error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create point light audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	waveDataLoaded = Scene1_audioManager->loadWaveAudio("RTR_resources/audio/CrashCar.wav", g_Scene3_iCarCrash_Buffer);

	if (!waveDataLoaded)
	{
		logError("Not able to point light audio file.\n");
	}
	// Init CarCrash End

	// Init Helicopter Start
	alGenBuffers(1, &g_Scene3_iHelicopter_Buffer);

	error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create point light audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	waveDataLoaded = Scene1_audioManager->loadWaveAudio("RTR_resources/audio/Helicopter.wav", g_Scene3_iHelicopter_Buffer);

	if (!waveDataLoaded)
	{
		logError("Not able to point light audio file.\n");
	}

	// Init Helicopter End
	//// Audio Buffers End   

	//// Audio Sources Start 
	g_SS_Scene3_Ambient = new SoundSource();
	g_SS_Scene3_Ambient->setPosition3f(0.0f, 0.0f, 0.0f);

	g_SS_Scene3_Car = new SoundSource();
	g_SS_Scene3_Car->setPosition3f(0.0f, 0.0f, 0.0f);

	g_SS_Scene3_WindSound = new SoundSource();
	g_SS_Scene3_WindSound->setPosition3f(0.0f, 0.0f, 0.0f);

	g_SS_Scene3_Helicopter = new SoundSource();
	g_SS_Scene3_Helicopter->setPosition3f(0.0f, 0.0f, 0.0f);
	//// Audio Sources End   *******

}

/******* Scene 3 Audio End   *******/

