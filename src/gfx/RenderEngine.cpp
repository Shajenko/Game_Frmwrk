#include "RenderEngine.h"

#include <GL/glew.h>

#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/System.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/ResourceProvider.h>
#include <CEGUI/DefaultResourceProvider.h>
#include <CEGUI/ImageManager.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/falagard/WidgetLookManager.h>
#include <CEGUI/ScriptModule.h>

#include <SDL_keyboard.h>

using namespace ftgl;

const std::string CEGUIPATH = "../CEGUI/";

RenderEngine::RenderEngine(int width, int height)
{
	Uint32 lastTime, delayTime;

	lastTime = SDL_GetTicks();

	glInit(width, height);
	std::cout << "glInit finished - ";

	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

	//Use Vsync 
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		std::cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
	}

	CEGUIInit();

	std::cout << "CEGUI initialized - ";

	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

	_shader = new Shader("./res/basicShader");

	std::cout << "Shaders created - ";

	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

	_shader->Bind();

	_transform = new Transform();

	std::cout << "Transform created - ";

	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";

	_transform->SetOrtho(glm::ortho(0.0f, (float)width, (float)height, 0.0f, 1.0f, -1.0f));
	_shader->Update(*_transform);
}

void RenderEngine::CEGUIInit()
{
	Uint32 lastTime, delayTime;

	using namespace CEGUI;

	ImageManager * imagemanager;

	lastTime = SDL_GetTicks();

	_GUIContext = nullptr;
	if (_CEGUIrenderer == nullptr)
	{
		_CEGUIrenderer = &OpenGL3Renderer::bootstrapSystem();

		// Set up resource locations
		DefaultResourceProvider* rp = static_cast<DefaultResourceProvider*>(
			System::getSingleton().getResourceProvider());

		rp->setResourceGroupDirectory("schemes", "../CEGUI/schemes/");
		rp->setResourceGroupDirectory("imagesets", "../CEGUI/imagesets/");
		rp->setResourceGroupDirectory("fonts", "../CEGUI/fonts/");
		rp->setResourceGroupDirectory("layouts", "../CEGUI/layouts/");
		rp->setResourceGroupDirectory("looknfeels", "../CEGUI/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", "../CEGUI/lua_scripts/");

		// set the default resource groups to be used
		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	}

	std::cout << "CEGUI Renderer created - ";
	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

	_GUIContext = &CEGUI::System::getSingleton().createGUIContext(_CEGUIrenderer->getDefaultRenderTarget());

	std::cout << "CEGUI GUIContext created - ";
	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

	_CEGUIWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");

	std::cout << "CEGUI Window created - ";
	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

	_GUIContext->setRootWindow(_CEGUIWindow);

	imagemanager = &ImageManager::getSingleton();

	imagemanager->loadImageset(
		"TaharezLook.imageset", "imagesets");

	imagemanager->addFromImageFile("TaharezLook.png", "TaharezLook.png");

	std::cout << "CEGUI TaharezLook loaded - ";
	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

	FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

	std::cout << "CEGUI Font loaded - ";
	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();


	// Load the scheme
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

	std::cout << "CEGUI Taharez scheme loaded - ";
	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

	_GUIContext->injectTimePulse(lastTime / 1000.0f); //bug - make sure to use the correct CEGUI dlls - release or debug

	_GUIContext->setDefaultFont("DejaVuSans-10");
	_GUIContext->getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	SDL_ShowCursor(0);

}


RenderEngine::~RenderEngine()
{
	//dtor
	//	_blackTex.freeTexture();
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_window);
}

bool RenderEngine::glInit(int width, int height)
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	if (_window == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	_glContext = SDL_GL_CreateContext(_window);

	//Initialize GLEW
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		return false;
	}

	//Make sure OpenGL 2.1 is supported
	if (!GLEW_VERSION_2_1)
	{
		printf("OpenGL 2.1 not supported!\n");
		return false;
	}

	//Initialize clear color
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	//Enable texturing
	glEnable(GL_TEXTURE_2D);

	//Set blending
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_SCISSOR_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		return false;
	}
	return true;
}

void RenderEngine::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderEngine::swapWindowBuffer()
{
	SDL_GL_SwapWindow(_window);
}


void RenderEngine::enqueue(Renderable r, GLuint * indices)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec4> colors;
	std::vector<float> tid;

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];




	// Currently assumes the renderable is a sprite, four vertices, six indices needed
	unsigned int vertNum;
	unsigned int indNum;

	vertNum = r.getVertices().size();
	indNum = vertNum / 4 * 6;

	std::vector<Vertex *> verts = r.getVertices();

	if (indices == NULL)
	{
		indices = new GLuint[6];
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;

	}


	// Currently drawing renderables to screenbuffer as soon as they are given to us
	for (unsigned int i = 0; i<vertNum; i++)
	{
		positions.push_back(*(verts[i]->GetPos()));
		texCoords.push_back(*(verts[i]->GetTexCoord()));
		normals.push_back(*(verts[i]->GetNormal()));
		colors.push_back(*(verts[i]->GetColor()));
		tid.push_back(r.getTid());
	}

	// Set everything up

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0]) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[COLOR_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors[0]) * colors.size(), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TID_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tid[0]) * tid.size(), &tid[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indNum, &indices[0], GL_STATIC_DRAW);

	// Set up texture
	if (tid[0] > 0) // texture isn't NULL
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tid[0]);
	}

	// Draw call

	glDrawElements(GL_TRIANGLES, indNum, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glDeleteBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glDeleteVertexArrays(1, &vertexArrayObject);

}

void RenderEngine::enqueue(CEGUI::Window ceguiWindow)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_CEGUIWindow);
}

