#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderEyelightTextured.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"
#include "PrimTriangleSmooth.h"
#include "PrimTriangleSmoothTextured.h"

#include <fstream>

void CScene::ParseOBJ(const std::string &fileName)
{
	std::ifstream file(fileName);

	if (file.is_open())
	{
		std::cout << "Parsing OBJFile : " << fileName << std::endl;

		std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 0.5f, 0));
		std::vector<Vec3f> vVertexes;

		std::vector<Vec2f> vVts;
		std::vector<Vec3f> Vnormal;

		std::string line;

		for (;;)
		{
			if (!getline(file, line))
				break;
			std::stringstream ss(line);
			getline(ss, line, ' ');
			if (line == "v")
			{
				Vec3f v;
				for (int i = 0; i < 3; i++)
					ss >> v.val[i];
				// std::cout << "Vertex: " << v << std::endl;
				vVertexes.emplace_back(v);
			}
			else if (line == "vt")
			{
				Vec2f vt;
				for (int i = 0; i < 2; i++)
					ss >> vt.val[i];

				//for checking
				// std:: cout << "Vt " << vt << std::endl;
				vVts.emplace_back(vt);
			}
			else if (line == "vn")
			{
				Vec3f vn;
				for (int i = 0; i < 2; i++)
					ss >> vn.val[i];

				//std:: cout << "normal: " << vn << std::endl;
				Vnormal.emplace_back(vn);
			}
			else if (line == "f")
			{
				//save u/v/t values in faceVal0, faceVal1, faceVal2 respectively
				Vec3i faceVal0, faceVal1, faceVal2;
				char eatSlash;
				for (int i = 0; i < 3; i++)
				{
					ss >> faceVal0.val[i] >> eatSlash >> faceVal1.val[i] >> eatSlash >> faceVal2.val[i];
				}

				//std::cout << "face: " << faceVal0 << "...1 " << faceVal1 << std::endl;

				//For smooth surface, add this to scene:
				//Note to self: For recalling why we pass parameters like this, read documentation of obj file again
				Add(std::make_shared<CPrimTriangleSmooth>(vVertexes[faceVal0.val[0] - 1], vVertexes[faceVal0.val[1] - 1], vVertexes[faceVal0.val[2] - 1], Vnormal[faceVal2.val[0] - 1], Vnormal[faceVal2.val[1] - 1], Vnormal[faceVal2.val[2] - 1], pShader));
				//Add(std::make_shared<CPrimTriangleSmoothTextured>(vVertexes[faceVal0.val[0] - 1], vVertexes[faceVal0.val[1] - 1], vVertexes[faceVal0.val[2] - 1], Vnormal[faceVal2.val[0] - 1], Vnormal[faceVal2.val[1] - 1], Vnormal[faceVal2.val[2] - 1], vVts[faceVal1.val[0] - 1], vVts[faceVal1.val[1] - 1], vVts[faceVal1.val[2] - 1], pShader));

				//Comment out regular triangles for now
				//Vec3i f;
				//for (int i = 0; i < 3; i++)
				//	ss >> f.val[i];
				//std::cout << "Face: " << f << ".. " << std::endl;
				//Add(std::make_shared<CPrimTriangle>(vVertexes[f.val[0] - 1], vVertexes[f.val[1] - 1], vVertexes[f.val[2] - 1], pShader));
			}
			else
			{
				std::cout << "Unknown key [" << line << "] met in the OBJ file" << std::endl;
			}
		}

		file.close();
		std::cout << "Finished Parsing" << std::endl;
	}
	else
		std::cout << "ERROR: Can't open OBJFile" << std::endl;
}
