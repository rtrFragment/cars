#pragma once

#include"Common_Header.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define SCENE2_1_MODEL_X_TRANSLATE		0.0f	//X-translation of MODEL
#define SCENE2_1_MODEL_Y_TRANSLATE		-1.0f	//Y-translation of MODEL
#define SCENE2_1_MODEL_Z_TRANSLATE		-15.0f	//Z-translation of MODEL

#define SCENE2_1_MODEL_X_SCALE_FACTOR	1.5f	//X-scale factor of MODEL
#define SCENE2_1_MODEL_Y_SCALE_FACTOR	1.5f	//Y-scale factor of MODEL
#define SCENE2_1_MODEL_Z_SCALE_FACTOR	1.5f	//Z-scale factor of MODEL

#define SCENE2_1_START_ANGLE_POS			0.0f	//Marks beginning angle position of rotation
#define SCENE2_1_END_ANGLE_POS				360.0f	//Marks terminating angle position rotation
#define SCENE2_1_MODEL_ANGLE_INCREMENT		0.8f	//Increment angle for MODEL

// For Engine Working
#define SCENE2_1_PISTON_POS_CHANGE_FACTOR		0.02f		// Exclusive to Piston
#define SCENE2_1_VALVE_POS_CHANGE_FACTOR		0.004f		// Exclusive to Inlet and Outlet Valves

#define SCENE2_1_RECT_CHANGE_FACTOR			SCENE2_1_PISTON_POS_CHANGE_FACTOR		// Our Cheating Rectangle
#define SCENE2_1_COLOR_CHANGE_FACTOR		0.01f							// Color Change Factor

#define SCENE2_1_NUMBER_OF_PARTICLE			100

#define SAM_FULLSCREEN WM_USER+0x0c


enum
{
	FRAG_ATTRIBUTE_POSITION = 0,
	FRAG_ATTRIBUTE_COLOR,
	FRAG_ATTRIBUTE_NORMAL,
	FRAG_ATTRIBUTE_TEXTURE0,
	FRAG_VELOCITY_ARRAY,
	FRAG_START_TIME_ARRAY
};




GLuint g_scene2_1_VertexShaderObject;
GLuint g_scene2_1_FragmentShaderObject;
GLuint g_scene2_1_ShaderProgramObject;

GLuint g_scene2_1_Vao_Piston;
GLuint g_scene2_1_Vao_Bore;
GLuint g_scene2_1_Vao_SparkPlug;
GLuint g_scene2_1_Vao_InletValve;
GLuint g_scene2_1_Vao_OutletValve;

GLuint g_scene2_1_Vbo_Position, g_scene2_1_Vbo_Normal;
GLuint g_scene2_1_Vbo_Position_Bore, g_scene2_1_Vbo_Normal_Bore;
GLuint g_scene2_1_Vbo_Position_SparkPlug, g_scene2_1_Vbo_Normal_SparkPlug;
GLuint g_scene2_1_Vbo_Position_InletValve, g_scene2_1_Vbo_Normal_InletValve;
GLuint g_scene2_1_Vbo_Position_OutletValve, g_scene2_1_Vbo_Normal_OutletValve;

GLuint g_scene2_1_ModelMatrixUniform, g_scene2_1_ViewMatrixUniform, g_scene2_1_ProjectionMatrixUniform;
GLuint gLKeyPressedUniform;

GLuint g_scene2_1_LaUniform, g_scene2_1_LdUniform, g_scene2_1_LsUniform;
GLuint gLightPositionUniform;

GLuint g_scene2_1_KaUniform, g_scene2_1_KdUniform, g_scene2_1_KsUniform;
GLuint g_scene2_1_MaterialShininessUniform;

GLfloat gAngle_Cube;

glm::mat4 g_scene2_1_PerspectiveProjectionMatrix;

