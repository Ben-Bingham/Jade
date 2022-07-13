#pragma once
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Jade.h"

#include "Mesh.h"

namespace Jade {
	struct MetaDataTexture {
		Texture texture;
		aiTextureType type;
	};

	class Model {
	public:
		Model(const std::string& path);

		std::vector<Mesh> getMeshes() { return m_Meshes; }

	private:
		std::string m_Path;
		std::string m_Directory;
		std::vector<Mesh> m_Meshes;
		std::vector<MetaDataTexture> m_Textures;

		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		void loadTextures(const aiScene* scene);
		void loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::vector<MetaDataTexture>& textureList);
	};
}