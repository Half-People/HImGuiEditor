#pragma once
#ifndef ImFileDialogTool
#define ImFileDialogTool
//#include "ImFileDialog/ImFileDialog.h"

#define InitImFileDialog ifd::FileDialog::Instance().CreateTexture = [](uint8_t* data, int w, int h, char fmt) -> void* {\
GLuint tex;\
\
glGenTextures(1, &tex);\
glBindTexture(GL_TEXTURE_2D, tex);\
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);\
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);\
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);\
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);\
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, (fmt == 0) ? GL_BGRA_EXT  : GL_RGBA, GL_UNSIGNED_BYTE, data);\
/*glGenerateMipmap(GL_TEXTURE_2D);*/\
glBindTexture(GL_TEXTURE_2D, 0);\
\
return (void*)tex;\
};\
ifd::FileDialog::Instance().DeleteTexture = [](void* tex) {\
	GLuint texID = (GLuint)tex;\
	glDeleteTextures(1, &texID);\
};\

#endif // !ImFileDialogTool