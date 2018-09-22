#include "Common_Header.h"

#pragma comment(lib,"opengl32.lib")
//#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"C:\\glew\\lib\\Release\\x64\\glew32.lib")
#pragma comment(lib,"openal32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define SCENE1_MODEL_X_TRANSLATE		0.0f	//X-translation of MODEL
#define SCENE1_MODEL_Y_TRANSLATE		-1.0f	//Y-translation of MODEL
#define SCENE1_MODEL_Z_TRANSLATE		-5.0f	//Z-translation of MODEL

#define SCENE1_MODEL_X_SCALE_FACTOR	1.5f	//X-scale factor of MODEL
#define SCENE1_MODEL_Y_SCALE_FACTOR	1.5f	//Y-scale factor of MODEL
#define SCENE1_MODEL_Z_SCALE_FACTOR	1.5f	//Z-scale factor of MODEL

#define SCENE1_START_ANGLE_POS			0.0f	//Marks beginning angle position of rotation
#define SCENE1_END_ANGLE_POS			360.0f	//Marks terminating angle position rotation
#define SCENE1_MODEL_ANGLE_INCREMENT	0.1f	//Increment angle for MODEL

#define SCENE1_DOOR_OPENING_SOUND_POSITION 0.0f

enum
{
	SCENE1_ATTRIBUTE_POSITION = 0,
	SCENE1_ATTRIBUTE_COLOR,
	SCENE1_ATTRIBUTE_NORMAL,
	SCENE1_ATTRIBUTE_TEXTURE0,
};

bool Scene1_gbDoor_Open_Flag = false;
bool Scene1_gbUpper_Middle_Light_On_Flag = false;
bool Scene1_gbUpper_Side_Light_On_Flag = false;
bool Scene1_gbInner_Side_Light_On_Flag = false;
bool Scene1_Black_Out_Flag = false;

struct Scene1_PointLight
{
	GLfloat lightAmbient[4] = { 0.2f,0.2f,0.2f,1.0f };
	GLfloat lightDiffuse[4] = { 0.5f,0.5f,0.5f,1.0f };
	GLfloat lightSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat lightPosition[3] = { -3.899998f, -0.600000f, -15.000002f };
	GLfloat gConstant = 1.0f;
	GLfloat gLinear = 1.419999f;
	GLfloat gQuadratic = 0.090000f;
	GLuint gLaUniform;
	GLuint gLdUniform;
	GLuint gLsUniform;
	GLuint gConstantUniform;
	GLuint gLinearUniform;
	GLuint gQuadraticUniform;
	GLuint gLightPositionUniform;
}Scene1_pointLight;

struct SpotLight
{
	GLfloat lightAmbient[4] = { 0.1f,0.1f,0.1f,1.0f };
	GLfloat lightDiffuse[4] = { 0.8f,0.8f,0.8f,1.0f };
	GLfloat lightSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat lightPosition[3] = { 0.099999f, 2.299999f, -48.299911f };
	GLfloat lightDirection[3] = { 0.0f, -1.0f, 0.0f };
	GLfloat gConstant = 1.0f;
	GLfloat gLinear = 0.09f;
	GLfloat gQuadratic = 0.032f;
	GLfloat cutoff_angle = 12.5f;
	GLfloat outer_cutoff_angle = 17.5f;
	GLuint gLaUniform;
	GLuint gLdUniform;
	GLuint gLsUniform;
	GLuint gLightPositionUniform;
	GLuint gLightDirectionUniform;
	GLuint gConstantUniform;
	GLuint gLinearUniform;
	GLuint gQuadraticUniform;
	GLuint gCutOffUniform;
	GLuint gOuterCutOffUniform;
}spotLight;

