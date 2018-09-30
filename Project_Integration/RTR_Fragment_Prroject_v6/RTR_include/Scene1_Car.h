#pragma once
#include"Common_Header.h"


#define SCENE1_MODEL_X_TRANSLATE		0.0f	//X-translation of MODEL
#define SCENE1_MODEL_Y_TRANSLATE		-0.5f	//Y-translation of MODEL
#define SCENE1_MODEL_Z_TRANSLATE		-5.0f	//Z-translation of MODEL

#define SCENE1_MODEL_X_SCALE_FACTOR	1.5f	//X-scale factor of MODEL
#define SCENE1_MODEL_Y_SCALE_FACTOR	1.5f	//Y-scale factor of MODEL
#define SCENE1_MODEL_Z_SCALE_FACTOR	1.5f	//Z-scale factor of MODEL

#define SCENE1_START_ANGLE_POS			0.0f	//Marks beginning angle position of rotation
#define SCENE1_END_ANGLE_POS			180.0f	//Marks terminating angle position rotation
#define SCENE1_MODEL_ANGLE_INCREMENT	0.3f	//Increment angle for MODEL

enum
{
	SCENE1_ATTRIBUTE_POSITION_CAR = 0,
	SCENE1_ATTRIBUTE_COLOR_CAR,
	SCENE1_ATTRIBUTE_NORMAL_CAR,
	SCENE1_ATTRIBUTE_TEXTURE0_CAR,
};

GLuint gScene1_VertexShaderObject_Car;
GLuint gScene1_FragmentShaderObject_Car;
GLuint gScene1_ShaderProgramObject_Car;

GLuint gScene1_Car_Vao, gVao_Cube;
GLuint gScene1_Car_Vbo_Position, gScene1_Car_Vbo_Normal, gScene1_Car_Vbo_Texture;

GLuint gScene1_ModelMatrixUniform_Car, gScene1_ViewMatrixUniform_Car, gScene1_ProjectionMatrixUniform_Car;
GLuint gScene1_LKeyPressedUniform_Car;

GLuint gScene1_LaUniform_Car, gScene1_LdUniform_Car, gScene1_LsUniform_Car;
GLuint gScene1_LightPosition_Uniform_Car, gScene1_LightDirectionUniform;
GLuint gScene1_CutOffUniform, gScene1_OuterCutOffUniform;

GLuint gScene1_ViewPositionUniform_Car;
GLuint gScene1_ConstantUniform_Car, gScene1_LinearUniform_Car, gScene1_QuadraticUniform_Car;

GLuint gScene1_KaUniform_Car, gScene1_KdUniform_Car, gScene1_KsUniform_Car, gScene1_AlphaUniform;
GLuint gScene1_MaterialShininessUniform_Car;

GLuint gScene1_TextureSamplerUniform_Car, gScene1_TextureActiveUniform_Car;

GLuint Scene1_Car_BlackOut_Value_Uniform;

glm::mat4 gPerspectiveProjectionMatrix;

bool gbScene1_Animate = false;
//bool gbLight = false;
//bool gbIsAKeyPressed = false;
//bool gbIsLKeyPressed = false;

