#include "BatchRenderEngine.h"


BatchRenderEngine::BatchRenderEngine(int width, int height) : RenderEngine(width, height)
{
	init();
}

void BatchRenderEngine::init()
{
	for (int i = 0; i < MAX_TEXTURES; i++)
		_texIDs[i] = i;

	_shader->Bind();
	_shader->setUniform1iv("textures", MAX_TEXTURES, _texIDs);

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);

	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, MAX_VERTS*sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(POSITION_VB);
	glEnableVertexAttribArray(TEXCOORD_VB);
	glEnableVertexAttribArray(NORMAL_VB);
	glEnableVertexAttribArray(COLOR_VB);
	glEnableVertexAttribArray(TID_VB);

	glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);
	glVertexAttribPointer(TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, texCoord)));
	glVertexAttribPointer(NORMAL_VB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, normal)));
	glVertexAttribPointer(COLOR_VB, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, color)));
	glVertexAttribPointer(TID_VB, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, tid)));

	glGenBuffers(1, &_indBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES * sizeof(GLuint), NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	startBatch();
}


BatchRenderEngine::~BatchRenderEngine()
{
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_window);

	glDeleteBuffers(NUM_BUFFERS, &_VBO);
	glDeleteVertexArrays(1, &_VAO);
}

void BatchRenderEngine::startBatch()
{
	int i;
	_shader->Bind();
	_shader->Update(*_transform);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);


	// Error - second time this is mapped, _vertices comes back with NULL pointer
	_vertices = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (_vertices == NULL)
		std::cout << "Error - failure to map _vertices\n";

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indBuffer);
	_indices = (GLuint *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (_indices == NULL)
		std::cout << "Error - failure to map _indices\n";

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Reset indices
	for (int i = 0; i < MAX_INDICES; i++)
	{
		_indices[i] = 0;
	}

	// reset textures
	for (int i = 0; i < MAX_TEXTURES; i++)
	{
		_textures[i] = 0.0f;
	}

	// reset vertices
	for (i = 0; i<MAX_VERTS; i++)
	{
		_vertices[i].pos = glm::vec3(0.0f);
		_vertices[i].texCoord = glm::vec2(0.0f);
		_vertices[i].normal = glm::vec3(0.0f);
		_vertices[i].color = glm::vec4(0.0f);
		_vertices[i].tid = 0.0f;
	}

	_currVerts = 0;
	_currInds = 0;
	_currTextures = 1;

	return;
}

void BatchRenderEngine::enqueue(Renderable r, GLuint * indices)
{
	// Check in regard to drawString function - error?

	unsigned int vertNum;
	unsigned int indNum;
	unsigned int i;
	const GLuint tid = (GLuint)r.getTid();
	float ts = 0.0f;

	vertNum = r.getVertices().size();
	indNum = vertNum / 4 * 6;  // Assumes all input renderables are sprites - fix


	if (vertNum + _currVerts > MAX_VERTS || indNum + _currInds > MAX_INDICES || _currTextures >= MAX_TEXTURES) // we've reached our limit, draw everything and restart
	{
		endBatch();
		flush();
		startBatch();
	}

	// Error possibly here - incorrect textures
	if (tid > 0)
	{
		bool found = false;
		for (unsigned int i = 0; i < _currTextures; i++)
		{
			if (_textures[i] == tid)
			{
				ts = (float)i;
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (_currTextures >= MAX_TEXTURES)
			{
				endBatch();
				flush();
				startBatch();
			}
			ts = _currTextures * 1.0f;
			_textures[_currTextures] = tid * 1.0f;
			_currTextures++;
		}
	}
	else
		ts = -1.0f;



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
		indNum = 6;
	}


	// Store all verts and attributes in arrays
	for (i = 0; i<vertNum; i++)
	{
		_vertices[_currVerts + i].pos = *(verts[i]->GetPos());
		_vertices[_currVerts + i].texCoord = *(verts[i]->GetTexCoord());
		_vertices[_currVerts + i].normal = *(verts[i]->GetNormal());
		_vertices[_currVerts + i].color = *(verts[i]->GetColor());
		_vertices[_currVerts + i].tid = ts;
	}

	// Store all indices in an array
	for (i = 0; i < indNum; i++)
	{
		_indices[_currInds + i] = indices[i] + _currVerts;
	}

	_currVerts += vertNum;
	_currInds += indNum;
}

void BatchRenderEngine::endBatch()
{
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	if (!glUnmapBuffer(GL_ARRAY_BUFFER))
		std::cout << "Error - glUnmapBuffer _vertices failed\n";
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indBuffer);
	if (!glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER))
		std::cout << "Error - glUnmapBuffer _indices failed\n";


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Set up texture
	for (unsigned int i = 0; i < _currTextures; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, (GLuint)_textures[i]);
	}
}


void BatchRenderEngine::flush()
{
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indBuffer);

	glFinish();

	glDrawElements(GL_TRIANGLES, _currInds, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BatchRenderEngine::render()
{
	endBatch();
	flush();

	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);

	CEGUI::System::getSingleton().renderAllGUIContexts();

	glDisable(GL_SCISSOR_TEST); // Prevents flickering caused by CEGUI call

	swapWindowBuffer();

	clear(0.0f, 0.15f, 0.3f, 1.0f);

	startBatch();

}