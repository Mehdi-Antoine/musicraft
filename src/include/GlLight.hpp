#pragma once
#include <glimac/glm.hpp>

class GlLight{
private:

	glm::vec3 m_position,
			  m_intensity,
			  m_ks;

	float	  m_shininess;

	GLint     u_position,
			  u_intensity,
			  u_shininess,
			  u_color;

public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	GlLight();
	~GlLight();

//--------------------------------------------------GETTERS-----------------------------------------------------

	glm::vec3 getPosition() const;
	glm::vec3 getIntensity() const;
	glm::vec3 getKs() const;
	float getShininess() const;

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	void updatePosition(glm::vec3 position);
	void updateIntensity(glm::vec3 position);
	void updateKs(glm::vec3 position);
	void updateShininess(glm::vec3 position);
	
};