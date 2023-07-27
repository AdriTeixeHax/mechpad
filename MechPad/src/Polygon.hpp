#ifndef _POLYGON__HPP_
#define _POLYGON__HPP_

using uint = unsigned int;

class Polygon
{
protected:
	const uint _numVertices;
	float _vertices[_numVertices * 3];

public:
	// Constructor
	Polygon(const uint numVertices) : _numVertices(numVertices) {}
	// Destructor
	~Polygon(void) { delete _vertices; }

	/* GETTERS */
	// Returns vertices pointer
	float* getVertices(void) { return _vertices; }

	/* SETTERS */
	// Sets the vertices
	void setVertices(float* vertices) { _vertices = vertices; }
};

#endif