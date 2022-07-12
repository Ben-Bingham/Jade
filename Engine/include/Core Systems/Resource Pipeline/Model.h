#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Jade {
	class Model {
		Assimp::Importer importer;
	};
}