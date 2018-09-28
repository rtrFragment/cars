#define STB_IMAGE_IMPLEMENTATION
#include<Windows.h>
#include<stdio.h>
#include<gl/GL.h>
#include<vector>
#include"stb_image.h"
#include "../RTR_lib/logger/logger.h"

#pragma comment(lib,"user32.lib")

#define BUFFER_SIZE 256
#define S_EQUAL 0
#define NR_KA 3
#define NR_KD 3
#define NR_KS 3


FILE *gpMtlFile;
char line_mtl[BUFFER_SIZE];
int counter_newmtl = 0;
int counter_Ka = 0;
int counter_Kd = 0;
int counter_Ks = 0;
int counter_Ns = 0;
int counter_Ni = 0;
int counter_d = 0;
int counter_illum = 0;
int counter_map_Kd = 0;
int counter_map_Ka = 0;
int counter_map_Ks = 0;
int counter_map_Bump = 0;
//int iterator=0;

struct material {
	char material_name[255];
	float Ns;
	float Ka[4];
	float Kd[4];
	float Ks[4];
	float Ni;
	float d;
	float illum;
	char map_Kd[255];
	char map_Ka[255];
	char map_Ks[255];
	char map_Bump[255];
	bool ismap_Kd = false;
	bool ismap_Ka = false;
	bool ismap_Ks = false;
	bool ismap_Bump = false;
	GLuint gTexture;

	material()
	{
		ismap_Kd = false;
		ismap_Ka = false;
		ismap_Ks = false;
		ismap_Bump = false;
	}
};

struct material material_temp;

TCHAR str_material[256];

bool gbFirstTime = false;

