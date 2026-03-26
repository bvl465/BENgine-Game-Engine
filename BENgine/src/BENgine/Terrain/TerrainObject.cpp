#include "TerrainObject.h"
#include "GpuVertTypes.h"
#include "TextureTGA.h"
#include "../Asset Managers/Shader Manager/ShaderManager.h"
#include "../Visualizer/Visualizer.h"
#include "../Math Tools/BENgineMathTools.h"
#include "../Game Object/Collidable/Collidable.h"
#include "../Collision/CollisionVolumeBSphere.h"

TerrainObject::~TerrainObject()
{
	delete pGObj_TerrainObject;
	delete pGObj_TerrainObjectWireframe;
	delete[] pCells;
	delete[] pNormals;
	delete pModTerrainObject;
}

//TerrainObject::TerrainObject() : len(0.f), halfLen(0.f), pGObj_TerrainObject(nullptr), pGObj_TerrainObjectWireframe(nullptr), pNormals(nullptr), pCells(nullptr), rowLength(0), nCells(0), cellSize(0.f), divCellSize(0.f), divSquaredCellSize(0.f)
//{
//	
//}

TerrainObject::TerrainObject(const char* heightmapFile, float length, float maxheight, float ytrans, Texture* tex, int RepeatU, int RepeatV) : len(length), halfLen(length * 0.5f)
{
	int imgWidth, imgHeight, icomp;
	unsigned int dtype;
	//std::string texturePath = std::string("../Assets/Height Maps/") + heightmapFile;
	GLbyte* hgtmap = gltReadTGABits(heightmapFile, &imgWidth, &imgHeight, &icomp, &dtype);
	assert(imgWidth == imgHeight && imgWidth != 0);

	size_t side = imgHeight; // the image should be square
	uint8_t h_val; // the 'R' byte of the pixel
	
	const int nverts = side * side;
	VertexStride_VUN* pVerts = new VertexStride_VUN[nverts];
	pNormals = new Vect[nverts];

	rowLength = side - 1;
	nCells = (rowLength) * (rowLength);
	pCells = new Cell[nCells];
	
	const int ntri = nCells * 2;
	TriangleIndex* pTris = new TriangleIndex[ntri];

	const float distBetweenVerts = len / side; //distance between actual points
	cellSize = distBetweenVerts; //the size of each cell in the TerrainObject
	divCellSize = 1.f / cellSize; //to avoid division by cellSize later in calculations
	divSquaredCellSize = divCellSize * divCellSize; //to avoid division by cellSize squared later in calculations
	//Distance between U an V repetitions derivation:
	//const float distPerURep = side / (float)(RepeatU) - 1.f / RepeatU;
	//const float distPerURep = ((side - 1.f) / (float)(RepeatU));
	//const float distPerURep = 1 / (((side - 1.f) / (float)(RepeatU))); //to avoid division by distPerURep later
	//const float distPerURep = (float)(RepeatU) / (side - 1.f); //to avoid division by one
	//extract 1.f / (side - 1.f) to avoid it in calculation of distPerURep and distPerVRep and later coord calculations
	const float step = 1.f / (side - 1.f);

	const float distPerURep = (float)(RepeatU)*step;

	const float distPerVRep = (float)(RepeatV)*step;

	const float div255MaxHeight = maxheight / 255.f;

	float u = 0.f;
	float v = 0.f;
	float x = halfLen;
	float z = -halfLen;

	//vind 0 is bottom left corner
	//vind numVerts is top right corner
	int vind = 0;

	//To avoid casting side to int repeatedly
	const int sideInt = (int)side;
	
	// ---------------------------------- Populate pVerts ---------------------------------- 
	for (int i = 0; i < sideInt; i++)
	{
		u = 0.f;
		x = halfLen;
		for (int j = 0; j < sideInt; j++)
		{
			h_val = hgtmap[TexelIndex(sideInt, i, j)];
			pVerts[vind].set(x, (h_val * div255MaxHeight) + ytrans, z, u, v, 0.f, 1.f, 0.f);
			x -= distBetweenVerts;
			u += distPerURep;
			vind += 1;
		}
		z += distBetweenVerts;
		v += distPerVRep;
	}

	//const float div6 = 1.f / 6.f;
	//const float div3 = 1.f / 3.f;
	// ------------------------- Populate pNormals -------------------------
	Vect v1, v2, v3, v4, v5, v6;
	Vect n1, n2, n3, n4, n5, n6;
	Vect pos;
	for (int i = 1; i < sideInt - 1; i++)
	{
		//avoids calculating repeated products
		const int iSide = i * sideInt;
		const int iMin1Side = (i - 1) * sideInt; 
		const int iAdd1Side = (i + 1) * sideInt;
		for (int j = 1; j < sideInt - 1; j++)
		{

			int ind = iSide + j;
			pos = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z);

			ind = iSide + j - 1;
			v1 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
			ind = iMin1Side + j;
			v2 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
			n1 = v1.cross(v2);

			ind = iMin1Side + j + 1;
			v3 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
			n2 = v2.cross(v3);

			ind = iSide + j + 1;
			v4 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
			n3 = v3.cross(v4);

			ind = iAdd1Side + j;
			v5 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
			n4 = v4.cross(v5);

			ind = iAdd1Side + j - 1;
			v6 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
			n5 = v5.cross(v6);

			n6 = v6.cross(v1);
			
			//Vect norm = ((div6) * (n1 + n2 + n3 + n4 + n5 + n6)).norm();
			const Vect norm = (n1 + n2 + n3 + n4 + n5 + n6).norm();

			
			//DebugMsg::out("norm %f, %f, %f\n", pNormals[i + j].X(), pNormals[i + j].Y(), pNormals[i + j].Z());
			ind = iSide + j;
			
			//pNormals[ind].X() = norm.X();
			//pNormals[ind].Y() = norm.Y();
			//pNormals[ind].Z() = norm.Z();
			//pNormals[ind] = norm; //store the normal in the pNormals array

			pVerts[ind].nx = norm.X();
			pVerts[ind].ny = norm.Y();
			pVerts[ind].nz = norm.Z();
			//store the normal in the pNormals array
			pNormals[ind] = Vect(pVerts[ind].nx, pVerts[ind].ny, pVerts[ind].nz); 
		}
	}

	//Bottom row normals without bottom corners
	for (int i = 1; i < sideInt; i++)
	{
		int ind = i;
		pos = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z);
		ind = i + 1;
		v4 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	
		ind = i + sideInt;
		v5 = Vect(pVerts[ind + sideInt].x, pVerts[ind + sideInt].y, pVerts[ind + sideInt].z) - pos;
		n4 = v4.cross(v5);
	
		ind = i + sideInt - 1;
		v6 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		n5 = v5.cross(v6);
	
		ind = i - 1;
		v1 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		n6 = v6.cross(v1);
	
		//Vect norm =((div3) * (n4 + n5 + n6)).norm();
		const Vect norm =(n4 + n5 + n6).norm();
	
		ind = i;
		pVerts[ind].nx = norm.X();
		pVerts[ind].ny = norm.Y();
		pVerts[ind].nz = norm.Z();
		pNormals[ind] = Vect(pVerts[ind].nx, pVerts[ind].ny, pVerts[ind].nz);
		//DebugMsg::out("norm %f, %f, %f\n", pNormals[i].X(), pNormals[i].Y(), pNormals[i].Z());
	}
	
	
	
	//Top row normals without top corners
	for (int i = nverts - sideInt + 1; i < nverts - 1; i++)
	{
		int ind = i;
		pos = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z);
	
		ind = i - 1;
		v1 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	
		ind = i - sideInt;
		v2 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		n1 = v1.cross(v2);
	
		ind = i - sideInt + 1;
		v3 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		n2 = v2.cross(v3);
	
		ind = i + 1;
		v4 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		n3 = v3.cross(v4);
	
		//Vect norm = ((div3) * (n1 + n2 + n3)).norm();
		const Vect norm = (n1 + n2 + n3).norm();
	
		ind = i;
		pVerts[ind].nx = norm.X();
		pVerts[ind].ny = norm.Y();
		pVerts[ind].nz = norm.Z();
		pNormals[ind] = Vect(pVerts[ind].nx, pVerts[ind].ny, pVerts[ind].nz);
		//DebugMsg::out("norm at i = %d : %f, %f, %f\n", i, pNormals[i].X(), pNormals[i].Y(), pNormals[i].Z());
	}
	
	//Left column normals without left corners
	for (int i = sideInt; i < nverts - sideInt; i += sideInt) {
		int ind = i;
		pos = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z);
		ind = i - sideInt;
		v2 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	
		ind = i - sideInt + 1;
		v3 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		n2 = v2.cross(v3);
	
		ind = i + 1;
		v4 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		n3 = v3.cross(v4);
	
		ind = i + sideInt;
		v5 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		n4 = v4.cross(v5);
	
		//Vect norm = ((div3) * (n2 + n3 + n4)).norm();
		const Vect norm = (n2 + n3 + n4).norm();
	
		ind = i;
		pVerts[ind].nx = norm.X();
		pVerts[ind].ny = norm.Y();
		pVerts[ind].nz = norm.Z();
		pNormals[ind] = Vect(pVerts[ind].nx, pVerts[ind].ny, pVerts[ind].nz);
		//DebugMsg::out("norm at i = %d: %f, %f, %f\n", i, pNormals[i].X(), pNormals[i].Y(), pNormals[i].Z());
	}
	
	//Right column normals without right corners
	for (int i = sideInt + sideInt - 1; i < nverts - 1; i += sideInt) {
		int ind = i;
		pos = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z);
	
		ind = i - 1;
		v1 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	
		ind = i - sideInt;
		v2 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		n1 = v1.cross(v2);
	
		ind = i + sideInt;
		v5 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		
		ind = i + sideInt - 1;
		v6 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
		n5 = v5.cross(v6);
		n6 = v6.cross(v1);
	
		//Vect norm = ((div3) * (n1 + n5 + n6)).norm();
		const Vect norm = (n1 + n5 + n6).norm();
	
		ind = i;
		pVerts[ind].nx = norm.X();
		pVerts[ind].ny = norm.Y();
		pVerts[ind].nz = norm.Z();
		pNormals[ind] = Vect(pVerts[ind].nx, pVerts[ind].ny, pVerts[ind].nz);
		//DebugMsg::out("right column norm ind = %d :%f, %f, %f\n", ind, pNormals[i].X(), pNormals[i].Y(), pNormals[i].Z());
	}
	
	//bottom left corner normal
	
	int ind = 0;
	pos = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z);
	ind = 1;
	v4 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	ind = sideInt;
	v5 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	n4 = v4.cross(v5);
	Vect normal = n4.getNorm();
	ind = 0;
	pVerts[ind].nx = normal.X();
	pVerts[ind].ny = normal.Y();
	pVerts[ind].nz = normal.Z();
	pNormals[ind] = Vect(pVerts[ind].nx, pVerts[ind].ny, pVerts[ind].nz);
	//DebugMsg::out("norm %f, %f, %f\n", pNormals[ind].X(), pNormals[ind].Y(), pNormals[ind].Z());
	
	//bottom right corner normal
	ind = sideInt - 1;
	pos = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z);
	ind = sideInt - 2;
	v1 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	ind = sideInt - 1 + sideInt;
	v5 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	ind = sideInt - 2 + sideInt;
	v6 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	n5 = v5.cross(v6);
	n6 = v6.cross(v1);
	//Vect normal = (.5f * (n5 + n6)).norm();
	normal = (n5 + n6).norm();
	ind = sideInt - 1;
	pVerts[ind].nx = normal.X();
	pVerts[ind].ny = normal.Y();
	pVerts[ind].nz = normal.Z();
	pNormals[ind] = Vect(pVerts[ind].nx, pVerts[ind].ny, pVerts[ind].nz);
	//DebugMsg::out("norm %f, %f, %f\n", pNormals[ind].X(), pNormals[ind].Y(), pNormals[ind].Z());
	
	
	//top left corner
	ind = nverts - sideInt;
	pos = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z);
	
	ind = nverts - sideInt - sideInt;
	v2 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	ind = nverts - sideInt - sideInt - 1;
	v3 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	n2 = v2.cross(v3);
	ind = nverts - sideInt + 1;
	v4 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	n3 = v3.cross(v4);
	ind = nverts - sideInt;
	normal = (n2 + n3).norm();
	pVerts[ind].nx = normal.X();
	pVerts[ind].ny = normal.Y();
	pVerts[ind].nz = normal.Z();
	pNormals[ind] = Vect(pVerts[ind].nx, pVerts[ind].ny, pVerts[ind].nz);
	//DebugMsg::out("top left corner norm %f, %f, %f\n", pNormals[ind].X(), pNormals[ind].Y(), pNormals[ind].Z());
	//DebugMsg::out("top left corner + 1 norm %f, %f, %f\n", pNormals[ind + 1].X(), pNormals[ind + 1].Y(), pNormals[ind + 1].Z());
	//DebugMsg::out("top left corner - sideint norm %f, %f, %f\n", pNormals[ind - sideInt].X(), pNormals[ind + sideInt].Y(), pNormals[ind + sideInt].Z());
	
	//top right corner
	ind = nverts - 1;
	pos = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z);
	ind = nverts - 2;
	v1 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	ind = nverts - 1 - sideInt;
	v2 = Vect(pVerts[ind].x, pVerts[ind].y, pVerts[ind].z) - pos;
	n1 = v1.cross(v2);
	normal = n1.getNorm();
	ind = nverts - 1;
	pVerts[ind].nx = normal.X();
	pVerts[ind].ny = normal.Y();
	pVerts[ind].nz = normal.Z();
	pNormals[ind] = Vect(pVerts[ind].nx, pVerts[ind].ny, pVerts[ind].nz);
	//DebugMsg::out("top right norm %f, %f, %f\n", pNormals[ind].X(), pNormals[ind].Y(), pNormals[ind].Z());
	//DebugMsg::out("1 below top right norm %f, %f, %f\n", pNormals[ind - sideInt].X(), pNormals[ind - sideInt].Y(), pNormals[ind - sideInt].Z());


	//for (int i = 0; i < nverts - 1; i++) {
	//	//pNormals[i] = Vect(pVerts[i].nx, pVerts[i].ny, pVerts[i].nz); //normalize the normals
	//	//DebugMsg::out("norm %f, %f, %f\n", pNormals[i].X(), pNormals[i].Y(), pNormals[i].Z());
	//}


	// -------------------------- Populate pCells and pTris --------------------------
	//WARNING UNCOMMENTING THE DEBUG MESSAGES HERE GREATLY SLOWS THINGS DOWN ON LOAD
	vind = 0;
	int tind = 0;
	int cellNum = 0;
	for (int i = 0; i < sideInt - 1; i++)
	{
		for (int j = 0; j < sideInt - 1; j++)
		{
			
			//============ Debug Messages ============
			//DebugMsg::out("\nvind %d\n", vind);
			//DebugMsg::out("cellNum %d\n", cellNum);
			//DebugMsg::out("x %f\n", pVerts[vind].x);
			//DebugMsg::out("z %f\n", pVerts[vind].y);
			//========================================

			float min = pVerts[vind].y;
			float max = pVerts[vind].y;
			const int vind1 = vind + 1;
			if (pVerts[vind1].y < min)
			{
				min = pVerts[vind1].y;
			}
			else if (pVerts[vind1].y > max)
			{
				max = pVerts[vind1].y;
			}
			const int vindSide = vind + sideInt;
			if (pVerts[vindSide].y < min)
			{
				min = pVerts[vindSide].y;
			}
			else if (pVerts[vindSide].y > max)
			{
				max = pVerts[vindSide].y;
			}
			const int vindSide1 = vind + sideInt + 1;
			if (pVerts[vindSide1].y < min)
			{
				min = pVerts[vindSide1].y;
			}
			else if (pVerts[vindSide1].y > max)
			{
				max = pVerts[vindSide1].y;
			}
			pCells[cellNum].set(min, max);

			cellNum += 1;

			//======================= Debug Messages =======================
			//DebugMsg::out("Min %f", min);
			//DebugMsg::out(" Max %f\n", max);
			//DebugMsg::out(" Cells Complete: %d / %d\n", cellNum, nCells);
			//==============================================================
			

			// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
			// =====================!!!IMPORTANT!!!====================
			// The winding is as follows:
			// 
			//		      +Z
			//             ^
			//             |
			//      +X <---+---> -X
			//		       |
			//             v
			//            -Z
			//
			// C vindside.-----.vindSide1 B
			//           |`._  |
			//           |   `.|
			//     B vind`-----'vind1 A
			//    
			// C Top Left, B Top Right & Bottom Left, A Bottom Right
			// 
			//                       v0 v1 v2
			// First triangle lower:  C, B, A
			// Second triangle upper: A, B, C
			// ========================================================
			// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/


			//============================================== Debug Messages ==============================================
			//DebugMsg::out("vind: %f , %f, %f\n", pVerts[vind].x, (pVerts[vind]).y, (pVerts[vind].z));
			//DebugMsg::out("vind1: %f , %f, %f\n", pVerts[vind1].x, (pVerts[vind1]).y, (pVerts[vind1]).z);
			//DebugMsg::out("vindSide: %f , %f, %f\n", pVerts[vindSide].x, (pVerts[vindSide]).y, (pVerts[vindSide]).z);
			//DebugMsg::out("vindSide1: %f , %f, %f\n", pVerts[vindSide1].x, (pVerts[vindSide1]).y, (pVerts[vindSide1]).z);
			//============================================================================================================
			pTris[tind].set(vindSide, vind, vind1);
			tind += 1;

			pTris[tind].set(vind1, vindSide1, vindSide);
			tind += 1;
			vind += 1;
		}
		vind += 1;
	}


	pModTerrainObject = new Model(pVerts, nverts, pTris, ntri);

	Vect LightColor(1.0f, 1.0f, 1.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pGObj_TerrainObject = new GraphicsObject_TextureLight(pModTerrainObject, ShaderManager::GetShaderObject("pShaderObject_textureLight"), tex, LightColor, LightPos);
	Vect color = Vect(0.0f, 1.0f, 0.0f, 1.0); //green
	pGObj_TerrainObjectWireframe = new GraphicsObject_WireframeConstantColor(pModTerrainObject, ShaderManager::GetShaderObject("pShaderObject_constantColor"), color);
	
	//Cleaning up memory

	//The model already stores a list of verts so we can delete pVerts.
	delete[] pVerts;

	//pTris is no longer needed since we can just keep track of the winding
	delete[] pTris;

	//This registers as an external lib leak but it is not
	delete[] hgtmap;

	//for (int i = 0; i < nverts - 1; i++) {
	//	DebugMsg::out("norm %f, %f, %f\n", pNormals[i].X(), pNormals[i].Y(), pNormals[i].Z());
	//}
}