struct MaterialProperties
{
	GLfloat materialAmbient[4] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat materialDiffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat materialSpecular[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat materialShininess = 50.0f;
	GLuint gKaUniform;
	GLuint gKdUniform;
	GLuint gKsUniform;
	GLuint gMaterialShininessUniform;
}Scene1_materialProperties;

struct Model
{
	GLuint Vao;
	std::vector<float> gv_vertices;
	std::vector<float> gv_textures;
	std::vector<float> gv_normals;
	int count_of_vertices;
};

Model Scene1_Gaurage_Body;
Model Scene1_Gaurage_Outer_Light;
Model Scene1_Gaurage_Inner_Upper_Middle_Light;
Model Scene1_Gaurage_Inner_Upper_Side_Light;
Model Scene1_Gaurage_Inner_Side_Light;
Model Scene1_Mustang;
Model Scene1_Left_Door;
Model Scene1_Right_Door;

GLfloat Scene1_pointLight1[3] = { 3.899998f, -0.700000f, -8.899998f };
GLfloat Scene1_pointLight2[3] = { 3.999998f, 2.100000f, -8.899998f };
GLfloat Scene1_pointLight3[3] = { -3.799999f, 2.000000f, -8.699999f };
GLfloat Scene1_pointLight4[3] = { -3.999998f, -0.600000f, -8.899998f };
GLfloat Scene1_pointLight5[3] = { 3.899998f, -0.700000f, -15.000002f };
GLfloat Scene1_pointLight6[3] = { 3.899998f, 2.000000f, -15.000002f };
GLfloat Scene1_pointLight7[3] = { -3.899998f, 2.000000f, -15.000002f };
GLfloat Scene1_pointLight8[3] = { -3.899998f, -0.600000f, -15.000002f };
GLfloat Scene1_pointLight9[3] = { 3.899999f, -0.700000f, -21.300026f };
GLfloat Scene1_pointLight10[3] = { 3.899999f, 2.100000f, -21.300026f };
GLfloat Scene1_pointLight11[3] = { -4.099998f, 2.100000f, -21.300026f };
GLfloat Scene1_pointLight12[3] = { -4.099998f, -0.600000f, -21.300026f };
GLfloat Scene1_pointLight13[3] = { 3.799999f, -0.700000f, -27.300049f };
GLfloat Scene1_pointLight14[3] = { 3.899999f, 2.000000f, -27.300049f };
GLfloat Scene1_pointLight15[3] = { -3.799998f, 2.000000f, -27.400049f };
GLfloat Scene1_pointLight16[3] = { -3.799998f, -0.600000f, -27.400049f };
GLfloat Scene1_pointLight17[3] = { 3.799999f, -0.700000f, -33.600073f };
GLfloat Scene1_pointLight18[3] = { 3.899999f, 2.000000f, -33.600073f };
GLfloat Scene1_pointLight19[3] = { -3.799998f, 2.100000f, -33.600073f };
GLfloat Scene1_pointLight20[3] = { -3.799998f, -0.600000f, -33.600073f };
GLfloat Scene1_pointLight21[3] = { -1.700001f, 2.299999f, -49.599892f };
GLfloat Scene1_pointLight22[3] = { 1.700000f, 2.299999f, -49.599892f };
GLfloat Scene1_pointLight23[3] = { 1.600000f, 2.299999f, -53.999825f };
GLfloat Scene1_pointLight24[3] = { -1.700001f, 2.299999f, -53.999825f };
GLfloat Scene1_pointLight25[3] = { -4.899998f, 2.399999f, -45.099960f };
GLfloat Scene1_pointLight26[3] = { 4.999997f, 2.399999f, -45.099960f };
GLfloat Scene1_pointLight27[3] = { 4.899997f, 2.299999f, -58.499756f };
GLfloat Scene1_pointLight28[3] = { -5.099998f, 2.299999f, -58.499756f };
GLfloat Scene1_pointLight29[3] = { -7.199996f, 0.699999f, -46.699936f };
GLfloat Scene1_pointLight30[3] = { -7.199996f, 0.699999f,-51.599861f };
GLfloat Scene1_pointLight31[3] = { -7.199996f, 0.699999f, -56.699783f };
GLfloat Scene1_pointLight32[3] = { 7.199995f, 0.699999f, -56.699783f };
GLfloat Scene1_pointLight33[3] = { 7.199995f, 0.699999f, -51.699860f };
GLfloat Scene1_pointLight34[3] = { 7.199996f, 0.699999f, -46.699936f };

GLuint Scene1_gLightUniform[34];

GLuint Scene1_gVertexShaderObject;
GLuint Scene1_gFragmentShaderObject;
GLuint Scene1_gShaderProgramObject;

GLuint Scene1_gVbo_Position, Scene1_gVbo_Normal;

GLuint Scene1_gModelMatrixUniform, Scene1_gViewMatrixUniform, Scene1_gProjectionMatrixUniform;
GLuint Scene1_gLKeyPressedUniform;
GLuint Scene1_blackOutColorUniform;
GLuint Scene1_blackOutUniform;

GLuint Scene1_Scene1_gViewPositionUniform;
GLuint Scene1_gNumberOfLightsUniform;

glm::mat4 Scene1_gPerspectiveProjectionMatrix;

glm::vec3 Scene1_gViewPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 Scene1_blackOutColor = glm::vec3(1.0f, 1.0f, 1.0f);

GLfloat lastX = WIN_WIDTH / 2.0;
GLfloat lastY = WIN_HEIGHT / 2.0;

glm::vec3 Scene1_cameraPosition;
glm::vec3 Scene1_cameraTarget;
glm::vec3 Scene1_cameraUP;
Camera Scene1_camera;

AudioManager *Scene1_audioManager = NULL;
SoundSource *Scene1_soundSourcePointLight = NULL;
SoundSource *Scene1_soundSourceDoorOpening = NULL;
SoundSource *Scene1_soundSourceSpotLight1 = NULL;
SoundSource *Scene1_soundSourceSpotLight2 = NULL;
SoundSource *Scene1_soundSourceSpotLight3 = NULL;
SoundSource *Scene1_soundSourceSpotLight4 = NULL;
ALuint Scene1_audioBufferIdPointLight = 0;
ALuint Scene1_audioBufferIdDoorOpening = 0;
ALuint Scene1_audioBufferIdSpotLight = 0;

int Scene1_giNumberOfLights = 20;
int Scene1_camera_Z_counter = 0.0f;
GLfloat deltaTime = 0.0f;
uint64_t initTime, initFrequency, changingTime;
GLfloat currentFrame = 0.0f, lastFrame = 0.0f;
GLfloat gfScene1_Left_Door_Translate = 0.0f;
GLfloat gfScene1_Right_Door_Translate = 0.0f;

void Scene1_loadPointLightAudio(void);
void Scene1_loadDoorOpeningAudio(void);
void Scene1_loadSpotLightAudio(void);
void Scene1_initializeAudio(void);
void Scene1_blackOut(void);

void Init_Scene1(void)
{
	void initializeObjects(void);
	Scene1_initializeAudio();

	//MessageBox(ghwnd, TEXT("Before LoadMeshData"), TEXT("MSG"), MB_OK);
	Scene1_Gaurage_Body.count_of_vertices = LoadMeshData("Gaurage_Body.obj", Scene1_Gaurage_Body.gv_vertices, Scene1_Gaurage_Body.gv_textures, Scene1_Gaurage_Body.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 1"), TEXT("MSG"), MB_OK);
	Scene1_Gaurage_Outer_Light.count_of_vertices = LoadMeshData("Outer_Lights.obj", Scene1_Gaurage_Outer_Light.gv_vertices, Scene1_Gaurage_Outer_Light.gv_textures, Scene1_Gaurage_Outer_Light.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 2"), TEXT("MSG"), MB_OK);
	Scene1_Gaurage_Inner_Upper_Middle_Light.count_of_vertices = LoadMeshData("Inner_Gaurage_Upper_Light_Middle.obj", Scene1_Gaurage_Inner_Upper_Middle_Light.gv_vertices, Scene1_Gaurage_Inner_Upper_Middle_Light.gv_textures, Scene1_Gaurage_Inner_Upper_Middle_Light.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 3"), TEXT("MSG"), MB_OK);
	Scene1_Gaurage_Inner_Upper_Side_Light.count_of_vertices = LoadMeshData("Inner_Gaurage_Upper_Light_Side.obj", Scene1_Gaurage_Inner_Upper_Side_Light.gv_vertices, Scene1_Gaurage_Inner_Upper_Side_Light.gv_textures, Scene1_Gaurage_Inner_Upper_Side_Light.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 4"), TEXT("MSG"), MB_OK);
	Scene1_Gaurage_Inner_Side_Light.count_of_vertices = LoadMeshData("Inner_Gaurage_Side_Light.obj", Scene1_Gaurage_Inner_Side_Light.gv_vertices, Scene1_Gaurage_Inner_Side_Light.gv_textures, Scene1_Gaurage_Inner_Side_Light.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 5"), TEXT("MSG"), MB_OK);
	Scene1_Left_Door.count_of_vertices = LoadMeshData("Left_Door.obj", Scene1_Left_Door.gv_vertices, Scene1_Left_Door.gv_textures, Scene1_Left_Door.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 6"), TEXT("MSG"), MB_OK);
	Scene1_Right_Door.count_of_vertices = LoadMeshData("Right_Door.obj", Scene1_Right_Door.gv_vertices, Scene1_Right_Door.gv_textures, Scene1_Right_Door.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 6"), TEXT("MSG"), MB_OK);
	Scene1_Mustang.count_of_vertices = LoadMeshData("Mustang_GT\\Mustang_GT_new.obj", Scene1_Mustang.gv_vertices, Scene1_Mustang.gv_textures, Scene1_Mustang.gv_normals);
	//MessageBox(ghwnd, TEXT("After LoadMeshData 6"), TEXT("MSG"), MB_OK);


	//Vertex Shader
	Scene1_gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
		"#version 450" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_lighting_enabled;" \
		"out vec3 transformed_normals;" \
		"out vec3 FragPos;" \
		"void main(void)" \
		"{" \
		"if(u_lighting_enabled==1)" \
		"{" \
		"transformed_normals = mat3(u_view_matrix*u_model_matrix)*vNormal;" \
		"FragPos = vec3(u_model_matrix * vPosition);" \
		"}" \
		"gl_Position = u_projection_matrix*u_view_matrix*u_model_matrix*vPosition;" \
		"}";

	glShaderSource(Scene1_gVertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	glCompileShader(Scene1_gVertexShaderObject);
	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(Scene1_gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(Scene1_gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(Scene1_gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				logError("Vertex Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				exit(EXIT_FAILURE);
			}
		}
	}

	//Fragment Shader
	Scene1_gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 450" \
		"\n" \
		"in vec3 transformed_normals;" \
		"in vec3 FragPos;" \

		"struct PointLight" \
		"{" \
		"vec3 u_La;" \
		"vec3 u_Ld;" \
		"vec3 u_Ls;" \
		"float u_constant;" \
		"float u_linear;" \
		"float u_quadratic;" \
		/*"vec3 u_light_position;" \*/
		"};" \

		"struct SpotLight" \
		"{" \
		"vec3 u_La;" \
		"vec3 u_Ld;" \
		"vec3 u_Ls;" \
		"float constant;" \
		"float linear;" \
		"float quadratic;" \
		"vec3 u_light_position;" \
		"vec3 u_light_direction;" \
		"float u_cutOff;" \
		"float u_outerCutOff;" \
		"};" \

		"struct Material" \
		"{" \
		"float u_material_shininess;" \
		"vec3 u_Ka;" \
		"vec3 u_Kd;" \
		"vec3 u_Ks;" \
		"};" \

		"uniform int u_lighting_enabled;" \
		"uniform vec3 u_viewPos;" \
		"uniform PointLight pointlight;" \
		"uniform SpotLight spotlight;" \
		"uniform Material material;" \
		"uniform vec3 u_light_position[34];" \
		"uniform int u_number_of_lights;" \
		"uniform vec3 u_black_out_color;" \
		"uniform int u_black_out;" \

		"out vec4 FragColor;" \

		"vec3 CalculatePointLight(vec3 lightpos)" \
		"{" \
		"vec3 ambient = pointlight.u_La * material.u_Ka;" \
		"vec3 normalized_transformed_normals = normalize(transformed_normals);" \
		"vec3 normalized_light_direction = normalize(lightpos);" \
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);" \
		"vec3 diffuse = pointlight.u_Ld * material.u_Kd * tn_dot_ld;" \
		"vec3 view_direction = normalize(u_viewPos - FragPos);" \
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);" \
		"vec3 specular = pointlight.u_Ls * material.u_Ks * pow(max(dot(reflection_vector,view_direction),0.0),material.u_material_shininess);" \
		"float distance = length(lightpos-FragPos);" \
		"float attenuation = 1.0 / (pointlight.u_constant + pointlight.u_linear * distance + pointlight.u_quadratic * (distance * distance));" \
		/*"ambient = ambient * attenuation;" \*/
		"diffuse = diffuse * attenuation;" \
		"specular = specular * attenuation;" \
		"return(ambient + diffuse + specular);" \
		"}" \

		"vec3 CalculateSpotLight(void)" \
		"{" \
		"vec3 ambient = spotlight.u_La * material.u_Ka;" \

		"vec3 normalized_transformed_normals = normalize(transformed_normals);" \
		"vec3 normalized_light_direction = normalize(spotlight.u_light_position - FragPos);" \
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);" \
		"vec3 diffuse = spotlight.u_Ld * material.u_Kd * tn_dot_ld;" \

		"vec3 view_direction = normalize(u_viewPos - FragPos);" \
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);" \
		"vec3 specular = spotlight.u_Ls * material.u_Ks * pow(max(dot(reflection_vector,view_direction),0.0),material.u_material_shininess);" \

		"float theta = dot(normalized_light_direction,normalize(-spotlight.u_light_direction));" \
		"float epsilon = (spotlight.u_cutOff - spotlight.u_outerCutOff);" \
		"float intensity = clamp((theta - spotlight.u_outerCutOff) / epsilon, 0.0, 1.0);" \
		"diffuse = diffuse + intensity;" \
		"specular = specular + intensity;" \

		"float distance = length(spotlight.u_light_position-FragPos);" \
		"float attenuation = 1.0 / (spotlight.constant + spotlight.linear * distance + spotlight.quadratic * (distance * distance));" \
		"ambient = ambient * attenuation;" \
		"diffuse = diffuse * attenuation;" \
		"specular = specular * attenuation;" \
		"return(ambient + diffuse + specular);" \
		"}" \

		"void main(void)" \
		"{" \
		"vec3 phong_ads_color;" \
		"if(u_lighting_enabled == 1)" \
		"{" \
		/*"phong_ads_color = CalculatePointLight(u_light_position);" \*/
		"for(int i = 0; i < u_number_of_lights; i++)" \
		"{" \
		"phong_ads_color += CalculatePointLight(u_light_position[i]);" \
		/*"phong_ads_color += CalculateSpotLight();" \*/
		"}" \
		/*"phong_ads_color += CalculateSpotLight();"*/
		"}" \
		"else if(u_lighting_enabled == 0)" \
		"{" \
		"phong_ads_color = vec3(0.0f,0.0f,0.0f);" \
		"}" \
		"else" \
		"{" \
		"phong_ads_color = vec3(1.0f,1.0f,1.0f);" \
		"}" \
		"if(u_black_out == 1)" \
		"{" \
		"	FragColor = vec4(phong_ads_color,1.0) * vec4(u_black_out_color, 1.0f);" \
		"}" \
		"else" \
		"{" \
		"	FragColor = vec4(phong_ads_color,1.0);" \
		"}" \
		"}";

	glShaderSource(Scene1_gFragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	glCompileShader(Scene1_gFragmentShaderObject);

	glGetShaderiv(Scene1_gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(Scene1_gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(Scene1_gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				logError("Fragment Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				exit(EXIT_FAILURE);
			}
		}
	}

	//Shader Program
	Scene1_gShaderProgramObject = glCreateProgram();

	glAttachShader(Scene1_gShaderProgramObject, Scene1_gVertexShaderObject);

	glAttachShader(Scene1_gShaderProgramObject, Scene1_gFragmentShaderObject);

	glBindAttribLocation(Scene1_gShaderProgramObject, SCENE1_ATTRIBUTE_POSITION, "vPosition");

	glBindAttribLocation(Scene1_gShaderProgramObject, SCENE1_ATTRIBUTE_NORMAL, "vNormal");

	glLinkProgram(Scene1_gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;

	glGetProgramiv(Scene1_gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(Scene1_gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(Scene1_gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				logError("Shader Program Link Log : %s\n", szInfoLog);
				free(szInfoLog);
				exit(EXIT_FAILURE);
			}
		}
	}

	Scene1_gModelMatrixUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "u_model_matrix");
	Scene1_gViewMatrixUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "u_view_matrix");
	Scene1_gProjectionMatrixUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "u_projection_matrix");

	Scene1_gLKeyPressedUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "u_lighting_enabled");

	Scene1_gNumberOfLightsUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "u_number_of_lights");
	Scene1_blackOutColorUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "u_black_out_color");
	Scene1_blackOutUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "u_black_out");

	//Point Light Uniform
	Scene1_pointLight.gLaUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "pointlight.u_La");
	Scene1_pointLight.gLdUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "pointlight.u_Ld");
	Scene1_pointLight.gLsUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "pointlight.u_Ls");

