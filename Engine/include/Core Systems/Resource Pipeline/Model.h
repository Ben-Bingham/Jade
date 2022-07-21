#pragma once
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Jade.h"

#include "Mesh.h"

namespace Jade {
	struct ImageMetaData {
		Image image;
		aiTextureType type;
	};

	class Model {
	public:
		Model(const std::string& path, bool flipTextures);

		std::vector<Mesh> getMeshes() { return m_Meshes; }
		Image* getDiffuseImage() {
			std::vector<ImageMetaData>::iterator it;
			for (it = m_Images.begin(); it != m_Images.end(); it++) {
				if (it->type == aiTextureType_DIFFUSE) {
					return &(*it).image;
				}
			}
			std::string message = "";
			message += "Model: ";
			message += m_Path;
			message += " does not have a diffuse texture";
			LOG(message, ERROR);
			return nullptr;
		}

		Image* getSpecularImage() {
			std::vector<ImageMetaData>::iterator it;
			for (it = m_Images.begin(); it != m_Images.end(); it++) {
				if (it->type == aiTextureType_SPECULAR) {
					return &(*it).image;
				}
			}
			std::string message = "";
			message += "Model: ";
			message += m_Path;
			message += " does not have a specular texture";
			LOG(message, ERROR);
			return nullptr;
		}

	private:
		std::string m_Path;
		std::string m_Directory;
		std::string m_Name;
		std::vector<Mesh> m_Meshes;
		std::vector<ImageMetaData> m_Images;

		void loadFromRaw(bool flipTextures);
		void createInternal();
		void loadFromInternal(const std::string& fileName);

		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		void loadTextures(const aiScene* scene);
		void loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::vector<ImageMetaData>& textureList);

		static std::string internalBinaryExtension;

		std::string nameInit() {
			std::string name;
			name = m_Path.substr(m_Path.find_last_of('\\') + 1, m_Path.size());
			name = name.erase(name.find_first_of('.'), name.size());
			return name;
		}
	};
}