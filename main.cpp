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

#include "Scene\SceneLoader.h"
#include "Scene\SceneDisplayer.h"

using namespace std;

int main(int argc, char *argv[])
{
	/* Initialisation du Contexte OpenGL en version 3.3 */
    Device device(800, 600, "OpenGL", 3, 3, true);

	// Ajout de la gestion des événements
    auto windowInput(std::make_shared<WindowInput>());
	auto mouseInput(std::make_shared<MouseInput>());
	auto keyboardInput(std::make_shared<KeyboardInput>());
    device.assignInput(windowInput);
	device.assignInput(mouseInput);
	device.assignInput(keyboardInput);

	// On cache le curseur et on l'emprisonne dans la fenêtre.
	device.hideCursor();

	// Classes permettant de gérer les shaders et programs
	ShaderRepository shaderRepository;

	// Classe permettant de charger les textures
	TextureRepository textureRepository;

	glEnable(GL_DEPTH_TEST); // On active le test de profondeur

	// On crée notre caméra
	CameraFPS camera(glm::vec3(0, 1, 0.1), 0.01f, 1.f, mouseInput, keyboardInput);

	SceneLoader sceneLoader;

	// On charge la scène dans le loader
	sceneLoader.load("../Models/map.png",
	{
		std::make_pair(0xffffff, SceneBlock::SOL), // blanc = sol,
		std::make_pair(0, SceneBlock::MUR), // couleur noir représente un mur
		std::make_pair(255, SceneBlock::COLLECTIBLE) // red  = collectible,
	}, 1.f);

	SceneDisplayer displayer(shaderRepository,
	{
		std::make_pair(SceneBlock::SOL, std::make_shared<ModelRenderer>("../Models/sol.obj", textureRepository)),
		std::make_pair(SceneBlock::MUR, std::make_shared<ModelRenderer>("../Models/mur.obj", textureRepository)),
		std::make_pair(SceneBlock::COLLECTIBLE, std::make_shared<ModelRenderer>("../Models/Collectible.obj", textureRepository))
	});

	auto scene = sceneLoader.load("../Models/map.png");

    while(windowInput->isRunning()) {
		if (!device.updateInputs())
			mouseInput->resetRelative();

		// Echap = quit
		if (keyboardInput->key(SDL_SCANCODE_ESCAPE))
			return 0;

		// On update la caméra
		camera.update(scene);

		// Efface l'écran et le depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// On l'affiche
		glm::mat4 perspMatrix(glm::perspective(glm::radians(70.f), (float)device.width() / device.height(), 0.01f, 500.f));
		displayer.draw(scene, camera.view(), perspMatrix);

		int a;
		std::cin >> a ;

        device.swapBuffers();
    }

    return 0;
}