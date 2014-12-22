#pragma once

#include <vector>



class GlEnvironnement{

private:

	std::vector<GlElement> m_elements;

	std::vector<GlTexture> m_textures;

	std::vector<GlLight>   m_lights;

	std::vector<GlShader>  m_shader;

	GlUniform              m_projection_matrix,
			               m_view_matrix;

	char*                  m_dir_path;

public:

	GlEnvironnement(char* dirPath);
	~GlEnvironnement();
	
	void addElement(GlElement gl_element);

	void addLight(GlLight gl_light);

	void addTexture(GlLight gl_texture);

	void addShader(GlShader gl_shader);

	void draw();

	void update();

};