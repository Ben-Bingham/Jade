#include "Jade.h"

#include "High Level Rendering/ShaderCreator.h"

namespace Jade {
	VertexShader& ShaderCreator::vertexShaderInit() {
		std::string vertexShaderSource = "#version 330 core\n\n";

		// ============================ Layout ============================
		if (m_RuleSet.Vertex_Positions && m_RuleSet.Vertex_Normals) {
			vertexShaderSource += "layout(location = 0) in vec3 inputPositon;\n";
			vertexShaderSource += "layout(location = 1) in vec3 inputNormal;\n";
		}
		else if (m_RuleSet.Vertex_Positions) {
			vertexShaderSource += "layout(location = 0) in vec3 inputPositon;\n";
		}
		else {
			LOGGER.log("Non standard vertex attributes used, none taken as input.", Jade::WARNING);
		}

		vertexShaderSource += "\n";

		// ============================ Out ============================
		if (m_RuleSet.Phong_Lighting) {
			vertexShaderSource += "out vec3 normal;\n";
			vertexShaderSource += "out vec3 fragmentPosition;\n";
		}

		vertexShaderSource += "\n";

		// ============================ Uniforms ============================
		vertexShaderSource += "uniform mat4 model;\n";
		vertexShaderSource += "uniform mat4 view;\n";
		vertexShaderSource += "uniform mat4 projection;\n";

		vertexShaderSource += "\n";

		// ============================ Main ============================
		vertexShaderSource += "void main() {\n";
		vertexShaderSource += "	gl_Position = projection * view * model * vec4(inputPositon, 1.0);\n";

		if (m_RuleSet.Phong_Lighting) {
			vertexShaderSource += "	normal = mat3(transpose(inverse(model))) * inputNormal;\n";
			vertexShaderSource += "	fragmentPosition = vec3(model * vec4(inputPositon, 1.0));\n";
		}

		vertexShaderSource += "}\0";

		std::string vertexShaderPath = "assets\\shaders\\ruleSet";
		vertexShaderPath += std::to_string(m_RuleSet.getID());
		vertexShaderPath += ".vert";

		
		return VertexShader(TextFile(vertexShaderPath, vertexShaderSource));;
	}

	FragmentShader& ShaderCreator::fragmentShaderInit() {
		std::string fragmentShaderSource = "#version 330 core\n\n";

		// ============================ Out ============================
		fragmentShaderSource += "out vec4 FragColor;\n";

		fragmentShaderSource += "\n";

		// ============================ In ============================
		if (m_RuleSet.Phong_Lighting) {
			fragmentShaderSource += "in vec3 normal;\n";
			fragmentShaderSource += "in vec3 fragmentPosition;\n";
		}

		fragmentShaderSource += "\n";

		// ============================ Uniforms ============================
		if (m_RuleSet.Object_Colour || m_RuleSet.Phong_Lighting) {
			fragmentShaderSource += "uniform vec3 objectColour;\n";
		}

		if (m_RuleSet.Phong_Lighting) {
			fragmentShaderSource += "uniform vec3 lightColour; \n";
			fragmentShaderSource += "uniform vec3 lightPosition; \n";
			fragmentShaderSource += "uniform vec3 cameraPosition;\n";
		}

		fragmentShaderSource += "\n";

		// ============================ Main ============================
		fragmentShaderSource += "void main() {\n";

		if (m_RuleSet.Phong_Lighting) {
			fragmentShaderSource += "	float ambientStrength = 0.1;\n";
			fragmentShaderSource += "	vec3 ambient = ambientStrength * lightColour;\n";
			fragmentShaderSource += "	\n";
			fragmentShaderSource += "	vec3 normalizedNormal = normalize(normal);\n";
			fragmentShaderSource += "	vec3 lightDirection = normalize(lightPosition - fragmentPosition);\n";
			fragmentShaderSource += "	float differenceInVectors = max(dot(normalizedNormal, lightDirection), 0.0);\n";
			fragmentShaderSource += "	vec3 diffuse = differenceInVectors * lightColour;\n";
			fragmentShaderSource += "	\n";
			fragmentShaderSource += "	float specularStrength = 0.5;\n";
			fragmentShaderSource += "	float shininess = 32;\n";
			fragmentShaderSource += "	\n";
			fragmentShaderSource += "	vec3 viewDirection = normalize(cameraPosition - fragmentPosition);\n";
			fragmentShaderSource += "	vec3 reflectionDirection = reflect(-lightDirection, normalizedNormal);\n";
			fragmentShaderSource += "	\n";
			fragmentShaderSource += "	float specularValue = pow(max(dot(viewDirection, reflectionDirection), 0.0), shininess);\n";
			fragmentShaderSource += "	vec3 specular = specularStrength * specularValue * lightColour;\n";
			fragmentShaderSource += "	\n";
			fragmentShaderSource += "	vec3 result = (ambient + diffuse + specular) * objectColour; // Default\n";
			fragmentShaderSource += "	FragColor = vec4(result, 1.0); // Default\n";
		}

		if (m_RuleSet.Object_Colour && !m_RuleSet.Phong_Lighting) {
			fragmentShaderSource += "	FragColor = vec4(objectColour, 1.0);\n";
		}
		
		if (!m_RuleSet.Phong_Lighting && !m_RuleSet.Object_Colour) {
			fragmentShaderSource += "	FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n";
		}

		fragmentShaderSource += "}\0";

		std::string fragmentShaderPath = "assets\\shaders\\ruleSet";
		fragmentShaderPath += std::to_string(m_RuleSet.getID());
		fragmentShaderPath += ".frag";

		
		return FragmentShader(TextFile(fragmentShaderPath, fragmentShaderSource));;
	}
}