float TerrainObject::GetVertexYFromModel(int ind) const
{
	assert(ind < (pModTerrainObject->getVectNum()) - 1);
	return ((pModTerrainObject->getVectList())[ind]).Y();
}

int TerrainObject::GetVertexIndex(int i, int j) const
{
	return i * j;
}

CellCoordinates TerrainObject::GetCellCoordinates(float x, float z) const
{
	//WARNING UNCOMMENTING THE DEBUG MESSAGES HERE GREATLY SLOWS THINGS DOWN DURING RUN
	CellCoordinates coords;
	const float lenMinCellSizeMinCellSize = len - cellSize - cellSize;

	// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
	// =============================================!!!IMPORTANT!!!=============================================
	// starting index is +x -z and then the last index is -x +z so thats why -x is used in the line below
	coords.X = (int)((BENgineMathTools::FloatClamp(halfLen - x, 0.f, lenMinCellSizeMinCellSize)) * divCellSize);
	coords.Z = (int)((BENgineMathTools::FloatClamp( z + halfLen, 0.f, lenMinCellSizeMinCellSize)) * divCellSize);
	// =========================================================================================================
	// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
	
	//========== Debug Messages ==========
	//DebugMsg::out("x %f\n", x);
	//DebugMsg::out("z %f\n", z);
	//DebugMsg::out("xInd %d\n", coords.X);
	//DebugMsg::out("zInd %d\n", coords.Z);
	//====================================

	return coords;
}

