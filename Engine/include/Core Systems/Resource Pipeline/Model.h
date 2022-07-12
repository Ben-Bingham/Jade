#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Jade {
	class threeDModel {
		Assimp::Importer importer;
	};
}