#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Jade.h"

#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderStructs.h"
#include "Low Level Rendering/Rendering Objects/Texture.h"

namespace Jade {
	class ShaderProgram {
	public:
		ShaderProgram(FragmentShader& fragmentShader, VertexShader& vertexShader);

		void use() { glUseProgram(m_Program); }
		void dispose() { glDeleteProgram(m_Program); }

		void setInt(const std::string& variableName, const int value) const {
			glUniform1i(glGetUniformLocation(m_Program, variableName.c_str()), value);
		}

		void setFloat(const std::string& variableName, const float value) const {
			glUniform1f(glGetUniformLocation(m_Program, variableName.c_str()), value);
		}

		void setMatrix4f(const std::string& variableName, const glm::mat4& matrix) const {
			glUniformMatrix4fv(glGetUniformLocation(m_Program, variableName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
		}

		void setVector3f(const std::string& variableName, const glm::vec3& vector) const {
			glUniform3fv(glGetUniformLocation(m_Program, variableName.c_str()), 1, &vector[0]);
		}

		void setVector4f(const std::string& variableName, const glm::vec4& vector) const {
			glUniform4fv(glGetUniformLocation(m_Program, variableName.c_str()), 1, &vector[0]);
		}

		void setPointLight(const std::string& structName, const PointLight& light) const {
			setVector3f(structName + ".position", light.position);

			setFloat(structName +  ".constant", light.constant);
			setFloat(structName +  ".linear", light.linear);
			setFloat(structName +  ".quadratic", light.quadratic);

			setVector3f(structName + ".ambient", light.ambient);
			setVector3f(structName + ".diffuse", light.diffuse);
			setVector3f(structName + ".specular", light.specular);
		}

		void setPointLights(const std::string& structName, std::vector<PointLight>& lights) const {
			setInt("numberOfLights", (int)lights.size());

			int count = 0;
			std::string StructName = "";
			std::vector<PointLight>::iterator it;
			for (it = lights.begin(); it != lights.end(); it++) {
				StructName = structName;
				StructName += "[";
				StructName += std::to_string(count);
				StructName += "]";
				setPointLight(StructName, *it);
				count++;
			}
		}

		void setDirectionalLight(const std::string& structName, const DirectionalLight& directionalLight) {
			setVector3f(structName + ".direction", directionalLight.direction);
			setVector3f(structName + ".ambient", directionalLight.ambient);
			setVector3f(structName + ".diffuse", directionalLight.diffuse);
			setVector3f(structName + ".specular", directionalLight.specular);
		}

		void setMaterial(const std::string& structName, const Material& material) const {
			setVector3f(structName + ".ambient", material.ambient);
			setVector3f(structName + ".diffuse", material.diffuse);
			setVector3f(structName + ".specular", material.specular);
			setFloat(structName + ".shininess", material.shininess);
		}

		void setTexturedMaterial(const std::string& structName, const TexturedMaterial& material) const {
			setInt(structName + ".diffuse", 0);
			setInt(structName + ".specular", 1);
			setFloat(structName + ".shininess", material.shininess);
		}

		void setDiffuseMaterial(const std::string& structName, const DiffuseMaterial& material) const {
			setInt(structName + ".diffuse", 0);
			setVector3f(structName + ".specular", material.specular);
			setFloat(structName + ".shininess", material.shininess);
		}

	private:
		unsigned int m_Program;
		std::vector<Shader*> m_Shaders;
	};
}