GLfloat Scene1_lightAmbient_Car[] = { 0.1f,0.1f,0.1f,1.0f };
GLfloat Scene1_lightDiffuse_Car[] = { 0.8f,0.8f,0.8f,1.0f };
GLfloat Scene1_lightSpecular_Car[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat Scene1_lightPosition_Car[] = { 0.0f, 2.3f, -46.2f };

GLfloat Scene1_materialAmbient_Car[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat Scene1_materialDiffuse_Car[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat Scene1_materialSpecular_Car[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat Scene1_materialShininess_Car = 50.0f;

GLfloat Scene1_g_rotate_car;

std::vector<float> scene1_mustang_vertices, scene1_mustang_textures, scene1_mustang_normals;

std::vector<material>scene1_mustang_material;
std::vector<Mesh_Data>scene1_mustang_mesh_data;
char scene1_mustang_Mtllib[256];

GLfloat Scene1_cutoff_angle_Car = 62.5f;
GLfloat Scene1_outer_cutoff_angle_Car = 67.5f;

//FILE *gpFile;

bool Scene1_Car_Rotation_Completed_Flag = false;

void Init_Scene1_Car(void)
{
	//MessageBox(NULL, TEXT("Before LoadMeshData"), TEXT("MSG"), MB_OK);
	LoadMeshData("RTR_resources/models/Mustang_GT/mustang_GT.obj", scene1_mustang_vertices, scene1_mustang_textures, scene1_mustang_normals, scene1_mustang_mesh_data, scene1_mustang_Mtllib);
	//MessageBox(NULL, TEXT("After LoadMeshData 3"), TEXT("MSG"), MB_OK);
	LoadMaterialData(scene1_mustang_Mtllib, scene1_mustang_material);
	//MessageBox(NULL, TEXT("After LoadMaterialData1"), TEXT("MSG"), MB_OK);
	Rearrange_Material_Data(scene1_mustang_mesh_data, scene1_mustang_material);
	//MessageBox(NULL, TEXT("After Rearrange_Material_Data 1"), TEXT("MSG"), MB_OK);

	//Vertex Shader
	gScene1_VertexShaderObject_Car = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
		"#version 450" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"in vec2 vTexture0_Coord;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_lighting_enabled;" \
		"out vec3 transformed_normals;" \
		"out vec3 FragPos;" \
		"out vec2 out_texture0_coord;" \
		"void main(void)" \
		"{" \
		"if(u_lighting_enabled==1)" \
		"{" \
		"transformed_normals = mat3(u_model_matrix)*vNormal;" \
		"FragPos = vec3(u_model_matrix * vPosition);" \
		"}" \
		"gl_Position = u_projection_matrix*u_view_matrix*u_model_matrix*vPosition;" \
		"out_texture0_coord = vTexture0_Coord;" \
		"}";

	glShaderSource(gScene1_VertexShaderObject_Car, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	glCompileShader(gScene1_VertexShaderObject_Car);
	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char *szInfoLog = NULL;

	glGetShaderiv(gScene1_VertexShaderObject_Car, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gScene1_VertexShaderObject_Car, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gScene1_VertexShaderObject_Car, iInfoLogLength, &written, szInfoLog);
				logError("Vertex Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				exit(0);
			}
		}
	}

	//Fragment Shader
	gScene1_FragmentShaderObject_Car = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSourceCode =
		"#version 450" \
		"\n" \
		"in vec3 transformed_normals;" \
		"in vec3 FragPos;" \
		"in vec2 out_texture0_coord;" \
		"out vec4 FragColor;" \
		"uniform vec3 u_La;" \
		"uniform vec3 u_Ld;" \
		"uniform vec3 u_Ls;" \
		"uniform vec3 u_Ka;" \
		"uniform vec3 u_Kd;" \
		"uniform vec3 u_Ks;" \
		"uniform float constant;" \
		"uniform float linear;" \
		"uniform float quadratic;" \
		"uniform float u_material_shininess;" \
		"uniform vec3 u_light_position;" \
		"uniform int u_lighting_enabled;" \
		"uniform vec3 u_viewPos;" \
		"uniform vec3 u_light_direction;" \
		"uniform float u_cutOff;" \
		"uniform float u_outerCutOff;" \
		"uniform float u_alpha;" \
		"uniform sampler2D u_texture0_sampler;"\
		"uniform int u_is_texture;" \
		"uniform float blackout;" \
		"vec4 Final_Texture;" \
		"vec4 Temp_Output;" \
		"void main(void)" \
		"{" \
		"vec3 phong_ads_color;" \
		"if(u_lighting_enabled == 1)" \
		"{" \
		"vec3 ambient = u_La * u_Ka;" \

		"vec3 normalized_transformed_normals = normalize(transformed_normals);" \
		"vec3 normalized_light_direction = normalize(u_light_position - FragPos);" \
		"float tn_dot_ld = max(dot(normalized_transformed_normals,normalized_light_direction),0.0);" \
		"vec3 diffuse = u_Ld * u_Kd * tn_dot_ld;" \

		"vec3 view_direction = normalize(u_viewPos - FragPos);" \
		"vec3 reflection_vector = reflect(-normalized_light_direction,normalized_transformed_normals);" \
		"vec3 specular = u_Ls * u_Ks * pow(max(dot(view_direction,reflection_vector),0.0),u_material_shininess);" \

		"float theta = dot(normalized_light_direction,normalize(-u_light_direction));" \
		"float epsilon = (u_cutOff - u_outerCutOff);" \
		"float intensity = clamp((theta - u_outerCutOff) / epsilon, 0.0, 1.0);" \
		"diffuse = diffuse * intensity;" \
		"specular = specular * intensity;" \

		"float distance = length(u_light_position-FragPos);" \
		"float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));" \
		"ambient = ambient * attenuation;" \
		"diffuse = diffuse * attenuation;" \
		"specular = specular * attenuation;" \
		"phong_ads_color = ambient + diffuse + specular;" \
		"}" \
		"else" \
		"{" \
		"phong_ads_color = vec3(1.0f,1.0f,1.0f);" \
		"}" \
		"if(u_is_texture == 1)" \
		"{" \
		"Final_Texture = texture(u_texture0_sampler,out_texture0_coord);" \
		"Temp_Output = vec4(phong_ads_color,u_alpha) * Final_Texture;" \
		"FragColor = Temp_Output * vec4(blackout);" \
		"}" \
		"else" \
		"{" \
		"FragColor = vec4(phong_ads_color,u_alpha) * vec4(blackout);" \
		"}" \
		"}";

	glShaderSource(gScene1_FragmentShaderObject_Car, 1, (const GLchar **)&fragmentShaderSourceCode, NULL);

	glCompileShader(gScene1_FragmentShaderObject_Car);

	glGetShaderiv(gScene1_FragmentShaderObject_Car, GL_COMPILE_STATUS, &iShaderCompiledStatus);
	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gScene1_FragmentShaderObject_Car, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gScene1_FragmentShaderObject_Car, iInfoLogLength, &written, szInfoLog);
				logError("Fragment Shader Compilation Log : %s\n", szInfoLog);
				free(szInfoLog);
				exit(0);
			}
		}
	}

	//Shader Program
	gScene1_ShaderProgramObject_Car = glCreateProgram();

	glAttachShader(gScene1_ShaderProgramObject_Car, gScene1_VertexShaderObject_Car);

	glAttachShader(gScene1_ShaderProgramObject_Car, gScene1_FragmentShaderObject_Car);

	glBindAttribLocation(gScene1_ShaderProgramObject_Car, SCENE1_ATTRIBUTE_POSITION_CAR, "vPosition");

	glBindAttribLocation(gScene1_ShaderProgramObject_Car, SCENE1_ATTRIBUTE_NORMAL_CAR, "vNormal");

	glBindAttribLocation(gScene1_ShaderProgramObject_Car, SCENE1_ATTRIBUTE_TEXTURE0_CAR, "vTexture0_Coord");

	glLinkProgram(gScene1_ShaderProgramObject_Car);

	GLint iShaderProgramLinkStatus = 0;

	glGetProgramiv(gScene1_ShaderProgramObject_Car, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gScene1_ShaderProgramObject_Car, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gScene1_ShaderProgramObject_Car, iInfoLogLength, &written, szInfoLog);
				logError("Shader Program Link Log : %s\n", szInfoLog);
				free(szInfoLog);
				exit(0);
			}
		}
	}

	gScene1_ModelMatrixUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_model_matrix");
	gScene1_ViewMatrixUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_view_matrix");
	gScene1_ProjectionMatrixUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_projection_matrix");

	gScene1_LKeyPressedUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_lighting_enabled");

	gScene1_LaUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_La");
	gScene1_LdUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_Ld");
	gScene1_LsUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_Ls");

	gScene1_LightPosition_Uniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_light_position");

	gScene1_KaUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_Ka");
	gScene1_KdUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_Kd");
	gScene1_KsUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_Ks");

	gScene1_MaterialShininessUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_material_shininess");

	gScene1_ViewPositionUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_viewPos");

	gScene1_ConstantUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "constant");
	gScene1_LinearUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "linear");
	gScene1_QuadraticUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "quadratic");

	gScene1_LightDirectionUniform = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_light_direction");
	gScene1_CutOffUniform = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_cutOff");
	gScene1_OuterCutOffUniform = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_outerCutOff");

	gScene1_AlphaUniform = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_alpha");

	gScene1_TextureSamplerUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_texture0_sampler");

	gScene1_TextureActiveUniform_Car = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "u_is_texture");

	Scene1_Car_BlackOut_Value_Uniform = glGetUniformLocation(gScene1_ShaderProgramObject_Car, "blackout");

	/*****************VAO For Cube*****************/
	glGenVertexArrays(1, &gScene1_Car_Vao);
	glBindVertexArray(gScene1_Car_Vao);

	/*****************Cube Position****************/
	glGenBuffers(1, &gScene1_Car_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gScene1_Car_Vbo_Position);
	glBufferData(GL_ARRAY_BUFFER, scene1_mustang_vertices.size() * sizeof(float), &scene1_mustang_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_POSITION_CAR, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_POSITION_CAR);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*****************Cube Color****************/
	glGenBuffers(1, &gScene1_Car_Vbo_Normal);
	glBindBuffer(GL_ARRAY_BUFFER, gScene1_Car_Vbo_Normal);
	glBufferData(GL_ARRAY_BUFFER, scene1_mustang_normals.size() * sizeof(float), &scene1_mustang_normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_NORMAL_CAR, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_NORMAL_CAR);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*******************Texture******************/
	glGenBuffers(1, &gScene1_Car_Vbo_Texture);
	glBindBuffer(GL_ARRAY_BUFFER, gScene1_Car_Vbo_Texture);
	glBufferData(GL_ARRAY_BUFFER, scene1_mustang_textures.size() * sizeof(float), &scene1_mustang_textures[0], GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_TEXTURE0_CAR, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_TEXTURE0_CAR);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	const GLfloat cubeVertices[] =
	{
		1.0f,1.0f,1.0f,
		-1.0f,1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		1.0f,-1.0f,1.0f,

		1.0f,1.0f,-1.0f,
		1.0f,1.0f,1.0f,
		1.0f,-1.0f,1.0f,
		1.0f,-1.0f,-1.0f,

		-1.0f,1.0f,-1.0f,
		1.0f,1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f,1.0f,1.0f,
		-1.0f,1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,1.0f,

		1.0f,1.0f,-1.0f,
		-1.0f,1.0f,-1.0f,
		-1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,

		1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f
	};

	/****************Cube************/
	glGenVertexArrays(1, &gVao_Cube);
	glBindVertexArray(gVao_Cube);

	/******************Cube Vertices*****************/
	glGenBuffers(1, &gScene1_Car_Vbo_Position);
	glBindBuffer(GL_ARRAY_BUFFER, gScene1_Car_Vbo_Position);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(SCENE1_ATTRIBUTE_POSITION_CAR, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(SCENE1_ATTRIBUTE_POSITION_CAR);

	glBindVertexArray(0);

	gPerspectiveProjectionMatrix = glm::mat4(1.0f);

	glEnable(GL_TEXTURE_2D);
	
}

