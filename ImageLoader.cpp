#include "ImageLoader.h"
#include "IOManager.h"
#include "Errors.h"
#include "picoPNG.h"


namespace TRXEngine {
    GLTexture ImageLoader::loadPNG(std::string fp)
    {
        GLTexture texture{};

        // load file data
        std::vector<unsigned char> in_buffer{};
        if (!IOManager::readFileToBuffer(fp, in_buffer))
        {
            fatalError("Failed to load PNG file " + fp + " to buffer!");
        }

        std::vector<unsigned char> out{};
        unsigned long width{};
        unsigned long height{};
        // decode PNG and retrieve attributes
        int errorCode{ decodePNG(out, width, height, &(in_buffer[0]),in_buffer.size()) };
        if (errorCode)
        {
            fatalError("decodePNG failed with error: " + std::to_string(errorCode));
        }

        // get unique texture id
        glGenTextures(1, &(texture.id));

        glBindTexture(GL_TEXTURE_2D, texture.id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        texture.width = width;
        texture.height = height;

        return texture;
    }
}