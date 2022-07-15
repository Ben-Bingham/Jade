#pragma once
#include <sstream>

#include "Jade.h"

#include "stb_image.h"

namespace Jade {
	class Image {
	public:
		Image(const std::string& path, bool flipVertically = true) : m_Path(path), m_Stbi(true) {
			stbi_set_flip_vertically_on_load(flipVertically);

			m_Content = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_Channels, 0);

			if (!m_Content) {
				LOGGER.log("Image: " + m_Path + "Failed to load.", Jade::ERROR);
				this->free();
			}
		}

		Image(unsigned char* content, int width, int height, int channels) 
			: m_Content(content), m_Width(width), m_Height(height), m_Channels(channels), m_Stbi(false) {}

		unsigned char* getContent() const { return m_Content; }
		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		int getChannels() const { return m_Channels; }
		std::string getPath() const { return m_Path; }
		bool getStbi() const { return m_Stbi; }

		void free() { if (m_Stbi) { stbi_image_free(m_Content); } else { delete[] m_Content; } }

	private:
		unsigned char* m_Content;
		std::string m_Path;
		int m_Width;
		int m_Height;
		int m_Channels;
		bool m_Stbi;
	};
}