#include "FrameBufferObject.h"
#include "FBOManager.h"

int FrameBufferObject::screenHeight= -1;
int FrameBufferObject::screenWidth = -1;
bool FrameBufferObject::resetViewport = true;

FrameBufferObject::FrameBufferObject(std::string name)
	: width(width),
	height(height),
	textureFormat(GL_RGBA),
	textureType(GL_TEXTURE_2D),
	texNum(0),
	nextIndex(0),
	Height(this->height),
	Width(this->width),
	Bound(this->bound)
{

	bound = false;
	setDrawBuffers = false;

	if (name == "")
	{
		char buf[64];
		sprintf(buf, "unnamed%d", ++nextIndex);
		this->name = buf;
	}
	else
	{
		this->name = name;
	}
	glID = 0;
}

void FrameBufferObject::Create(int width, int height, int depthBufferBitDepth, int stencilBufferBitDepth, GLenum textureFormat, GLenum textureType)
{
	bool rebind = false;
	if (bound)
	{
		Unbind();
		rebind = true;
	}
	if (glID)
		glDeleteFramebuffers(1, &glID);

	this->width = width;
	this->height = height;

	glGenFramebuffers(1, &glID);
	
	glBindFramebuffer(GL_FRAMEBUFFER, glID);
	if (depthBufferBitDepth || stencilBufferBitDepth)
	{
		GLenum format = 0;
		if (depthBufferBitDepth && stencilBufferBitDepth)
		{
			if (depthBufferBitDepth == 32 && stencilBufferBitDepth == 8)
				format = GL_DEPTH32F_STENCIL8;
			else
				format = GL_DEPTH24_STENCIL8;
			GLuint id;
			glGenRenderbuffers(1, &id);
			renderBuffers.push_back(id);
			renderBufferFormats.push_back(format);
			glBindRenderbuffer(GL_RENDERBUFFER, id);
			glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, id);
		}
		else if (stencilBufferBitDepth == 0)
		{
			if (depthBufferBitDepth == 16)			
				format = GL_DEPTH_COMPONENT16;
			else if (depthBufferBitDepth == 24)
				format = GL_DEPTH_COMPONENT24;
			else
				format = GL_DEPTH_COMPONENT32F;
			GLuint id;
			glGenRenderbuffers(1, &id);
			renderBuffers.push_back(id);
			renderBufferFormats.push_back(format);
			glBindRenderbuffer(GL_RENDERBUFFER, id);
			glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, id);			
		}
		
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (rebind)
		Bind();
}

FrameBufferObject::FrameBufferObject(int width, int height, int depthBufferBitDepth, int stencilBufferBitDepth, GLenum textureFormat, GLenum textureType, std::string name)
	: width(width),
	height(height),
	textureFormat(textureFormat),
	textureType(textureType),
	texNum(0),
	nextIndex(0),
	Height(this->height),
	Width(this->width),
	Bound(this->bound)
{

	bound = false;
	setDrawBuffers = false;

	if (name == "")
	{
		char buf[64];
		sprintf(buf, "unnamed%d", ++nextIndex);
		this->name = buf;
	}
	else
	{
		this->name = name;
	}

	glID = 0;
	Create(width, height, depthBufferBitDepth, stencilBufferBitDepth, textureFormat, textureType);

}

FrameBufferObject::~FrameBufferObject(void)
{
	glDeleteFramebuffers(1, &glID);
}

void FrameBufferObject::SetDrawBuffers(bool active)
{
	setDrawBuffers = active;
}

void FrameBufferObject::AttachDepthTexture(std::string name, GLenum magFilter, GLenum minFilter, GLenum depthFormat)
{
	AttachTextureTo(name, magFilter, minFilter, GL_DEPTH_ATTACHMENT, depthFormat, GL_DEPTH_COMPONENT);
}

