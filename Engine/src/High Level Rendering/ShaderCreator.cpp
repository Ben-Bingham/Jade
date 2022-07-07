#include "Jade.h"

#include "High Level Rendering/ShaderCreator.h"
#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	VertexShader ShaderCreator::vertexShaderInit() {
		std::string vertexShaderPath = "..\\Engine\\assets\\shaders\\";

		switch (m_RuleSet->ruleSet) { //TODO add more cases
		default:
		case STANDARD: vertexShaderPath += "StandardRuleSet.vert"; break;
		}

		TextFile vertexShaderFile(vertexShaderPath);

		return VertexShader(vertexShaderFile);

		/*vertexShaderSource += "#version 330 core\n";
		vertexShaderSource += "\n";
		vertexShaderSource += "layout(location = 0) in vec3 inputPositon;\n";
		vertexShaderSource += "layout(location = 1) in vec3 inputNormal;\n";
		if (m_RuleSet.ruleSet == TEXTURE) {
			vertexShaderSource += "layout(location = 2) in vec2 inputTextureCordinates;\n";
		}

		vertexShaderSource += "\n";
		if (m_RuleSet.ruleSet == TEXTURE || m_RuleSet.ruleSet == STANDARD) {
			vertexShaderSource += "out vec3 normal;\n";
			vertexShaderSource += "out vec3 fragmentPosition;\n";
		}
		if (m_RuleSet.ruleSet == TEXTURE) {
			vertexShaderSource += "out vec2 textureCordinates;\n";
		}

		vertexShaderSource += "\n";
		vertexShaderSource += "uniform mat4 model;\n";
		vertexShaderSource += "uniform mat4 view;\n";
		vertexShaderSource += "uniform mat4 projection;\n";
		vertexShaderSource += "\n";
		vertexShaderSource += "void main() {\n";
		vertexShaderSource += "	gl_Position = projection * view * model * vec4(inputPositon, 1.0);\n";
		if (m_RuleSet.ruleSet == TEXTURE || m_RuleSet.ruleSet == STANDARD) {
			vertexShaderSource += "	normal = mat3(transpose(inverse(model))) * inputNormal;\n";
			vertexShaderSource += "	fragmentPosition = vec3(model * vec4(inputPositon, 1.0));\n";
		}
		if (m_RuleSet.ruleSet == TEXTURE) {
			vertexShaderSource += "textureCordinates = inputTextureCordinates;\n";
		}
		vertexShaderSource += "}\0";

		std::string vertexShaderPath = "assets\\shaders\\ruleSet";
		vertexShaderPath += std::to_string(m_RuleSet.getID());
		vertexShaderPath += ".vert";*/

		
	}

	FragmentShader ShaderCreator::fragmentShaderInit() {
		std::string fragmentShaderPath = "..\\Engine\\assets\\shaders\\";

		switch (m_RuleSet->ruleSet) { //TODO add more cases
		default:
		case STANDARD: fragmentShaderPath += "StandardRuleSet.frag"; break;
		}

		TextFile fragmentShaderFile(fragmentShaderPath);

		return FragmentShader(fragmentShaderFile);

		//std::string fragmentShaderSource = "";

		//fragmentShaderSource += "#version 330 core\n";
		//fragmentShaderSource += "\n";
		//fragmentShaderSource += "out vec4 FragColor;\n";
		//if (m_RuleSet.ruleSet == TEXTURE || m_RuleSet.ruleSet == STANDARD) {
		//	fragmentShaderSource += "\n";
		//	fragmentShaderSource += "struct Material {\n";
		//	fragmentShaderSource += "	vec3 ambient;\n";
		//	fragmentShaderSource += "	vec3 diffuse;\n";
		//	fragmentShaderSource += "	vec3 specular;\n";
		//	fragmentShaderSource += "	float shininess;\n";
		//	fragmentShaderSource += "};\n";
		//	fragmentShaderSource += "\n";
		//	fragmentShaderSource += "struct Light {\n";
		//	fragmentShaderSource += "	vec3 position;\n";
		//	fragmentShaderSource += "\n";
		//	fragmentShaderSource += "	vec3 ambient;\n";
		//	fragmentShaderSource += "	vec3 diffuse;\n";
		//	fragmentShaderSource += "	vec3 specular;\n";
		//	fragmentShaderSource += "};\n";
		//	fragmentShaderSource += "vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);\n";
		//}
		//fragmentShaderSource += "\n";
		//if (m_RuleSet.ruleSet == TEXTURE || m_RuleSet.ruleSet == STANDARD) {
		//	fragmentShaderSource += "in vec3 normal;\n";
		//	fragmentShaderSource += "in vec3 fragmentPosition;\n";
		//}
		//if (m_RuleSet.ruleSet == TEXTURE) {
		//	fragmentShaderSource += "in vec2 textureCordinates;\n"; //TODO actually do something with this stuff
		//}
		//fragmentShaderSource += "\n";
		//if (m_RuleSet.ruleSet == TEXTURE || m_RuleSet.ruleSet == STANDARD) {
		//	fragmentShaderSource += "uniform vec3 cameraPosition;\n";
		//	fragmentShaderSource += "uniform Material material;\n";
		//	//fragmentShaderSource += "uniform Light light;\n";
		//	fragmentShaderSource += "\n";
		//	fragmentShaderSource += "#define NUMBER_OF_POINT_LIGHTS ";
		//	fragmentShaderSource += std::to_string(m_RuleSet.getLights().size());
		//	fragmentShaderSource += "\n\n";
		//	fragmentShaderSource += "uniform Light lights[NUMBER_OF_POINT_LIGHTS];\n";
		//}
		//if (m_RuleSet.ruleSet == SOLID_COLOUR) {
		//	fragmentShaderSource += "uniform vec4 objectColour;\n";
		//}
		//fragmentShaderSource += "\n";
		//fragmentShaderSource += "void main() {\n";
		//if (m_RuleSet.ruleSet == TEXTURE || m_RuleSet.ruleSet == STANDARD) {
		//	/*fragmentShaderSource += "	vec3 ambient = light.ambient * material.ambient;\n";
		//	fragmentShaderSource += "\n";
		//	fragmentShaderSource += "	vec3 norm = normalize(normal);\n";
		//	fragmentShaderSource += "	vec3 lightDir = normalize(light.position - fragmentPosition);\n";
		//	fragmentShaderSource += "	float diff = max(dot(norm, lightDir), 0.0);\n";
		//	fragmentShaderSource += "	vec3 diffuse = light.diffuse * (diff * material.diffuse);\n";
		//	fragmentShaderSource += "\n";
		//	fragmentShaderSource += "	vec3 viewDir = normalize(cameraPosition - fragmentPosition);\n";
		//	fragmentShaderSource += "	vec3 reflectDir = reflect(-lightDir, norm);\n";
		//	fragmentShaderSource += "	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n";
		//	fragmentShaderSource += "	vec3 specular = light.specular * (spec * material.specular);\n";
		//	fragmentShaderSource += "\n";
		//	fragmentShaderSource += "	vec3 result = ambient + diffuse + specular;\n";
		//	fragmentShaderSource += "	FragColor = vec4(result, 1.0);\n";*/

		//	"vec3 result = (0.0, 0.0, 0.0);\n";
		//	"\n";
		//	"for (int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++) {\n";
		//	"	result += CalcPointLight(lights[i], normal, fragmentPosition, cameraPosition);\n";
		//	"}\n";
		//	"\n";
		//	"FragColor = vec4(result, 1.0);\n";
		//}
		//if (m_RuleSet.ruleSet == SOLID_COLOUR) {
		//	fragmentShaderSource += "	FragColor = objectColour;\n";
		//}
		//fragmentShaderSource += "}\n";

		//if (m_RuleSet.ruleSet == TEXTURE || m_RuleSet.ruleSet == STANDARD) {
		//	"vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 cameraPosition) {\n";
		//	"	vec3 ambient = light.ambient * material.ambient;\n";
		//	"\n";
		//	"	vec3 norm = normalize(normal);\n";
		//	"	vec3 lightDir = normalize(light.position - fragmentPosition);\n";
		//	"	float diff = max(dot(norm, lightDir), 0.0);\n";
		//	"	vec3 diffuse = light.diffuse * (diff * material.diffuse);\n";
		//	"\n";
		//	"	vec3 viewDir = normalize(cameraPosition - fragmentPosition);\n";
		//	"	vec3 reflectDir = reflect(-lightDir, norm);\n";
		//	"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n";
		//	"	vec3 specular = light.specular * (spec * material.specular);\n";
		//	"\n";
		//	"	return (ambient + diffuse + specular);\n";
		//	"}\n";
		//}

		//fragmentShaderSource += "\0";

		//std::string fragmentShaderPath = "assets\\shaders\\ruleSet";
		//fragmentShaderPath += std::to_string(m_RuleSet.getID());
		//fragmentShaderPath += ".frag";
		//
		//return FragmentShader(TextFile(fragmentShaderPath, fragmentShaderSource));;
	}
}