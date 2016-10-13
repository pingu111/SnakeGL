#include "OpenGLTools/device.h"
#include "OpenGLTools/Input/windowinput.h"
#include "OpenGLTools/Input/mouseinput.h"
#include "OpenGLTools/Input/keyboardinput.h"
#include "OpenGLTools/shaderrepository.h"
#include "OpenGLTools/program.h"
#include "OpenGLTools/glm.h"
#include "OpenGLTools/texturerepository.h"
#include "OpenGLTools\Model\modelrenderer.h"
#include "camera.h"
#include <iostream>
#include <GL/glew.h>
#include "main.h"

using namespace std;

unique_ptr<ModelRenderer> getCube(TextureRepository *textureRepository, Program *modelProgram, ShaderRepository *sR)
{
	unique_ptr<ModelRenderer> modelRenderer;
	modelProgram->attach(sR->shader("../Shaders/model.vert", GL_VERTEX_SHADER));
	modelProgram->attach(sR->shader("../Shaders/model.frag", GL_FRAGMENT_SHADER));
	modelProgram->link();
	
	modelRenderer = std::make_unique<ModelRenderer>("../Models/CubeBasic.obj", *textureRepository);
	return modelRenderer;
}

int main(int argc, char *argv[])
{
	/* Initialisation du Contexte OpenGL en version 3.3 */
    Device device(800, 600, "SnakeGL", 3, 3, true);

	// Ajout de la gestion des événements
    auto windowInput(make_shared<WindowInput>());
	auto mouseInput(make_shared<MouseInput>());
	auto keyboardInput(make_shared<KeyboardInput>());
    device.assignInput(windowInput);
	device.assignInput(mouseInput);
	device.assignInput(keyboardInput);

	// On cache le curseur et on l'emprisonne dans la fenêtre.
	device.hideCursor();

	// Classes permettant de gérer les shaders et programs
	ShaderRepository sR;
	Program modelProgram;

	// Classe permettant de charger les textures
	TextureRepository textureRepository;

	unique_ptr<ModelRenderer> modelRenderer;

	// On test les erreurs
	try 
	{

		// On tente d'ouvrir un modèle 3D (ici Sponza atrium)

		modelRenderer = getCube(&textureRepository, &modelProgram , &sR);
	}

	catch (runtime_error const &exception) {
		cerr << exception.what() << endl;
	}

	// On récupère les différentes locations correpondant aux variables uniforms des shaders model.vert/frag
	int locationMatrices = glGetUniformLocation(modelProgram, "matrices");
	int locationDiffuseTexture = glGetUniformLocation(modelProgram, "diffuseTexture");
	int locationDiffuseColor = glGetUniformLocation(modelProgram, "diffuseColor");
	int locationUseTexture = glGetUniformLocation(modelProgram, "useTexture");

	// On assigne la textureDiffuse à l'unité de texture 0
	glUseProgram(modelProgram);
	glUniform1i(locationDiffuseTexture, 0);
	glUseProgram(0);

	glEnable(GL_DEPTH_TEST); // On active le test de profondeur

	// On crée notre caméra
	CameraFPS camera(glm::vec3(1, 1, 1), 2.0f, 1.f, mouseInput, keyboardInput);
	int i = 0;
    while(windowInput->isRunning()) {
		if (!device.updateInputs())
			mouseInput->resetRelative();
		i++;
		// Echap = quit
		if (keyboardInput->key(SDL_SCANCODE_ESCAPE))
			return 0;


		// On update la caméra
		camera.update();

		// Efface l'écran et le depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

		// On utilise le modelProgram qui va nous servir pour le rendu de notre modèle3D
		glUseProgram(modelProgram);
		glm::mat4 matrices[3];
#define WORLD 0
#define VIEW 1
#define PROJ 2
		/* Matrice Modèle
			Peut contenir les transformations comme :
				- Les translations
				- Les rotations
				- Les changements d'échelles / homothéties */
		matrices[WORLD] = glm::mat4(1.f); 

		/* Matrice View
			Correspond tout simplement à la caméra */
		matrices[VIEW] = camera.view();

		/* Matrice de projection
			Correspond à la projection, ici on choisit la projection en perspective */
		matrices[PROJ] = glm::perspective(glm::radians(70.f), 4.f / 3, (float)1+ (float)i/1000.f, 10000.f);

		// on envoie les 3 matrices à notre tableau de matrice
		glUniformMatrix4fv(locationMatrices, 3, false, glm::value_ptr(matrices[0]));

		/* On dessine l'objet en prenant compte les matériaux,
		   La classe attends la location des variables diffuseColor (un vec3)
													 et useTexture (unt int) */
		modelRenderer->draw(true, locationDiffuseColor, locationUseTexture);

        device.swapBuffers();
    }

    return 0;
}