	//pointLight.gLightPositionUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "pointlight.u_light_position");
	Scene1_pointLight.gConstantUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "pointlight.u_constant");
	Scene1_pointLight.gLinearUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "pointlight.u_linear");
	Scene1_pointLight.gQuadraticUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "pointlight.u_quadratic");

	Scene1_materialProperties.gKaUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "material.u_Ka");
	Scene1_materialProperties.gKdUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "material.u_Kd");
	Scene1_materialProperties.gKsUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "material.u_Ks");

	Scene1_materialProperties.gMaterialShininessUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "material.u_material_shininess");

	Scene1_Scene1_gViewPositionUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "u_viewPos");

	//Spot Light Uniform
	spotLight.gLaUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "spotlight.u_La");
	spotLight.gLdUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "spotlight.u_Ld");
	spotLight.gLsUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "spotlight.u_Ls");
	spotLight.gLightPositionUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "spotlight.u_light_position");

	spotLight.gConstantUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "spotlight.constant");
	spotLight.gLinearUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "spotlight.linear");
	spotLight.gQuadraticUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "spotlight.quadratic");

	spotLight.gLightDirectionUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "spotlight.u_light_direction");
	spotLight.gCutOffUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "spotlight.u_cutOff");
	spotLight.gOuterCutOffUniform = glGetUniformLocation(Scene1_gShaderProgramObject, "spotlight.u_outerCutOff");

	Scene1_gLightUniform[0] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[0]");
	Scene1_gLightUniform[1] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[1]");
	Scene1_gLightUniform[2] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[2]");
	Scene1_gLightUniform[3] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[3]");
	Scene1_gLightUniform[4] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[4]");
	Scene1_gLightUniform[5] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[5]");
	Scene1_gLightUniform[6] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[6]");
	Scene1_gLightUniform[7] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[7]");
	Scene1_gLightUniform[8] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[8]");
	Scene1_gLightUniform[9] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[9]");
	Scene1_gLightUniform[10] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[10]");
	Scene1_gLightUniform[11] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[11]");
	Scene1_gLightUniform[12] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[12]");
	Scene1_gLightUniform[13] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[13]");
	Scene1_gLightUniform[14] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[14]");
	Scene1_gLightUniform[15] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[15]");
	Scene1_gLightUniform[16] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[16]");
	Scene1_gLightUniform[17] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[17]");
	Scene1_gLightUniform[18] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[18]");
	Scene1_gLightUniform[19] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[19]");
	Scene1_gLightUniform[20] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[20]");
	Scene1_gLightUniform[21] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[21]");
	Scene1_gLightUniform[22] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[22]");
	Scene1_gLightUniform[23] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[23]");
	Scene1_gLightUniform[24] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[24]");
	Scene1_gLightUniform[25] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[25]");
	Scene1_gLightUniform[26] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[26]");
	Scene1_gLightUniform[27] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[27]");
	Scene1_gLightUniform[28] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[28]");
	Scene1_gLightUniform[29] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[29]");
	Scene1_gLightUniform[30] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[30]");
	Scene1_gLightUniform[31] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[31]");
	Scene1_gLightUniform[32] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[32]");
	Scene1_gLightUniform[33] = glGetUniformLocation(Scene1_gShaderProgramObject, "u_light_position[33]");

	initializeObjects();

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	Scene1_gPerspectiveProjectionMatrix = glm::mat4(1.0f);
	Scene1_cameraPosition = glm::vec3(0.0f, 0.0f, -5.0f);
	Scene1_cameraTarget = glm::vec3(0.0f, 0.0f, -100.0f);
	Scene1_cameraUP = glm::vec3(0.0f, 1.0f, 0.0f);
	Scene1_camera = Camera(Scene1_cameraPosition, Scene1_cameraTarget, Scene1_cameraUP);

}

