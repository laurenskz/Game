#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include "Types.h"

char* filetobuf(char *file);
void loadToVAO(RenderableMold* mold,PointerWithSize vertices, PointerWithSize normals, PointerWithSize textureCoords, PointerWithSize indices);

#endif
