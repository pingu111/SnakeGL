#include <GL/glew.h>
#include "OpenGLTools/device.h"
#include "OpenGLTools/Input/windowinput.h"
#include "OpenGLTools/Input/keyboardinput.h"
#include "OpenGLTools/Input/mouseinput.h"
#include "OpenGLTools/shaderrepository.h"
#include "OpenGLTools/program.h"
#include "OpenGLTools/glm.h"
#include "OpenGLTools/texturerepository.h"
#include "OpenGLTools/Model/modelrenderer.h"
#include "camera.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Device device(800, 600, "SnakeGL", 3, 3, true);
    std::shared_ptr<WindowInput> windowInput(std::make_shared<WindowInput>());
    std::shared_ptr<KeyboardInput> keyboardInput(std::make_shared<KeyboardInput>());
    std::shared_ptr<MouseInput> mouseInput(std::make_shared<MouseInput>());
    device.assignInput(windowInput);
    device.assignInput(keyboardInput);
    device.assignInput(mouseInput);

    TextureRepository textureRepository;
    ShaderRepository shaderRepository;

	ModelRenderer cube("../Models/CubeBasic.obj", textureRepository);

    Program modelProgram;

    modelProgram.attach(shaderRepository.shader("../Shaders/model.vert", GL_VERTEX_SHADER));
    modelProgram.attach(shaderRepository.shader("../Shaders/model.frag", GL_FRAGMENT_SHADER));

    modelProgram.link();

    glm::mat4 proj = glm::perspective(glm::radians(70.0f), 800.f / 600.f, 1.f, 10000.f);
    glm::mat4 view = glm::lookAt(glm::vec3(700, 1000, 1), glm::vec3(0, 500, 10), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.f);

    int projLocation = glGetUniformLocation(modelProgram, "proj");
    int viewLocation = glGetUniformLocation(modelProgram, "view");
    int modelLocation = glGetUniformLocation(modelProgram, "model");
    int texLocation = glGetUniformLocation(modelProgram, "tex");
    int colorLocation = glGetUniformLocation(modelProgram, "color");
    int useTextureLocation = glGetUniformLocation(modelProgram, "useTexture");

    glUseProgram(modelProgram);
    glUniformMatrix4fv(projLocation, 1, false, glm::value_ptr(proj));
    glUniformMatrix4fv(modelLocation, 1, false, glm::value_ptr(model));
    glUniform1i(texLocation, 0);
    glUseProgram(0);

    glEnable(GL_DEPTH_TEST);

  //  CameraFPS camera(glm::vec3(700, 1000, 1), 5, 1, mouseInput, keyboardInput);
    CameraFPS camera(glm::vec3(1, 1, 1), 1, 1, mouseInput, keyboardInput);

    device.hideCursor();

    while(windowInput->isRunning()) 
	{
        if(!device.updateInputs())
            mouseInput->resetRelative();

		camera.update();

        view = camera.view();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(modelProgram);
        glUniformMatrix4fv(viewLocation, 1, false, glm::value_ptr(view));

        cube.draw(true, colorLocation);
        device.swapBuffers();

		if (keyboardInput->key(SDL_SCANCODE_ESCAPE))
			return 0;
    }

    return 0;
}