int TerrainObject::GetCellIndex(int x, int z) const
{
	return x + (z * (rowLength));
}

int TerrainObject::GetCellIndexFromCoord(float xOrZ) const
{
	
	int i = (int)((xOrZ + len * 0.5f) * divCellSize);
	i = BENgineMathTools::IntClamp(i, 0, rowLength - 1);
	return i;
}

CellMinMaxVects TerrainObject::GetCellMinMaxVects(CellCoordinates coords) const
{
	//WARNING UNCOMMENTING THE DEBUG MESSAGES HERE GREATLY SLOWS THINGS DOWN DURING RUN

	
	const int cellIndex = BENgineMathTools::IntClamp(GetCellIndex(coords.X, coords.Z), 0, nCells - 1);
	
	assert(0 <= cellIndex && cellIndex < nCells);
	CellMinMaxVects minMax;
	minMax.Max = Vect(halfLen - ((float)(coords.X) * cellSize), pCells[cellIndex].Max, -halfLen + ((float)(coords.Z + 1) * cellSize));
	minMax.Min = Vect(minMax.Max.X() - cellSize, pCells[cellIndex].Min, minMax.Max.Z() - cellSize);
	//==================================== Debug Messages ====================================
	//DebugMsg::out("Min Vect: %f , %f, %f\n", minMax.Min.X(), minMax.Min.Y(), minMax.Min.Z());
	//DebugMsg::out("Max Vect: %f , %f, %f\n", minMax.Max.X(), minMax.Max.Y(), minMax.Max.Z
	//========================================================================================

	return minMax;
}