void Display_Scene1_Car(void)
{
	//Use Shader Program Object
	glUseProgram(gScene1_ShaderProgramObject_Car);

	if (gbLight == true)
	{
		glUniform1i(gScene1_LKeyPressedUniform_Car, 1);

		glUniform3fv(gScene1_LaUniform_Car, 1, Scene1_lightAmbient_Car);
		glUniform3fv(gScene1_LdUniform_Car, 1, Scene1_lightDiffuse_Car);
		glUniform3fv(gScene1_LsUniform_Car, 1, Scene1_lightSpecular_Car);
		glUniform3fv(gScene1_LightPosition_Uniform_Car, 1, Scene1_lightPosition_Car);

		glUniform3fv(gScene1_KaUniform_Car, 1, Scene1_materialAmbient_Car);
		glUniform3fv(gScene1_KdUniform_Car, 1, Scene1_materialDiffuse_Car);
		glUniform3fv(gScene1_KsUniform_Car, 1, Scene1_materialSpecular_Car);
		glUniform1f(gScene1_MaterialShininessUniform_Car, Scene1_materialShininess_Car);
		glUniform3f(gScene1_ViewPositionUniform_Car, 0.0f, 0.0f, 3.0f);
		glUniform1f(gScene1_ConstantUniform_Car, 1.0f);
		glUniform1f(gScene1_LinearUniform_Car, 0.09f);
		glUniform1f(gScene1_QuadraticUniform_Car, 0.032f);
		glUniform3f(gScene1_LightDirectionUniform, 0.0f, -1.0f, 0.0f);
		glUniform1f(gScene1_CutOffUniform, cos(glm::radians(Scene1_cutoff_angle_Car)));
		glUniform1f(gScene1_OuterCutOffUniform, cos(glm::radians(Scene1_outer_cutoff_angle_Car)));
		glUniform1f(Scene1_Car_BlackOut_Value_Uniform, gfBlackOut);
	}
	else
	{
		glUniform1i(gScene1_LKeyPressedUniform_Car, 0);
	}

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 rotationMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(SCENE1_MODEL_X_TRANSLATE, -0.9f, SCENE1_MODEL_Z_TRANSLATE-43.0f));

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Scene1_g_rotate_car), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = modelMatrix*rotationMatrix;

	viewMatrix = Scene1_camera.getViewMatrix();

	//viewMatrix = lookat(vec3(0.0f, 1.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(gScene1_ModelMatrixUniform_Car, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(gScene1_ViewMatrixUniform_Car, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(gScene1_ProjectionMatrixUniform_Car, 1, GL_FALSE, glm::value_ptr(gPerspectiveProjectionMatrix));

	glBindVertexArray(gScene1_Car_Vao);

	for (int i = 0; i < scene1_mustang_mesh_data.size(); i++)
	{
		if (gbLight == true)
		{
			glUniform3fv(gScene1_KaUniform_Car, 1, scene1_mustang_material[scene1_mustang_mesh_data[i].material_index].Ka);
			glUniform3fv(gScene1_KdUniform_Car, 1, scene1_mustang_material[scene1_mustang_mesh_data[i].material_index].Kd);
			glUniform3fv(gScene1_KsUniform_Car, 1, scene1_mustang_material[scene1_mustang_mesh_data[i].material_index].Ks);
			glUniform1f(gScene1_MaterialShininessUniform_Car, Scene1_materialShininess_Car);
			glUniform1f(gScene1_AlphaUniform, scene1_mustang_material[scene1_mustang_mesh_data[i].material_index].d);

			if (scene1_mustang_material[scene1_mustang_mesh_data[i].material_index].ismap_Kd == true)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, scene1_mustang_material[scene1_mustang_mesh_data[i].material_index].gTexture);
				glUniform1i(gScene1_TextureSamplerUniform_Car, 0);
				glUniform1i(gScene1_TextureActiveUniform_Car, 1);
			}
			else
				glUniform1i(gScene1_TextureActiveUniform_Car, 0);
		}

		glDrawArrays(GL_TRIANGLES, scene1_mustang_mesh_data[i].vertex_Index, scene1_mustang_mesh_data[i].vertex_Count);
	}

	glBindVertexArray(0);

	/*******************Cube**********************/

	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(Scene1_lightPosition_Car[0], Scene1_lightPosition_Car[1], Scene1_lightPosition_Car[2]));

	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.04f, 0.04f, 0.04f));
	modelMatrix = modelMatrix * scaleMatrix;

	glUniformMatrix4fv(gScene1_ModelMatrixUniform_Car, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glUniformMatrix4fv(gScene1_ViewMatrixUniform_Car, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniformMatrix4fv(gScene1_ProjectionMatrixUniform_Car, 1, GL_FALSE, glm::value_ptr(gPerspectiveProjectionMatrix));

	glUniform1i(gScene1_LKeyPressedUniform_Car, 0);

	glBindVertexArray(gVao_Cube);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);

	glUseProgram(0);
}