GLfloat lightAmbient[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat lightPosition[] = { 0.0f,20.0f,0.0f,0.0f };

GLfloat materialAmbient[] = { 0.25f,0.25f,0.25f,1.0f };
GLfloat materialDiffuse[] = { 0.4f,0.4f,0.4f,1.0f };
GLfloat materialSpecular[] = { 0.774597f,0.774597f,0.774597f,1.0f };
GLfloat materialShininess = 0.6f * 128.0f;

GLfloat g_rotate;

std::vector<float> gv_scene2_1_vertices_1, gv_scene2_2_textures_1, gv_scene2_2_normals_1;
std::vector<int> gv_scene2_2_face_tri_1, gv_scene2_2_face_textures_1, gv_scene2_2_face_normals_1;

int g_scene2_1_count_of_vertices_Piston;
int g_scene2_1_count_of_vertices_Bore;
int g_scene2_1_count_of_vertices_Inlet_Valve;
int g_scene2_1_count_of_vertices_Outlet_Valve;
int g_scene2_1_count_of_vertices_Spark_Plug;

/// Piston Movements
/*** View Port 1 Start ***/
GLfloat g_scene2_1_piston_inc_factor_1 = 0.3f;
bool g_scene2_1_bPistionIncFlag_1 = false;

/// Inlet valve
GLfloat g_scene2_1_inletValve_inc_factor_1[3] = { -1.2f,1.2f,-14.5f };
bool g_scene2_1_bInletValveIncFlag_1 = false;

/// Outlet valve
GLfloat g_scene2_1_outletValve_inc_factor_1[3] = { 1.2f,1.2f,-14.5f };
bool g_scene2_1_bOutletValveIncFlag_1 = false;

bool g_scene2_1_bSyncFlag_Inlet_1 = true;
short g_scene2_1_piston_down_count_1 = 0;
bool g_scene2_1_bSyncFlag_Outlet_1 = true;
/*** View Port 1 End  ***/

/*** View Port 2 Start ***/
// Piston Movements
GLfloat g_scene2_1_piston_inc_factor_2 = -2.5f;
bool g_scene2_1_bPistionIncFlag_2 = true;

// Inlet valve
GLfloat g_scene2_1_inletValve_inc_factor_2[3] = { -1.2f,1.2f,-14.5f };
bool g_scene2_1_bInletValveIncFlag_2 = false;

GLfloat g_scene2_1_outletValve_inc_factor_2[3] = { 1.2f,1.2f,-14.5f };
bool g_scene2_1_bOutletValveIncFlag_2 = false;

bool g_scene2_1_bSyncFlag_Inlet_2 = false;
short g_scene2_1_piston_down_count_2 = 1;
bool g_scene2_1_bSyncFlag_Outlet_2 = true;
/*** View Port 2 End   ***/

/*** View Port 3 Start ***/
// Piston Movements
GLfloat g_scene2_1_piston_inc_factor_3 = -2.5f;
bool g_scene2_1_bPistionIncFlag_3 = false;

// Inlet valve
GLfloat g_scene2_1_inletValve_inc_factor_3[3] = { -1.2f,1.2f,-14.5f };
bool g_scene2_1_bInletValveIncFlag_3 = false;

GLfloat outletValve_inc_factor_3[3] = { 1.2f,1.2f,-14.5f };
bool gbOutletValveIncFlag_3 = false;

bool g_scene2_1_bSyncFlag_Inlet_3 = false;
short g_scene2_1_piston_down_count_3 = 2;
bool g_scene2_1_bSyncFlag_Outlet_3 = true;
/*** View Port 3 End   ***/

/*** View Port 4 Start ***/
// Piston Movements
GLfloat g_scene2_1_piston_inc_factor_4 = 0.3f;
bool g_scene2_1_bPistionIncFlag_4 = false;

// Inlet valve
GLfloat g_scene2_1_inletValve_inc_factor_4[3] = { -1.2f,1.2f,-14.5f };
bool g_scene2_1_bInletValveIncFlag_4 = true;

GLfloat outletValve_inc_factor_4[3] = { 1.2f,1.2f,-14.5f };
bool gbOutletValveIncFlag_4 = false;

bool g_scene2_1_bSyncFlag_Inlet_4 = true;
short g_scene2_1_piston_down_count_4 = 1;
bool g_scene2_1_bSyncFlag_Outlet_4 = true;
/*** View Port 4 End   ***/
/// Cheating Board Start

GLuint g_scene2_1_VertexShaderObject_Rectangle;
GLuint g_scene2_1_FragmentShaderObject_Rectangle;
GLuint g_scene2_1_ShaderProgramObject_Rectangle;

GLuint g_scene2_1_VertexArrayObject_Rectangle;

GLuint g_scene2_1_VertexBufferObject_Rectangle_Pos;
GLuint g_scene2_1_VertexBufferObject_Rectangle_Color;

GLuint g_scene2_1_Uniform_ModelMatrix, g_scene2_1_Uniform_ViewMatrix, g_scene2_1_Uniform_ProjectionMatrix;

// Perspective Matrix will be same as prevoiusly defined
/*** View Port 1 Start ***/
GLfloat g_scene2_1_RectangleVertices_1[] =
{
	0.85f,0.3f,-14.5f,  // Using 0.3 to eliminate the jerky looking motion 
	-0.85f,0.3f,-14.5f, // at the end 
	-0.85f,0.2f,-14.5f,
	0.85f,0.2f,-14.5f
};

GLfloat g_scene2_1_RectangleColors_1[] =
{
	0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f
};

bool g_scene2_1_IncrementbRect_1 = true;
unsigned short g_scene2_1_rect_color_states_1 = 0;
/*** View Port 1 End  ***/

/*** View Port 2 Start ***/
GLfloat g_scene2_1_RectangleVertices_2[] =
{
	0.85f,0.3f,-14.5f,  // Using 0.3 to eliminate the jerky looking motion 
	-0.85f,0.3f,-14.5f, // at the end 
	-0.85f,-2.5f,-14.5f,
	0.85f,-2.5f,-14.5f
};

GLfloat g_scene2_1_RectangleColors_2[] =
{
	0.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f
};

bool g_scene2_1_bIncrementbRect_2 = true;
unsigned short rect_color_states_2 = 1;
/*** View Port 2 End   ***/

/*** View Port 3 Start ***/
GLfloat g_scene2_1_RectangleVertices_3[] =
{
	0.85f,0.3f,-14.5f,  // Using 0.3 to eliminate the jerky looking motion 
	-0.85f,0.3f,-14.5f, // at the end 
	-0.85f,-2.5f,-14.5f,
	0.85f,-2.5f,-14.5f
};
// 0.72f, 0.21f, 0.04f
GLfloat g_scene2_1_RectangleColors_3[] =
{
	0.72f,0.21f,0.04f,
	0.72f,0.21f,0.04f,
	0.72f,0.21f,0.04f,
	0.72f,0.21f,0.04f
};

bool g_scene2_1_bIncrementbRect_3 = true;
unsigned short rect_color_states_3 = 2;
/*** View Port 3 End   ***/

/*** View Port 4 Start ***/
GLfloat g_scene2_1_RectangleVertices_4[] =
{
	0.85f,0.3f,-14.5f,  // Using 0.3 to eliminate the jerky looking motion 
	-0.85f,0.3f,-14.5f, // at the end 
	-0.85f,0.2f,-14.5f,
	0.85f,0.2f,-14.5f
};

GLfloat g_scene2_1_RectangleColors_4[] =
{
	0.74f,0.22f,0.03f,
	0.74f,0.22f,0.03f,
	0.74f,0.22f,0.03f,
	0.74f,0.22f,0.03f
};

bool g_scene2_1_bIncrementbRect_4 = true;
unsigned short rect_color_states_4 = 1;
/*** View Port 4 End   ***/
/// Cheating Board End

/// Add Particle Start

/// Inlet Start
static GLint g_scene2_1_arrayWidth_inlet, g_scene2_1_arrayHeight_inlet;
static GLfloat *g_scene2_1_pfVerts_inlet = NULL;
static GLfloat *g_scene2_1_pfColors_inlet = NULL;
static GLfloat *g_scene2_1_pfVelocities_inlet = NULL;
static GLfloat *g_scene2_1_pfStartTimes_inlet = NULL;
static GLfloat g_scene2_1_pfParticleTime_inlet = 0.0f;
GLint g_scene2_1_Location_inlet = 0;

GLuint g_scene2_1_VertexShaderObject_Particle_Inlet;
GLuint g_scene2_1_FragmentShaderObject_Particle_Inlet;
GLuint g_scene2_1_ShaderProgramObject_Particle_Inlet;

GLuint g_scene2_1_VertexArrayObject_Particle_Inlet;

GLuint g_scene2_1_VertexBufferObject_ParticlePosition_Inlet;
GLuint g_scene2_1_VertexBufferObject_ParticleColor_Inlet;
GLuint g_scene2_1_VertexBufferObject_ParticleVelocity_Inlet;
GLuint g_scene2_1_VertexBufferObject_ParticleStartTime_Inlet;

//GLuint g_Uniform_ModelViewProjection_Particle;
GLuint g_scene2_1_Uniform_ModelMatrix_Particle_Inlet, g_scene2_1_Uniform_ViewMatrix_Particle_Inlet, g_scene2_1_Uniform_ProjectionMatrix_Particle_Inlet;
glm::mat4 g_scene2_1_PerspectiveProjectionMatrix_Particle;

bool g_scene2_1_bShow_Inlet_Particle = true;
/// Inlet End

/// Outlet Start
static GLint g_scene2_1_arrayWidth_Outlet, g_scene2_1_arrayHeight_Outlet;
static GLfloat *g_scene2_1_pfVerts_Outlet = NULL;
static GLfloat *g_scene2_1_pfColors_Outlet = NULL;
static GLfloat *g_scene2_1_pfVelocities_Outlet = NULL;
static GLfloat *g_scene2_1_pfStartTimes_Outlet = NULL;
static GLfloat g_scene2_1_pfParticleTime_Outlet = 0.0f;
GLint g_scene2_1_Location_Outlet = 0;

GLuint g_scene2_1_VertexShaderObject_Particle_Outlet;
GLuint g_scene2_1_FragmentShaderObject_Particle_Outlet;
GLuint g_scene2_1_ShaderProgramObject_Particle_Outlet;

GLuint g_scene2_1_VertexArrayObject_Particle_Outlet;

GLuint g_scene2_1_VertexBufferObject_ParticlePosition_Outlet;
GLuint g_scene2_1_VertexBufferObject_ParticleColor_Outlet;
GLuint g_scene2_1_VertexBufferObject_ParticleVelocity_Outlet;
GLuint g_scene2_1_VertexBufferObject_ParticleStartTime_Outlet;

GLuint g_scene2_1_Uniform_ModelMatrix_Particle_Outlet, g_scene2_1_Uniform_ViewMatrix_Particle_Outlet, g_scene2_1_Uniform_ProjectionMatrix_Particle_Outlet;

bool g_scene2_1_bShow_Outlet_Particle = false;

/// Outlet End

/// Engine Spark Start
static GLint g_scene2_1_arrayWidth_Particle_Spark, g_scene2_1_arrayHeight_Particle_Spark;
static GLfloat *g_scene2_1_pfVerts_Particle_Spark = NULL;
static GLfloat *g_scene2_1_pfColors_Particle_Spark = NULL;
static GLfloat *g_scene2_1_pfVelocities_Particle_Spark = NULL;
static GLfloat *g_scene2_1_pfStartTimes_Particle_Spark = NULL;
static GLfloat g_scene2_1_pfParticleTime_Particle_Spark = 0.0f;
static const GLfloat g_scene2_1_fDeviationRadius = 0.4f;
GLint g_scene2_1_Location_Particle_Spark = 0;

GLuint g_scene2_1_VertexShaderObject_Spark;
GLuint g_scene2_1_FragmentShaderObject_Spark;
GLuint g_scene2_1_ShaderProgramObject_Spark;

GLuint g_scene2_1_VertexArrayObject_Particle_Spark;

GLuint g_scene2_1_VertexBufferObject_ParticlePosition_Spark;
GLuint g_scene2_1_VertexBufferObject_ParticleColor_Spark;
GLuint g_scene2_1_VertexBufferObject_ParticleVelocity_Spark;
GLuint g_scene2_1_VertexBufferObject_ParticleStartTime_Spark;

GLuint g_scene2_1_Uniform_ModelMatrix_Particle_Spark, g_scene2_1_Uniform_ViewMatrix_Particle_Spark, g_scene2_1_Uniform_ProjectionMatrix_Particle_Spark;

bool g_scene2_1_bShow_Spark_Particle = false;
/// Engine Spark End
GLfloat g_scene2_1_ShowScene_One = 0.0f;
/// Add Particle End


/// Adjust Viewport Start
GLint g_scene2_1_iPresentViewPort_1 = -500;
GLint g_scene2_1_iPresentViewPort_2 = -200;
GLint g_scene2_1_iPresentViewPort_3 = 100;
GLint g_scene2_1_iPresentViewPort_4 = 400;
/// Adjust Viewport End

/// Show Text Start
TextData tdInletValveText;
TextData tdOutletletValveText;
TextData tdMainBoreText;
TextData tdPistonText;
TextData tdSparkPlugText;

TextData tdIntakeText;
TextData tdExhaustText;
TextData tdCompressionText;
TextData tdPowerText;

FontRenderer *frFontRenderer_InletletValveText = NULL;
FontRenderer *frFontRenderer_OutletletValveText = NULL;
FontRenderer *frFontRenderer_MainBoreText = NULL;
FontRenderer *frFontRenderer_PistonText = NULL;
FontRenderer *frFontRenderer_SparkPlugText = NULL;

FontRenderer *frFontRenderer_IntakeText = NULL;
FontRenderer *frFontRenderer_CompressionText = NULL;
FontRenderer *frFontRenderer_PowerText = NULL;
FontRenderer *frFontRenderer_ExhaustText = NULL;

short g_scene2_1_iPresentStroke_1 = 0;

/// Manage Lines Start
GLfloat g_scene2_1_InletLineVertices_1[] =
{
	// -4.5f, 2.0f, -14.5f
	-4.5f, 1.9f, -14.5f,
	-1.8f,1.9f,-14.5f,
	-1.8f, 1.9f, -14.5f,
	-0.85f,1.0f, -14.5f
};

GLfloat g_scene2_1_SparkPlugLineVertices_1[] =
{
	-1.2f, 2.9f, -14.5f,
	1.2f, 2.9f, -14.5f,
	0.0f, 2.9f, -14.5f,
	0.0f, 2.0f, -14.5f
};

GLfloat g_scene2_1_OutletLineVertices_1[] =
{
	// 2.3f, 2.0f, -14.5f
	2.3f, 1.9f, -14.5f,
	5.4f, 1.9f, -14.5f,
	2.3f, 1.9f, -14.5f,
	1.2f, 1.2f, -14.5f
};

GLfloat g_scene2_1_PistonLineVertices_1[] =
{
	//-4.0f, -3.0f, -14.5f
	-4.0f, -3.1f, -14.5f,
	-1.0f, -3.1f, -14.5f,
	-1.0f, -3.1f, -14.5f,
	0.0f, -3.1f, -14.5f
};

GLuint g_scene2_Line_VertexShaderObject;
GLuint g_scene2_Line_FragmentShaderObject;
GLuint g_scene2_Line_ShaderProgramObject;

GLuint g_scene2_Line_VertexArrayObject;

GLuint g_scene2_Line_VertexBufferObject_Position;

GLuint g_scene2_1_Uniform_ModelMatrix_Line, g_scene2_1_Uniform_ViewMatrix_Line, g_scene2_1_Uniform_ProjectionMatrix_Line;
/// Manage Lines End
/// Show Text End

/// Audio Start
//AudioManager *Scene1_audioManager = NULL;
SoundSource  *g_pSS_Scene2_SoundSource = NULL;
ALuint g_Scene2_AudioBuffer_LoopSound = 0;

/// Audio End

void Scene2_InitializeAudio(void)
{
	//Scene1_audioManager = new AudioManager();
	//ALboolean bAudioManagerInit = Scene1_audioManager->initialize();

	//if (bAudioManagerInit == AL_TRUE)
	//{
		Scene1_audioManager->setListenerPosition(0.0f, 0.0f, 0.0f);
		Scene1_audioManager->setListenerVelocity(0.0f, 0.0f, 0.0f);

		// Load Audio File
		alGenBuffers(1, &g_Scene2_AudioBuffer_LoopSound);

		ALenum error = alGetError();

		if (error != AL_NO_ERROR)
		{
			logError("Not able to create point light audio buffer, error code: %d\n", error);
		}

		error = AL_NO_ERROR;

		ALboolean waveDataLoaded = Scene1_audioManager->loadWaveAudio("RTR_resources/audio/Castamere.wav", g_Scene2_AudioBuffer_LoopSound);

		if (!waveDataLoaded)
		{
			logError("Not able to point light audio file.\n");
		}

		g_pSS_Scene2_SoundSource = new SoundSource();
		g_pSS_Scene2_SoundSource->setPosition3f(SCENE2_1_MODEL_X_TRANSLATE, SCENE2_1_MODEL_Y_TRANSLATE, SCENE2_1_MODEL_Z_TRANSLATE);

	//}
	//else
	//{
		//logError("Not able to initialize audio manager Scene 2.\n");
	//}

}

void Scene2_Initialize(void)
{
	void resize(int, int);
	void Scene2_UnInitialize(int);
	void CreatePoints_Inlet(GLint iWidth, GLint iHeight);
	void CreatePoints_Outlet(GLint iWidth, GLint iHeight);
	void CreatePoints_ParticleSpark(GLint iWidth, GLint iHeight);
	void Scene2_InitializeAudio(void);


	//Vertex Shader
	g_scene2_1_VertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
		"#version 450 core" \
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
		"	if(u_lighting_enabled==1)" \
		"	{" \
		"		vec4 eye_coordinates = u_view_matrix*u_model_matrix*vPosition;" \
		"		transformed_normals = mat3(u_view_matrix*u_model_matrix)*vNormal;" \
		"		light_direction = vec3(u_light_position)-eye_coordinates.xyz;" \
		"		viewer_vector = -eye_coordinates.xyz;" \
		"	}" \
		"	gl_Position = u_projection_matrix*u_view_matrix*u_model_matrix*vPosition;" \
		"}";

	glShaderSource(g_scene2_1_VertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	glCompileShader(g_scene2_1_VertexShaderObject);
	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(g_scene2_1_VertexShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_1_VertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_1_VertexShaderObject, iInfoLogLength, &written, szInfoLog);
				//fprintf(gpFile, "Vertex Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				Scene2_UnInitialize(1);
				exit(0);
			}
		}
	}

	//Fragment Shader
	g_scene2_1_FragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 460 core" \
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
		"	vec3 phong_ads_color;" \
		"	if(u_lighting_enabled == 1)" \
		"	{" \
		"		vec3 normalized_transformed_normals = normalize(transformed_normals);" \
		"		vec3 normalized_light_direction = normalize(light_direction);" \
		"		vec3 normalized_viewer_vector = normalize(viewer_vector);" \
		"		vec3 ambient = u_La * u_Ka;" \
		"		float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);" \
		"		vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;" \
		"		vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);" \
		"		vec3 specular = u_Ls * u_Ks * pow(max(dot(reflection_vector,normalized_viewer_vector),0.0),u_material_shininess);" \
		"		phong_ads_color = ambient + diffuse + specular;" \
		"	}" \
		"	else" \
		"	{" \
		"		phong_ads_color = vec3(1.0f,1.0f,1.0f);" \
		"	}" \
		"	FragColor = vec4(phong_ads_color,1.0);" \
		"}";

	glShaderSource(g_scene2_1_FragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	glCompileShader(g_scene2_1_FragmentShaderObject);

	glGetShaderiv(g_scene2_1_FragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_1_FragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_1_FragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				//fprintf(gpFile, "Fragment Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				Scene2_UnInitialize(1);
				exit(0);
			}
		}
	}

	//Shader Program
	g_scene2_1_ShaderProgramObject = glCreateProgram();

	glAttachShader(g_scene2_1_ShaderProgramObject, g_scene2_1_VertexShaderObject);

	glAttachShader(g_scene2_1_ShaderProgramObject, g_scene2_1_FragmentShaderObject);

	glBindAttribLocation(g_scene2_1_ShaderProgramObject, FRAG_ATTRIBUTE_POSITION, "vPosition");

	glBindAttribLocation(g_scene2_1_ShaderProgramObject, FRAG_ATTRIBUTE_NORMAL, "vNormal");

	glLinkProgram(g_scene2_1_ShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;

	glGetProgramiv(g_scene2_1_ShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_scene2_1_ShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(g_scene2_1_ShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				//fprintf(gpFile, "Shader Program Link Log : %s\n", szInfoLog);
				free(szInfoLog);
				Scene2_UnInitialize(1);
				exit(0);
			}
		}
	}

	g_scene2_1_ModelMatrixUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_model_matrix");
	g_scene2_1_ViewMatrixUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_view_matrix");
	g_scene2_1_ProjectionMatrixUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_projection_matrix");

	gLKeyPressedUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_lighting_enabled");

	g_scene2_1_LaUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_La");
	g_scene2_1_LdUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_Ld");
	g_scene2_1_LsUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_Ls");

	gLightPositionUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_light_position");

	g_scene2_1_KaUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_Ka");
	g_scene2_1_KdUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_Kd");
	g_scene2_1_KsUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_Ks");

	g_scene2_1_MaterialShininessUniform = glGetUniformLocation(g_scene2_1_ShaderProgramObject, "u_material_shininess");

	// Piston Start
	//g_scene2_1_count_of_vertices_Piston = LoadMeshData("RTR_resources/models/Engine/Main_Piston.obj", gv_scene2_1_vertices_1, gv_scene2_2_textures_1, gv_scene2_2_normals_1);
	std::vector<Mesh_Data> Scene2_MD_Engine;
	char Scene2_chMtlPath[256];
	ZeroMemory((void*)&Scene2_chMtlPath, sizeof(Scene2_chMtlPath));
	LoadMeshData("RTR_resources/models/Engine/Main_Piston.obj", gv_scene2_1_vertices_1, gv_scene2_2_textures_1, gv_scene2_2_normals_1, Scene2_MD_Engine, Scene2_chMtlPath);
	g_scene2_1_count_of_vertices_Piston = gv_scene2_1_vertices_1.size();
	glGenVertexArrays(1, &g_scene2_1_Vao_Piston);
	glBindVertexArray(g_scene2_1_Vao_Piston);

	glGenBuffers(1, &g_scene2_1_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_Vbo_Position);
	glBufferData(GL_ARRAY_BUFFER, gv_scene2_1_vertices_1.size() * sizeof(float), &gv_scene2_1_vertices_1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_Vbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_Vbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, gv_scene2_2_normals_1.size() * sizeof(float), &gv_scene2_2_normals_1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	// Piston End
	gv_scene2_1_vertices_1.clear();
	gv_scene2_2_normals_1.clear();
	gv_scene2_1_vertices_1.clear();
	Scene2_MD_Engine.clear();
	ZeroMemory((void*)&Scene2_chMtlPath, sizeof(Scene2_chMtlPath));
	// Spark Plug Start
	//g_scene2_1_count_of_vertices_Spark_Plug = LoadMeshData("RTR_resources/models/Engine/Spark_Plug.obj", gv_scene2_1_vertices_1, gv_scene2_2_textures_1, gv_scene2_2_normals_1);
	LoadMeshData("RTR_resources/models/Engine/Spark_Plug.obj", gv_scene2_1_vertices_1, gv_scene2_2_textures_1, gv_scene2_2_normals_1, Scene2_MD_Engine, Scene2_chMtlPath);
	g_scene2_1_count_of_vertices_Spark_Plug = gv_scene2_1_vertices_1.size();
	glGenVertexArrays(1, &g_scene2_1_Vao_SparkPlug);
	glBindVertexArray(g_scene2_1_Vao_SparkPlug);

	glGenBuffers(1, &g_scene2_1_Vbo_Position_SparkPlug);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_Vbo_Position_SparkPlug);
	glBufferData(GL_ARRAY_BUFFER, gv_scene2_1_vertices_1.size() * sizeof(float), &gv_scene2_1_vertices_1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_Vbo_Normal_SparkPlug);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_Vbo_Normal_SparkPlug);
	glBufferData(GL_ARRAY_BUFFER, gv_scene2_2_normals_1.size() * sizeof(float), &gv_scene2_2_normals_1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	// Spark Plug End
	gv_scene2_1_vertices_1.clear();
	gv_scene2_2_normals_1.clear();
	gv_scene2_1_vertices_1.clear();
	ZeroMemory((void*)&Scene2_chMtlPath, sizeof(Scene2_chMtlPath));
	// Spark Bore Start
	//g_scene2_1_count_of_vertices_Bore = LoadMeshData("RTR_resources/models/Engine/Main_Bore.obj", gv_scene2_1_vertices_1, gv_scene2_2_textures_1, gv_scene2_2_normals_1);
	LoadMeshData("RTR_resources/models/Engine/Main_Bore.obj", gv_scene2_1_vertices_1, gv_scene2_2_textures_1, gv_scene2_2_normals_1, Scene2_MD_Engine, Scene2_chMtlPath);
	g_scene2_1_count_of_vertices_Bore = gv_scene2_1_vertices_1.size();
	glGenVertexArrays(1, &g_scene2_1_Vao_Bore);
	glBindVertexArray(g_scene2_1_Vao_Bore);

	glGenBuffers(1, &g_scene2_1_Vbo_Position_Bore);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_Vbo_Position_Bore);
	glBufferData(GL_ARRAY_BUFFER, gv_scene2_1_vertices_1.size() * sizeof(float), &gv_scene2_1_vertices_1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_Vbo_Normal_Bore);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_Vbo_Normal_Bore);
	glBufferData(GL_ARRAY_BUFFER, gv_scene2_2_normals_1.size() * sizeof(float), &gv_scene2_2_normals_1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	// Spark Bore End
	gv_scene2_1_vertices_1.clear();
	gv_scene2_2_normals_1.clear();
	gv_scene2_1_vertices_1.clear();
	ZeroMemory((void*)&Scene2_chMtlPath, sizeof(Scene2_chMtlPath));
	// Inlet Start
	//g_scene2_1_count_of_vertices_Inlet_Valve = LoadMeshData("RTR_resources/models/Engine/Main_Valve_Inlet.obj", gv_scene2_1_vertices_1, gv_scene2_2_textures_1, gv_scene2_2_normals_1);
	LoadMeshData("RTR_resources/models/Engine/Main_Valve_Inlet.obj", gv_scene2_1_vertices_1, gv_scene2_2_textures_1, gv_scene2_2_normals_1,Scene2_MD_Engine,Scene2_chMtlPath);
	g_scene2_1_count_of_vertices_Inlet_Valve = gv_scene2_1_vertices_1.size();
	glGenVertexArrays(1, &g_scene2_1_Vao_InletValve);
	glBindVertexArray(g_scene2_1_Vao_InletValve);

	glGenBuffers(1, &g_scene2_1_Vbo_Position_InletValve);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_Vbo_Position_InletValve);
	glBufferData(GL_ARRAY_BUFFER, gv_scene2_1_vertices_1.size() * sizeof(float), &gv_scene2_1_vertices_1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_Vbo_Normal_InletValve);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_Vbo_Normal_InletValve);
	glBufferData(GL_ARRAY_BUFFER, gv_scene2_2_normals_1.size() * sizeof(float), &gv_scene2_2_normals_1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	// Inlet End
	gv_scene2_1_vertices_1.clear();
	gv_scene2_2_normals_1.clear();
	gv_scene2_1_vertices_1.clear();
	ZeroMemory((void*)&Scene2_chMtlPath, sizeof(Scene2_chMtlPath));
	/* // Outlet Start
	g_scene2_1_count_of_vertices_Outlet_Valve = LoadMeshData("Main_Valve_Outlet.obj", gv_scene2_1_vertices_1, gv_scene2_1_vertices_1, gv_scene2_2_normals_1);
	glGenVertexArrays(1, &g_scene2_1_Vao_OutletValve);
	glBindVertexArray(g_scene2_1_Vao_OutletValve);

	glGenBuffers(1, &g_scene2_1_Vbo_Position_OutletValve);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_Vbo_Position_OutletValve);
	glBufferData(GL_ARRAY_BUFFER, gv_scene2_1_vertices_1.size() * sizeof(float), &gv_scene2_1_vertices_1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_Vbo_Normal_OutletValve);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_Vbo_Normal_OutletValve);
	glBufferData(GL_ARRAY_BUFFER, gv_scene2_2_normals_1.size() * sizeof(float), &gv_scene2_2_normals_1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	// Outlet Start */

	gv_scene2_1_vertices_1.clear();
	gv_scene2_2_normals_1.clear();
	gv_scene2_1_vertices_1.clear();
	ZeroMemory((void*)&Scene2_chMtlPath, sizeof(Scene2_chMtlPath));
	// Config For Cheating Board Start

	//***** Vertex Shader *****
	//Create Shader
	g_scene2_1_VertexShaderObject_Rectangle = glCreateShader(GL_VERTEX_SHADER);

	// give source code to shader
	const GLchar *vertexShaderSourceCodeRect = "#version 460 core"	\
		"\n" \
		"in vec4 vPosition;"	\
		"in vec3 vColor;"	\
		"out vec3 out_Color;"	\
		"uniform mat4 u_model_matrix;"	\
		"uniform mat4 u_view_matrix;"	\
		"uniform mat4 u_projection_matrix;"	\
		"void main (void)"	\
		"{"	\
		"	gl_Position = (u_projection_matrix * u_view_matrix * u_model_matrix) * vPosition;"	\
		"	out_Color = vColor;"\
		"}";
	glShaderSource(g_scene2_1_VertexShaderObject_Rectangle, 1, (const GLchar**)&vertexShaderSourceCodeRect, NULL);

	// Compile Source Code
	glCompileShader(g_scene2_1_VertexShaderObject_Rectangle);
	iInfoLogLength = 0;
	GLint iShaderCompileStatus = 0;
	szInfoLog = NULL;
	glGetShaderiv(g_scene2_1_VertexShaderObject_Rectangle, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_1_VertexShaderObject_Rectangle, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_1_VertexShaderObject_Rectangle, GL_INFO_LOG_LENGTH, &written, szInfoLog);
				//(gpFile, "Error : Vertex Shader Compilation Log : %s \n", szInfoLog);
				free(szInfoLog);
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}

		}

	}

	//***** Fragment Shader *****
	g_scene2_1_FragmentShaderObject_Rectangle = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCodeRect = "#version 460 core"	\
		"\n"	\
		"out vec4 FragColor;"	\
		"in vec3 out_Color;"	\
		"void main (void)" \
		"{"	\
		"	FragColor = vec4(out_Color,0.4f);"	\
		"}";
	glShaderSource(g_scene2_1_FragmentShaderObject_Rectangle, 1, (const GLchar **)&fragmentShaderSourceCodeRect, NULL);

	// Compile Source Code
	glCompileShader(g_scene2_1_FragmentShaderObject_Rectangle);
	iInfoLogLength = 0;
	iShaderCompileStatus = 0;
	szInfoLog = NULL;
	glGetShaderiv(g_scene2_1_FragmentShaderObject_Rectangle, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_1_FragmentShaderObject_Rectangle, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength>0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_1_FragmentShaderObject_Rectangle, GL_INFO_LOG_LENGTH, &written, szInfoLog);
				//fprintf_s(gpFile, "Error : Fragment Shader Compilation Log : %s \n", szInfoLog);
				free(szInfoLog);
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	//***** Shader Program *****
	// Create
	g_scene2_1_ShaderProgramObject_Rectangle = glCreateProgram();
	// Attach Vertex Shader
	glAttachShader(g_scene2_1_ShaderProgramObject_Rectangle, g_scene2_1_VertexShaderObject_Rectangle);
	// Attach Fragment Shader
	glAttachShader(g_scene2_1_ShaderProgramObject_Rectangle, g_scene2_1_FragmentShaderObject_Rectangle);
	// pre-link Program object with Vertex Sahder position attribute
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Rectangle, FRAG_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Rectangle, FRAG_ATTRIBUTE_COLOR, "vColor");


	// link Shader 
	glLinkProgram(g_scene2_1_ShaderProgramObject_Rectangle);

	iShaderProgramLinkStatus = 0;
	glGetProgramiv(g_scene2_1_ShaderProgramObject_Rectangle, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	szInfoLog = NULL;
	iInfoLogLength = 0;
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_scene2_1_ShaderProgramObject_Rectangle, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_1_ShaderProgramObject_Rectangle, GL_INFO_LOG_LENGTH, &written, szInfoLog);
				//fprintf_s(gpFile, "Error : Shader Program Link Log : %s \n", szInfoLog);
				free(szInfoLog);
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	g_scene2_1_Uniform_ModelMatrix = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Rectangle, "u_model_matrix");
	g_scene2_1_Uniform_ViewMatrix = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Rectangle, "u_view_matrix");
	g_scene2_1_Uniform_ProjectionMatrix = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Rectangle, "u_projection_matrix");

	// **** Verttices, Colors, Shader Attribs, Vbo, Vao Initializations ****

	//// Rectangle Section Start

	glGenVertexArrays(1, &g_scene2_1_VertexArrayObject_Rectangle);
	glBindVertexArray(g_scene2_1_VertexArrayObject_Rectangle);

	//vbo creation and binding for Rectangle
	glGenBuffers(1, &g_scene2_1_VertexBufferObject_Rectangle_Pos);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_Rectangle_Pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_RectangleVertices_1), g_scene2_1_RectangleVertices_1, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_Rectangle_Color);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_Rectangle_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_RectangleColors_1), g_scene2_1_RectangleColors_1, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);

	//// Rectangle Section End 

	// Config For Cheating Board End

	/// Config For Particles Start

	// Inlet Particle Engine Start
	g_scene2_1_VertexShaderObject_Particle_Inlet = glCreateShader(GL_VERTEX_SHADER);

	// VS Source Code
	const GLchar* chVertexShaderSourceCode_Inlet = "#version 460 core"	\
		"\n"	\
		"uniform float Time;"	\
		"uniform mat4 u_model_matrix;"	\
		"uniform mat4 u_view_matrix;"	\
		"uniform mat4 u_projection_matrix;"	\
		"in vec4 vPosition;"	\
		"in vec4 vColor;"	\
		"in vec3 Velocity;"	\
		"in float StartTime;"	\
		"out vec4 out_Color;"	\
		"out float t_out;"
		"void main(void)"	\
		"{"	\
		"	vec4 vert;"	\
		"	float t=Time-StartTime;"	\
		"	if(t>=0.0)"	\
		"	{"	\
		"		vert = vPosition-vec4(Velocity*t,0.0);"	\
		"		vert.y *= -4.9f * t * t * t ;"	\
		"		out_Color = vColor;"	\
		"	}"	\
		"	else"	\
		"	{"	\
		"		vert = vPosition;"	\
		"		out_Color = vec4(0.0,1.0,0.0,1.0);"	\
		"	}"	\
		"	gl_Position = (u_projection_matrix * u_view_matrix * u_model_matrix) * vert;"	\
		"	t_out = t ;"
		"}";

	glShaderSource(g_scene2_1_VertexShaderObject_Particle_Inlet, 1, (const GLchar**)&chVertexShaderSourceCode_Inlet, NULL);
	// Compile VS
	glCompileShader(g_scene2_1_VertexShaderObject_Particle_Inlet);
	iInfoLogLength = 0;
	GLint iCompileStatus = 0;
	char *chErrorMessage = NULL;
	glGetShaderiv(g_scene2_1_VertexShaderObject_Particle_Inlet, GL_COMPILE_STATUS, &iCompileStatus);
	if (iCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_1_VertexShaderObject_Particle_Inlet, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			chErrorMessage = (char*)malloc(iInfoLogLength);
			if (chErrorMessage != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_1_VertexShaderObject_Particle_Inlet, GL_INFO_LOG_LENGTH, &written, chErrorMessage);
				//fprintf_s(gpFile, "Vertex Shader Error : %s \n", chErrorMessage);
				free(chErrorMessage); chErrorMessage = NULL;
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}


	//FS Object
	g_scene2_1_FragmentShaderObject_Particle_Inlet = glCreateShader(GL_FRAGMENT_SHADER);
	// FS Source Code
	const GLchar* chFragmentShaderSourceCode_Inlet = "#version 460 core"	\
		"\n"	\
		"in vec4 out_Color;"	\
		"in  float t_out;"
		"out vec4 FragColor;"	\
		"void main(void)"	\
		"{"	\
		"	if( t_out > 0.55f )"	\
		"	{"	\
		"		discard;"	\
		"	}"	\
		"	FragColor = vec4(out_Color.r, out_Color.g, out_Color.b, 0.4f) ;"	\
		"}";
	glShaderSource(g_scene2_1_FragmentShaderObject_Particle_Inlet, 1, (const GLchar**)&chFragmentShaderSourceCode_Inlet, NULL);

	iInfoLogLength = 0;
	iCompileStatus = 0;
	chErrorMessage = NULL;

	glCompileShader(g_scene2_1_FragmentShaderObject_Particle_Inlet);
	glGetShaderiv(g_scene2_1_FragmentShaderObject_Particle_Inlet, GL_COMPILE_STATUS, &iCompileStatus);
	if (iCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_1_FragmentShaderObject_Particle_Inlet, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength>0)
		{
			GLsizei written;
			chErrorMessage = (char*)malloc(iInfoLogLength);
			glGetShaderInfoLog(g_scene2_1_FragmentShaderObject_Particle_Inlet, GL_INFO_LOG_LENGTH, &written, chErrorMessage);
			//fprintf_s(gpFile, "Fragment Shader Error : %s \n ", chErrorMessage);
			free(chErrorMessage); chErrorMessage = NULL;
			Scene2_UnInitialize(EXIT_FAILURE);
			exit(EXIT_FAILURE);
		}
	}

	// ** Shader Program Object **
	g_scene2_1_ShaderProgramObject_Particle_Inlet = glCreateProgram();
	// Attach all Shaders
	glAttachShader(g_scene2_1_ShaderProgramObject_Particle_Inlet, g_scene2_1_VertexShaderObject_Particle_Inlet);
	glAttachShader(g_scene2_1_ShaderProgramObject_Particle_Inlet, g_scene2_1_FragmentShaderObject_Particle_Inlet);
	// Bind Attributes in Shader

	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Particle_Inlet, FRAG_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Particle_Inlet, FRAG_ATTRIBUTE_COLOR, "vColor");
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Particle_Inlet, FRAG_VELOCITY_ARRAY, "Velocity");
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Particle_Inlet, FRAG_START_TIME_ARRAY, "StartTime");
	//Link Shader
	glLinkProgram(g_scene2_1_ShaderProgramObject_Particle_Inlet);

	GLint iLinkStatus = 0;
	iInfoLogLength = 0;
	chErrorMessage = NULL;
	glGetProgramiv(g_scene2_1_ShaderProgramObject_Particle_Inlet, GL_LINK_STATUS, &iLinkStatus);

	if (iLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_scene2_1_ShaderProgramObject_Particle_Inlet, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength>0)
		{
			GLsizei written;
			chErrorMessage = (char*)malloc(iInfoLogLength);
			if (chErrorMessage != NULL)
			{
				glGetProgramInfoLog(g_scene2_1_ShaderProgramObject_Particle_Inlet, GL_INFO_LOG_LENGTH, &written, chErrorMessage);
				//fprintf_s(gpFile, "Error In ShaderProgram: %s \n", chErrorMessage);
				free(chErrorMessage); chErrorMessage = NULL;
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	// Set Model View Projection Matrix
	//g_Uniform_ModelViewProjection_Particle = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Particle_Inlet, "u_mvp_matrix");

	g_scene2_1_Uniform_ModelMatrix_Particle_Inlet = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Particle_Inlet, "u_model_matrix");
	g_scene2_1_Uniform_ViewMatrix_Particle_Inlet = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Particle_Inlet, "u_view_matrix");
	g_scene2_1_Uniform_ProjectionMatrix_Particle_Inlet = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Particle_Inlet, "u_projection_matrix");
	g_scene2_1_Location_inlet = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Particle_Inlet, "Time");

	// ***** Begin : All Vertices, Normals, Texture amd Etc data/Bindings *****
	//CreatePoints_Inlet(150, 150);
	CreatePoints_Inlet(1000, 1000);
	// ***** End : All Vertices, Normals, Texture amd Etc data/Bindings *****

	glGenVertexArrays(1, &g_scene2_1_VertexArrayObject_Particle_Inlet);
	glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Inlet);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticlePosition_Inlet);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticlePosition_Inlet);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfVerts_inlet, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticleColor_Inlet);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticleColor_Inlet);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfColors_inlet, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticleVelocity_Inlet);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticleVelocity_Inlet);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfVelocities_inlet, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_VELOCITY_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_VELOCITY_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticleStartTime_Inlet);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticleStartTime_Inlet);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfStartTimes_inlet, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_START_TIME_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_START_TIME_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// Inlet Particle Engine End

	// Outlet Particle Engine Start

	/**** Begin : All Shaders and Data ****/
	g_scene2_1_VertexShaderObject_Particle_Outlet = glCreateShader(GL_VERTEX_SHADER);

	// VS Source Code
	const GLchar *chVertexShaderSourceCode_Outlet =
		"#version 460 core"	\
		"\n"	\
		"uniform float Time;"	\
		"uniform mat4 u_model_matrix;"	\
		"uniform mat4 u_view_matrix;"	\
		"uniform mat4 u_projection_matrix;"	\
		"in vec4 vPosition;"\
		"in vec4 vColor;"\
		"in vec3 Velocity;"	\
		"in float StartTime;"	\
		"out vec4 out_Color;"\
		"out float t_out;"\
		"void main(void)"	\
		"{"	\
		"	vec4 vert;"	\
		"	float t=Time-StartTime;"	\
		"	if(t>=0.0f)"	\
		"	{"	\
		"		vert = vPosition + vec4(Velocity*t,0.0);"	\
		"		vert.y += 4.8f * t * t ;"	\
		"		vert.x *=  vert.y * vert.y ;"	\
		"		out_Color = vColor;"	\
		"	}"	\
		"	else"	\
		"	{"	\
		"		vert = vPosition;"	\
		"		out_Color = vec4(0.0,1.0,0.0,1.0);"	\
		"	}"
		"	gl_Position = (u_projection_matrix * u_view_matrix * u_model_matrix) * vert;"	\
		"	t_out = t ;"	\
		"}";

	glShaderSource(g_scene2_1_VertexShaderObject_Particle_Outlet, 1, (const GLchar **)&chVertexShaderSourceCode_Outlet, NULL);
	// Compile VS
	glCompileShader(g_scene2_1_VertexShaderObject_Particle_Outlet);
	iInfoLogLength = 0;
	iCompileStatus = 0;
	chErrorMessage = NULL;
	glGetShaderiv(g_scene2_1_VertexShaderObject_Particle_Outlet, GL_COMPILE_STATUS, &iCompileStatus);
	if (iCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_1_VertexShaderObject_Particle_Outlet, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			chErrorMessage = (char *)malloc(iInfoLogLength);
			if (chErrorMessage != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_1_VertexShaderObject_Particle_Outlet, GL_INFO_LOG_LENGTH, &written, chErrorMessage);
				//fprintf_s(gpFile, "Vertex Shader Error : %s \n", chErrorMessage);
				free(chErrorMessage);
				chErrorMessage = NULL;
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	//FS Object
	g_scene2_1_FragmentShaderObject_Particle_Outlet = glCreateShader(GL_FRAGMENT_SHADER);
	// FS Source Code
	const GLchar *chFragmentShaderSourceCode_Outlet =
		"#version 460 core"	\
		"\n"	\
		"in vec4 out_Color;"	\
		"in  float t_out;"	\
		"out vec4 FragColor;"	\
		"void main(void)"	\
		"{"	\
		"	if( t_out > 0.35f )"	\
		"	{"	\
		"		discard;"	\
		"	}"	\
		"	FragColor = vec4(out_Color.r, out_Color.g, out_Color.b, 0.4f) ;"	\
		"}";
	glShaderSource(g_scene2_1_FragmentShaderObject_Particle_Outlet, 1, (const GLchar **)&chFragmentShaderSourceCode_Outlet, NULL);

	iInfoLogLength = 0;
	iCompileStatus = 0;
	chErrorMessage = NULL;

	glCompileShader(g_scene2_1_FragmentShaderObject_Particle_Outlet);
	glGetShaderiv(g_scene2_1_FragmentShaderObject_Particle_Outlet, GL_COMPILE_STATUS, &iCompileStatus);
	if (iCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_1_FragmentShaderObject_Particle_Outlet, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			GLsizei written;
			chErrorMessage = (char *)malloc(iInfoLogLength);
			glGetShaderInfoLog(g_scene2_1_FragmentShaderObject_Particle_Outlet, GL_INFO_LOG_LENGTH, &written, chErrorMessage);
			//fprintf_s(gpFile, "Fragment Shader Error : %s \n ", chErrorMessage);
			free(chErrorMessage);
			chErrorMessage = NULL;
			Scene2_UnInitialize(EXIT_FAILURE);
			exit(EXIT_FAILURE);
		}
	}

	// ** Shader Program Object **
	g_scene2_1_ShaderProgramObject_Particle_Outlet = glCreateProgram();
	// Attach all Shaders
	glAttachShader(g_scene2_1_ShaderProgramObject_Particle_Outlet, g_scene2_1_VertexShaderObject_Particle_Outlet);
	glAttachShader(g_scene2_1_ShaderProgramObject_Particle_Outlet, g_scene2_1_FragmentShaderObject_Particle_Outlet);
	// Bind Attributes in Shader

	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Particle_Outlet, FRAG_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Particle_Outlet, FRAG_ATTRIBUTE_COLOR, "vColor");
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Particle_Outlet, FRAG_VELOCITY_ARRAY, "Velocity");
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Particle_Outlet, FRAG_START_TIME_ARRAY, "StartTime");
	//Link Shader
	glLinkProgram(g_scene2_1_ShaderProgramObject_Particle_Outlet);

	iLinkStatus = 0;
	iInfoLogLength = 0;
	chErrorMessage = NULL;
	glGetProgramiv(g_scene2_1_ShaderProgramObject_Particle_Outlet, GL_LINK_STATUS, &iLinkStatus);

	if (iLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_scene2_1_ShaderProgramObject_Particle_Outlet, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			GLsizei written;
			chErrorMessage = (char *)malloc(iInfoLogLength);
			if (chErrorMessage != NULL)
			{
				glGetProgramInfoLog(g_scene2_1_ShaderProgramObject_Particle_Outlet, GL_INFO_LOG_LENGTH, &written, chErrorMessage);
				//fprintf_s(gpFile, "Error In ShaderProgram: %s \n", chErrorMessage);
				free(chErrorMessage);
				chErrorMessage = NULL;
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	// Set Model View Projection Matrix
	g_scene2_1_Uniform_ModelMatrix_Particle_Outlet = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Particle_Outlet, "u_model_matrix");
	g_scene2_1_Uniform_ViewMatrix_Particle_Outlet = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Particle_Outlet, "u_view_matrix");
	g_scene2_1_Uniform_ProjectionMatrix_Particle_Outlet = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Particle_Outlet, "u_projection_matrix");
	g_scene2_1_Location_Outlet = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Particle_Outlet, "Time");

	// ***** Begin : All Vertices, Normals, Texture amd Etc data/Bindings *****
	CreatePoints_Outlet(250, 250);
	// ***** End : All Vertices, Normals, Texture amd Etc data/Bindings *****

	glGenVertexArrays(1, &g_scene2_1_VertexArrayObject_Particle_Outlet);
	glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Outlet);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticlePosition_Outlet);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticlePosition_Outlet);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfVerts_Outlet, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticleColor_Outlet);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticleColor_Outlet);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfColors_Outlet, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticleVelocity_Outlet);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticleVelocity_Outlet);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfVelocities_Outlet, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_VELOCITY_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_VELOCITY_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticleStartTime_Outlet);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticleStartTime_Outlet);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfStartTimes_Outlet, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_START_TIME_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_START_TIME_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/**** End : All Shaders and Data ****/
	// Outlet Particle Engine End

	// Spark Particle Engine Start
	/**** Begin : All Shaders and Data ****/
	g_scene2_1_VertexShaderObject_Spark = glCreateShader(GL_VERTEX_SHADER);

	// VS Source Code
	const GLchar *chVertexShaderSourceCode_Spark =
		"#version 460 core"	\
		"\n"	\
		"uniform float Time;"	\
		"uniform mat4 u_model_matrix;"	\
		"uniform mat4 u_view_matrix;"	\
		"uniform mat4 u_projection_matrix;"	\
		"in vec4 vPosition;"	\
		"in vec4 vColor;"	\
		"in vec3 Velocity;"		\
		"in float StartTime;"	\
		"out vec4 out_Color;"	\
		"out float t_out;"	\
		"void main(void)"	\
		"{"
		"	vec4 vert;"
		"	float t=Time-StartTime;"
		"	if(t>=0.0f)"
		"	{"
		"		vert = vPosition - vec4(Velocity*t,0.0);"
		"		vert.y  -= (t * 0.8f) ;"
		"		out_Color = vColor;"
		"	}"
		"	else"
		"	{"
		"		vert = vPosition;"
		"		out_Color = vec4(0.0,1.0,0.0,1.0);"
		"	}"
		"	gl_Position = (u_projection_matrix * u_view_matrix * u_model_matrix) * vert;"
		"	t_out = t ;"
		"}";;

	glShaderSource(g_scene2_1_VertexShaderObject_Spark, 1, (const GLchar **)&chVertexShaderSourceCode_Spark, NULL);
	// Compile VS
	glCompileShader(g_scene2_1_VertexShaderObject_Spark);
	iInfoLogLength = 0;
	iCompileStatus = 0;
	chErrorMessage = NULL;
	glGetShaderiv(g_scene2_1_VertexShaderObject_Spark, GL_COMPILE_STATUS, &iCompileStatus);
	if (iCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_1_VertexShaderObject_Spark, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			chErrorMessage = (char *)malloc(iInfoLogLength);
			if (chErrorMessage != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_1_VertexShaderObject_Spark, GL_INFO_LOG_LENGTH, &written, chErrorMessage);
				//fprintf_s(gpFile, "Spark Vertex Shader Error : %s \n", chErrorMessage);
				free(chErrorMessage);
				chErrorMessage = NULL;
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	//FS Object
	g_scene2_1_FragmentShaderObject_Spark = glCreateShader(GL_FRAGMENT_SHADER);
	// FS Source Code
	const GLchar *chFragmentShaderSourceCode_Spark =
		"#version 460 core"	\
		"\n"	\
		"in vec4 out_Color;"	\
		"in  float t_out;"	\
		"out vec4 FragColor;"	\
		"void main(void)"	\
		"{"	\
		"	if( (t_out > 0.6f) )"	\
		"	{"	\
		"		discard;"	\
		"	}"	\
		"	FragColor = vec4(out_Color.r, out_Color.g, out_Color.b, 0.3) ;"	\
		"}";
	glShaderSource(g_scene2_1_FragmentShaderObject_Spark, 1, (const GLchar **)&chFragmentShaderSourceCode_Spark, NULL);

	iInfoLogLength = 0;
	iCompileStatus = 0;
	chErrorMessage = NULL;

	glCompileShader(g_scene2_1_FragmentShaderObject_Spark);
	glGetShaderiv(g_scene2_1_FragmentShaderObject_Spark, GL_COMPILE_STATUS, &iCompileStatus);
	if (iCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_1_FragmentShaderObject_Spark, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			GLsizei written;
			chErrorMessage = (char *)malloc(iInfoLogLength);
			glGetShaderInfoLog(g_scene2_1_FragmentShaderObject_Spark, GL_INFO_LOG_LENGTH, &written, chErrorMessage);
			//fprintf_s(gpFile, "Spark Fragment Shader Error : %s \n ", chErrorMessage);
			free(chErrorMessage);
			chErrorMessage = NULL;
			Scene2_UnInitialize(EXIT_FAILURE);
			exit(EXIT_FAILURE);
		}
	}

	// ** Shader Program Object **
	g_scene2_1_ShaderProgramObject_Spark = glCreateProgram();
	// Attach all Shaders
	glAttachShader(g_scene2_1_ShaderProgramObject_Spark, g_scene2_1_VertexShaderObject_Spark);
	glAttachShader(g_scene2_1_ShaderProgramObject_Spark, g_scene2_1_FragmentShaderObject_Spark);
	// Bind Attributes in Shader

	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Spark, FRAG_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Spark, FRAG_ATTRIBUTE_COLOR, "vColor");
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Spark, FRAG_VELOCITY_ARRAY, "Velocity");
	glBindAttribLocation(g_scene2_1_ShaderProgramObject_Spark, FRAG_START_TIME_ARRAY, "StartTime");
	//Link Shader
	glLinkProgram(g_scene2_1_ShaderProgramObject_Spark);

	iLinkStatus = 0;
	iInfoLogLength = 0;
	chErrorMessage = NULL;
	glGetProgramiv(g_scene2_1_ShaderProgramObject_Spark, GL_LINK_STATUS, &iLinkStatus);

	if (iLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_scene2_1_ShaderProgramObject_Spark, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			GLsizei written;
			chErrorMessage = (char *)malloc(iInfoLogLength);
			if (chErrorMessage != NULL)
			{
				glGetProgramInfoLog(g_scene2_1_ShaderProgramObject_Spark, GL_INFO_LOG_LENGTH, &written, chErrorMessage);
				//fprintf_s(gpFile, "Error In Spark ShaderProgram: %s \n", chErrorMessage);
				free(chErrorMessage);
				chErrorMessage = NULL;
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	// Set Model View Projection Matrix
	g_scene2_1_Uniform_ModelMatrix_Particle_Spark = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Spark, "u_model_matrix");
	g_scene2_1_Uniform_ViewMatrix_Particle_Spark = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Spark, "u_view_matrix");
	g_scene2_1_Uniform_ProjectionMatrix_Particle_Spark = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Spark, "u_projection_matrix");
	g_scene2_1_Location_Particle_Spark = glGetUniformLocation(g_scene2_1_ShaderProgramObject_Spark, "Time");

	// ***** Begin : All Vertices, Normals, Texture amd Etc data/Bindings *****
	CreatePoints_ParticleSpark(100, 100);
	// ***** End : All Vertices, Normals, Texture amd Etc data/Bindings *****

	glGenVertexArrays(1, &g_scene2_1_VertexArrayObject_Particle_Spark);
	glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Spark);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticlePosition_Spark);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticlePosition_Spark);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfVerts_Particle_Spark, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticleColor_Spark);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticleColor_Spark);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfColors_Particle_Spark, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticleVelocity_Spark);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticleVelocity_Spark);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfVelocities_Particle_Spark, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_VELOCITY_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_VELOCITY_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_scene2_1_VertexBufferObject_ParticleStartTime_Spark);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_ParticleStartTime_Spark);
	glBufferData(GL_ARRAY_BUFFER, SCENE2_1_NUMBER_OF_PARTICLE * 3 * sizeof(float), g_scene2_1_pfStartTimes_Particle_Spark, GL_STATIC_DRAW);
	glVertexAttribPointer(FRAG_START_TIME_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_START_TIME_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/**** End : All Shaders and Data ****/
	// Spark Particle Engine Stop

	/// Config For Particles End

	/// Text Config Start
	frFontRenderer_InletletValveText = new FontRenderer("RTR_resources/fonts/AlegreyaSans-MediumItalic.ttf", 72);
	FT_Error err = frFontRenderer_InletletValveText->initialize();
	if (err != 0)
	{
		//fprintf_s(gpFile, "[Error] | Not able to initialize FreeType, error code: %d", err);
		Scene2_UnInitialize(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	tdInletValveText.text = "Inlet Valve";
	tdInletValveText.textSize = strlen(tdInletValveText.text);
	tdInletValveText.textColor = glm::vec3(1.0f, 0.0f, 0.0f);
	tdInletValveText.textPosition = glm::vec3(-4.5f, 2.0f, -14.5f);
	tdInletValveText.scale = 0.0085f; // 0 to 1 for convinience
	frFontRenderer_InletletValveText->loadCharacters(tdInletValveText.text, (int)tdInletValveText.textSize);

	frFontRenderer_OutletletValveText = new FontRenderer("RTR_resources/fonts/AlegreyaSans-MediumItalic.ttf", 72);
	err = frFontRenderer_OutletletValveText->initialize();
	if (err != 0)
	{
		//fprintf_s(gpFile, "[Error] | Not able to initialize FreeType, error code: %d", err);
		Scene2_UnInitialize(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	tdOutletletValveText.text = "Outlet Valve";
	tdOutletletValveText.textSize = strlen(tdOutletletValveText.text);
	tdOutletletValveText.textColor = glm::vec3(1.0f, 0.0f, 0.0f);
	tdOutletletValveText.textPosition = glm::vec3(2.3f, 2.0f, -14.5f);
	tdOutletletValveText.scale = 0.0085f; // 0 to 1 for convinience
	frFontRenderer_OutletletValveText->loadCharacters(tdOutletletValveText.text, (int)tdOutletletValveText.textSize);

	/*frFontRenderer_MainBoreText = new FontRenderer("fonts/AlegreyaSans-MediumItalic.ttf", 72);
	err = frFontRenderer_MainBoreText->initialize();
	if (err != 0)
	{
	fprintf_s(gpFile, "[Error] | Not able to initialize FreeType, error code: %d", err);
	Scene2_UnInitialize(EXIT_FAILURE);
	exit(EXIT_FAILURE);
	}
	tdMainBoreText.text = "Main Bore";
	tdMainBoreText.textSize = strlen(tdMainBoreText.text);
	tdMainBoreText.textColor = glm::vec3(1.0f, 0.0f, 0.0f);
	tdMainBoreText.textPosition = glm::vec3(-2.0f, -4.0f, -14.5f);
	tdMainBoreText.scale = 0.0085f; // 0 to 1 for convinience
	frFontRenderer_MainBoreText->loadCharacters(tdMainBoreText.text, (int)tdMainBoreText.textSize);*/


	frFontRenderer_PistonText = new FontRenderer("RTR_resources/fonts/AlegreyaSans-MediumItalic.ttf", 72);
	err = frFontRenderer_PistonText->initialize();
	if (err != 0)
	{
		//fprintf_s(gpFile, "[Error] | Not able to initialize FreeType, error code: %d", err);
		Scene2_UnInitialize(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	tdPistonText.text = "Piston";
	tdPistonText.textSize = strlen(tdPistonText.text);
	tdPistonText.textColor = glm::vec3(1.0f, 0.0f, 0.0f);
	tdPistonText.textPosition = glm::vec3(-4.0f, -3.0f, -14.5f);
	tdPistonText.scale = 0.0085f; // 0 to 1 for convinience
	frFontRenderer_PistonText->loadCharacters(tdPistonText.text, (int)tdPistonText.textSize);

	frFontRenderer_SparkPlugText = new FontRenderer("RTR_resources/fonts/AlegreyaSans-MediumItalic.ttf", 72);
	err = frFontRenderer_SparkPlugText->initialize();
	if (err != 0)
	{
		//fprintf_s(gpFile, "[Error] | Not able to initialize FreeType, error code: %d", err);
		Scene2_UnInitialize(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	tdSparkPlugText.text = "Spark Plug";
	tdSparkPlugText.textSize = strlen(tdSparkPlugText.text);
	tdSparkPlugText.textColor = glm::vec3(1.0f, 0.0f, 0.0f);
	tdSparkPlugText.textPosition = glm::vec3(-1.2f, 3.0f, -14.5f);
	tdSparkPlugText.scale = 0.0085f; // 0 to 1 for convinience
	frFontRenderer_SparkPlugText->loadCharacters(tdSparkPlugText.text, (int)tdSparkPlugText.textSize);


	frFontRenderer_IntakeText = new FontRenderer("RTR_resources/fonts/AlegreyaSans-Bold.ttf", 78);
	err = frFontRenderer_IntakeText->initialize();
	if (err != 0)
	{
		//fprintf_s(gpFile, "[Error] | Not able to initialize FreeType, error code: %d", err);
		Scene2_UnInitialize(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	tdIntakeText.text = "INTAKE";
	tdIntakeText.textSize = strlen(tdIntakeText.text);
	tdIntakeText.textColor = glm::vec3(0.0f, 0.0f, 1.0f);
	tdIntakeText.textPosition = glm::vec3(1.5f, -2.0f, -14.5f);
	tdIntakeText.scale = 0.015f;
	frFontRenderer_IntakeText->loadCharacters(tdIntakeText.text, (int)tdIntakeText.textSize);

	frFontRenderer_CompressionText = new FontRenderer("RTR_resources/fonts/AlegreyaSans-Bold.ttf", 78);
	err = frFontRenderer_CompressionText->initialize();
	if (err != 0)
	{
		//fprintf_s(gpFile, "[Error] | Not able to initialize FreeType, error code: %d", err);
		Scene2_UnInitialize(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	tdCompressionText.text = "COMPRESSION";
	tdCompressionText.textSize = strlen(tdCompressionText.text);
	//tdCompressionText.textColor = glm::vec3(0.56f, 0.74f, 0.56f);//1.00, 0.84
	tdCompressionText.textColor = glm::vec3(1.0f, 1.0f, 0.56f);
	tdCompressionText.textPosition = glm::vec3(1.5f, -2.0f, -14.5f);
	tdCompressionText.scale = 0.015f;
	frFontRenderer_CompressionText->loadCharacters(tdCompressionText.text, (int)tdCompressionText.textSize);

	frFontRenderer_PowerText = new FontRenderer("RTR_resources/fonts/AlegreyaSans-Bold.ttf", 78);
	err = frFontRenderer_PowerText->initialize();
	if (err != 0)
	{
		//fprintf_s(gpFile, "[Error] | Not able to initialize FreeType, error code: %d", err);
		Scene2_UnInitialize(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	tdPowerText.text = "POWER";
	tdPowerText.textSize = strlen(tdPowerText.text);
	tdPowerText.textColor = glm::vec3(0.72f, 0.21f, 0.04f);
	tdPowerText.textPosition = glm::vec3(1.5f, -2.0f, -14.5f);
	tdPowerText.scale = 0.015f;
	frFontRenderer_PowerText->loadCharacters(tdPowerText.text, (int)tdPowerText.textSize);

	frFontRenderer_ExhaustText = new FontRenderer("RTR_resources/fonts/AlegreyaSans-Bold.ttf", 78);
	err = frFontRenderer_ExhaustText->initialize();
	if (err != 0)
	{
		//fprintf_s(gpFile, "[Error] | Not able to initialize FreeType, error code: %d", err);
		Scene2_UnInitialize(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	tdExhaustText.text = "EXHAUST";
	tdExhaustText.textSize = strlen(tdExhaustText.text);
	tdExhaustText.textColor = glm::vec3(0.0f, 0.85f, 0.0f);
	tdExhaustText.textPosition = glm::vec3(1.5f, -2.0f, -14.5f);
	tdExhaustText.scale = 0.015f;
	frFontRenderer_ExhaustText->loadCharacters(tdExhaustText.text, (int)tdExhaustText.textSize);
	/// Text Config End

	/// Line Config Start
	g_scene2_Line_VertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	// give source code to shader
	const GLchar *vertexShaderSourceCode_Line =
		"#version 460 core"	\
		"\n" \
		"in vec4 vPosition;"	\
		"uniform mat4 u_model_matrix;"	\
		"uniform mat4 u_view_matrix;"	\
		"uniform mat4 u_projection_matrix;"	\
		"void main (void)"	\
		"{"	\
		"	gl_Position = (u_projection_matrix * u_view_matrix * u_model_matrix) * vPosition;"	\
		"}";
	glShaderSource(g_scene2_Line_VertexShaderObject, 1, (const GLchar**)&vertexShaderSourceCode_Line, NULL);

	// Compile Source Code
	glCompileShader(g_scene2_Line_VertexShaderObject);
	iInfoLogLength = 0;
	iShaderCompileStatus = 0;
	szInfoLog = NULL;
	glGetShaderiv(g_scene2_Line_VertexShaderObject, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_Line_VertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_Line_VertexShaderObject, GL_INFO_LOG_LENGTH, &written, szInfoLog);
				//fprintf_s(gpFile, "Error : Vertex Shader Compilation Log : %s \n", szInfoLog);
				free(szInfoLog);
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}

		}

	}

	g_scene2_Line_FragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode_Line =
		"#version 460 core"	\
		"\n"	\
		"out vec4 FragColor;"	\
		"void main (void)" \
		"{"	\
		"	FragColor = vec4(1.0f,0.0f,0.0f,0.3f);"	\
		"}";
	glShaderSource(g_scene2_Line_FragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode_Line, NULL);

	// Compile Source Code
	glCompileShader(g_scene2_Line_FragmentShaderObject);
	iInfoLogLength = 0;
	iShaderCompileStatus = 0;
	szInfoLog = NULL;
	glGetShaderiv(g_scene2_Line_FragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(g_scene2_Line_FragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength>0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_Line_FragmentShaderObject, GL_INFO_LOG_LENGTH, &written, szInfoLog);
				//fprintf_s(gpFile, "Error : Fragment Shader Compilation Log : %s \n", szInfoLog);
				free(szInfoLog);
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	g_scene2_Line_ShaderProgramObject = glCreateProgram();
	// Attach Vertex Shader
	glAttachShader(g_scene2_Line_ShaderProgramObject, g_scene2_Line_VertexShaderObject);
	// Attach Fragment Shader
	glAttachShader(g_scene2_Line_ShaderProgramObject, g_scene2_Line_FragmentShaderObject);
	// pre-link Program object with Vertex Sahder position attribute
	glBindAttribLocation(g_scene2_Line_ShaderProgramObject, FRAG_ATTRIBUTE_POSITION, "vPosition");
	// link Shader 
	glLinkProgram(g_scene2_Line_ShaderProgramObject);

	iShaderProgramLinkStatus = 0;
	glGetProgramiv(g_scene2_Line_ShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	szInfoLog = NULL;
	iInfoLogLength = 0;
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(g_scene2_Line_ShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(g_scene2_Line_ShaderProgramObject, GL_INFO_LOG_LENGTH, &written, szInfoLog);
				//fprintf_s(gpFile, "Error : Shader Program Link Log : %s \n", szInfoLog);
				free(szInfoLog);
				Scene2_UnInitialize(EXIT_FAILURE);
				exit(EXIT_FAILURE);
			}
		}
	}

	g_scene2_1_Uniform_ModelMatrix_Line = glGetUniformLocation(g_scene2_Line_ShaderProgramObject, "u_model_matrix");
	g_scene2_1_Uniform_ViewMatrix_Line = glGetUniformLocation(g_scene2_Line_ShaderProgramObject, "u_view_matrix");
	g_scene2_1_Uniform_ProjectionMatrix_Line = glGetUniformLocation(g_scene2_Line_ShaderProgramObject, "u_projection_matrix");

	//glGenBuffers(1, &g_scene2_Line_VertexArrayObject);
	glGenVertexArrays(1, &g_scene2_Line_VertexArrayObject);
	glBindVertexArray(g_scene2_Line_VertexArrayObject);

	//vbo creation and binding
	glGenBuffers(1, &g_scene2_Line_VertexBufferObject_Position);
	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_Line_VertexBufferObject_Position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_InletLineVertices_1), g_scene2_1_InletLineVertices_1, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(FRAG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAG_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/// Line Config End

	g_scene2_1_PerspectiveProjectionMatrix = glm::mat4(1.0f);

	Scene2_InitializeAudio();
}


void CreatePoints_Inlet(GLint iWidth, GLint iHeight)
{
	GLfloat *vptr = NULL, *cptr = NULL, *velptr = NULL, *stptr = NULL;
	GLfloat i, j;

	if (g_scene2_1_pfVerts_inlet != NULL)
		free(g_scene2_1_pfVerts_inlet);

	g_scene2_1_pfVerts_inlet = (GLfloat*)malloc(iWidth*iHeight * 3 * (sizeof(GLfloat)));
	g_scene2_1_pfColors_inlet = (GLfloat*)malloc(iWidth*iHeight * 3 * (sizeof(GLfloat)));
	g_scene2_1_pfVelocities_inlet = (GLfloat*)malloc(iWidth*iHeight * 3 * (sizeof(GLfloat)));
	g_scene2_1_pfStartTimes_inlet = (GLfloat*)malloc(iWidth * iHeight * (sizeof(GLfloat)));

	vptr = g_scene2_1_pfVerts_inlet;
	cptr = g_scene2_1_pfColors_inlet;
	velptr = g_scene2_1_pfVelocities_inlet;
	stptr = g_scene2_1_pfStartTimes_inlet;

	for (i = 0.5f / iWidth - 0.5f; i < 0.5f; i = i + 1.0f / iWidth)
	{
		for (j = 0.5f / iHeight - 0.5f; j<0.5f; j = j + 1.0f / iHeight)
		{
			// 1.2f, -1.2f, -14.5f
			//*(vptr + 0) = sinf(((float)rand() / RAND_MAX));
			*(vptr + 0) = 0.0f;
			*(vptr + 1) = -0.8f;
			//*(vptr + 1) = cosf((float)rand() / RAND_MAX);
			*(vptr + 2) = -14.5f;
			vptr += 3;

			*cptr = 0.0f;
			*(cptr + 1) = 0.0f;
			*(cptr + 2) = 1.0f;
			cptr += 3;

			*velptr = ((float)rand() / (GLfloat)RAND_MAX) - 4.0f;
			*(velptr + 1) = -3.0f;
			*(velptr + 2) = 0.0f;
			velptr += 3;

			*stptr = ((float)rand() / (GLfloat)RAND_MAX) * 0.5f;
			stptr++;

		}
	}

	g_scene2_1_arrayWidth_inlet = iWidth;
	g_scene2_1_arrayHeight_inlet = iHeight;

}

void CreatePoints_Outlet(GLint iWidth, GLint iHeight)
{
	GLfloat *vptr = NULL, *cptr = NULL, *velptr = NULL, *stptr = NULL;
	GLfloat i, j;

	if (g_scene2_1_pfVerts_Outlet != NULL)
		free(g_scene2_1_pfVerts_Outlet);

	g_scene2_1_pfVerts_Outlet = (GLfloat *)malloc(iWidth * iHeight * 3 * (sizeof(GLfloat)));
	g_scene2_1_pfColors_Outlet = (GLfloat *)malloc(iWidth * iHeight * 3 * (sizeof(GLfloat)));
	g_scene2_1_pfVelocities_Outlet = (GLfloat *)malloc(iWidth * iHeight * 3 * (sizeof(GLfloat)));
	g_scene2_1_pfStartTimes_Outlet = (GLfloat *)malloc(iWidth * iHeight * (sizeof(GLfloat)));

	vptr = g_scene2_1_pfVerts_Outlet;
	cptr = g_scene2_1_pfColors_Outlet;
	velptr = g_scene2_1_pfVelocities_Outlet;
	stptr = g_scene2_1_pfStartTimes_Outlet;

	for (i = 0.5f / iWidth - 0.5f; i < 0.5f; i = i + 1.0f / iWidth)
	{
		for (j = 0.5f / iHeight - 0.5f; j < 0.5f; j = j + 1.0f / iHeight)
		{

			*(vptr + 0) = 0.0f;
			*(vptr + 1) = 0.0f;
			*(vptr + 2) = 0.0f;
			vptr += 3;

			*cptr = 0.0f;
			*(cptr + 1) = 0.85f;
			*(cptr + 2) = 0.0f;
			cptr += 3;

			*velptr = 8.0f;
			*(velptr + 1) = (((float)rand() / (float)RAND_MAX) == 0) ? ((float)rand() / (float)RAND_MAX) : ((float)rand() / (float)RAND_MAX);
			*(velptr + 2) = 0.0f;
			velptr += 3;

			*stptr = ((float)rand() / RAND_MAX) * 0.5f;
			stptr++;
		}
	}

	g_scene2_1_arrayWidth_Outlet = iWidth;
	g_scene2_1_arrayHeight_Outlet = iHeight;
}

void CreatePoints_ParticleSpark(GLint iWidth, GLint iHeight)
{
	GLfloat *vptr = NULL, *cptr = NULL, *velptr = NULL, *stptr = NULL;
	GLfloat i, j;

	GLfloat fNewRandomRadius = 0.0f;
	GLfloat fNewRandomAngle = 0.0f;

	if (g_scene2_1_pfVerts_Particle_Spark != NULL)
		free(g_scene2_1_pfVerts_Particle_Spark);

	g_scene2_1_pfVerts_Particle_Spark = (GLfloat *)malloc(iWidth * iHeight * 3 * (sizeof(GLfloat)));
	g_scene2_1_pfColors_Particle_Spark = (GLfloat *)malloc(iWidth * iHeight * 3 * (sizeof(GLfloat)));
	g_scene2_1_pfVelocities_Particle_Spark = (GLfloat *)malloc(iWidth * iHeight * 3 * (sizeof(GLfloat)));
	g_scene2_1_pfStartTimes_Particle_Spark = (GLfloat *)malloc(iWidth * iHeight * (sizeof(GLfloat)));

	vptr = g_scene2_1_pfVerts_Particle_Spark;
	cptr = g_scene2_1_pfColors_Particle_Spark;
	velptr = g_scene2_1_pfVelocities_Particle_Spark;
	stptr = g_scene2_1_pfStartTimes_Particle_Spark;
	// (high - low) * ((float)rand() / RAND_MAX)+low
	for (i = 0.5f / iWidth - 0.5f; i < 0.5f; i = i + 1.0f / iWidth)
	{
		for (j = 0.5f / iHeight - 0.5f; j < 0.5f; j = j + 1.0f / iHeight)
		{
			fNewRandomRadius = (1.0f * ((float)rand() / (float)RAND_MAX)) * g_scene2_1_fDeviationRadius;
			fNewRandomAngle = 360.0f * ((float)rand() / (float)RAND_MAX);

			*(vptr + 0) = 0.0f;
			*(vptr + 1) = 0.0f;
			*(vptr + 2) = 0.0f;
			vptr += 3;

			// spark => 1.00, 0.84, 0.00
			*(cptr + 0) = 1.0f;
			*(cptr + 1) = ((float)rand() / (float)RAND_MAX) * 0.84f;
			*(cptr + 2) = 0.0f;
			cptr += 3;

			*(velptr + 0) = (0.2f * ((float)rand() / (float)RAND_MAX));
			*(velptr + 1) = 0.1f;   // 0.5 to 1
			*(velptr + 2) = 0.0f;
			velptr += 3;

			*stptr = ((float)rand() / RAND_MAX) * 0.3f;
			stptr++;
		}
	}

	g_scene2_1_arrayWidth_Particle_Spark = iWidth;
	g_scene2_1_arrayHeight_Particle_Spark = iHeight;
}

void Scene2_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	logInfo("\n Sam : In of Display_Scene2. \n");
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 rotationMatrix = glm::mat4(1.0f);

	/*** View Port 1 Start ***/
	//Use Shader Program Object
	glViewport(g_scene2_1_iPresentViewPort_1, 0, (GLsizei)currentWidth, (GLsizei)currentHeight);
	//glViewport(0, 0, (GLsizei)currentWidth, (GLsizei)currentHeight);
	glUseProgram(g_scene2_1_ShaderProgramObject);


	glUniform1i(gLKeyPressedUniform, 1);

	glUniform3fv(g_scene2_1_LaUniform, 1, lightAmbient);
	glUniform3fv(g_scene2_1_LdUniform, 1, lightDiffuse);
	glUniform3fv(g_scene2_1_LsUniform, 1, lightSpecular);
	glUniform4fv(gLightPositionUniform, 1, lightPosition);

	glUniform3fv(g_scene2_1_KaUniform, 1, materialAmbient);
	glUniform3fv(g_scene2_1_KdUniform, 1, materialDiffuse);
	glUniform3fv(g_scene2_1_KsUniform, 1, materialSpecular);
	glUniform1f(g_scene2_1_MaterialShininessUniform, materialShininess);


	//modelMatrix = translate(SCENE2_1_MODEL_X_TRANSLATE, SCENE2_1_MODEL_Y_TRANSLATE, SCENE2_1_MODEL_Z_TRANSLATE);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, SCENE2_1_MODEL_Y_TRANSLATE, SCENE2_1_MODEL_Z_TRANSLATE));

	//rotationMatrix = vmath::rotate(g_rotate, 0.0f, 1.0f, 0.0f);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	// Piston Start
	modelMatrix = glm::mat4(1.0f); // SCENE2_1_MODEL_Y_TRANSLATE => max 0.3f min => -2.5f
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, g_scene2_1_piston_inc_factor_1, SCENE2_1_MODEL_Z_TRANSLATE));

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_Vao_Piston);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Piston);
	glBindVertexArray(0);
	// Piston End

	// Bore Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, SCENE2_1_MODEL_Y_TRANSLATE, SCENE2_1_MODEL_Z_TRANSLATE));

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));
	glBindVertexArray(g_scene2_1_Vao_Bore);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Bore);
	glBindVertexArray(0);
	// Bore End


	// Inlet Valve Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(g_scene2_1_inletValve_inc_factor_1[0], g_scene2_1_inletValve_inc_factor_1[1], g_scene2_1_inletValve_inc_factor_1[2]));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_Vao_InletValve);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Inlet_Valve);
	glBindVertexArray(0);
	// Inlet Valve End

	// Outlet Valve Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	//modelMatrix = translate(1.1f, 1.1f, -14.5f);
	//modelMatrix = translate(0.9f, 0.9f, -14.5f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(g_scene2_1_outletValve_inc_factor_1[0], g_scene2_1_outletValve_inc_factor_1[1], g_scene2_1_outletValve_inc_factor_1[2]));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));
	glBindVertexArray(g_scene2_1_Vao_InletValve);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Inlet_Valve);
	glBindVertexArray(0);
	// Outlet Valve End

	// Spark Plug Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 1.4f, -15.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_Vao_SparkPlug);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Spark_Plug);
	glBindVertexArray(0);

	// Spark Plug End
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	glUseProgram(0);

	// Cheating Board Start
	glUseProgram(g_scene2_1_ShaderProgramObject_Rectangle);

	glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_VertexArrayObject_Rectangle);

	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_Rectangle_Pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_RectangleVertices_1), g_scene2_1_RectangleVertices_1, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_Rectangle_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_RectangleColors_1), g_scene2_1_RectangleColors_1, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisable(GL_BLEND);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glUseProgram(0);
	// Cheating Board End

	if (g_scene2_1_iPresentViewPort_1 >= 0.0f)
	{
		/***** Particle Start *****/
		modelMatrix = glm::mat4(1.0f);
		viewMatrix = glm::mat4(1.0f);
		scaleMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::mat4(1.0f);
		if (g_scene2_1_bShow_Inlet_Particle == true)
		{
			//fprintf_s(gpFile, "Show Inlet Particles. \n");
			// Inlet Particle Start
			glUseProgram(g_scene2_1_ShaderProgramObject_Particle_Inlet);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.7f, 1.0f, 0.0f));

			glUniform1f(g_scene2_1_Location_inlet, g_scene2_1_pfParticleTime_inlet);
			glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Particle_Inlet, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Particle_Inlet, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Particle_Inlet, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

			glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Inlet);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPointSize(3.0);
			glDrawArrays(GL_POINTS, 0, g_scene2_1_arrayWidth_inlet*g_scene2_1_arrayHeight_inlet);
			//glPointSize(1.0);
			glDisable(GL_BLEND);
			glBindVertexArray(0);

			glUseProgram(0);

			// Set 2 Start
			modelMatrix = glm::mat4(1.0f);
			glUseProgram(g_scene2_1_ShaderProgramObject_Particle_Inlet);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.7f, 0.96f, 0.0f));
			//modelMatrix = vmath::translate(1.2f, -1.2f, -12.5f);

			glUniform1f(g_scene2_1_Location_inlet, g_scene2_1_pfParticleTime_inlet);
			glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Particle_Inlet, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Particle_Inlet, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Particle_Inlet, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

			glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Inlet);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPointSize(3.0);
			glDrawArrays(GL_POINTS, 0, g_scene2_1_arrayWidth_inlet*g_scene2_1_arrayHeight_inlet);
			//glPointSize(1.0);
			glDisable(GL_BLEND);
			glBindVertexArray(0);

			glUseProgram(0);
			// Set 2 End
			// Set 3 Start
			modelMatrix = glm::mat4(1.0f);
			glUseProgram(g_scene2_1_ShaderProgramObject_Particle_Inlet);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.7f, 0.93f, 0.0f));
			//modelMatrix = vmath::translate(1.2f, -1.2f, -12.5f);

			glUniform1f(g_scene2_1_Location_inlet, g_scene2_1_pfParticleTime_inlet);
			glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Particle_Inlet, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Particle_Inlet, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Particle_Inlet, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

			glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Inlet);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPointSize(3.0);
			glDrawArrays(GL_POINTS, 0, g_scene2_1_arrayWidth_inlet*g_scene2_1_arrayHeight_inlet);
			//glPointSize(1.0);
			glDisable(GL_BLEND);
			glBindVertexArray(0);

			glUseProgram(0);
			// Set 3 End
			// Inlet Particle End
			//fprintf_s(gpFile, "End Of Inlet Particles. \n");
		}


		modelMatrix = glm::mat4(1.0f);
		viewMatrix = glm::mat4(1.0f);
		scaleMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::mat4(1.0f);

		if (g_scene2_1_bShow_Outlet_Particle == true)
		{
			//fprintf_s(gpFile, "Show Outlet Particles. \n");
			// Outlet Particle Start
			// Set 1 Start
			glUseProgram(g_scene2_1_ShaderProgramObject_Particle_Outlet);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.6f, 0.3f, -14.5f));

			glUniform1f(g_scene2_1_Location_Outlet, g_scene2_1_pfParticleTime_Outlet);
			glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

			glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Outlet);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPointSize(3.0);
			glDrawArrays(GL_POINTS, 0, g_scene2_1_arrayWidth_Outlet * g_scene2_1_arrayHeight_Outlet);

			glDisable(GL_BLEND);
			glBindVertexArray(0);

			glUseProgram(0);
			// Set 1 End
			modelMatrix = glm::mat4(1.0f);
			// Set 2 Start
			glUseProgram(g_scene2_1_ShaderProgramObject_Particle_Outlet);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.3f, 0.3f, -14.5f));

			glUniform1f(g_scene2_1_Location_Outlet, g_scene2_1_pfParticleTime_Outlet);
			glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

			glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Outlet);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPointSize(3.0);
			glDrawArrays(GL_POINTS, 0, g_scene2_1_arrayWidth_Outlet * g_scene2_1_arrayHeight_Outlet);

			glDisable(GL_BLEND);
			glBindVertexArray(0);

			glUseProgram(0);
			// Set 2 End
			modelMatrix = glm::mat4(1.0f);
			// Set 3 Start
			glUseProgram(g_scene2_1_ShaderProgramObject_Particle_Outlet);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.3f, -14.5f));

			glUniform1f(g_scene2_1_Location_Outlet, g_scene2_1_pfParticleTime_Outlet);
			glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

			glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Outlet);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPointSize(3.0);
			glDrawArrays(GL_POINTS, 0, g_scene2_1_arrayWidth_Outlet * g_scene2_1_arrayHeight_Outlet);

			glDisable(GL_BLEND);
			glBindVertexArray(0);

			glUseProgram(0);
			// Set 3 End
			modelMatrix = glm::mat4(1.0f);
			// Set 4 Start
			glUseProgram(g_scene2_1_ShaderProgramObject_Particle_Outlet);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.3f, 0.3f, -14.5f));

			glUniform1f(g_scene2_1_Location_Outlet, g_scene2_1_pfParticleTime_Outlet);
			glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

			glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Outlet);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPointSize(3.0);
			glDrawArrays(GL_POINTS, 0, g_scene2_1_arrayWidth_Outlet * g_scene2_1_arrayHeight_Outlet);

			glDisable(GL_BLEND);
			glBindVertexArray(0);

			glUseProgram(0);
			// Set 4 End
			modelMatrix = glm::mat4(1.0f);
			// Set 5 Start
			glUseProgram(g_scene2_1_ShaderProgramObject_Particle_Outlet);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.6f, 0.3f, -14.5f));

			glUniform1f(g_scene2_1_Location_Outlet, g_scene2_1_pfParticleTime_Outlet);
			glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Particle_Outlet, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

			glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Outlet);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPointSize(3.0);
			glDrawArrays(GL_POINTS, 0, g_scene2_1_arrayWidth_Outlet * g_scene2_1_arrayHeight_Outlet);

			glDisable(GL_BLEND);
			glBindVertexArray(0);

			glUseProgram(0);
			// Set 5 End 

			// Outlet Particle End
			//fprintf_s(gpFile, "Out Outlet Particles. \n");
		}

		if (g_scene2_1_bShow_Spark_Particle == true)
		{
			//fprintf_s(gpFile, "Show Spark Particles. \n");
			// Spark Particle Satrt
			glUseProgram(g_scene2_1_ShaderProgramObject_Spark);
			//modelViewMatrix = vmath::translate(1.2f, -1.2f, -14.5f);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.8f, -14.5f));

			glUniform1f(g_scene2_1_Location_Outlet, g_scene2_1_pfParticleTime_Particle_Spark);
			glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Particle_Spark, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Particle_Spark, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Particle_Spark, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

			glBindVertexArray(g_scene2_1_VertexArrayObject_Particle_Spark);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPointSize(3.0);
			glDrawArrays(GL_POINTS, 0, g_scene2_1_arrayWidth_Particle_Spark * g_scene2_1_arrayHeight_Particle_Spark);
			glDisable(GL_BLEND);
			glBindVertexArray(0);

			glUseProgram(0);
			// Spark Particle End
			//fprintf_s(gpFile, "Out Spark Particles. \n");
		}

		/***** Particle End *****/
		modelMatrix = glm::mat4(1.0f);
		viewMatrix = glm::mat4(1.0f);
		scaleMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::mat4(1.0f);

		frFontRenderer_InletletValveText->renderText(&tdInletValveText, modelMatrix, viewMatrix, g_scene2_1_PerspectiveProjectionMatrix);

		frFontRenderer_OutletletValveText->renderText(&tdOutletletValveText, modelMatrix, viewMatrix, g_scene2_1_PerspectiveProjectionMatrix);

		frFontRenderer_SparkPlugText->renderText(&tdSparkPlugText, modelMatrix, viewMatrix, g_scene2_1_PerspectiveProjectionMatrix);

		/*frFontRenderer_MainBoreText->renderText(&tdMainBoreText, modelMatrix, viewMatrix, g_scene2_1_PerspectiveProjectionMatrix);*/

		frFontRenderer_PistonText->renderText(&tdPistonText, modelMatrix, viewMatrix, g_scene2_1_PerspectiveProjectionMatrix);


		modelMatrix = glm::mat4(1.0f);
		viewMatrix = glm::mat4(1.0f);
		scaleMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::mat4(1.0f);

		switch (g_scene2_1_iPresentStroke_1)
		{
		case 0:
			frFontRenderer_IntakeText->renderText(&tdIntakeText, modelMatrix, viewMatrix, g_scene2_1_PerspectiveProjectionMatrix);
			break;
		case 1:
			frFontRenderer_CompressionText->renderText(&tdCompressionText, modelMatrix, viewMatrix, g_scene2_1_PerspectiveProjectionMatrix);
			break;
		case 2:
			frFontRenderer_PowerText->renderText(&tdPowerText, modelMatrix, viewMatrix, g_scene2_1_PerspectiveProjectionMatrix);
			break;
		case 3:
			frFontRenderer_ExhaustText->renderText(&tdExhaustText, modelMatrix, viewMatrix, g_scene2_1_PerspectiveProjectionMatrix);
			break;
		default:
			break;
		}

		modelMatrix = glm::mat4(1.0f);
		viewMatrix = glm::mat4(1.0f);
		scaleMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::mat4(1.0f);

		/// Line Draw Start
		// Inlet valve Line
		glUseProgram(g_scene2_Line_ShaderProgramObject);

		glBindVertexArray(g_scene2_Line_VertexArrayObject);

		glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Line, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Line, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Line, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

		glBindBuffer(GL_ARRAY_BUFFER, g_scene2_Line_VertexBufferObject_Position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_InletLineVertices_1), g_scene2_1_InletLineVertices_1, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glLineWidth(3.0f);
		glDrawArrays(GL_LINES, 0, 2);
		glDrawArrays(GL_LINES, 2, 2);
		glBindVertexArray(0);

		glUseProgram(0);

		// Spark Plug Line
		glUseProgram(g_scene2_Line_ShaderProgramObject);

		glBindVertexArray(g_scene2_Line_VertexArrayObject);

		glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Line, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Line, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Line, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

		glBindBuffer(GL_ARRAY_BUFFER, g_scene2_Line_VertexBufferObject_Position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_SparkPlugLineVertices_1), g_scene2_1_SparkPlugLineVertices_1, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glLineWidth(3.0f);
		glDrawArrays(GL_LINES, 0, 2);
		glDrawArrays(GL_LINES, 2, 2);
		glBindVertexArray(0);

		glUseProgram(0);

		// Outlet Line 
		glUseProgram(g_scene2_Line_ShaderProgramObject);

		glBindVertexArray(g_scene2_Line_VertexArrayObject);

		glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Line, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Line, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Line, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

		glBindBuffer(GL_ARRAY_BUFFER, g_scene2_Line_VertexBufferObject_Position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_OutletLineVertices_1), g_scene2_1_OutletLineVertices_1, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glLineWidth(3.0f);
		glDrawArrays(GL_LINES, 0, 2);
		glDrawArrays(GL_LINES, 2, 2);
		glBindVertexArray(0);

		glUseProgram(0);

		// Piston Line 
		glUseProgram(g_scene2_Line_ShaderProgramObject);

		glBindVertexArray(g_scene2_Line_VertexArrayObject);

		glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix_Line, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix_Line, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix_Line, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

		glBindBuffer(GL_ARRAY_BUFFER, g_scene2_Line_VertexBufferObject_Position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_PistonLineVertices_1), g_scene2_1_PistonLineVertices_1, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glLineWidth(3.0f);
		glDrawArrays(GL_LINES, 0, 2);
		glDrawArrays(GL_LINES, 2, 2);
		glBindVertexArray(0);

		glUseProgram(0);

		/// Line Draw End
	}
	/*** View Port 1 End ***/

	/*** View Port 2 Start ***/
	//Use Shader Program Object
	glViewport(g_scene2_1_iPresentViewPort_2, 0, (GLsizei)currentWidth, (GLsizei)currentHeight);
	//glViewport(-200, 0, (GLsizei)currentWidth, (GLsizei)currentHeight);
	glUseProgram(g_scene2_1_ShaderProgramObject);

	glUniform1i(gLKeyPressedUniform, 1);

	glUniform3fv(g_scene2_1_LaUniform, 1, lightAmbient);
	glUniform3fv(g_scene2_1_LdUniform, 1, lightDiffuse);
	glUniform3fv(g_scene2_1_LsUniform, 1, lightSpecular);
	glUniform4fv(gLightPositionUniform, 1, lightPosition);

	glUniform3fv(g_scene2_1_KaUniform, 1, materialAmbient);
	glUniform3fv(g_scene2_1_KdUniform, 1, materialDiffuse);
	glUniform3fv(g_scene2_1_KsUniform, 1, materialSpecular);
	glUniform1f(g_scene2_1_MaterialShininessUniform, materialShininess);

	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, SCENE2_1_MODEL_Y_TRANSLATE, SCENE2_1_MODEL_Z_TRANSLATE));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	// Piston Start
	modelMatrix = glm::mat4(1.0f); // SCENE2_1_MODEL_Y_TRANSLATE => max 0.3f min => -2.5f
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, g_scene2_1_piston_inc_factor_2, SCENE2_1_MODEL_Z_TRANSLATE));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_Vao_Piston);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Piston);
	glBindVertexArray(0);
	// Piston End

	// Bore Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, SCENE2_1_MODEL_Y_TRANSLATE, SCENE2_1_MODEL_Z_TRANSLATE));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));
	glBindVertexArray(g_scene2_1_Vao_Bore);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Bore);
	glBindVertexArray(0);
	// Bore End


	// Inlet Valve Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(g_scene2_1_inletValve_inc_factor_2[0], g_scene2_1_inletValve_inc_factor_2[1], g_scene2_1_inletValve_inc_factor_2[2]));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));


	glBindVertexArray(g_scene2_1_Vao_InletValve);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Inlet_Valve);
	glBindVertexArray(0);
	// Inlet Valve End

	// Outlet Valve Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(g_scene2_1_outletValve_inc_factor_2[0], g_scene2_1_outletValve_inc_factor_2[1], g_scene2_1_outletValve_inc_factor_2[2]));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));
	glBindVertexArray(g_scene2_1_Vao_InletValve);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Inlet_Valve);
	glBindVertexArray(0);
	// Outlet Valve End

	// Spark Plug Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 1.4f, -15.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_Vao_SparkPlug);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Spark_Plug);
	glBindVertexArray(0);
	glUseProgram(0);
	// Spark Plug End

	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	// Cheating Board Start

	glUseProgram(g_scene2_1_ShaderProgramObject_Rectangle);

	glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_VertexArrayObject_Rectangle);

	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_Rectangle_Pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_RectangleVertices_2), g_scene2_1_RectangleVertices_2, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_Rectangle_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_RectangleColors_2), g_scene2_1_RectangleColors_2, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisable(GL_BLEND);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glUseProgram(0);
	// Cheating Board End
	/*** View Port 2 End   ***/

	/*** View Port 3 Start ***/
	//Use Shader Program Object 
	glViewport(g_scene2_1_iPresentViewPort_3, 0, (GLsizei)currentWidth, (GLsizei)currentHeight);
	//glViewport((GLint)100, 0, (GLsizei)currentWidth, (GLsizei)currentHeight);
	glUseProgram(g_scene2_1_ShaderProgramObject);

	glUniform1i(gLKeyPressedUniform, 1);

	glUniform3fv(g_scene2_1_LaUniform, 1, lightAmbient);
	glUniform3fv(g_scene2_1_LdUniform, 1, lightDiffuse);
	glUniform3fv(g_scene2_1_LsUniform, 1, lightSpecular);
	glUniform4fv(gLightPositionUniform, 1, lightPosition);

	glUniform3fv(g_scene2_1_KaUniform, 1, materialAmbient);
	glUniform3fv(g_scene2_1_KdUniform, 1, materialDiffuse);
	glUniform3fv(g_scene2_1_KsUniform, 1, materialSpecular);
	glUniform1f(g_scene2_1_MaterialShininessUniform, materialShininess);


	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, SCENE2_1_MODEL_Y_TRANSLATE, SCENE2_1_MODEL_Z_TRANSLATE));

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	// Piston Start
	modelMatrix = glm::mat4(1.0f); // SCENE2_1_MODEL_Y_TRANSLATE => max 0.3f min => -2.5f
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, g_scene2_1_piston_inc_factor_3, SCENE2_1_MODEL_Z_TRANSLATE));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_Vao_Piston);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Piston);
	glBindVertexArray(0);
	// Piston End

	// Bore Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, SCENE2_1_MODEL_Y_TRANSLATE, SCENE2_1_MODEL_Z_TRANSLATE));

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));
	glBindVertexArray(g_scene2_1_Vao_Bore);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Bore);
	glBindVertexArray(0);
	// Bore End


	// Inlet Valve Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(g_scene2_1_inletValve_inc_factor_3[0], g_scene2_1_inletValve_inc_factor_3[1], g_scene2_1_inletValve_inc_factor_3[2]));

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));


	glBindVertexArray(g_scene2_1_Vao_InletValve);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Inlet_Valve);
	glBindVertexArray(0);
	// Inlet Valve End

	// Outlet Valve Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	//modelMatrix = translate(1.1f, 1.1f, -14.5f);
	//modelMatrix = translate(0.9f, 0.9f, -14.5f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(outletValve_inc_factor_3[0], outletValve_inc_factor_3[1], outletValve_inc_factor_3[2]));

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));
	glBindVertexArray(g_scene2_1_Vao_InletValve);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Inlet_Valve);
	glBindVertexArray(0);
	// Outlet Valve End

	// Spark Plug Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 1.4f, -15.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_Vao_SparkPlug);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Spark_Plug);
	glBindVertexArray(0);

	glUseProgram(0);
	// Spark Plug End
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	// Cheating Board Start

	glUseProgram(g_scene2_1_ShaderProgramObject_Rectangle);

	glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_VertexArrayObject_Rectangle);

	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_Rectangle_Pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_RectangleVertices_3), g_scene2_1_RectangleVertices_3, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_Rectangle_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_RectangleColors_3), g_scene2_1_RectangleColors_3, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisable(GL_BLEND);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glUseProgram(0);
	// Cheating Board End
	/*** View Port 3 End   ***/

	/*** View Port 4 Start ***/
	//Use Shader Program Object //g_scene2_1_iPresentViewPort_3
	glViewport(g_scene2_1_iPresentViewPort_4, 0, (GLsizei)currentWidth, (GLsizei)currentHeight);
	//glViewport((GLint)400, 0, (GLsizei)currentWidth, (GLsizei)currentHeight);
	glUseProgram(g_scene2_1_ShaderProgramObject);

	glUniform1i(gLKeyPressedUniform, 1);

	glUniform3fv(g_scene2_1_LaUniform, 1, lightAmbient);
	glUniform3fv(g_scene2_1_LdUniform, 1, lightDiffuse);
	glUniform3fv(g_scene2_1_LsUniform, 1, lightSpecular);
	glUniform4fv(gLightPositionUniform, 1, lightPosition);

	glUniform3fv(g_scene2_1_KaUniform, 1, materialAmbient);
	glUniform3fv(g_scene2_1_KdUniform, 1, materialDiffuse);
	glUniform3fv(g_scene2_1_KsUniform, 1, materialSpecular);
	glUniform1f(g_scene2_1_MaterialShininessUniform, materialShininess);


	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, SCENE2_1_MODEL_Y_TRANSLATE, SCENE2_1_MODEL_Z_TRANSLATE));
	//rotationMatrix = vmath::rotate(g_scene2_1_bRotate, 0.0f, 1.0f, 0.0f);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	// Piston Start
	modelMatrix = glm::mat4(1.0f); // SCENE2_1_MODEL_Y_TRANSLATE => max 0.3f min => -2.5f
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, g_scene2_1_piston_inc_factor_4, SCENE2_1_MODEL_Z_TRANSLATE));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_Vao_Piston);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Piston);
	glBindVertexArray(0);
	// Piston End

	// Bore Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE2_1_MODEL_X_TRANSLATE, SCENE2_1_MODEL_Y_TRANSLATE, SCENE2_1_MODEL_Z_TRANSLATE));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));
	glBindVertexArray(g_scene2_1_Vao_Bore);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Bore);
	glBindVertexArray(0);
	// Bore End


	// Inlet Valve Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(g_scene2_1_inletValve_inc_factor_4[0], g_scene2_1_inletValve_inc_factor_4[1], g_scene2_1_inletValve_inc_factor_4[2]));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));


	glBindVertexArray(g_scene2_1_Vao_InletValve);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Inlet_Valve);
	glBindVertexArray(0);
	// Inlet Valve End

	// Outlet Valve Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	//modelMatrix = translate(1.1f, 1.1f, -14.5f);
	//modelMatrix = translate(0.9f, 0.9f, -14.5f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(outletValve_inc_factor_4[0], outletValve_inc_factor_4[1], outletValve_inc_factor_4[2]));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));
	glBindVertexArray(g_scene2_1_Vao_InletValve);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Inlet_Valve);
	glBindVertexArray(0);
	// Outlet Valve End

	// Spark Plug Start
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 1.4f, -15.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	glUniformMatrix4fv(g_scene2_1_ModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_ViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_ProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_Vao_SparkPlug);
	glDrawArrays(GL_TRIANGLES, 0, g_scene2_1_count_of_vertices_Spark_Plug);
	glBindVertexArray(0);
	glUseProgram(0);
	// Spark Plug End
	modelMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	// Cheating Board Start
	glUseProgram(g_scene2_1_ShaderProgramObject_Rectangle);

	glUniformMatrix4fv(g_scene2_1_Uniform_ModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(g_scene2_1_Uniform_ViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(g_scene2_1_Uniform_ProjectionMatrix, 1, GL_FALSE, glm::value_ptr(g_scene2_1_PerspectiveProjectionMatrix));

	glBindVertexArray(g_scene2_1_VertexArrayObject_Rectangle);

	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_Rectangle_Pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_RectangleVertices_4), g_scene2_1_RectangleVertices_4, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, g_scene2_1_VertexBufferObject_Rectangle_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_scene2_1_RectangleColors_4), g_scene2_1_RectangleColors_4, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisable(GL_BLEND);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glUseProgram(0);
	// Cheating Board End
	/*** View Port 4 End   ***/
	logInfo("\n Sam : Out of Display_Scene2. \n");

	//SwapBuffers(ghdc);
}

