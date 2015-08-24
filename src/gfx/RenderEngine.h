#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SDL.h>
#include "Renderable.h"
#include "./OpenGL/shader.h"
#include "../Constants.h"

#include "./OpenGL/freetype-gl/texture-font.h"
#include "./OpenGL/freetype-gl/texture-atlas.h"

#include "Font.h"
#include "../Input/InputManager.h"

#include <CEGUI/Window.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <SDL_events.h>


class RenderEngine
{
public:
	RenderEngine(int width, int height);
	virtual ~RenderEngine();

	// Items to draw
	virtual void drawString(std::string text, const glm::vec3 &position, Font * font, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	virtual void drawSprite(Texture * tex, glm::vec4 &position, glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	
	//virtual void drawSprite(Spritesheet * spritesheet, glm::vec4 &position, glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	virtual void addCEGUIElement(CEGUI::Window * element);
	virtual CEGUI::Window * createCEGUIElement(CEGUI::String elementType, const glm::vec4 &destRectPerc, const glm::vec4 &destRectPix, CEGUI::String name, CEGUI::String text = "");
	virtual CEGUI::Window * createButton(std::string buttonName, const glm::vec4 &destRectPerc, const glm::vec4 &destRectPix, std::string buttonText);
	//virtual void drawSlider()

	virtual CEGUI::GUIContext * getGUIContext() { return _GUIContext; }

	virtual void render();

	bool glInit(int width, int height);

	void clear(float r, float g, float b, float a);
	void swapWindowBuffer();

	void draw3DScene();

protected:
	void CEGUIInit();
	virtual void enqueue(Renderable r, GLuint * indices);
	virtual void enqueue(CEGUI::Window ceguiWindow);

	SDL_Window *_window;
	SDL_GLContext _glContext;

	Shader * _shader;
	Transform * _transform;

	GLuint _VAO;
	GLuint _VBO;
	GLuint *_indices;
	GLuint _indicesCount;
	Vertex *_vertices;
	GLuint _verticesCount;

	CEGUI::Window* _CEGUIWindow = nullptr;
	CEGUI::OpenGL3Renderer* _CEGUIrenderer = nullptr;
	CEGUI::GUIContext * _GUIContext = nullptr;
};

