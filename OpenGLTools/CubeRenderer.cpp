#include <iostream>
#include "../OpenGLTools/texturerepository.h"
#include "../OpenGLTools\Model\modelrenderer.h"
#include "../OpenGLTools/shaderrepository.h"
#include "../OpenGLTools/program.h"

#include "CubeRenderer.h"


CubeRenderer::CubeRenderer(string path, TextureRepository *textureRepository, Program *modelProgram, ShaderRepository *sR) 
{
	modelProgram->attach(sR->shader("../Shaders/model.vert", GL_VERTEX_SHADER));
	modelProgram->attach(sR->shader("../Shaders/model.frag", GL_FRAGMENT_SHADER));
	modelProgram->link();
	modelRenderer = ModelRenderer(path, *textureRepository);
}

ModelRenderer* CubeRenderer::getCubeModel()
{
	cout << &modelRenderer << endl;
	return &modelRenderer;
}

ModelRenderer* CubeRenderer::getCubeModel(ModelRenderer model)
{
	return &model;
}

void CubeRenderer::setMatrices(glm::mat4 _matrices[3])
{
	//matrices = glm::mat4[_matrices->length()];
	for (int i = 0; i < _matrices->length(); i++)
	{
		std::cout << i << endl;
		matrices[i] = _matrices[i];
	}
}

CubeRenderer::~CubeRenderer()
{
}