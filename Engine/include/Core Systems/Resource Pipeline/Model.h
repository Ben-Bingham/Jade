#pragma once
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Jade.h"

#include "Mesh.h"

namespace Jade {
	enum ImageType {
		DIFFUSE,
		SPECULAR
	};

	struct AssimpMaterial {
		Image diffuse;
		Image specular;
		float shininess;
		unsigned int index;

		bool operator==(const AssimpMaterial& other) {
			if (diffuse.getPath() == other.diffuse.getPath() &&
				specular.getPath() == other.specular.getPath() &&
				shininess == other.shininess &&
				index == other.index) {

				return true;
			}
			else {
				return false;
			}
		}

		bool operator!=(const AssimpMaterial& other) {
			return !operator==(other);
		}
	};

	class Model {
	public:
		Model(const std::string& path, bool flipTextures = false);

		std::vector<Mesh> getMeshes() { return m_Meshes; }
		std::vector<AssimpMaterial> getMaterials() { return m_Materials; }

	private:
		std::string m_Path;
		std::string m_Directory;
		std::string m_Name;
		std::vector<Mesh> m_Meshes;
		std::vector<AssimpMaterial> m_Materials;

		void loadFromRaw(bool flipTextures);
		void createInternal();
		void loadFromInternal(const std::string& fileName);

		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		void loadTextures(const aiScene* scene);
		AssimpMaterial loadMaterial(aiMaterial* mat, unsigned int index);
		Image loadMaterialImage(aiMaterial* mat, ImageType type, unsigned int index);
		aiTextureType imageTypeToTextureType(ImageType type);

		static std::string internalBinaryExtension;

		std::string nameInit() {
			std::string name;
			name = m_Path.substr(m_Path.find_last_of('\\') + 1, m_Path.size());
			name = name.erase(name.find_first_of('.'), name.size());
			return name;
		}
	};
}