void LoadMaterialData(char *filename, std::vector<material>&mat)
{
	int LoadGLTextures(GLuint *, char *);
	void InitTextures(std::vector<material>&);

	//MessageBox(NULL, TEXT("In LoadMaterialData()"), TEXT("MSG"), MB_OK);
	fopen_s(&gpMtlFile, filename, "r");
	if (!gpMtlFile)
	{
		//MessageBox(NULL, TEXT("Cannot Open MTL File"), TEXT("ERROR"), MB_OK);
		logError("Cannot Open MTL File '%s'", filename);
		exit(EXIT_FAILURE);
	}

	char *first_token = NULL;
	char *token = NULL;
	char *sep_space = " ";
	char *context = NULL;
	gbFirstTime = false;
	ZeroMemory(&material_temp, sizeof(material));
	mat.clear();

	while (fgets(line_mtl, BUFFER_SIZE, gpMtlFile) != NULL)
	{
		first_token = strtok_s(line_mtl, sep_space, &context);
		if (strcmp(first_token, "newmtl") == S_EQUAL)
		{
			if (gbFirstTime == true)
			{
				mat.push_back(material_temp);
				ZeroMemory(&material_temp, sizeof(material));
			}
			token = strtok_s(NULL, sep_space, &context);
			strcpy_s(material_temp.material_name, token);
			counter_newmtl++;
			gbFirstTime = true;
		}
		else if (strcmp(first_token, "Ns") == S_EQUAL)
		{
			token = strtok_s(NULL, sep_space, &context);
			material_temp.Ns = atof(token);
			counter_Ns++;
		}
		else if (strcmp(first_token, "Ka") == S_EQUAL)
		{
			for (int i = 0; i < NR_KA; i++)
			{
				token = strtok_s(NULL, sep_space, &context);
				material_temp.Ka[i] = atof(token);
			}
			counter_Ka++;
		}
		else if (strcmp(first_token, "Kd") == S_EQUAL)
		{
			for (int i = 0; i < NR_KD; i++)
			{
				token = strtok_s(NULL, sep_space, &context);
				material_temp.Kd[i] = atof(token);
			}
			counter_Kd++;
		}
		else if (strcmp(first_token, "Ks") == S_EQUAL)
		{
			for (int i = 0; i < NR_KS; i++)
			{
				token = strtok_s(NULL, sep_space, &context);
				material_temp.Ks[i] = atof(token);
			}
			counter_Ks++;
		}
		else if (strcmp(first_token, "Ni") == S_EQUAL)
		{
			token = strtok_s(NULL, sep_space, &context);
			material_temp.Ni = atof(token);
			counter_Ni++;
		}
		else if (strcmp(first_token, "d") == S_EQUAL)
		{
			token = strtok_s(NULL, sep_space, &context);
			material_temp.d = atof(token);
			counter_d++;
		}
		else if (strcmp(first_token, "illum") == S_EQUAL)
		{
			token = strtok_s(NULL, sep_space, &context);
			material_temp.illum = atof(token);
			counter_illum++;
		}
		else if (strcmp(first_token, "map_Kd") == S_EQUAL)
		{
			int size;
			token = strtok_s(NULL, sep_space, &context);
			size = strlen(token);

			memcpy(material_temp.map_Kd, token, size - 1);
			//strcpy_s(mat[counter_newmtl-1].map_Kd,token);
			material_temp.ismap_Kd = true;
			/*int result = LoadGLTextures(&mat[counter_newmtl - 1].gTexture, mat[counter_newmtl - 1].map_Kd);
			if (result == FALSE)
			{
			sprintf(str_material, "Cannot Load Image :%s.", mat[counter_newmtl - 1].map_Kd);
			MessageBox(NULL, str_material, TEXT("Error"), MB_OK);
			}*/
			counter_map_Kd++;
		}
		else if (strcmp(first_token, "map_Ka") == S_EQUAL)
		{
			token = strtok_s(NULL, sep_space, &context);
			strcpy_s(material_temp.map_Ka, token);
			material_temp.ismap_Ka = true;
			counter_map_Ka++;
		}
		else if (strcmp(first_token, "map_Ks") == S_EQUAL)
		{
			token = strtok_s(NULL, sep_space, &context);
			strcpy_s(material_temp.map_Ks, token);
			material_temp.ismap_Ks = true;
			counter_map_Ks++;
		}
		else if (strcmp(first_token, "map_Bump") == S_EQUAL)
		{
			token = strtok_s(NULL, sep_space, &context);
			strcpy_s(material_temp.map_Bump, token);
			material_temp.ismap_Bump = true;
			counter_map_Bump++;
		}
		//iterator++;
	}

	mat.push_back(material_temp);
	ZeroMemory(&material_temp, sizeof(material));

	fclose(gpMtlFile);
	InitTextures(mat);
	logInfo("Material data loaded");
	//MessageBox(NULL, TEXT("END"), TEXT("MSG"), MB_OK);
	//return(0);
}

void InitTextures(std::vector<material>&mat)
{
	int LoadGLTextures(GLuint *, char *);
	for (int i = 0; i < mat.size(); i++)
	{
		if (mat[i].ismap_Kd == true)
		{
			int result = LoadGLTextures(&mat[i].gTexture, mat[i].map_Kd);
			if (result == FALSE)
			{
				//wsprintf(str_material, TEXT("Cannot Load Image :%s."), mat[i].map_Kd);
				//MessageBox(NULL, str_material, TEXT("Error"), MB_OK);
				logError("Cannot Load Image :%s.", mat[i].map_Kd);
			}
			else if (result == TRUE)
			{
				//MessageBox(NULL, TEXT("Texture Loaded Successfully"), TEXT("MSG"), MB_OK);
			}
		}
	}
}

int LoadGLTextures(GLuint *texture, char *filename)
{
	//	HBITMAP hBitmap;
	//BITMAP bmp;
	int iStatus = FALSE;
	int width, height, nrComponents;
	unsigned char *image = NULL;

	glGenTextures(1, texture);
	//	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResourceId, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	image = stbi_load(filename, &width, &height, &nrComponents, 0);
	if (image)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		iStatus = TRUE;
		//GetObject(hBitmap, sizeof(bmp), &bmp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, image);

		glGenerateMipmap(GL_TEXTURE_2D);

		//DeleteObject(hBitmap);
		stbi_image_free(image);
	}
	return(iStatus);
}
