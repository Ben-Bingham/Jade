#pragma once
#include <sstream>

#include "Jade.h"

#include "stb_image.h"

namespace Jade {
	namespace Resources {
		class Image {
		public:
			Image() {}
			Image(std::string& path) { setPath(path); }
			Image(std::string&& path) { setPath(std::move(path)); }

			void setPath(std::string& newPath) {
				m_Path = newPath;
				m_Content = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_Channels, 0);

				if (!m_Content) {
					LOGGER.log("Image: " + newPath + "Failed to load.", Jade::ERROR);
					this->free();
				}
			}

			void setPath(std::string&& newPath) {
				m_Path = newPath;
				m_Content = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_Channels, 0);

				if (!m_Content) {
					LOGGER.log("Image: " + newPath + "Failed to load.", Jade::ERROR);
					this->free();
				}
			}

			unsigned char* getContent() const { return m_Content; }
			int getWidth() const { return m_Width; }
			int getHeight() const { return m_Height; }
			int getChannels() const { return m_Channels; }
			void free() { stbi_image_free(m_Content); }

		private:
			unsigned char* m_Content;
			std::string m_Path;
			int m_Width;
			int m_Height;
			int m_Channels;
		};
	}
}