#pragma once

#include<stdlib.h>
#include<stdio.h>
#include<vector>

#include "objLoader.h"

void getFileNameAndPrefix(char* sourceFileName, char** headerFileName, char** prefix);
void printVertices(FILE *headerFile, std::vector<float> vertices, const char *prefix);
void printTextureCoordinates(FILE *headerFile, std::vector<float> textures, const char *prefix);
void printNormals(FILE *headerFile, std::vector<float> normals, const char *prefix);

int main(int argc, char *argv[])
{
    FILE *headerFile = NULL;
    char *headerFileName = NULL;
    char *prefix = NULL;
	int number_of_Vertices;

   if(argc != 2)
   {
       printf("\nMissing mesh file.\n");
       printf("Usage:\n");
       printf("\t%s fileName.obj\n", argv[0]);
		exit(EXIT_FAILURE);
   }

    getFileNameAndPrefix(argv[1], &headerFileName, &prefix);
    printf("prefix: %s\n", prefix);
    printf("Header file name: %s\n", headerFileName);

    if (fopen_s(&headerFile, headerFileName, "w") != 0)
	{
		printf("Unable to create header file %s", argv[1]);
		exit(EXIT_FAILURE);
	}

    std::vector<float> vertices;
    std::vector<float> textures;
    std::vector<float> normals;

	number_of_Vertices = LoadMeshData(argv[1], vertices, textures, normals);

    fprintf_s(headerFile, "// Created by Fragments of AstroMediComp | Knowledge is Inter-related\n");
    fprintf_s(headerFile, "// Signature: 0x55aa\n\n");
    fprintf_s(headerFile, "#pragma once\n\n");
    fprintf_s(headerFile, "#include <GL/gl.h>\n\n");
	fprintf_s(headerFile, "int %s_vertices_count = %d;\n\n", prefix, number_of_Vertices);

    printVertices(headerFile, vertices, prefix);
    fprintf_s(headerFile, "\n");

    printTextureCoordinates(headerFile, textures, prefix);
    fprintf_s(headerFile, "\n");

    printNormals(headerFile, normals, prefix);

    fprintf_s(headerFile, "\n// 0101010110101010\n");
    fflush(headerFile);
    fclose(headerFile);

    if(prefix != NULL)
    {
        free(prefix);
        prefix = NULL;
    }

    if(headerFileName != NULL)
    {
        free(headerFileName);
        headerFileName = NULL;
    }

    return 0;
}

void getFileNameAndPrefix(char *sourceFileName, char** headerFileName, char** prefix)
{
    char *ext = strrchr(sourceFileName, '.');

    size_t inputFileNameSize = strlen(sourceFileName);

    if(ext != NULL)
    {
        size_t extSize = strlen(ext);
        size_t prefixSize = inputFileNameSize - extSize + 1;
        size_t headerFileNameSize = inputFileNameSize - extSize + 3; // + 2 for '.h'

        *prefix = (char *)malloc(prefixSize * sizeof(char));
        *headerFileName = (char *)malloc(headerFileNameSize * sizeof(char));

		memset(*prefix, '\0', prefixSize * sizeof(char));
		memset(*headerFileName, '\0', headerFileNameSize * sizeof(char));

        strncpy_s(*prefix, prefixSize + 1, sourceFileName, inputFileNameSize - extSize);
        strncpy_s(*headerFileName, headerFileNameSize, sourceFileName, inputFileNameSize - extSize);

        char *s;

        while ((s = strchr(*prefix, '.')) != NULL)
        {
            *s = '_';
        }

        while ((s = strchr(*headerFileName, '.')) != NULL)
        {
            *s = '_';
        }

        strcat_s(*headerFileName, headerFileNameSize, ".h");
    }
    else
    {
        size_t prefixSize = inputFileNameSize;
        size_t headerFileNameSize = inputFileNameSize + 3; // + 3 for '.h\0'

        *prefix = (char *)malloc(inputFileNameSize * sizeof(char));
        *headerFileName = (char *)malloc(headerFileNameSize * sizeof(char));

        strcpy_s(*prefix, inputFileNameSize, sourceFileName);
        strcpy_s(*headerFileName, headerFileNameSize, sourceFileName);

        char *s;

        while ((s = strchr(*prefix, '.')) != NULL)
        {
            *s = '_';
        }

        while ((s = strchr(*headerFileName, '.')) != NULL)
        {
            *s = '_';
        }

        strcat_s(*headerFileName, headerFileNameSize, ".h");
    }
}

void printVertices(FILE *headerFile, std::vector<float> vertices, const char *prefix)
{
    size_t numberOfVertices = vertices.size();

    fprintf_s(headerFile, "GLfloat %s_vertices[%zd] = {\n\t", prefix, numberOfVertices);

    for(size_t counter = 0; counter < numberOfVertices; ++counter)
    {
        fprintf_s(headerFile, "%ff", vertices[counter]);

        if(counter + 1 != numberOfVertices)
        {
            fprintf_s(headerFile, ", ");
        }

        if(counter % NR_POINT_COORDS == (NR_POINT_COORDS - 1))
        {
            fprintf_s(headerFile, "\n");

            if(counter + 1 != numberOfVertices)
            {
                fprintf_s(headerFile, "\t");
            }
        }
    }

    fprintf_s(headerFile, "};\n");
    fflush(headerFile);
}

void printTextureCoordinates(FILE *headerFile, std::vector<float> textures, const char *prefix)
{
    size_t numberOfTextures = textures.size();

    fprintf_s(headerFile, "GLfloat %s_textures[%zd] = {\n\t", prefix, numberOfTextures);

    for(size_t counter = 0; counter < numberOfTextures; ++counter)
    {
        fprintf_s(headerFile, "%ff", textures[counter]);

        if(counter + 1 != numberOfTextures)
        {
            fprintf_s(headerFile, ", ");
        }

        if(counter % NR_TEXTURE_COORDS == (NR_TEXTURE_COORDS - 1))
        {
            fprintf_s(headerFile, "\n");

            if(counter + 1 != numberOfTextures)
            {
                fprintf_s(headerFile, "\t");
            }
        }
    }

    fprintf_s(headerFile, "};\n");
    fflush(headerFile);
}

void printNormals(FILE *headerFile, std::vector<float> normals, const char *prefix)
{
    size_t numberOfNormals = normals.size();

    fprintf_s(headerFile, "GLfloat %s_normals[%zd] = {\n\t", prefix, numberOfNormals);

    for(size_t counter = 0; counter < numberOfNormals; ++counter)
    {
        fprintf_s(headerFile, "%ff", normals[counter]);

        if(counter + 1 != numberOfNormals)
        {
            fprintf_s(headerFile, ", ");
        }

        if(counter % NR_NORMAL_COORDS == (NR_NORMAL_COORDS - 1))
        {
            fprintf_s(headerFile, "\n");

            if(counter + 1 != numberOfNormals)
            {
                fprintf_s(headerFile, "\t");
            }
        }
    }

    fprintf_s(headerFile, "};\n");
    fflush(headerFile);
}
