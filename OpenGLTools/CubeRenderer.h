
#pragma once

class CubeRenderer
{
	static const int maxSize = 100;

	private :


		/// The ptr to the model of the cube
		ModelRenderer modelRenderer;

		/// The position etc matrix
		glm::mat4 matrices[maxSize];

	public:

		/// Constructor 
		CubeRenderer(string path, TextureRepository *textureRepository, Program *modelProgram, ShaderRepository *sR);

		/// Destroctor
		~CubeRenderer();

		/// Set the matrix for this cube
		void setMatrices(glm::mat4 matrices[]);

		/// Get the cube to render
		ModelRenderer* getCubeModel();
};

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   