int TerrainObject::TexelIndex(int side, int i, int j) const {
	return pixel_width * (i * side + j);
}

Model* TerrainObject::GetModel()
{
	return pModTerrainObject;
}

float TerrainObject::GetTerrainObjectHeight(Vect pos) const
{
	//============================================================================================
	//IF THINGS ARE RUNNING SLOW CHECK IF DEBUG MESSAGES ARE UNCOMMENTED IN THE FOLLOWING METHODS:
	//GetCellCoordinates
	//============================================================================================
	CellCoordinates cellCoords = GetCellCoordinates(pos.X(), pos.Z());
	int cellIndex = GetCellIndex(cellCoords.X, cellCoords.Z);
	const int lowerTriIndexIndex = cellIndex * 2; //each cell has two triangles
	TriangleIndex tind = pModTerrainObject->getTriangleList()[lowerTriIndexIndex];
	Vect A = pModTerrainObject->getVectList()[tind.v2];
	Vect C = pModTerrainObject->getVectList()[tind.v0];
	Vect color = Vect(1.0f, 0.0f, 0.0f, 1.0); //green

	// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
	// ============================!!!IMPORTANT!!!=============================
	// The reason A.Y() is used instead of pos.Y() is to make v.Y() equal to 0
	float clampedX = BENgineMathTools::FloatClamp(pos.X(), -halfLen, halfLen);
	float clampedZ = BENgineMathTools::FloatClamp(pos.Z(), -halfLen, halfLen);
	const Vect v = Vect(clampedX, A.Y(), clampedZ) - A; //vector from A to pos
	//const Vect v = Vect(pos.X(), A.Y(), pos.Z()) - A; //vector from A to pos
	// ========================================================================
	// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

	Vect B;
	if (v.X() > v.Z()) {
		//Lower Triangle
		B = pModTerrainObject->getVectList()[tind.v1];
	}
	else {
		//Upper Triangle
		color = Vect(10.0f, 0.0f, 8.0f, 1.0);
		tind = pModTerrainObject->getTriangleList()[lowerTriIndexIndex + 1];
		B = pModTerrainObject->getVectList()[tind.v1];
	}

	float beta = (v.dot(B - A)) * divSquaredCellSize;
	float gamma = (v.dot(C - B)) * divSquaredCellSize;

	float height = A.Y() + beta * (B.Y() - A.Y()) + gamma * (C.Y() - B.Y());
	//DebugMsg::out("height %f\n", height);
	Visualizer::ShowAABBUsingMinMax(Vect(pos.X() - .25f, height - .25f, pos.Z() - .25f), Vect(pos.X() + .25f, height + .25f, pos.Z() + .25f), color);
	return height;
}

