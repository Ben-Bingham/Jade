#pragma once
#include <sstream>
#include <vector>

#include "Jade.h"

#include "stb_image.h"
#include "stb_image_write.h"
#include "High Level Rendering/Colour.h"

namespace Jade {
	class Image {
	public:
		Image(const std::string& path, bool flipVertically = true) : m_Path(path) {
			stbi_set_flip_vertically_on_load(flipVertically);

			unsigned char* data = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
			m_Content.resize(m_Width * m_Height * m_Channels);

			memcpy(&m_Content[0], data, m_Content.size());

			if (!data) {
				LOG("Image: " + m_Path + "Failed to load. ", Jade::ERROR);
			}
			stbi_image_free(data);
		}

		Image(unsigned char* content, int width, int height, int channels) 
			: m_Content(content), m_Width(width), m_Height(height), m_Channels(channels), m_Stbi(false) {}

		std::vector<unsigned char> getContent() const { return m_Content; }
		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		int getChannels() const { return m_Channels; }
		std::string getPath() const { return m_Path; }

	private:
		std::vector<unsigned char> m_Content;
		std::string m_Path;
		int m_Width;
		int m_Height;
		int m_Channels;
	};
}