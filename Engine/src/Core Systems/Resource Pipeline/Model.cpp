#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/Model.h"
#include "Core Systems/Resource Pipeline/TextFile.h"
#include "High Level Rendering/Colour.h"

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
		std::string message = "";
		message += "Loading make take longer than usual, " + m_Name + " needs to be formated.";
		LOG(message, INFO);

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

				std::vector<unsigned int> indicies = it->getIndicies();
				size = indicies.size() * sizeof(unsigned int);
				outputFile.write((char*)&size, sizeof(size_t));
				outputFile.write((char*)&indicies[0], size);

				unsigned int index = (it)->getMaterialIndex();
				outputFile.write((char*)&index, sizeof(unsigned int));
			}

			size = m_Materials.size();
			outputFile.write((char*)&size, sizeof(size_t));

			std::vector<AssimpMaterial>::iterator it2;
			for (it2 = m_Materials.begin(); it2 != m_Materials.end(); it2++) {
				AssimpMaterial material = *it2;

				Image diffuseImage = material.diffuse;
				size = diffuseImage.getWidth();
				outputFile.write((char*)&size, sizeof(size_t));
				size = diffuseImage.getHeight();
				outputFile.write((char*)&size, sizeof(size_t));
				size = diffuseImage.getChannels();
				outputFile.write((char*)&size, sizeof(size_t));

				outputFile.write((char*)&diffuseImage.getContent()[0], diffuseImage.getWidth() * diffuseImage.getHeight() * diffuseImage.getChannels() * sizeof(unsigned char));

				Image specularImage = material.specular;
				size = specularImage.getWidth();
				outputFile.write((char*)&size, sizeof(size_t));
				size = specularImage.getHeight();
				outputFile.write((char*)&size, sizeof(size_t));
				size = specularImage.getChannels();
				outputFile.write((char*)&size, sizeof(size_t));

				outputFile.write((char*)&specularImage.getContent()[0], specularImage.getWidth() * specularImage.getHeight() * specularImage.getChannels() * sizeof(unsigned char));

				outputFile.write((char*)&material.shininess, sizeof(float));
				outputFile.write((char*)&material.index, sizeof(unsigned int));
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

				unsigned int index;
				inputFileStream.read((char*)&index, sizeof(unsigned int));

				meshes.push_back(Mesh(verticies, indicies, index));
			}

			m_Meshes = meshes;

			size_t numberOfMaterials = 0;
			inputFileStream.read((char*)&numberOfMaterials, sizeof(size_t));

			std::vector<AssimpMaterial> materials;
			for (unsigned int i = 0; i < numberOfMaterials; i++) {
				int width{ 0 }, height{ 0 }, channels{ 0 };
				float shininess{ 0 };
				unsigned int index{ 0 };
			
				inputFileStream.read((char*)&size, sizeof(size_t));
				width = (int)size;
				inputFileStream.read((char*)&size, sizeof(size_t));
				height = (int)size;
				inputFileStream.read((char*)&size, sizeof(size_t));
				channels = (int)size;
			
				std::vector<unsigned char> imageData(width * height * channels * sizeof(unsigned char));
			
				inputFileStream.read((char*)&imageData[0], imageData.size());
				Image diffuseImage(imageData, width, height, channels);

				inputFileStream.read((char*)&size, sizeof(size_t));
				width = (int)size;
				inputFileStream.read((char*)&size, sizeof(size_t));
				height = (int)size;
				inputFileStream.read((char*)&size, sizeof(size_t));
				channels = (int)size;

				imageData.resize(width * height * channels * sizeof(unsigned char));

				inputFileStream.read((char*)&imageData[0], imageData.size());
				Image specularImage(imageData, width, height, channels);

				inputFileStream.read((char*)&shininess, sizeof(float));
				inputFileStream.read((char*)&index, sizeof(unsigned int));

				materials.push_back(AssimpMaterial{ diffuseImage, specularImage, shininess, index });
			}

			m_Materials = materials;

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

	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
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

		return Mesh(verticies, indicies, mesh->mMaterialIndex);
	}

	void Model::loadTextures(const aiScene* scene) {
		unsigned int numberOfDiffuse = 0;
		unsigned int numberOfSpecular = 0;
		for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
			aiMaterial* mat = scene->mMaterials[i];

			bool repeat = false;

			AssimpMaterial material = loadMaterial(mat, i);
			for (AssimpMaterial assimpMat : m_Materials) {
				if (assimpMat == material) {
					repeat = true;
					break;
				}
			}

			if (!repeat) {
				m_Materials.push_back(material);
			}
		}
	}

	AssimpMaterial Model::loadMaterial(aiMaterial* mat, unsigned int index) {
		
		Image diffuseImage = loadMaterialImage(mat, DIFFUSE, index);

		Image specularImage = loadMaterialImage(mat, SPECULAR, index);

		float shininess;
		mat->Get(AI_MATKEY_SHININESS, shininess);
		if (shininess == 0.0f) {
			shininess = 32.0f;
		}
		
		return AssimpMaterial { std::move(diffuseImage), std::move(specularImage), std::move(shininess), std::move(index) };
	}

	Image Model::loadMaterialImage(aiMaterial* mat, ImageType type, unsigned int index) {
		if (mat->GetTextureCount(imageTypeToTextureType(type)) != 0) {
			aiString str;
			mat->GetTexture(imageTypeToTextureType(type), 0, &str);

			return Image(m_Directory + '\\' + str.C_Str());
		}
		else {
			std::string imageType;
			aiColor3D colour;
			switch (type) {
			default:
			case DIFFUSE: mat->Get(AI_MATKEY_COLOR_DIFFUSE, colour); imageType = "Diffuse"; break;
			case SPECULAR: mat->Get(AI_MATKEY_COLOR_SPECULAR, colour); imageType = "Specular"; break;
			}
			
			return Image(m_Directory + '\\' + m_Name + "_Procedural_" + imageType + std::to_string(index) + ".png", Colour(colour), 1, 1);
		}
	}

	aiTextureType Model::imageTypeToTextureType(ImageType type) {
		switch (type) {
		default:
		case DIFFUSE: return aiTextureType_DIFFUSE;
		case SPECULAR: return aiTextureType_SPECULAR;
		}
	}

	std::string Model::internalBinaryExtension = ".JadeModel";
}