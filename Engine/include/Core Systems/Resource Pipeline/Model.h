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
		std::vector<Mesh> m_Meshes;

		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<TextureStruct> loadMaterialTextures(aiMaterial* material, aiTextureType textureType, std::string type);
	};
}