void Update_Scene1_Car(void)
{
	if (gbScene1_Animate == true)
	{
		if (Scene1_g_rotate_car < SCENE1_END_ANGLE_POS)
			Scene1_g_rotate_car = Scene1_g_rotate_car + SCENE1_MODEL_ANGLE_INCREMENT;
	}
	if (Scene1_g_rotate_car >=  170)
	{
		Scene1_Car_Rotation_Completed_Flag = true;
	}
	if (gbScene1_BlackOut_Flag == true)
		gfBlackOut -= 0.002f;

	if (gfBlackOut <= 0.0f)
	{
		logInfo("Sam : Play Scene 2 And End Sene 1. \n");
		g_scene2_bShowScene2 = true;
		g_scene2_1_PlayAudio = true;
		g_scene1_bShowScene1 = false;
	}
}

void Uninitialize_Scene1_Car(void)
{
	if (gScene1_Car_Vao)
	{
		glDeleteVertexArrays(1, &gScene1_Car_Vao);
		gScene1_Car_Vao = 0;
	}

	if (gScene1_Car_Vbo_Position)
	{
		glDeleteBuffers(1, &gScene1_Car_Vbo_Position);
		gScene1_Car_Vbo_Position = 0;
	}

	if (gScene1_Car_Vbo_Normal)
	{
		glDeleteBuffers(1, &gScene1_Car_Vbo_Normal);
		gScene1_Car_Vbo_Normal = 0;
	}

	//Detach Shader 
	glDetachShader(gScene1_ShaderProgramObject_Car, gScene1_VertexShaderObject_Car);
	glDetachShader(gScene1_ShaderProgramObject_Car, gScene1_FragmentShaderObject_Car);

	//Delete Shader
	glDeleteShader(gScene1_VertexShaderObject_Car);
	gScene1_VertexShaderObject_Car = 0;

	glDeleteShader(gScene1_FragmentShaderObject_Car);
	gScene1_FragmentShaderObject_Car = 0;

	//Delete Program
	glDeleteProgram(gScene1_ShaderProgramObject_Car);
	gScene1_ShaderProgramObject_Car = 0;
}