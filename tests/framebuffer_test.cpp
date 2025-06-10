#include <gtest/gtest.h>
#include <SDL.h>
#include <GL/glew.h>
#include "framebuffer.h"

class SDLFixture : public ::testing::Test {
protected:
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;

    void SetUp() override {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        window = SDL_CreateWindow("test", 0, 0, 64, 64, SDL_WINDOW_OPENGL);
        context = SDL_GL_CreateContext(window);
        glewExperimental = GL_TRUE;
        glewInit();
    }

    void TearDown() override {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

TEST_F(SDLFixture, TextureIdNonZero) {
    Framebuffer fb(64, 64);
    EXPECT_NE(fb.getTextureID(), 0u);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
