#include <algorithm>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/Model.h"

namespace Jade {
	Model::Model(const std::string& path) 
		: m_Path(path), m_Directory(m_Path.substr(0, m_Path.find_last_of('\\'))) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_Path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_FlipWindingOrder);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::string message = "Failed to load model ";
			message += m_Path;
			message += ' ';
			message += importer.GetErrorString();
			LOGGER.log(message, ERROR);
			return;
		}

		processNode(scene->mRootNode, scene);

		loadTextures(scene);
	}

	void Model::processNode(aiNode* node, const aiScene* scene) {
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(processMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene) {
		std::vector<Vertex> verticies;
		std::vector<unsigned int> indicies;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;

			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;

			if (mesh->mTextureCoords[0]) {
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.textureCordinates = vec;
			}
			else {
				vertex.textureCordinates = glm::vec2(0.0f, 0.0f);
			}
			verticies.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indicies.push_back(face.mIndices[j]);
			}
		}

		return Mesh(verticies, indicies);
	}

	void Model::loadTextures(const aiScene* scene) {
		int val = scene->mNumMaterials;
		for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
			aiMaterial* mat = scene->mMaterials[i];
			loadMaterialTextures(mat, aiTextureType_DIFFUSE, m_Textures);
			loadMaterialTextures(mat, aiTextureType_SPECULAR, m_Textures);
		}
	}

	void Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::vector<MetaDataTexture>& textureList) {
		for (unsigned int j = 0; j < mat->GetTextureCount(type); j++) {
			aiString str;
			mat->GetTexture(type, j, &str);

			std::vector<MetaDataTexture>::iterator it;
			for (it = textureList.begin(); it != textureList.end(); it++) {
				if (it->type == type) {
					return;
				}
			}

			textureList.push_back(MetaDataTexture{Texture(Image(m_Directory + '\\' + str.C_Str())), type});
		}
	}
}