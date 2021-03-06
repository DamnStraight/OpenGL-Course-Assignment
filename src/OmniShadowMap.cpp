#include "OmniShadowMap.h"

OmniShadowMap::OmniShadowMap() : ShadowMap() {}

bool OmniShadowMap::init(unsigned int width, unsigned int height)
{
    shadow_width = width;
    shadow_height = height;

    glGenFramebuffers(1, &FBO);

    glGenTextures(1, &shadow_map);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadow_map);

    for (size_t i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }

    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadow_map, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Framebuffer error: %u\n", Status);
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

void OmniShadowMap::write() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
}

void OmniShadowMap::read(GLenum texture_unit) {
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadow_map);
}
