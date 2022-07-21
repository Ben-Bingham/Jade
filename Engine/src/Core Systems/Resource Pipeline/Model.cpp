#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/Model.h"
#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	Model::Model(const std::string& path, bool flipTextures) 
		: m_Path(path), m_Directory(m_Path.substr(0, m_Path.find_last_of('\\'))), m_Name(nameInit()) {

		std::string fileName = "";
		fileName += m_Directory.c_str();
		fileName += '\\';
		fileName += m_Name;
		fileName += internalBinaryExtension;

		std::ifstream f(fileName);
		if (f.good()) {
			std::string fileNameNoExtension = "";
			fileNameNoExtension += m_Directory.c_str();
			fileNameNoExtension += '\\';
			fileNameNoExtension += m_Name;
			loadFromInternal(fileNameNoExtension);
		}
		else {
			loadFromRaw(flipTextures);
		}
		f.close();
	}

	void Model::loadFromRaw(bool flipTextures) {
		Assimp::Importer importer;
		unsigned int flags = aiProcess_Triangulate | aiProcess_FlipWindingOrder;
		if (flipTextures) {
			flags |= aiProcess_FlipUVs;
		}

		const aiScene* scene = importer.ReadFile(m_Path, flags);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::string message = "Failed to load model ";
			message += m_Path;
			message += ' ';
			message += importer.GetErrorString();
			LOG(message, ERROR);
			return;
		}

		processNode(scene->mRootNode, scene);

		loadTextures(scene);

		createInternal();
	}

	void Model::createInternal() {
		std::string message = "";
		message += "Loading make take longer than usual, certain models need to be formated, including: ";
		message += m_Name;
		LOG(message, INFO);

		std::ofstream outputFile(m_Directory + '\\' + m_Name + internalBinaryExtension, std::ios::out | std::ios::binary);
		if (outputFile.is_open()) {

			size_t size = m_Meshes.size();
			outputFile.write((char*)&size, sizeof(size_t));
			std::vector<Mesh>::iterator it;
			for (it = m_Meshes.begin(); it != m_Meshes.end(); it++) {

				std::vector<Vertex> verticies = it->getVerticies();
				size = verticies.size() * sizeof(Vertex);
				outputFile.write((char*)&size, sizeof(size_t));
				outputFile.write((char*)&verticies[0], size);

				size_t sizeVert = sizeof(Vertex);
				size_t sizeUI = sizeof(unsigned int);

				std::vector<unsigned int> indicies = it->getIndicies();
				size = indicies.size() * sizeof(unsigned int);
				outputFile.write((char*)&size, sizeof(size_t));
				outputFile.write((char*)&indicies[0], size);
			}

			size = m_Images.size();
			outputFile.write((char*)&size, sizeof(size_t));
			std::vector<ImageMetaData>::iterator it2;
			for (it2 = m_Images.begin(); it2 != m_Images.end(); it2++) {
				ImageMetaData image = *it2;
				outputFile.write((char*)&image.type, sizeof(aiTextureType));

				Image pic = image.image;
				size = pic.getWidth();
				outputFile.write((char*)&size, sizeof(size_t));
				size = pic.getHeight();
				outputFile.write((char*)&size, sizeof(size_t));
				size = pic.getChannels();
				outputFile.write((char*)&size, sizeof(size_t));

				outputFile.write((char*)&pic.getContent()[0], pic.getWidth() * pic.getHeight() * pic.getChannels() * sizeof(unsigned char));
			}

			outputFile.close();
		}
		else {
			LOG("Unable to open binary file: " + m_Directory + m_Name + internalBinaryExtension, ERROR);
		}
	}

	void Model::loadFromInternal(const std::string& fileName) {
		std::ifstream inputFileStream(fileName + internalBinaryExtension, std::ios::in | std::ios::binary);
		if (inputFileStream.is_open()) {
			size_t size = 0;
			size_t numberOfMeshes = 0;
			inputFileStream.read((char*)&numberOfMeshes, sizeof(size_t));

			std::vector<Mesh> meshes;

			for (unsigned int i = 0; i < numberOfMeshes; i++) {
				inputFileStream.read((char*)&size, sizeof(size_t));
				
				std::vector<Vertex> verticies(size / sizeof(Vertex));
				inputFileStream.read((char*)&verticies[0], size);

				inputFileStream.read((char*)&size, sizeof(size_t));

				std::vector<unsigned int> indicies(size / sizeof(unsigned int));
				inputFileStream.read((char*)&indicies[0], size);

				Mesh mesh(verticies, indicies);
				meshes.push_back(mesh);
			}

			size_t numberOfTextures = 0;
			inputFileStream.read((char*)&numberOfTextures, sizeof(size_t));

			std::vector<ImageMetaData> images;

			for (unsigned int i = 0; i < numberOfTextures; i++) {
				aiTextureType imageType;
				int width = 0, height = 0, channels = 0;

				inputFileStream.read((char*)&imageType, sizeof(aiTextureType));
				inputFileStream.read((char*)&size, sizeof(size_t));
				width = (int)size;
				inputFileStream.read((char*)&size, sizeof(size_t));
				height = (int)size;
				inputFileStream.read((char*)&size, sizeof(size_t));
				channels = (int)size;

				unsigned char* imageData = new unsigned char[width * height * channels * sizeof(unsigned char)];

				inputFileStream.read((char*)imageData, width * height * channels * sizeof(unsigned char));

				Image image(imageData, width, height, channels);
				images.push_back(ImageMetaData{ image, imageType });
			}

			m_Meshes = meshes;
			m_Images = images;
			inputFileStream.close();
		}
		else {
			LOG("Unable to open binary file: " + fileName, ERROR);
		}
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
			loadMaterialTextures(mat, aiTextureType_DIFFUSE, m_Images);
			loadMaterialTextures(mat, aiTextureType_SPECULAR, m_Images);
		}
	}

	void Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::vector<ImageMetaData>& textureList) {
		for (unsigned int j = 0; j < mat->GetTextureCount(type); j++) {
			aiString str;
			mat->GetTexture(type, j, &str);

			std::vector<ImageMetaData>::iterator it;
			for (it = textureList.begin(); it != textureList.end(); it++) {
				if (it->type == type) {
					return;
				}
			}

			textureList.push_back(ImageMetaData{Image(m_Directory + '\\' + str.C_Str(), false), type});
		}
	}

	std::string Model::internalBinaryExtension = ".JadeModel";
}