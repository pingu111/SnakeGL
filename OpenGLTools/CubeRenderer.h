
#pragma once

class CubeRenderer
{
	private :
		/// The ptr to the model of the cube
		ModelRenderer modelRenderer;

		/// The position etc matrix
		glm::mat4 matrices[3];

	public:

		/// Constructor 
		CubeRenderer(string path, TextureRepository *textureRepository, Program *modelProgram, ShaderRepository *sR);

		/// Destroctor
		~CubeRenderer();

		/// Set the matrix for this cube
		void setMatrices(glm::mat4 matrices[3]);

		/// Get the cube to render
		ModelRenderer* getCubeModel();

		ModelRenderer * getCubeModel(ModelRenderer model);

};

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   