void Scene2_Update(void)
{
	//fprintf_s(gpFile, "in Scene2_Update\n");
	/*g_rotate = g_rotate + SCENE2_1_MODEL_ANGLE_INCREMENT;
	if (g_rotate >= SCENE2_1_END_ANGLE_POS)
		g_rotate = SCENE2_1_START_ANGLE_POS;*/

	// Audio Setup Start
	if (g_scene2_1_PlayAudio == true)
	{
		g_pSS_Scene2_SoundSource->play(g_Scene2_AudioBuffer_LoopSound);
		g_scene2_1_PlayAudio = false;
	}

	/*if (g_pSS_Scene2_SoundSource->isLooping())
	{
	g_pSS_Scene2_SoundSource->loop(AL_FALSE);
	}
	else
	{
	g_pSS_Scene2_SoundSource->loop(AL_TRUE);
	}*/
	// Audio Setup End

	// Synchronizing all sets
	/*************************************************************************************************************

	1. Open Inlet
	2. Enable Piston DOWN
	3. Close Inlet
	4. Enable Piston UP
	5. Enable Piston DOWN (After Spark)
	6. Open Outlet
	7. Enable Piston UP
	8. Close Outlet
	9. Repeat.......!!

	*************************************************************************************************************/

	// 1. Open Inlet
	// Input Valve
	// Init value { -1.0f,1.0f,-12.0f };
	// Final Value { -0.9f,0.9f,-12.0f };

	/*** View Port 1 Start ***/
	if (g_scene2_1_bSyncFlag_Inlet_1 == true)
	{
		if (!g_scene2_1_bInletValveIncFlag_1)
		{
			g_scene2_1_rect_color_states_1 = 0;
			g_scene2_1_iPresentStroke_1 = 0;
			g_scene2_1_inletValve_inc_factor_1[0] = g_scene2_1_inletValve_inc_factor_1[0] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_inletValve_inc_factor_1[1] = g_scene2_1_inletValve_inc_factor_1[1] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_bShow_Inlet_Particle = true;
			g_scene2_1_bShow_Outlet_Particle = false;
			if ((g_scene2_1_inletValve_inc_factor_1[0] >= -0.9f) & (g_scene2_1_inletValve_inc_factor_1[1] <= 0.9f))
				g_scene2_1_bInletValveIncFlag_1 = true;
		}
		else
		{

			g_scene2_1_inletValve_inc_factor_1[0] = g_scene2_1_inletValve_inc_factor_1[0] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_inletValve_inc_factor_1[1] = g_scene2_1_inletValve_inc_factor_1[1] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_inletValve_inc_factor_1[0] <= -1.2f) & (g_scene2_1_inletValve_inc_factor_1[1] >= 1.2f))
			{
				g_scene2_1_bInletValveIncFlag_1 = false;
				g_scene2_1_bSyncFlag_Inlet_1 = false;
				g_scene2_1_rect_color_states_1 = 1;
				g_scene2_1_iPresentStroke_1 = 1;
				g_scene2_1_bShow_Inlet_Particle = false;
				g_scene2_1_bShow_Outlet_Particle = false;
			}
		}
	}

	if (g_scene2_1_bPistionIncFlag_1)// Piston Up
	{
		g_scene2_1_piston_inc_factor_1 = g_scene2_1_piston_inc_factor_1 + SCENE2_1_PISTON_POS_CHANGE_FACTOR;
		if (g_scene2_1_piston_inc_factor_1 >= 0.3f)
			g_scene2_1_bPistionIncFlag_1 = false;

	}
	else // Piston Down
	{
		//g_scene2_1_bShow_Spark_Particle
		if ((g_scene2_1_piston_down_count_1 == 1) & ((g_scene2_1_piston_inc_factor_1 <= 0.0f) | (g_scene2_1_piston_inc_factor_1 >= 1.0f)))
		{
			g_scene2_1_bShow_Spark_Particle = true;
			g_scene2_1_iPresentStroke_1 = 2;
		}
		else
			g_scene2_1_bShow_Spark_Particle = false;

		g_scene2_1_piston_inc_factor_1 = g_scene2_1_piston_inc_factor_1 - SCENE2_1_PISTON_POS_CHANGE_FACTOR;
		if (g_scene2_1_piston_inc_factor_1 <= -2.5f)
		{
			g_scene2_1_bPistionIncFlag_1 = true;
			g_scene2_1_piston_down_count_1++;
		}

	}



	// Enable Outlet at 2nd Down Pos Piston
	// Output Valve
	// Init value { 1.0f,1.0f,-14.5f };
	// Final Value { 0.9f,0.9f,-14.5f };
	if (g_scene2_1_piston_down_count_1 >= (short)2)
	{
		g_scene2_1_rect_color_states_1 = 3;
		g_scene2_1_iPresentStroke_1 = 3;
		if (!g_scene2_1_bOutletValveIncFlag_1)
		{
			g_scene2_1_outletValve_inc_factor_1[0] = g_scene2_1_outletValve_inc_factor_1[0] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_outletValve_inc_factor_1[1] = g_scene2_1_outletValve_inc_factor_1[1] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_outletValve_inc_factor_1[0] <= 0.9f) & (g_scene2_1_outletValve_inc_factor_1[1] <= 0.9f))
			{
				g_scene2_1_bOutletValveIncFlag_1 = true;
				g_scene2_1_rect_color_states_1 = 4;
				g_scene2_1_iPresentStroke_1 = 4;
				g_scene2_1_bShow_Inlet_Particle = false;
				g_scene2_1_bShow_Outlet_Particle = true;
			}
		}
		else
		{
			g_scene2_1_outletValve_inc_factor_1[0] = g_scene2_1_outletValve_inc_factor_1[0] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_outletValve_inc_factor_1[1] = g_scene2_1_outletValve_inc_factor_1[1] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_outletValve_inc_factor_1[0] >= 1.2f) & (g_scene2_1_outletValve_inc_factor_1[1] >= 1.2f))
			{
				g_scene2_1_bOutletValveIncFlag_1 = false;
				g_scene2_1_piston_down_count_1 = 0;
				g_scene2_1_bSyncFlag_Inlet_1 = true;
				g_scene2_1_rect_color_states_1 = 0;
				g_scene2_1_iPresentStroke_1 = 0;
			}
		}
	}

	// Cheating Board Start
	if (g_scene2_1_IncrementbRect_1)
	{
		g_scene2_1_RectangleVertices_1[7] += SCENE2_1_RECT_CHANGE_FACTOR;
		g_scene2_1_RectangleVertices_1[10] += SCENE2_1_RECT_CHANGE_FACTOR;
		if ((g_scene2_1_RectangleVertices_1[7] >= 0.3f) & (g_scene2_1_RectangleVertices_1[10] >= 0.3f))
			g_scene2_1_IncrementbRect_1 = false;
	}
	else
	{
		g_scene2_1_RectangleVertices_1[7] -= SCENE2_1_RECT_CHANGE_FACTOR;
		g_scene2_1_RectangleVertices_1[10] -= SCENE2_1_RECT_CHANGE_FACTOR;

		if ((g_scene2_1_RectangleVertices_1[7] <= -2.5f) & (g_scene2_1_RectangleVertices_1[10] <= -2.5f))
			g_scene2_1_IncrementbRect_1 = true;
	}


	switch (g_scene2_1_rect_color_states_1)
	{
	case 0:// Black to blue
		g_scene2_1_RectangleColors_1[0] = 0.0f;
		g_scene2_1_RectangleColors_1[1] = 0.0f;
		g_scene2_1_RectangleColors_1[2] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_1[3] = 0.0f;
		g_scene2_1_RectangleColors_1[4] = 0.0f;
		g_scene2_1_RectangleColors_1[5] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_1[6] = 0.0f;
		g_scene2_1_RectangleColors_1[7] = 0.0f;
		g_scene2_1_RectangleColors_1[8] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_1[9] = 0.0f;
		g_scene2_1_RectangleColors_1[10] = 0.0f;
		g_scene2_1_RectangleColors_1[11] += SCENE2_1_COLOR_CHANGE_FACTOR;
		//g_scene2_1_bShow_Inlet_Particle = true;
		//g_scene2_1_bShow_Outlet_Particle = false;
		break;
	case 1://	0.72, 0.21, 0.04
		   // Blue to color for compression
		g_scene2_1_RectangleColors_1[0] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[1] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[2] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[3] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[4] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[5] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[6] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[7] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[8] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[9] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[10] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[11] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		if ((g_scene2_1_RectangleColors_1[0] >= 0.72f) & (g_scene2_1_RectangleColors_1[1] >= 0.21f) & (g_scene2_1_RectangleColors_1[2] <= 0.04f))
		{
			g_scene2_1_RectangleColors_1[0] = 0.72f;
			g_scene2_1_RectangleColors_1[1] = 0.21f;
			g_scene2_1_RectangleColors_1[2] = 0.04f;
			g_scene2_1_RectangleColors_1[3] = 0.72f;
			g_scene2_1_RectangleColors_1[4] = 0.21f;
			g_scene2_1_RectangleColors_1[5] = 0.04f;
			g_scene2_1_RectangleColors_1[6] = 0.72f;
			g_scene2_1_RectangleColors_1[7] = 0.21f;
			g_scene2_1_RectangleColors_1[8] = 0.04f;
			g_scene2_1_RectangleColors_1[9] = 0.72f;
			g_scene2_1_RectangleColors_1[10] = 0.21f;
			g_scene2_1_RectangleColors_1[11] = 0.04f;
		}
		//g_scene2_1_bShow_Inlet_Particle = false;
		//g_scene2_1_bShow_Outlet_Particle = false;
		break;
	case 2: // Compression to Combustion
			//g_scene2_1_bShow_Inlet_Particle = false;
			//g_scene2_1_bShow_Outlet_Particle = false;
		break;
	case 3: // Combustion to Black
			//ZeroMemory((void*)&g_scene2_1_RectangleColors_1, sizeof(g_scene2_1_RectangleColors_1));
			//g_scene2_1_bShow_Inlet_Particle = false;
			//g_scene2_1_bShow_Outlet_Particle = true;
		g_scene2_1_RectangleColors_1[0] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[1] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[2] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[3] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[4] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[5] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[6] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[7] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[8] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[9] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[10] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_1[11] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		if ((g_scene2_1_RectangleColors_1[0] <= 0.0f) & (g_scene2_1_RectangleColors_1[1] <= 0.0f) & (g_scene2_1_RectangleColors_1[2] <= 0.0f))
			ZeroMemory((void*)&g_scene2_1_RectangleColors_1, sizeof(g_scene2_1_RectangleColors_1));

		break;

	}
	// Cheating Board End


	// Particle Start
	g_scene2_1_pfParticleTime_inlet += 0.01f;

	g_scene2_1_pfParticleTime_Outlet += 0.01f;

	g_scene2_1_pfParticleTime_Particle_Spark += 0.03f;

	if (g_scene2_1_bShow_Inlet_Particle == false)
		g_scene2_1_pfParticleTime_inlet = 0.0f;

	if (g_scene2_1_bShow_Outlet_Particle == false)
		g_scene2_1_pfParticleTime_Outlet = 0.0f;

	if (g_scene2_1_bShow_Spark_Particle == false)
		g_scene2_1_pfParticleTime_Particle_Spark = 0.0f;
	// Particle End

	if (g_scene2_1_ShowScene_One >= 1250.0f)
	{
		/// Manage ViewPorts Start
		if (g_scene2_1_iPresentViewPort_1 != 0)
		{
			g_scene2_1_iPresentViewPort_1 += 1;
			g_scene2_1_iPresentViewPort_2 += 3;
			g_scene2_1_iPresentViewPort_3 += 3;
			g_scene2_1_iPresentViewPort_4 += 3;
		}

		if (g_scene2_1_iPresentViewPort_1 >= 0)
			g_scene2_1_iPresentViewPort_1 = 0;
		/// Manage ViewPorts End
	}

	g_scene2_1_ShowScene_One++;
	/*** View Port 1 End  ***/


	/*** View Port 2 Start ***/
	if (g_scene2_1_bSyncFlag_Inlet_2 == true)
	{
		if (!g_scene2_1_bInletValveIncFlag_2)
		{
			rect_color_states_2 = 0;
			g_scene2_1_inletValve_inc_factor_2[0] = g_scene2_1_inletValve_inc_factor_2[0] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_inletValve_inc_factor_2[1] = g_scene2_1_inletValve_inc_factor_2[1] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_inletValve_inc_factor_2[0] >= -0.9f) & (g_scene2_1_inletValve_inc_factor_2[1] <= 0.9f))
				g_scene2_1_bInletValveIncFlag_2 = true;
		}
		else
		{

			g_scene2_1_inletValve_inc_factor_2[0] = g_scene2_1_inletValve_inc_factor_2[0] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_inletValve_inc_factor_2[1] = g_scene2_1_inletValve_inc_factor_2[1] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_inletValve_inc_factor_2[0] <= -1.2f) & (g_scene2_1_inletValve_inc_factor_2[1] >= 1.2f))
			{
				g_scene2_1_bInletValveIncFlag_2 = false;
				g_scene2_1_bSyncFlag_Inlet_2 = false;
				rect_color_states_2 = 1;
			}
		}
	}

	if (g_scene2_1_bPistionIncFlag_2)// Piston Up
	{
		g_scene2_1_piston_inc_factor_2 = g_scene2_1_piston_inc_factor_2 + SCENE2_1_PISTON_POS_CHANGE_FACTOR;
		if (g_scene2_1_piston_inc_factor_2 >= 0.3f)
			g_scene2_1_bPistionIncFlag_2 = false;

	}
	else // Piston Down
	{
		g_scene2_1_piston_inc_factor_2 = g_scene2_1_piston_inc_factor_2 - SCENE2_1_PISTON_POS_CHANGE_FACTOR;
		if (g_scene2_1_piston_inc_factor_2 <= -2.5f)
		{
			g_scene2_1_bPistionIncFlag_2 = true;
			g_scene2_1_piston_down_count_2++;
		}

	}

	if (g_scene2_1_piston_down_count_2 >= (short)2)
	{
		rect_color_states_2 = 3;
		if (!g_scene2_1_bOutletValveIncFlag_2)
		{
			g_scene2_1_outletValve_inc_factor_2[0] = g_scene2_1_outletValve_inc_factor_2[0] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_outletValve_inc_factor_2[1] = g_scene2_1_outletValve_inc_factor_2[1] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_outletValve_inc_factor_2[0] <= 0.9f) & (g_scene2_1_outletValve_inc_factor_2[1] <= 0.9f))
			{
				g_scene2_1_bOutletValveIncFlag_2 = true;
				rect_color_states_2 = 4;
			}
		}
		else
		{

			g_scene2_1_outletValve_inc_factor_2[0] = g_scene2_1_outletValve_inc_factor_2[0] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_outletValve_inc_factor_2[1] = g_scene2_1_outletValve_inc_factor_2[1] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_outletValve_inc_factor_2[0] >= 1.2f) & (g_scene2_1_outletValve_inc_factor_2[1] >= 1.2f))
			{
				g_scene2_1_bOutletValveIncFlag_2 = false;
				g_scene2_1_piston_down_count_2 = 0;
				g_scene2_1_bSyncFlag_Inlet_2 = true;
				rect_color_states_2 = 0;
			}
		}
	}

	// Cheating Board Start
	if (g_scene2_1_bIncrementbRect_2)
	{
		g_scene2_1_RectangleVertices_2[7] += SCENE2_1_RECT_CHANGE_FACTOR;
		g_scene2_1_RectangleVertices_2[10] += SCENE2_1_RECT_CHANGE_FACTOR;
		if ((g_scene2_1_RectangleVertices_2[7] >= 0.3f) & (g_scene2_1_RectangleVertices_2[10] >= 0.3f))
			g_scene2_1_bIncrementbRect_2 = false;
	}
	else
	{
		g_scene2_1_RectangleVertices_2[7] -= SCENE2_1_RECT_CHANGE_FACTOR;
		g_scene2_1_RectangleVertices_2[10] -= SCENE2_1_RECT_CHANGE_FACTOR;

		if ((g_scene2_1_RectangleVertices_2[7] <= -2.5f) & (g_scene2_1_RectangleVertices_2[10] <= -2.5f))
			g_scene2_1_bIncrementbRect_2 = true;
	}


	switch (rect_color_states_2)
	{
	case 0:// Black to blue
		g_scene2_1_RectangleColors_2[0] = 0.0f;
		g_scene2_1_RectangleColors_2[1] = 0.0f;
		g_scene2_1_RectangleColors_2[2] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_2[3] = 0.0f;
		g_scene2_1_RectangleColors_2[4] = 0.0f;
		g_scene2_1_RectangleColors_2[5] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_2[6] = 0.0f;
		g_scene2_1_RectangleColors_2[7] = 0.0f;
		g_scene2_1_RectangleColors_2[8] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_2[9] = 0.0f;
		g_scene2_1_RectangleColors_2[10] = 0.0f;
		g_scene2_1_RectangleColors_2[11] += SCENE2_1_COLOR_CHANGE_FACTOR;
		break;
	case 1://	0.72, 0.21, 0.04
		   // Blue to color for compression
		g_scene2_1_RectangleColors_2[0] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[1] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[2] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[3] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[4] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[5] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[6] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[7] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[8] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[9] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[10] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[11] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		if ((g_scene2_1_RectangleColors_2[0] >= 0.72f) & (g_scene2_1_RectangleColors_2[1] >= 0.21f) & (g_scene2_1_RectangleColors_2[2] <= 0.04f))
		{
			g_scene2_1_RectangleColors_2[0] = 0.72f;
			g_scene2_1_RectangleColors_2[1] = 0.21f;
			g_scene2_1_RectangleColors_2[2] = 0.04f;
			g_scene2_1_RectangleColors_2[3] = 0.72f;
			g_scene2_1_RectangleColors_2[4] = 0.21f;
			g_scene2_1_RectangleColors_2[5] = 0.04f;
			g_scene2_1_RectangleColors_2[6] = 0.72f;
			g_scene2_1_RectangleColors_2[7] = 0.21f;
			g_scene2_1_RectangleColors_2[8] = 0.04f;
			g_scene2_1_RectangleColors_2[9] = 0.72f;
			g_scene2_1_RectangleColors_2[10] = 0.21f;
			g_scene2_1_RectangleColors_2[11] = 0.04f;
		}
		break;
	case 2: // Compression to Combustion
		break;
	case 3: // Combustion to Black
			//ZeroMemory((void*)&g_scene2_1_RectangleColors_1, sizeof(g_scene2_1_RectangleColors_1));
		g_scene2_1_RectangleColors_2[0] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[1] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[2] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[3] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[4] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[5] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[6] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[7] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[8] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[9] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[10] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_2[11] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		if ((g_scene2_1_RectangleColors_2[0] <= 0.0f) & (g_scene2_1_RectangleColors_2[1] <= 0.0f) & (g_scene2_1_RectangleColors_2[2] <= 0.0f))
			ZeroMemory((void*)&g_scene2_1_RectangleColors_2, sizeof(g_scene2_1_RectangleColors_2));

		break;

	}
	// Cheating Board End
	/*** View Port 2 End   ***/

	/*** View Port 3 Start ***/
	if (g_scene2_1_bSyncFlag_Inlet_3 == true)
	{
		if (!g_scene2_1_bInletValveIncFlag_3)
		{
			rect_color_states_3 = 0;
			g_scene2_1_inletValve_inc_factor_3[0] = g_scene2_1_inletValve_inc_factor_3[0] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_inletValve_inc_factor_3[1] = g_scene2_1_inletValve_inc_factor_3[1] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_inletValve_inc_factor_3[0] >= -0.9f) & (g_scene2_1_inletValve_inc_factor_3[1] <= 0.9f))
				g_scene2_1_bInletValveIncFlag_3 = true;
		}
		else
		{

			g_scene2_1_inletValve_inc_factor_3[0] = g_scene2_1_inletValve_inc_factor_3[0] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_inletValve_inc_factor_3[1] = g_scene2_1_inletValve_inc_factor_3[1] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_inletValve_inc_factor_3[0] <= -1.2f) & (g_scene2_1_inletValve_inc_factor_3[1] >= 1.2f))
			{
				g_scene2_1_bInletValveIncFlag_3 = false;
				g_scene2_1_bSyncFlag_Inlet_3 = false;
				rect_color_states_3 = 1;
			}
		}
	}

	if (g_scene2_1_bPistionIncFlag_3)// Piston Up
	{
		g_scene2_1_piston_inc_factor_3 = g_scene2_1_piston_inc_factor_3 + SCENE2_1_PISTON_POS_CHANGE_FACTOR;
		if (g_scene2_1_piston_inc_factor_3 >= 0.3f)
			g_scene2_1_bPistionIncFlag_3 = false;

	}
	else // Piston Down
	{
		g_scene2_1_piston_inc_factor_3 = g_scene2_1_piston_inc_factor_3 - SCENE2_1_PISTON_POS_CHANGE_FACTOR;
		if (g_scene2_1_piston_inc_factor_3 <= -2.5f)
		{
			g_scene2_1_bPistionIncFlag_3 = true;
			g_scene2_1_piston_down_count_3++;
		}

	}

	// Enable Outlet at 2nd Down Pos Piston
	// Output Valve
	// Init value { 1.0f,1.0f,-14.5f };
	// Final Value { 0.9f,0.9f,-14.5f };
	if (g_scene2_1_piston_down_count_3 >= (short)2)
	{
		rect_color_states_3 = 3;
		if (!gbOutletValveIncFlag_3)
		{
			outletValve_inc_factor_3[0] = outletValve_inc_factor_3[0] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			outletValve_inc_factor_3[1] = outletValve_inc_factor_3[1] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((outletValve_inc_factor_3[0] <= 0.9f) & (outletValve_inc_factor_3[1] <= 0.9f))
			{
				gbOutletValveIncFlag_3 = true;
				rect_color_states_3 = 4;
			}
		}
		else
		{

			outletValve_inc_factor_3[0] = outletValve_inc_factor_3[0] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			outletValve_inc_factor_3[1] = outletValve_inc_factor_3[1] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((outletValve_inc_factor_3[0] >= 1.2f) & (outletValve_inc_factor_3[1] >= 1.2f))
			{
				gbOutletValveIncFlag_3 = false;
				g_scene2_1_piston_down_count_3 = 0;
				g_scene2_1_bSyncFlag_Inlet_3 = true;
				rect_color_states_3 = 0;
			}
		}
	}

	// Cheating Board Start
	if (g_scene2_1_bIncrementbRect_3)
	{
		g_scene2_1_RectangleVertices_3[7] += SCENE2_1_RECT_CHANGE_FACTOR;
		g_scene2_1_RectangleVertices_3[10] += SCENE2_1_RECT_CHANGE_FACTOR;
		if ((g_scene2_1_RectangleVertices_3[7] >= 0.3f) & (g_scene2_1_RectangleVertices_3[10] >= 0.3f))
			g_scene2_1_bIncrementbRect_3 = false;
	}
	else
	{
		g_scene2_1_RectangleVertices_3[7] -= SCENE2_1_RECT_CHANGE_FACTOR;
		g_scene2_1_RectangleVertices_3[10] -= SCENE2_1_RECT_CHANGE_FACTOR;

		if ((g_scene2_1_RectangleVertices_3[7] <= -2.5f) & (g_scene2_1_RectangleVertices_3[10] <= -2.5f))
			g_scene2_1_bIncrementbRect_3 = true;
	}


	switch (rect_color_states_3)
	{
	case 0:// Black to blue
		g_scene2_1_RectangleColors_3[0] = 0.0f;
		g_scene2_1_RectangleColors_3[1] = 0.0f;
		g_scene2_1_RectangleColors_3[2] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_3[3] = 0.0f;
		g_scene2_1_RectangleColors_3[4] = 0.0f;
		g_scene2_1_RectangleColors_3[5] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_3[6] = 0.0f;
		g_scene2_1_RectangleColors_3[7] = 0.0f;
		g_scene2_1_RectangleColors_3[8] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_3[9] = 0.0f;
		g_scene2_1_RectangleColors_3[10] = 0.0f;
		g_scene2_1_RectangleColors_3[11] += SCENE2_1_COLOR_CHANGE_FACTOR;
		break;
	case 1://	0.72, 0.21, 0.04
		   // Blue to color for compression
		g_scene2_1_RectangleColors_3[0] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[1] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[2] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[3] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[4] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[5] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[6] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[7] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[8] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[9] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[10] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[11] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		if ((g_scene2_1_RectangleColors_3[0] >= 0.72f) & (g_scene2_1_RectangleColors_3[1] >= 0.21f) & (g_scene2_1_RectangleColors_3[2] <= 0.04f))
		{
			g_scene2_1_RectangleColors_3[0] = 0.72f;
			g_scene2_1_RectangleColors_3[1] = 0.21f;
			g_scene2_1_RectangleColors_3[2] = 0.04f;
			g_scene2_1_RectangleColors_3[3] = 0.72f;
			g_scene2_1_RectangleColors_3[4] = 0.21f;
			g_scene2_1_RectangleColors_3[5] = 0.04f;
			g_scene2_1_RectangleColors_3[6] = 0.72f;
			g_scene2_1_RectangleColors_3[7] = 0.21f;
			g_scene2_1_RectangleColors_3[8] = 0.04f;
			g_scene2_1_RectangleColors_3[9] = 0.72f;
			g_scene2_1_RectangleColors_3[10] = 0.21f;
			g_scene2_1_RectangleColors_3[11] = 0.04f;
		}
		break;
	case 2: // Compression to Combustion
		break;
	case 3: // Combustion to Black
			//ZeroMemory((void*)&g_scene2_1_RectangleColors_1, sizeof(g_scene2_1_RectangleColors_1));
		g_scene2_1_RectangleColors_3[0] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[1] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[2] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[3] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[4] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[5] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[6] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[7] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[8] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[9] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[10] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_3[11] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		if ((g_scene2_1_RectangleColors_3[0] <= 0.0f) & (g_scene2_1_RectangleColors_3[1] <= 0.0f) & (g_scene2_1_RectangleColors_3[2] <= 0.0f))
			ZeroMemory((void*)&g_scene2_1_RectangleColors_3, sizeof(g_scene2_1_RectangleColors_3));

		break;

	}
	// Cheating Board End
	/*** View Port 3 End   ***/

	/*** View Port 4 Start ***/
	if (g_scene2_1_bSyncFlag_Inlet_4 == true)
	{
		if (!g_scene2_1_bInletValveIncFlag_4)
		{
			rect_color_states_4 = 0;
			g_scene2_1_inletValve_inc_factor_4[0] = g_scene2_1_inletValve_inc_factor_4[0] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_inletValve_inc_factor_4[1] = g_scene2_1_inletValve_inc_factor_4[1] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_inletValve_inc_factor_4[0] >= -0.9f) & (g_scene2_1_inletValve_inc_factor_4[1] <= 0.9f))
				g_scene2_1_bInletValveIncFlag_4 = true;
		}
		else
		{

			g_scene2_1_inletValve_inc_factor_4[0] = g_scene2_1_inletValve_inc_factor_4[0] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			g_scene2_1_inletValve_inc_factor_4[1] = g_scene2_1_inletValve_inc_factor_4[1] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((g_scene2_1_inletValve_inc_factor_4[0] <= -1.2f) & (g_scene2_1_inletValve_inc_factor_4[1] >= 1.2f))
			{
				g_scene2_1_bInletValveIncFlag_4 = false;
				g_scene2_1_bSyncFlag_Inlet_4 = false;
				rect_color_states_4 = 1;
			}
		}
	}

	if (g_scene2_1_bPistionIncFlag_4)// Piston Up
	{
		g_scene2_1_piston_inc_factor_4 = g_scene2_1_piston_inc_factor_4 + SCENE2_1_PISTON_POS_CHANGE_FACTOR;
		if (g_scene2_1_piston_inc_factor_4 >= 0.3f)
			g_scene2_1_bPistionIncFlag_4 = false;

	}
	else // Piston Down
	{
		g_scene2_1_piston_inc_factor_4 = g_scene2_1_piston_inc_factor_4 - SCENE2_1_PISTON_POS_CHANGE_FACTOR;
		if (g_scene2_1_piston_inc_factor_4 <= -2.5f)
		{
			g_scene2_1_bPistionIncFlag_4 = true;
			g_scene2_1_piston_down_count_4++;
		}

	}

	// Enable Outlet at 2nd Down Pos Piston
	// Output Valve
	// Init value { 1.0f,1.0f,-14.5f };
	// Final Value { 0.9f,0.9f,-14.5f };
	if (g_scene2_1_piston_down_count_4 >= (short)2)
	{
		rect_color_states_4 = 3;
		if (!gbOutletValveIncFlag_4)
		{
			outletValve_inc_factor_4[0] = outletValve_inc_factor_4[0] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			outletValve_inc_factor_4[1] = outletValve_inc_factor_4[1] - SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((outletValve_inc_factor_4[0] <= 0.9f) & (outletValve_inc_factor_4[1] <= 0.9f))
			{
				gbOutletValveIncFlag_4 = true;
				rect_color_states_4 = 4;
			}
		}
		else
		{
			outletValve_inc_factor_4[0] = outletValve_inc_factor_4[0] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			outletValve_inc_factor_4[1] = outletValve_inc_factor_4[1] + SCENE2_1_VALVE_POS_CHANGE_FACTOR;
			if ((outletValve_inc_factor_4[0] >= 1.2f) & (outletValve_inc_factor_4[1] >= 1.2f))
			{
				gbOutletValveIncFlag_4 = false;
				g_scene2_1_piston_down_count_4 = 0;
				g_scene2_1_bSyncFlag_Inlet_4 = true;
				rect_color_states_4 = 0;
			}
		}
	}

	// Cheating Board Start
	if (g_scene2_1_bIncrementbRect_4)
	{
		g_scene2_1_RectangleVertices_4[7] += SCENE2_1_RECT_CHANGE_FACTOR;
		g_scene2_1_RectangleVertices_4[10] += SCENE2_1_RECT_CHANGE_FACTOR;
		if ((g_scene2_1_RectangleVertices_4[7] >= 0.3f) & (g_scene2_1_RectangleVertices_4[10] >= 0.3f))
			g_scene2_1_bIncrementbRect_4 = false;
	}
	else
	{
		g_scene2_1_RectangleVertices_4[7] -= SCENE2_1_RECT_CHANGE_FACTOR;
		g_scene2_1_RectangleVertices_4[10] -= SCENE2_1_RECT_CHANGE_FACTOR;

		if ((g_scene2_1_RectangleVertices_4[7] <= -2.5f) & (g_scene2_1_RectangleVertices_4[10] <= -2.5f))
			g_scene2_1_bIncrementbRect_4 = true;
	}


	switch (rect_color_states_4)
	{
	case 0:// Black to blue
		g_scene2_1_RectangleColors_4[0] = 0.0f;
		g_scene2_1_RectangleColors_4[1] = 0.0f;
		g_scene2_1_RectangleColors_4[2] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_4[3] = 0.0f;
		g_scene2_1_RectangleColors_4[4] = 0.0f;
		g_scene2_1_RectangleColors_4[5] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_4[6] = 0.0f;
		g_scene2_1_RectangleColors_4[7] = 0.0f;
		g_scene2_1_RectangleColors_4[8] += SCENE2_1_COLOR_CHANGE_FACTOR;
		g_scene2_1_RectangleColors_4[9] = 0.0f;
		g_scene2_1_RectangleColors_4[10] = 0.0f;
		g_scene2_1_RectangleColors_4[11] += SCENE2_1_COLOR_CHANGE_FACTOR;
		break;
	case 1://	0.72, 0.21, 0.04
		   // Blue to color for compression
		g_scene2_1_RectangleColors_4[0] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[1] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[2] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[3] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[4] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[5] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[6] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[7] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[8] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[9] += (2 * SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[10] += (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[11] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		if ((g_scene2_1_RectangleColors_4[0] >= 0.72f) & (g_scene2_1_RectangleColors_4[1] >= 0.21f) & (g_scene2_1_RectangleColors_4[2] <= 0.04f))
		{
			g_scene2_1_RectangleColors_4[0] = 0.72f;
			g_scene2_1_RectangleColors_4[1] = 0.21f;
			g_scene2_1_RectangleColors_4[2] = 0.04f;
			g_scene2_1_RectangleColors_4[3] = 0.72f;
			g_scene2_1_RectangleColors_4[4] = 0.21f;
			g_scene2_1_RectangleColors_4[5] = 0.04f;
			g_scene2_1_RectangleColors_4[6] = 0.72f;
			g_scene2_1_RectangleColors_4[7] = 0.21f;
			g_scene2_1_RectangleColors_4[8] = 0.04f;
			g_scene2_1_RectangleColors_4[9] = 0.72f;
			g_scene2_1_RectangleColors_4[10] = 0.21f;
			g_scene2_1_RectangleColors_4[11] = 0.04f;
		}
		break;
	case 2: // Compression to Combustion
		break;
	case 3: // Combustion to Black
			//ZeroMemory((void*)&g_scene2_1_RectangleColors_4, sizeof(g_scene2_1_RectangleColors_4));
		g_scene2_1_RectangleColors_4[0] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[1] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[2] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[3] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[4] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[5] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[6] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[7] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[8] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[9] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[10] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		g_scene2_1_RectangleColors_4[11] -= (SCENE2_1_COLOR_CHANGE_FACTOR);
		if ((g_scene2_1_RectangleColors_4[0] <= 0.0f) & (g_scene2_1_RectangleColors_4[1] <= 0.0f) & (g_scene2_1_RectangleColors_4[2] <= 0.0f))
			ZeroMemory((void*)&g_scene2_1_RectangleColors_4, sizeof(g_scene2_1_RectangleColors_4));

		break;

	}
	// Cheating Board End
	/*** View Port 4 End   ***/

	// Stop the Rendering of Scene 2 If Music is done playing
	if (g_pSS_Scene2_SoundSource->isPlaying())
	{
		// show Scene 2
		g_scene2_bShowScene2 = true;
	}
	else
	{
		// stop scene 2
		g_scene2_bShowScene2 = false;
		g_scene3_bShowScene3 = true;
	}

}

//void resize(int width, int height)
//{
//	if (height == 0)
//		height = 1;
//	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
//
//	g_scene2_1_PerspectiveProjectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
//}

void Scene2_UnInitialize(int i_Exit_Flag)
{
	/*if (gbFullscreen == false)
	{
	SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
	SetWindowPlacement(ghwnd, &wpPrev);
	SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	ShowCursor(TRUE);
	}*/

	if (frFontRenderer_InletletValveText)
	{
		delete frFontRenderer_InletletValveText;
		frFontRenderer_InletletValveText = NULL;
	}

	if (frFontRenderer_OutletletValveText)
	{
		delete frFontRenderer_OutletletValveText;
		frFontRenderer_OutletletValveText = NULL;
	}

	if (frFontRenderer_SparkPlugText)
	{
		delete frFontRenderer_SparkPlugText;
		frFontRenderer_SparkPlugText = NULL;
	}

	if (frFontRenderer_PistonText)
	{
		delete frFontRenderer_PistonText;
		frFontRenderer_PistonText = NULL;
	}

	if (frFontRenderer_MainBoreText)
	{
		delete frFontRenderer_MainBoreText;
		frFontRenderer_MainBoreText = NULL;
	}

	if (frFontRenderer_IntakeText)
	{
		delete frFontRenderer_IntakeText;
		frFontRenderer_IntakeText = NULL;
	}

	if (frFontRenderer_CompressionText)
	{
		delete frFontRenderer_CompressionText;
		frFontRenderer_CompressionText = NULL;
	}

	if (frFontRenderer_PowerText)
	{
		delete frFontRenderer_PowerText;
		frFontRenderer_PowerText = NULL;
	}

	if (frFontRenderer_ExhaustText)
	{
		delete frFontRenderer_ExhaustText;
		frFontRenderer_ExhaustText = NULL;
	}

	if (g_scene2_1_Vao_Piston)
	{
		glDeleteVertexArrays(1, &g_scene2_1_Vao_Piston);
		g_scene2_1_Vao_Piston = 0;
	}

	if (g_scene2_1_VertexArrayObject_Rectangle)
	{
		glDeleteVertexArrays(1, &g_scene2_1_VertexArrayObject_Rectangle);
		g_scene2_1_VertexArrayObject_Rectangle = 0;
	}

	if (g_scene2_1_VertexArrayObject_Particle_Inlet)
	{
		glDeleteVertexArrays(1, &g_scene2_1_VertexArrayObject_Particle_Inlet);
		g_scene2_1_VertexArrayObject_Particle_Inlet = 0;
	}

	if (g_scene2_1_VertexArrayObject_Particle_Outlet)
	{
		glDeleteVertexArrays(1, &g_scene2_1_VertexArrayObject_Particle_Outlet);
		g_scene2_1_VertexArrayObject_Particle_Outlet = 0;
	}

	if (g_scene2_1_VertexArrayObject_Particle_Spark)
	{
		glDeleteVertexArrays(1, &g_scene2_1_VertexArrayObject_Particle_Spark);
		g_scene2_1_VertexArrayObject_Particle_Spark = 0;
	}

	if (g_scene2_Line_VertexArrayObject)
	{
		glDeleteVertexArrays(1, &g_scene2_Line_VertexArrayObject);
		g_scene2_Line_VertexArrayObject = 0;
	}

	if (g_scene2_Line_VertexBufferObject_Position)
	{
		glDeleteBuffers(1, &g_scene2_Line_VertexBufferObject_Position);
		g_scene2_1_Vbo_Position = 0;
	}
	if (g_scene2_1_Vbo_Position)
	{
		glDeleteBuffers(1, &g_scene2_1_Vbo_Position);
		g_scene2_1_Vbo_Position = 0;
	}
	if (g_scene2_1_Vbo_Normal)
	{
		glDeleteBuffers(1, &g_scene2_1_Vbo_Normal);
		g_scene2_1_Vbo_Normal = 0;
	}

	if (g_scene2_1_VertexBufferObject_Rectangle_Color)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_Rectangle_Color);
		g_scene2_1_VertexBufferObject_Rectangle_Color = 0;
	}
	if (g_scene2_1_VertexBufferObject_Rectangle_Pos)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_Rectangle_Pos);
		g_scene2_1_VertexBufferObject_Rectangle_Pos = 0;
	}

	if (g_scene2_1_VertexBufferObject_ParticlePosition_Inlet)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticlePosition_Inlet);
		g_scene2_1_VertexBufferObject_ParticlePosition_Inlet = 0;
	}
	if (g_scene2_1_VertexBufferObject_ParticleColor_Inlet)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticleColor_Inlet);
		g_scene2_1_VertexBufferObject_ParticleColor_Inlet = 0;
	}
	if (g_scene2_1_VertexBufferObject_ParticleStartTime_Inlet)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticleStartTime_Inlet);
		g_scene2_1_VertexBufferObject_ParticleStartTime_Inlet = 0;
	}
	if (g_scene2_1_VertexBufferObject_ParticleVelocity_Inlet)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticleVelocity_Inlet);
		g_scene2_1_VertexBufferObject_ParticleVelocity_Inlet = 0;
	}

	if (g_scene2_1_VertexBufferObject_ParticlePosition_Outlet)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticlePosition_Outlet);
		g_scene2_1_VertexBufferObject_ParticlePosition_Outlet = 0;
	}
	if (g_scene2_1_VertexBufferObject_ParticleColor_Outlet)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticleColor_Outlet);
		g_scene2_1_VertexBufferObject_ParticleColor_Outlet = 0;
	}
	if (g_scene2_1_VertexBufferObject_ParticleStartTime_Outlet)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticleStartTime_Outlet);
		g_scene2_1_VertexBufferObject_ParticleStartTime_Outlet = 0;
	}
	if (g_scene2_1_VertexBufferObject_ParticleVelocity_Outlet)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticleVelocity_Outlet);
		g_scene2_1_VertexBufferObject_ParticleVelocity_Outlet = 0;
	}

	if (g_scene2_1_VertexBufferObject_ParticlePosition_Spark)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticlePosition_Spark);
		g_scene2_1_VertexBufferObject_ParticlePosition_Spark = 0;
	}
	if (g_scene2_1_VertexBufferObject_ParticleColor_Spark)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticleColor_Spark);
		g_scene2_1_VertexBufferObject_ParticleColor_Spark = 0;
	}
	if (g_scene2_1_VertexBufferObject_ParticleStartTime_Spark)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticleStartTime_Spark);
		g_scene2_1_VertexBufferObject_ParticleStartTime_Spark = 0;
	}
	if (g_scene2_1_VertexBufferObject_ParticleVelocity_Spark)
	{
		glDeleteBuffers(1, &g_scene2_1_VertexBufferObject_ParticleVelocity_Spark);
		g_scene2_1_VertexBufferObject_ParticleVelocity_Spark = 0;
	}

	//Detach Shader 
	glDetachShader(g_scene2_1_ShaderProgramObject, g_scene2_1_VertexShaderObject);
	glDetachShader(g_scene2_1_ShaderProgramObject, g_scene2_1_FragmentShaderObject);

	glDetachShader(g_scene2_1_ShaderProgramObject_Rectangle, g_scene2_1_VertexShaderObject_Rectangle);
	glDetachShader(g_scene2_1_ShaderProgramObject_Rectangle, g_scene2_1_FragmentShaderObject_Rectangle);

	glDetachShader(g_scene2_1_ShaderProgramObject_Particle_Inlet, g_scene2_1_VertexShaderObject_Particle_Inlet);
	glDetachShader(g_scene2_1_ShaderProgramObject_Particle_Inlet, g_scene2_1_FragmentShaderObject_Particle_Inlet);

	glDetachShader(g_scene2_1_ShaderProgramObject_Particle_Outlet, g_scene2_1_VertexShaderObject_Particle_Outlet);
	glDetachShader(g_scene2_1_ShaderProgramObject_Particle_Outlet, g_scene2_1_FragmentShaderObject_Particle_Outlet);

	glDetachShader(g_scene2_1_ShaderProgramObject_Spark, g_scene2_1_VertexShaderObject_Spark);
	glDetachShader(g_scene2_1_ShaderProgramObject_Spark, g_scene2_1_FragmentShaderObject_Spark);

	glDetachShader(g_scene2_Line_ShaderProgramObject, g_scene2_Line_VertexShaderObject);
	glDetachShader(g_scene2_Line_ShaderProgramObject, g_scene2_Line_FragmentShaderObject);

	//Delete Shader
	glDeleteShader(g_scene2_1_VertexShaderObject);
	g_scene2_1_VertexShaderObject = 0;
	glDeleteShader(g_scene2_1_FragmentShaderObject);
	g_scene2_1_FragmentShaderObject = 0;

	glDeleteShader(g_scene2_1_VertexShaderObject_Rectangle);
	g_scene2_1_VertexShaderObject_Rectangle = 0;
	glDeleteShader(g_scene2_1_FragmentShaderObject_Rectangle);
	g_scene2_1_FragmentShaderObject_Rectangle = 0;

	glDeleteShader(g_scene2_1_VertexShaderObject_Particle_Inlet);
	g_scene2_1_VertexShaderObject_Particle_Inlet = 0;
	glDeleteShader(g_scene2_1_FragmentShaderObject_Particle_Inlet);
	g_scene2_1_FragmentShaderObject_Particle_Inlet = 0;

	glDeleteShader(g_scene2_1_VertexShaderObject_Particle_Outlet);
	g_scene2_1_VertexShaderObject_Particle_Outlet = 0;
	glDeleteShader(g_scene2_1_FragmentShaderObject_Particle_Outlet);
	g_scene2_1_FragmentShaderObject_Particle_Outlet = 0;

	glDeleteShader(g_scene2_1_VertexShaderObject_Spark);
	g_scene2_1_VertexShaderObject_Spark = 0;
	glDeleteShader(g_scene2_1_FragmentShaderObject_Spark);
	g_scene2_1_FragmentShaderObject_Spark = 0;

	glDeleteShader(g_scene2_Line_VertexShaderObject);
	g_scene2_Line_VertexShaderObject = 0;
	glDeleteShader(g_scene2_Line_FragmentShaderObject);
	g_scene2_Line_FragmentShaderObject = 0;

	//Delete Program
	glDeleteProgram(g_scene2_1_ShaderProgramObject);
	g_scene2_1_ShaderProgramObject = 0;

	glDeleteProgram(g_scene2_1_ShaderProgramObject_Rectangle);
	g_scene2_1_ShaderProgramObject_Rectangle = 0;

	glDeleteProgram(g_scene2_1_ShaderProgramObject_Particle_Inlet);
	g_scene2_1_ShaderProgramObject_Particle_Inlet = 0;

	glDeleteProgram(g_scene2_1_ShaderProgramObject_Particle_Outlet);
	g_scene2_1_ShaderProgramObject_Particle_Outlet = 0;

	glDeleteProgram(g_scene2_1_ShaderProgramObject_Spark);
	g_scene2_1_ShaderProgramObject_Spark = 0;

	glDeleteProgram(g_scene2_Line_ShaderProgramObject);
	g_scene2_Line_ShaderProgramObject = 0;

	//Stray call to glUseProgram(0)
	glUseProgram(0);

	

	
}

