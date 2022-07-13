#pragma once
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Jade.h"

#include "Mesh.h"

namespace Jade {
	class Model {
	public:
		Model(const std::string& path);/* : m_Path(path) {
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(m_Path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
				std::string message = "Assimp failed to load model ";
				message += m_Path;
				message += ' ';
				message += importer.GetErrorString();
				LOGGER.log(message, ERROR);
				return;
			}

			processNode(scene->mRootNode, scene);
		}*/

		std::vector<Mesh> getMeshes() { return m_Meshes; }

	private:
		std::string m_Path;
		std::vector<Mesh> m_Meshes;

		void processNode(aiNode* node, const aiScene* scene);/* {
			for (unsigned int i = 0; i < node->mNumMeshes; i++) {
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				m_Meshes.push_back(processMesh(mesh, scene));
			}

			for (unsigned int i = 0; i < node->mNumChildren; i++) {
				processNode(node->mChildren[i], scene);
			}
		}*/

		Mesh processMesh(aiMesh* mesh, const aiScene* scene);/* {
			std::vector<Vertex> verticies;
			std::vector<unsigned int> indicies;
			std::vector<TextureStruct> textures;

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

			if (mesh->mMaterialIndex >= 0) {
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

				std::vector<TextureStruct> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");

				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

				std::vector<TextureStruct> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			}

			return Mesh(verticies, indicies, textures);
		}*/

		std::vector<TextureStruct> loadMaterialTextures(aiMaterial* material, aiTextureType textureType, std::string type); //{
		//	std::vector<TextureStruct> textures;
		//	for (unsigned int i = 0; i < material->GetTextureCount(textureType); i++) {
		//		aiString str;
		//		material->GetTexture(textureType, i, &str);
		//		TextureStruct texture;
		//		//texture.id = TextureFromFile(); //TODO
		//		texture.type = type;
		//		//texture.path = str;
		//		textures.push_back(texture);
		//	}

		//	return textures;
		//}
	};
}