void initializeObjects(void)
{
	/*****************VAO For Gaurage Body*****************/
	glGenVertexArrays(1, &Scene1_Gaurage_Body.Vao);
	glBindVertexArray(Scene1_Gaurage_Body.Vao);

	/*****************Gaurage Body Position****************/
	glGenBuffers(1, &Scene1_gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Gaurage_Body.gv_vertices.size() * sizeof(float), &Scene1_Gaurage_Body.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Body Normal****************/
	glGenBuffers(1, &Scene1_gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Gaurage_Body.gv_normals.size() * sizeof(float), &Scene1_Gaurage_Body.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Outer Light*****************/
	glGenVertexArrays(1, &Scene1_Gaurage_Outer_Light.Vao);
	glBindVertexArray(Scene1_Gaurage_Outer_Light.Vao);

	/*****************Gaurage Body Position****************/
	glGenBuffers(1, &Scene1_gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Gaurage_Outer_Light.gv_vertices.size() * sizeof(float), &Scene1_Gaurage_Outer_Light.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Body Normal****************/
	glGenBuffers(1, &Scene1_gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Gaurage_Outer_Light.gv_normals.size() * sizeof(float), &Scene1_Gaurage_Outer_Light.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Inner Upper Middle Light*****************/
	glGenVertexArrays(1, &Scene1_Gaurage_Inner_Upper_Middle_Light.Vao);
	glBindVertexArray(Scene1_Gaurage_Inner_Upper_Middle_Light.Vao);

	/*****************Gaurage Inner Upper Middle Light Position****************/
	glGenBuffers(1, &Scene1_gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Gaurage_Inner_Upper_Middle_Light.gv_vertices.size() * sizeof(float), &Scene1_Gaurage_Inner_Upper_Middle_Light.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Inner Upper Middle Light Normal****************/
	glGenBuffers(1, &Scene1_gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Gaurage_Inner_Upper_Middle_Light.gv_normals.size() * sizeof(float), &Scene1_Gaurage_Inner_Upper_Middle_Light.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Inner Upper Side Light*****************/
	glGenVertexArrays(1, &Scene1_Gaurage_Inner_Upper_Side_Light.Vao);
	glBindVertexArray(Scene1_Gaurage_Inner_Upper_Side_Light.Vao);

	/*****************Gaurage Inner Upper Side Light Position****************/
	glGenBuffers(1, &Scene1_gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Gaurage_Inner_Upper_Side_Light.gv_vertices.size() * sizeof(float), &Scene1_Gaurage_Inner_Upper_Side_Light.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Inner Upper Side Light Normal****************/
	glGenBuffers(1, &Scene1_gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Gaurage_Inner_Upper_Side_Light.gv_normals.size() * sizeof(float), &Scene1_Gaurage_Inner_Upper_Side_Light.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Inner Side Light*****************/
	glGenVertexArrays(1, &Scene1_Gaurage_Inner_Side_Light.Vao);
	glBindVertexArray(Scene1_Gaurage_Inner_Side_Light.Vao);

	/*****************Gaurage Inner Side Light Position****************/
	glGenBuffers(1, &Scene1_gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Gaurage_Inner_Side_Light.gv_vertices.size() * sizeof(float), &Scene1_Gaurage_Inner_Side_Light.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Inner Side Light Normal****************/
	glGenBuffers(1, &Scene1_gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Gaurage_Inner_Side_Light.gv_normals.size() * sizeof(float), &Scene1_Gaurage_Inner_Side_Light.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Left Door*****************/
	glGenVertexArrays(1, &Scene1_Left_Door.Vao);
	glBindVertexArray(Scene1_Left_Door.Vao);

	/*****************Gaurage Left Door****************/
	glGenBuffers(1, &Scene1_gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Left_Door.gv_vertices.size() * sizeof(float), &Scene1_Left_Door.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Left Door****************/
	glGenBuffers(1, &Scene1_gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Left_Door.gv_normals.size() * sizeof(float), &Scene1_Left_Door.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO For Gaurage Right Door*****************/
	glGenVertexArrays(1, &Scene1_Right_Door.Vao);
	glBindVertexArray(Scene1_Right_Door.Vao);

	/*****************Gaurage Right Door****************/
	glGenBuffers(1, &Scene1_gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Right_Door.gv_vertices.size() * sizeof(float), &Scene1_Right_Door.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Gaurage Right Door****************/
	glGenBuffers(1, &Scene1_gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Right_Door.gv_normals.size() * sizeof(float), &Scene1_Right_Door.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/*****************VAO Scene1_Mustang*****************/
	glGenVertexArrays(1, &Scene1_Mustang.Vao);
	glBindVertexArray(Scene1_Mustang.Vao);

	/*****************Scene1_Mustang Position****************/
	glGenBuffers(1, &Scene1_gVbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Position);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Mustang.gv_vertices.size() * sizeof(float), &Scene1_Mustang.gv_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Scene1_Mustang Normal****************/
	glGenBuffers(1, &Scene1_gVbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, Scene1_gVbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, Scene1_Mustang.gv_normals.size() * sizeof(float), &Scene1_Mustang.gv_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Display_Scene1(void)
{
	//Use Shader Program Object
	glUseProgram(Scene1_gShaderProgramObject);

	if (gbLight == true)
	{
		if(Scene1_Black_Out_Flag == true)
		{
			glUniform3fv(Scene1_blackOutColorUniform, 1, glm::value_ptr(Scene1_blackOutColor));
			glUniform1i(Scene1_blackOutUniform, 1);
		}

		if (Scene1_gbUpper_Middle_Light_On_Flag == true)
			Scene1_giNumberOfLights = 24;
		if (Scene1_gbUpper_Side_Light_On_Flag == true)
			Scene1_giNumberOfLights = 28;
		if (Scene1_gbInner_Side_Light_On_Flag == true)
			Scene1_giNumberOfLights = 34;

		glUniform1i(Scene1_gLKeyPressedUniform, 1);//1 For Material and Light Calculation
		glUniform1i(Scene1_gNumberOfLightsUniform, Scene1_giNumberOfLights);

		//Point Light
		glUniform3fv(Scene1_pointLight.gLaUniform, 1, Scene1_pointLight.lightAmbient);
		glUniform3fv(Scene1_pointLight.gLdUniform, 1, Scene1_pointLight.lightDiffuse);
		glUniform3fv(Scene1_pointLight.gLsUniform, 1, Scene1_pointLight.lightSpecular);
		glUniform3fv(Scene1_pointLight.gLightPositionUniform, 1, Scene1_pointLight.lightPosition);
		glUniform1f(Scene1_pointLight.gConstantUniform, Scene1_pointLight.gConstant);
		glUniform1f(Scene1_pointLight.gLinearUniform, Scene1_pointLight.gLinear);
		glUniform1f(Scene1_pointLight.gQuadraticUniform, Scene1_pointLight.gQuadratic);

		//Material
		glUniform3fv(Scene1_materialProperties.gKaUniform, 1, Scene1_materialProperties.materialAmbient);
		glUniform3fv(Scene1_materialProperties.gKdUniform, 1, Scene1_materialProperties.materialDiffuse);
		glUniform3fv(Scene1_materialProperties.gKsUniform, 1, Scene1_materialProperties.materialSpecular);
		glUniform1f(Scene1_materialProperties.gMaterialShininessUniform, Scene1_materialProperties.materialShininess);
		glUniform3fv(Scene1_Scene1_gViewPositionUniform, 1, glm::value_ptr(Scene1_gViewPosition));

		//Spot Light
		glUniform3fv(spotLight.gLaUniform, 1, spotLight.lightAmbient);
		glUniform3fv(spotLight.gLdUniform, 1, spotLight.lightDiffuse);
		glUniform3fv(spotLight.gLsUniform, 1, spotLight.lightSpecular);
		glUniform3fv(spotLight.gLightPositionUniform, 1, spotLight.lightPosition);
		glUniform1f(spotLight.gConstantUniform, spotLight.gConstant);
		glUniform1f(spotLight.gLinearUniform, spotLight.gLinear);
		glUniform1f(spotLight.gQuadraticUniform, spotLight.gQuadratic);
		glUniform3fv(spotLight.gLightDirectionUniform, 1, spotLight.lightDirection);
		glUniform1f(spotLight.gCutOffUniform, glm::radians(spotLight.cutoff_angle));
		glUniform1f(spotLight.gOuterCutOffUniform, glm::radians(spotLight.outer_cutoff_angle));

		glUniform3fv(Scene1_gLightUniform[0], 1, Scene1_pointLight1);
		glUniform3fv(Scene1_gLightUniform[1], 1, Scene1_pointLight2);
		glUniform3fv(Scene1_gLightUniform[2], 1, Scene1_pointLight3);
		glUniform3fv(Scene1_gLightUniform[3], 1, Scene1_pointLight4);
		glUniform3fv(Scene1_gLightUniform[4], 1, Scene1_pointLight5);
		glUniform3fv(Scene1_gLightUniform[5], 1, Scene1_pointLight6);
		glUniform3fv(Scene1_gLightUniform[6], 1, Scene1_pointLight7);
		glUniform3fv(Scene1_gLightUniform[7], 1, Scene1_pointLight8);
		glUniform3fv(Scene1_gLightUniform[8], 1, Scene1_pointLight9);
		glUniform3fv(Scene1_gLightUniform[9], 1, Scene1_pointLight10);
		glUniform3fv(Scene1_gLightUniform[10], 1, Scene1_pointLight11);
		glUniform3fv(Scene1_gLightUniform[11], 1, Scene1_pointLight12);
		glUniform3fv(Scene1_gLightUniform[12], 1, Scene1_pointLight13);
		glUniform3fv(Scene1_gLightUniform[13], 1, Scene1_pointLight14);
		glUniform3fv(Scene1_gLightUniform[14], 1, Scene1_pointLight15);
		glUniform3fv(Scene1_gLightUniform[15], 1, Scene1_pointLight16);
		glUniform3fv(Scene1_gLightUniform[16], 1, Scene1_pointLight17);
		glUniform3fv(Scene1_gLightUniform[17], 1, Scene1_pointLight18);
		glUniform3fv(Scene1_gLightUniform[18], 1, Scene1_pointLight19);
		glUniform3fv(Scene1_gLightUniform[19], 1, Scene1_pointLight20);
		glUniform3fv(Scene1_gLightUniform[20], 1, Scene1_pointLight21);
		glUniform3fv(Scene1_gLightUniform[21], 1, Scene1_pointLight22);
		glUniform3fv(Scene1_gLightUniform[22], 1, Scene1_pointLight23);
		glUniform3fv(Scene1_gLightUniform[23], 1, Scene1_pointLight24);
		glUniform3fv(Scene1_gLightUniform[24], 1, Scene1_pointLight25);
		glUniform3fv(Scene1_gLightUniform[25], 1, Scene1_pointLight26);
		glUniform3fv(Scene1_gLightUniform[26], 1, Scene1_pointLight27);
		glUniform3fv(Scene1_gLightUniform[27], 1, Scene1_pointLight28);
		glUniform3fv(Scene1_gLightUniform[28], 1, Scene1_pointLight29);
		glUniform3fv(Scene1_gLightUniform[29], 1, Scene1_pointLight30);
		glUniform3fv(Scene1_gLightUniform[30], 1, Scene1_pointLight31);
		glUniform3fv(Scene1_gLightUniform[31], 1, Scene1_pointLight32);
		glUniform3fv(Scene1_gLightUniform[32], 1, Scene1_pointLight33);
		glUniform3fv(Scene1_gLightUniform[33], 1, Scene1_pointLight34);

	}
	else
	{
		glUniform1i(Scene1_gLKeyPressedUniform, 0);//0 For Black Color
	}

	/*************Gaurage Body*************/

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 rotationMatrix = glm::mat4(1.0f);

	viewMatrix = Scene1_camera.getViewMatrix();

	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE1_MODEL_X_TRANSLATE, SCENE1_MODEL_Y_TRANSLATE, SCENE1_MODEL_Z_TRANSLATE));

	glUniformMatrix4fv(Scene1_gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(Scene1_gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(Scene1_gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(Scene1_gPerspectiveProjectionMatrix));

	glBindVertexArray(Scene1_Gaurage_Body.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Scene1_Gaurage_Body.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Outer Light*************/

	if (gbLight == true)
	{
		glUniform1i(Scene1_gLKeyPressedUniform, 2);//White Color
	}
	else
	{
		glUniform1i(Scene1_gLKeyPressedUniform, 0);
	}

	glBindVertexArray(Scene1_Gaurage_Outer_Light.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Scene1_Gaurage_Outer_Light.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Inner Upper Middle Light*************/

	if (Scene1_gbUpper_Middle_Light_On_Flag == true)
		glUniform1i(Scene1_gLKeyPressedUniform, 2);//White Color
	else
		glUniform1i(Scene1_gLKeyPressedUniform, 0);//Black Color

	glBindVertexArray(Scene1_Gaurage_Inner_Upper_Middle_Light.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Scene1_Gaurage_Inner_Upper_Middle_Light.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Inner Upper Side Light*************/
	if (Scene1_gbUpper_Side_Light_On_Flag == true)
		glUniform1i(Scene1_gLKeyPressedUniform, 2);//White Color
	else
		glUniform1i(Scene1_gLKeyPressedUniform, 0);//Black Color

	glBindVertexArray(Scene1_Gaurage_Inner_Upper_Side_Light.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Scene1_Gaurage_Inner_Upper_Side_Light.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Inner Side Light*************/
	if (Scene1_gbInner_Side_Light_On_Flag == true)
		glUniform1i(Scene1_gLKeyPressedUniform, 2);//White Color
	else
		glUniform1i(Scene1_gLKeyPressedUniform, 0);//Black Color

	glBindVertexArray(Scene1_Gaurage_Inner_Side_Light.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Scene1_Gaurage_Inner_Side_Light.count_of_vertices);

	glBindVertexArray(0);

	/*************Scene1_Mustang*************/

	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	viewMatrix = Scene1_camera.getViewMatrix();

	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE1_MODEL_X_TRANSLATE, SCENE1_MODEL_Y_TRANSLATE + 0.1f, SCENE1_MODEL_Z_TRANSLATE - 43.0f));

	glUniformMatrix4fv(Scene1_gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(Scene1_gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(Scene1_gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(Scene1_gPerspectiveProjectionMatrix));

	glUniform1i(Scene1_gLKeyPressedUniform, 1);

	glBindVertexArray(Scene1_Mustang.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Scene1_Mustang.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Left Door*************/

	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	viewMatrix = Scene1_camera.getViewMatrix();

	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE1_MODEL_X_TRANSLATE + gfScene1_Left_Door_Translate, SCENE1_MODEL_Y_TRANSLATE, SCENE1_MODEL_Z_TRANSLATE));
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(-6.900008, SCENE1_MODEL_Y_TRANSLATE, SCENE1_MODEL_Z_TRANSLATE));

	glUniformMatrix4fv(Scene1_gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(Scene1_gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(Scene1_gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(Scene1_gPerspectiveProjectionMatrix));

	glUniform1i(Scene1_gLKeyPressedUniform, 1);

	glBindVertexArray(Scene1_Left_Door.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Scene1_Left_Door.count_of_vertices);

	glBindVertexArray(0);

	/*************Gaurage Right Door*************/

	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);

	viewMatrix = Scene1_camera.getViewMatrix();

	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE1_MODEL_X_TRANSLATE + gfScene1_Right_Door_Translate, SCENE1_MODEL_Y_TRANSLATE, SCENE1_MODEL_Z_TRANSLATE));

	//modelMatrix = glm::translate(modelMatrix, glm::vec3(6.900008, SCENE1_MODEL_Y_TRANSLATE, SCENE1_MODEL_Z_TRANSLATE));

	glUniformMatrix4fv(Scene1_gModelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(Scene1_gViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(Scene1_gProjectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(Scene1_gPerspectiveProjectionMatrix));

	glUniform1i(Scene1_gLKeyPressedUniform, 1);

	glBindVertexArray(Scene1_Right_Door.Vao);

	glDrawArrays(GL_TRIANGLES, 0, Scene1_Right_Door.count_of_vertices);

	glBindVertexArray(0);

	glUseProgram(0);
}

void Update_Scene1(void)
{
	Scene1_camera_Z_counter++;

	if (Scene1_camera_Z_counter < 600)
	{
		Scene1_camera.MoveCamera(CameraMoveOnZ, -0.06f, deltaTime);
		if (Scene1_camera_Z_counter == 410)
		{
			Scene1_gbDoor_Open_Flag = true;
			Scene1_soundSourceDoorOpening->play(Scene1_audioBufferIdDoorOpening);
		}

		if (Scene1_camera_Z_counter == 460)
		{
			Scene1_gbUpper_Middle_Light_On_Flag = true;
			Scene1_soundSourceSpotLight1->play(Scene1_audioBufferIdSpotLight);
		}

		if (Scene1_camera_Z_counter == 500)
		{
			Scene1_soundSourceSpotLight2->play(Scene1_audioBufferIdSpotLight);
			Scene1_gbUpper_Side_Light_On_Flag = true;
			//Scene1_gbUpper_Middle_Light_On_Flag = false;
		}

		if (Scene1_camera_Z_counter == 558)
		{
			Scene1_gbInner_Side_Light_On_Flag = true;
			Scene1_soundSourceSpotLight3->play(Scene1_audioBufferIdSpotLight);
			//Scene1_gbUpper_Side_Light_On_Flag = false;
			//Scene1_gbUpper_Middle_Light_On_Flag = false;
		}
	}
	else if (Scene1_camera_Z_counter > 700 && Scene1_blackOutColor[0] > 0.0f)
	{
		Scene1_Black_Out_Flag = true;
		Scene1_blackOut();
	}

	if (Scene1_gbDoor_Open_Flag == true)
	{
		if (gfScene1_Left_Door_Translate > -6.900008 && gfScene1_Right_Door_Translate < 6.900008)
		{
			gfScene1_Left_Door_Translate = gfScene1_Left_Door_Translate - 0.05f;
			gfScene1_Right_Door_Translate = gfScene1_Right_Door_Translate + 0.05f;
		}
	}
}

void Scene1_blackOut(void)
{
	Scene1_blackOutColor[0] -= 0.0075f;
	Scene1_blackOutColor[1] -= 0.0075f;
	Scene1_blackOutColor[2] -= 0.0075f;
}

void Scene1_initializeAudio(void)
{
	Scene1_audioManager = new AudioManager();
	ALboolean Scene1_audioManagerrInitialize = Scene1_audioManager->initialize();

	if (!Scene1_audioManagerrInitialize)
	{
		logError("Not able to initialize audio manager.\n");
	}
	else
	{
		Scene1_audioManager->setListenerPosition(0.0f, 0.0f, 0.0f);
		Scene1_audioManager->setListenerVelocity(0.0f, 0.0f, 0.0f);

		Scene1_loadPointLightAudio();
		Scene1_loadDoorOpeningAudio();
		Scene1_loadSpotLightAudio();
	}
}

void Scene1_loadPointLightAudio()
{
	alGenBuffers(1, &Scene1_audioBufferIdPointLight);

	ALenum error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create point light audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	ALboolean waveDataLoaded = Scene1_audioManager->loadWaveAudio("resources/audio/PointLight.wav", Scene1_audioBufferIdPointLight);

	if (!waveDataLoaded)
	{
		logError("Not able to point light audio file.\n");
	}

	Scene1_soundSourcePointLight = new SoundSource();
	Scene1_soundSourcePointLight->setPosition3f(SCENE1_MODEL_X_TRANSLATE, SCENE1_MODEL_Y_TRANSLATE, 0.0f);
}

void Scene1_loadDoorOpeningAudio()
{
	alGenBuffers(1, &Scene1_audioBufferIdDoorOpening);

	ALenum error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create door opening audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	ALboolean waveDataLoaded = Scene1_audioManager->loadWaveAudio("resources/audio/DoorOpening.wav", Scene1_audioBufferIdDoorOpening);

	if (!waveDataLoaded)
	{
		logError("Not able to door opening load audio file.\n");
	}

	Scene1_soundSourceDoorOpening = new SoundSource();
}

void Scene1_loadSpotLightAudio(void)
{
	alGenBuffers(1, &Scene1_audioBufferIdSpotLight);

	ALenum error = alGetError();

	if (error != AL_NO_ERROR)
	{
		logError("Not able to create spot light audio buffer, error code: %d\n", error);
	}

	error = AL_NO_ERROR;

	ALboolean waveDataLoaded = Scene1_audioManager->loadWaveAudio("resources/audio/SpotLightSound.wav", Scene1_audioBufferIdSpotLight);

	if (!waveDataLoaded)
	{
		logError("Not able to load spot light audio file.\n");
	}

	Scene1_soundSourceSpotLight1 = new SoundSource();
	Scene1_soundSourceSpotLight2 = new SoundSource();
	Scene1_soundSourceSpotLight3 = new SoundSource();
	Scene1_soundSourceSpotLight4 = new SoundSource();
}

void Uninitialize_Scene1(void)
{
	if (Scene1_soundSourcePointLight != NULL)
	{
		delete Scene1_soundSourcePointLight;
		Scene1_soundSourcePointLight = NULL;
	}

	if (Scene1_soundSourceDoorOpening != NULL)
	{
		delete Scene1_soundSourceDoorOpening;
		Scene1_soundSourceDoorOpening = NULL;
	}

	if (Scene1_soundSourceSpotLight1 != NULL)
	{
		delete Scene1_soundSourceSpotLight1;
		Scene1_soundSourceSpotLight1 = NULL;
	}

	if (Scene1_soundSourceSpotLight2 != NULL)
	{
		delete Scene1_soundSourceSpotLight2;
		Scene1_soundSourceSpotLight2 = NULL;
	}

	if (Scene1_soundSourceSpotLight3 != NULL)
	{
		delete Scene1_soundSourceSpotLight3;
		Scene1_soundSourceSpotLight3 = NULL;
	}

	if (Scene1_soundSourceSpotLight4 != NULL)
	{
		delete Scene1_soundSourceSpotLight4;
		Scene1_soundSourceSpotLight4 = NULL;
	}

	alDeleteBuffers(1, &Scene1_audioBufferIdPointLight);
	alDeleteBuffers(1, &Scene1_audioBufferIdDoorOpening);
	alDeleteBuffers(1, &Scene1_audioBufferIdSpotLight);

	if (Scene1_audioManager != NULL)
	{
		delete Scene1_audioManager;
		Scene1_audioManager = NULL;
	}

	if (Scene1_Gaurage_Body.Vao)
	{
		glDeleteVertexArrays(1, &Scene1_Gaurage_Body.Vao);
		Scene1_Gaurage_Body.Vao = 0;
	}

	if(Scene1_Gaurage_Body.Vao)
	{
		glDeleteVertexArrays(1, &Scene1_Gaurage_Body.Vao);
		Scene1_Gaurage_Body.Vao = 0;
	}

	if(Scene1_Gaurage_Outer_Light.Vao)
	{
		glDeleteVertexArrays(1, &Scene1_Gaurage_Outer_Light.Vao);
		Scene1_Gaurage_Outer_Light.Vao = 0;
	}

	if(Scene1_Gaurage_Inner_Upper_Middle_Light.Vao)
	{
		glDeleteVertexArrays(1, &Scene1_Gaurage_Inner_Upper_Middle_Light.Vao);
		Scene1_Gaurage_Inner_Upper_Middle_Light.Vao = 0;
	}

	if(Scene1_Gaurage_Inner_Upper_Side_Light.Vao)
	{
		glDeleteVertexArrays(1, &Scene1_Gaurage_Inner_Upper_Side_Light.Vao);
		Scene1_Gaurage_Inner_Upper_Side_Light.Vao = 0;
	}

	if(Scene1_Gaurage_Inner_Side_Light.Vao)
	{
		glDeleteVertexArrays(1, &Scene1_Gaurage_Inner_Side_Light.Vao);
		Scene1_Gaurage_Inner_Side_Light.Vao = 0;
	}

	if(Scene1_Mustang.Vao)
	{
		glDeleteVertexArrays(1, &Scene1_Mustang.Vao);
		Scene1_Mustang.Vao = 0;
	}

	if(Scene1_Left_Door.Vao)
	{
		glDeleteVertexArrays(1, &Scene1_Left_Door.Vao);
		Scene1_Left_Door.Vao = 0;
	}

	if(Scene1_Right_Door.Vao)
	{
		glDeleteVertexArrays(1, &Scene1_Right_Door.Vao);
		Scene1_Right_Door.Vao = 0;
	}

	if (Scene1_gVbo_Position)
	{
		glDeleteBuffers(1, &Scene1_gVbo_Position);
		Scene1_gVbo_Position = 0;
	}

	if (Scene1_gVbo_Normal)
	{
		glDeleteBuffers(1, &Scene1_gVbo_Normal);
		Scene1_gVbo_Normal = 0;
	}

	//Detach Shader
	glDetachShader(Scene1_gShaderProgramObject, Scene1_gVertexShaderObject);
	glDetachShader(Scene1_gShaderProgramObject, Scene1_gFragmentShaderObject);

	//Delete Shader
	glDeleteShader(Scene1_gVertexShaderObject);
	Scene1_gVertexShaderObject = 0;

	glDeleteShader(Scene1_gFragmentShaderObject);
	Scene1_gFragmentShaderObject = 0;

	//Delete Program
	glDeleteProgram(Scene1_gShaderProgramObject);
	Scene1_gShaderProgramObject = 0;

}