float TerrainObject::GetHeightAboveTerrain(Vect pos) const
{
	return pos.Y() - GetTerrainObjectHeight(pos);
}

Vect TerrainObject::GetTerrainObjectNormal(Vect pos) const
{
	//============================================================================================
	//IF THINGS ARE RUNNING SLOW CHECK IF DEBUG MESSAGES ARE UNCOMMENTED IN THE FOLLOWING METHODS:
	//GetCellCoordinates
	//============================================================================================

	const CellCoordinates cellCoords = GetCellCoordinates(pos.X(), pos.Z());
	const int cellIndex = GetCellIndex(cellCoords.X, cellCoords.Z);
	int triIndexIndex = cellIndex * 2; //each cell has two triangles
	TriangleIndex tind = pModTerrainObject->getTriangleList()[triIndexIndex];
	const Vect A = pModTerrainObject->getVectList()[tind.v2];
	const Vect ANorm = pNormals[tind.v2];
	const Vect C = pModTerrainObject->getVectList()[tind.v0];
	const Vect CNorm = pNormals[tind.v0];


	Vect color = Vect(0.0f, 1.0f, 0.0f, 1.0); //green

	// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
	// ============================!!!IMPORTANT!!!=============================
	// The reason A.Y() is used instead of pos.Y() is to make v.Y() equal to 0
	float clampedX = BENgineMathTools::FloatClamp(pos.X(), -halfLen, halfLen);
	float clampedZ = BENgineMathTools::FloatClamp(pos.Z(), -halfLen, halfLen);
	const Vect v = Vect(clampedX, A.Y(), clampedZ) - A; //vector from A to pos
	//const Vect v = Vect(pos.X(), A.Y(), pos.Z()) - A; //vector from A to pos
	// ========================================================================
	// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

	Vect B;
	Vect BNorm;
	if (v.X() > v.Z()) {
		//Lower Triangle
		B = pModTerrainObject->getVectList()[tind.v1];
		
		BNorm = pNormals[tind.v1];
	}
	else {
		//Upper Triangle
		color = Vect(1.0f, 0.0f, 1.0f, 1.0);
		triIndexIndex += 1;
		tind = pModTerrainObject->getTriangleList()[triIndexIndex];
		B = pModTerrainObject->getVectList()[tind.v1];
		BNorm = pNormals[tind.v1];
	}

	const float beta = (v.dot(B - A)) * divSquaredCellSize;
	const float gamma = (v.dot(C - B)) * divSquaredCellSize;

	const float height = A.Y() + beta * (B.Y() - A.Y()) + gamma * (C.Y() - B.Y());
	//Visualizer::ShowAABBUsingMinMax(Vect(pos.X() - .25f, height - .25f, pos.Z() - .25f), Vect(pos.X() + .25f, height + .25f, pos.Z() + .25f), color);

	const Vect normal = (ANorm + beta * (BNorm - ANorm) + gamma * (CNorm - BNorm)).norm();
	//normal.norm(); //normalize the normal vector
	//DebugMsg::out("normal Vect: %f , %f, %f\n", normal.X(), normal.Y(), normal.Z());
	const Vect normalEndPoint = Vect(pos.X(), height , pos.Z()) + normal; //to visualize the normal
	Visualizer::ShowMarker(normalEndPoint, color);
	Visualizer::ShowAABBUsingMinMax(Vect(normalEndPoint.X() - .15f, normalEndPoint.Y() - .15f, normalEndPoint.Z() - .15f), Vect(normalEndPoint.X() + .15f, normalEndPoint.Y() + .15f, normalEndPoint.Z() + .15f), color);

	return normal;
}