void FrameBufferObject::AttachTextureTo(std::string name, GLenum magFilter, GLenum minFilter, GLenum attachmentPoint, GLenum texFormat, GLenum extFormat)
{
	FBOTexture* tex = new FBOTexture();
	tex->name = name;
	tex->type = GL_TEXTURE_2D;
	tex->format = texFormat;
	glGenTextures(1, &tex->glID);
	glBindTexture(textureType, tex->glID);
	glTexImage2D(textureType, 0, texFormat, width, height, 0, extFormat, GL_FLOAT, 0);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, minFilter);
	glBindFramebuffer(GL_FRAMEBUFFER, glID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentPoint, GL_TEXTURE_2D, tex->glID, 0);
	textures.push_back(tex);
	glBindTexture(textureType, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::AttachTexture(std::string name, GLenum minFilter, GLenum magFilter)
{
	AttachTextureTo(name, magFilter, minFilter, GL_COLOR_ATTACHMENT0 + texNum++, textureFormat);
}

FBOTexture* FrameBufferObject::GetTexture(std::string name)
{
	for (int i = 0; i < textures.size(); ++i)
	{
		if (!name.compare(textures[i]->name))
			return textures[i];
	}
	return 0;
}

FBOTexture* FrameBufferObject::GetTexture(GLuint index)
{
	return textures[index];
}

GLuint FrameBufferObject::GetTextureID(std::string name)
{
	return GetTexture(name)->glID;
}

GLuint FrameBufferObject::GetTextureID(GLuint index)
{
	return GetTexture(index)->glID;
}


bool FrameBufferObject::CheckCompleteness()
{
	if (!glID)
	{
		printf("Buffer not created yet!\n");
		return false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, glID);
	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if (result != GL_FRAMEBUFFER_COMPLETE)
	{
		switch(result)
		{
		case GL_FRAMEBUFFER_UNDEFINED:
			printf("Framebuffer undefined!\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			printf("Framebuffer incomplete attachment!\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			printf("Framebuffer incomplete, missing attachment!\n");
			break;
		default:
			printf("Framebuffer incomplete!\n");
			break;
		}
	}
	return (result == GL_FRAMEBUFFER_COMPLETE);
}

void FrameBufferObject::Bind()
{
	if (screenWidth < 0 && screenHeight < 0)
	{
		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		screenWidth = viewport[2];
		screenHeight = viewport[3];
	}	
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, glID);
	if (setDrawBuffers)
	{
		GLenum* buffers;
		buffers = (GLenum*)malloc(sizeof(GLenum) * texNum);
		for (int i = 0; i < texNum; ++i)
		{
			buffers[i] = GL_COLOR_ATTACHMENT0 + i;
		}
		glDrawBuffers(texNum, buffers);
	}
	bound = true;
}

void FrameBufferObject::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, screenWidth, screenHeight);
	if (setDrawBuffers)
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	bound = false;
}

void FrameBufferObject::ResizeBuffers(int width, int height)
{
	for (int i = 0; i < renderBuffers.size(); ++i)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffers[i]);
		glRenderbufferStorage(GL_RENDERBUFFER, renderBufferFormats[i], width, height);
	}
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FrameBufferObject::ResizeTextures(int width, int height)
{
	for (int i = 0; i < textures.size(); ++i)
	{
		glBindTexture(textures[i]->type, textures[i]->glID);
		glTexImage2D(textures[i]->type, 0, textures[i]->format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glBindTexture(textures[i]->type, 0);
	}	
}

void FrameBufferObject::Resize(int width, int height)
{
	bool rebind = false;
	if (bound)
	{
		Unbind();
		rebind = true;
	}
	ResizeBuffers(width, height);
	ResizeTextures(width, height);
	this->width = width;
	this->height = height;
	if (rebind)
		Bind();
}

void FrameBufferObject::SetTextureFormat(GLenum texFormat)
{
	textureFormat = texFormat;
}

void FrameBufferObject::SetTextureType(GLenum texType)
{
	textureType = texType;
}

