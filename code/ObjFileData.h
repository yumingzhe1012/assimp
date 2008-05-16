/*
Free Asset Import Library (ASSIMP)
----------------------------------------------------------------------

Copyright (c) 2006-2008, ASSIMP Development Team
All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the 
following conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/

#ifndef OBJ_FILEDATA_H_INC
#define OBJ_FILEDATA_H_INC

#include <vector>
#include <map>
#include "aiTypes.h"

namespace Assimp
{

namespace ObjFile
{

struct Object;
struct Face;
struct Material;

// ------------------------------------------------------------------------------------------------
//!	\struct	Face
//!	\brief	Datastructure for a simple obj-face, descripes discredisation and materials
struct Face
{
	typedef std::vector<unsigned int> IndexArray;

	//!	Primitive type
	int m_PrimitiveType;
	//!	Vertex indices
	IndexArray *m_pVertices;
	//!	Normal indices
	IndexArray *m_pNormals;
	//!	Texture coordinates indices
	IndexArray *m_pTexturCoords;
	//!	Pointer to assigned material
	Material *m_pMaterial;
	
	//!	\brief	Default constructor
	//!	\param	pVertices	Pointer to assigned vertex indexbuffer
	//!	\param	pNormals	Pointer to assigned normals indexbuffer
	//!	\param	pTexCoords	Pointer to assigned texture indexbuffer
	Face(std::vector<unsigned int> *pVertices, 
			std::vector<unsigned int> *pNormals, 
			std::vector<unsigned int> *pTexCoords) : 
		m_PrimitiveType(2), 
		m_pVertices(pVertices), 
		m_pNormals(pNormals),
		m_pTexturCoords(pTexCoords), 
		m_pMaterial(0L)
	{
		// empty
	}
	
	//!	\brief	Destructor	
	~Face()
	{	
		// empty
	}
};

// ------------------------------------------------------------------------------------------------
//!	\struct	Object
//!	\brief	Stores all objects of an objfile object definition
struct Object
{
	//!	Obejct name
	std::string m_strObjName;
	//!	Assigend face instances
	std::vector<Face*> m_Faces;
	//!	Transformation matrix, stored in OpenGL format
	aiMatrix4x4 m_Transformation;
	//!	All subobjects references by this object
	std::vector<Object*> m_SubObjects;

	//!	\brief	Default constructor
	Object() :
		m_strObjName("")
	{
		// empty
	}
	
	//!	\brief	Destructor	
	~Object()
	{
		for (std::vector<Object*>::iterator it = m_SubObjects.begin();
			it != m_SubObjects.end(); ++it)
		{
			delete *it;
		}
		m_SubObjects.clear();
	}
};

// ------------------------------------------------------------------------------------------------
//!	\struct	Material
//!	\brief	Data structure to store all material specific data
struct Material
{
	aiString MaterialName;
	aiString texture;
	aiColor3D ambient;
	aiColor3D diffuse;
	aiColor3D specular;
	float alpha;
	float shineness;
	int illumination_model;
};

// ------------------------------------------------------------------------------------------------
//!	\struct	Model
//!	\brief	Data structure to store all obj-specific model datas
struct Model
{
	typedef std::map<std::string*, std::vector<unsigned int>* > GroupMap;
	typedef std::map<std::string*, std::vector<unsigned int>* >::iterator GroupMapIt;
	typedef std::map<std::string*, std::vector<unsigned int>* >::const_iterator ConstGroupMapIt;

	//!	Model name
	std::string m_ModelName;
	//!	List ob assigned objects
	std::vector<Object*> m_Objects;
	//!	Pointer to current object
	ObjFile::Object *m_pCurrent;
	//!	Pointer to current material
	ObjFile::Material *m_pCurrentMaterial;
	//!	Pointer to default material
	ObjFile::Material *m_pDefaultMaterial;
	//!	Vector with all generated materials
	std::vector<std::string> m_MaterialLib;
	//!	Vector with all generated group
	std::vector<std::string> m_GroupLib;
	//!	Vector with all generated vertices
	std::vector<aiVector3D*> m_Vertices;
	//!	vector with all generated normals
	std::vector<aiVector3D*> m_Normals;
	//!	Groupmap
	GroupMap m_Groups;
	//!	Group to face id assignment
	std::vector<unsigned int> *m_pGroupFaceIDs;
	//!	Active group
	std::string m_strActiveGroup;
	//!	Vector with generated texture coordinates
	std::vector<aiVector2D*> m_TextureCoord;
	//!	Material map
	std::map<std::string, Material*> m_MaterialMap;

	//!	\brief	Default constructor
	Model() :
		m_ModelName(""),
		m_pCurrent(NULL),
		m_pCurrentMaterial(NULL),
		m_pDefaultMaterial(NULL),
		m_strActiveGroup("")
	{
		// empty
	}
	
	//!	\brief	DEstructor
	~Model()
	{
		for (std::vector<Object*>::iterator it = m_Objects.begin();
		it != m_Objects.end(); ++it)
		{
			delete *it;
		}
		m_Objects.clear();
	}
};

} // Namespace ObjFile
} // Namespace Assimp

#endif
