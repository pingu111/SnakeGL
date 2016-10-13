#include <iostream>
#include "../OpenGLTools/texturerepository.h"
#include "../OpenGLTools\Model\modelrenderer.h"
#include "../OpenGLTools/shaderrepository.h"
#include "../OpenGLTools/program.h"

#include "CubeRenderer.h"


CubeRenderer::CubeRenderer(string path, TextureRepository *textureRepository, Program *modelProgram, ShaderRepository *sR) : modelRenderer(path, *textureRepository)
{
	modelProgram->attach(sR->shader("../Shaders/model.vert", GL_VERTEX_SHADER));
	modelProgram->attach(sR->shader("../Shaders/model.frag", GL_FRAGMENT_SHADER));
	modelProgram->link();
}

ModelRenderer CubeRenderer::getCubeModel()
{
	std::cout << &modelRenderer << endl;
	return modelRenderer;
}

void CubeRenderer::setMatrices(glm::mat4 _matrices[3])
{
	for (int i = 0; i < matrices->length(); i++)
	{
		std::cout << i << endl;
		matrices[i] = _matrices[i];
	}
}

CubeRenderer::~CubeRenderer()
{
}