void RenderEngine::drawString(std::string text, const glm::vec3 &position, Font * font, const glm::vec4 &color)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec4> colors;
	std::vector<float> tid;
	GLuint *indices;

	GLuint scale = 2;

//	GLuint vertexArrayObject;
//	GLuint vertexArrayBuffers[NUM_BUFFERS];

	ftgl::texture_font_t * font_tex = font->getFont();

	int strLength = strlen(text.c_str());

	const unsigned int vertNum = strLength * 4;
	const unsigned int indNum = strLength * 6;

	if (text == "")
		return;

	std::vector<Vertex *> verts;
	indices = new GLuint[indNum];


	glm::vec2 * pen;

	pen = new glm::vec2;
	pen->x = position.x;
	pen->y = position.y;

	Texture * tex = new Texture(font->getAtlas()->id);

	for (int i = 0; i < strLength; ++i)
	{
		texture_glyph_t *glyph = ftgl::texture_font_get_glyph(font_tex, text[i]);
		if (glyph != NULL)
		{
			int kerning = 0;
			if (i > 0)
			{
				kerning = ftgl::texture_glyph_get_kerning(glyph, text[i - 1]);
			}
			pen->x += (kerning) * scale;
			int x0 = (int)(pen->x + (glyph->offset_x) * scale);
			int y0 = (int)(pen->y - (glyph->offset_y) * scale);
			int x1 = (int)(x0 + (glyph->width) * scale);
			int y1 = (int)(y0 + (glyph->height) * scale);
			float s0 = glyph->s0;
			float t0 = glyph->t0;
			float s1 = glyph->s1;
			float t1 = glyph->t1;

			indices[(i * 6) + 0] = (i * 4) + 0;
			indices[(i * 6) + 1] = (i * 4) + 1;
			indices[(i * 6) + 2] = (i * 4) + 2;
			indices[(i * 6) + 3] = (i * 4) + 2;
			indices[(i * 6) + 4] = (i * 4) + 3;
			indices[(i * 6) + 5] = (i * 4) + 0;

			verts.push_back(new Vertex(glm::vec3(x0, y0, 0), glm::vec2(s0, t0), glm::vec3(0.0f, 0.0f, 0.0f), color, tex->getTID()));
			verts.push_back(new Vertex(glm::vec3(x0, y1, 0), glm::vec2(s0, t1), glm::vec3(0.0f, 0.0f, 0.0f), color, tex->getTID()));
			verts.push_back(new Vertex(glm::vec3(x1, y1, 0), glm::vec2(s1, t1), glm::vec3(0.0f, 0.0f, 0.0f), color, tex->getTID()));
			verts.push_back(new Vertex(glm::vec3(x1, y0, 0), glm::vec2(s1, t0), glm::vec3(0.0f, 0.0f, 0.0f), color, tex->getTID()));
			pen->x += (glyph->advance_x) * scale;

		}
		else
		{
			// load the glyph into the atlas, try again
		}
	}

	Renderable * r = new Renderable(verts, tex);
	enqueue(*r, indices);
}

void RenderEngine::drawSprite(Texture * tex, glm::vec4 &position, glm::vec4 &color)
{
	Renderable *r;
	std::vector<Vertex *> verts;

	float tid;

	GLuint indices[6];

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;


	if (tex == NULL)
		tid = -1.0f;
	else
		tid = tex->getTID();

	verts.push_back(new Vertex(glm::vec3(position.x, position.y, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), color, tid));
	verts.push_back(new Vertex(glm::vec3(position.x + position.z, position.y, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), color, tid));
	verts.push_back(new Vertex(glm::vec3(position.x + position.z, position.y + position.w, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), color, tid));
	verts.push_back(new Vertex(glm::vec3(position.x, position.y + position.w, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), color, tid));

	r = new Renderable(verts, tex);

	enqueue(*r, indices);
	delete r;
}

void RenderEngine::addCEGUIElement(CEGUI::Window * element)
{
	_CEGUIWindow->addChild(element);
}

CEGUI::Window * RenderEngine::createCEGUIElement(CEGUI::String elementType, const glm::vec4 &destRectPerc, const glm::vec4 &destRectPix, CEGUI::String name, CEGUI::String text)
{
	CEGUI::Window * guiElement = nullptr;
	guiElement = CEGUI::WindowManager::getSingleton().createWindow(elementType, name);  // Create Window
	guiElement->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
	guiElement->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
	guiElement->setText(text);
	addCEGUIElement(guiElement);

	return guiElement;

}

CEGUI::Window * RenderEngine::createButton(std::string buttonName, const glm::vec4 &destRectPerc, const glm::vec4 &destRectPix, std::string buttonText)
{
	CEGUI::Window *BtnWindow = nullptr;

	createCEGUIElement("TaharezLook/Button", destRectPerc, destRectPix, buttonText.c_str(), buttonText.c_str());

	return BtnWindow;
}

void RenderEngine::render()
{
	// user function to draw 3D scene
	//draw3DScene();

	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);

	// make sure that before calling renderAllGUIContexts, that any bound textures
	// and shaders used to render the scene above are disabled using
	// glBindTexture(0) and glUseProgram(0) respectively also set
	// glActiveTexture(GL_TEXTURE_0) 
	// draw GUI
	// NB: When not using >=3.2 core profile, this call should not occur
	// between glBegin/glEnd calls.
	CEGUI::System::getSingleton().renderAllGUIContexts();

	glDisable(GL_SCISSOR_TEST); // Prevents flickering caused by CEGUI call

	// Currently drawing renderables to screenbuffer as soon as they are given to us
	swapWindowBuffer();

	//Clear color buffer
	clear(0.0f, 0.15f, 0.3f, 1.0f);

	_shader->Bind();
	_shader->Update(*_transform);
}


void RenderEngine::draw3DScene()
{

}