void TerrainObject::ShowCell(Vect pos) const
{
	//============================================================================================
	//IF THINGS ARE RUNNING SLOW CHECK IF DEBUG MESSAGES ARE UNCOMMENTED IN THE FOLLOWING METHODS:
	//GetCellCoordinates
	//GetCellMinMaxVects
	//============================================================================================
	
	//DebugMsg::out("\nShowCell called\n");
	const CellCoordinates cellIndexCoords = GetCellCoordinates(pos.X(), pos.Z());
	const CellMinMaxVects minMax = GetCellMinMaxVects(cellIndexCoords);

	Visualizer::ShowAABBUsingMinMax(minMax.Min, minMax.Max, Vect(10.f, 10.f, 0.f));
}

void TerrainObject::Intersect(Collidable* collidable)
{
	//============================================================================================
	//IF THINGS ARE RUNNING SLOW CHECK IF DEBUG MESSAGES ARE UNCOMMENTED IN THE FOLLOWING METHODS:
	//GetCellCoordinates
	//GetCellMinMaxVects
	//============================================================================================
	
	//DebugMsg::out("\nIntersect called\n");
	const float radius = ((collidable->GetBSphere()).GetRadius());
	const Vect center = ((collidable->GetBSphere()).GetCenter());
	const Vect min = center - Vect(radius, radius, radius);
	const Vect max = center + Vect(radius, radius, radius);
	const CellCoordinates minCoords = GetCellCoordinates(min.X(), min.Z());
	const CellCoordinates maxCoords = GetCellCoordinates(max.X(), max.Z());
	const int xLen = minCoords.X - maxCoords.X + 1;
	const int zLen = maxCoords.Z - minCoords.Z + 1;
	CellCoordinates coords;
	for (int i = 0; i < zLen; i++)
	{
		for (int j = 0; j < xLen; j++)
		{
			coords.set(maxCoords.X + j, minCoords.Z + i);
			const CellMinMaxVects minMax = GetCellMinMaxVects(coords);
			Visualizer::ShowAABBUsingMinMax(minMax.Min, minMax.Max, Vect(10.f, 10.f, 0.f));
		}
	}
}

void TerrainObject::Render(Camera* camera)
{
	pGObj_TerrainObject->Render(camera);

	// Uncomment the line below to render the wireframe
	//pGObj_TerrainObjectWireframe->Render(camera);
}

void TerrainObject::ShowPointBelow(Vect pos) const
{
	CellCoordinates cellCoords = GetCellCoordinates(pos.X(), pos.Z());
	int cellIndex = GetCellIndex(cellCoords.X, cellCoords.Z);
	const int lowerTriIndexIndex = cellIndex * 2; //each cell has two triangles
	TriangleIndex tind = pModTerrainObject->getTriangleList()[lowerTriIndexIndex];
	Vect A = pModTerrainObject->getVectList()[tind.v2];
	Vect C = pModTerrainObject->getVectList()[tind.v0];
	Vect color = Vect(1.0f, 0.0f, 0.0f, 1.0); //green

	// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
	// ============================!!!IMPORTANT!!!=============================
	// The reason A.Y() is used instead of pos.Y() is to make v.Y() equal to 0
	float clampedX = BENgineMathTools::FloatClamp(pos.X(), -halfLen, halfLen);
	float clampedZ = BENgineMathTools::FloatClamp(pos.Z(), -halfLen, halfLen);
	const Vect v = Vect(clampedX, A.Y(), clampedZ) - A; //vector from A to pos
	//const Vect v = Vect(pos.X(), A.Y(), pos.Z()) - A; //vector from A to pos
	// ========================================================================
	// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

	Vect B;
	if (v.X() > v.Z()) {
		//Lower Triangle
		B = pModTerrainObject->getVectList()[tind.v1];
	}
	else {
		//Upper Triangle
		color = Vect(10.0f, 0.0f, 8.0f, 1.0);
		tind = pModTerrainObject->getTriangleList()[lowerTriIndexIndex + 1];
		B = pModTerrainObject->getVectList()[tind.v1];
	}

	float beta = (v.dot(B - A)) * divSquaredCellSize;
	float gamma = (v.dot(C - B)) * divSquaredCellSize;

	float height = A.Y() + beta * (B.Y() - A.Y()) + gamma * (C.Y() - B.Y());
	//DebugMsg::out("height %f\n", height);
	Visualizer::ShowMarker(Vect(pos.X(), height, pos.Z()), color);
}
