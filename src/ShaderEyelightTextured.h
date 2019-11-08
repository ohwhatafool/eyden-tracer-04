#pragma once

#include "ShaderEyelight.h"
#include "texture.h"

/**
* @brief Eye-light shader with support of textures class
*/
class CShaderEyelightTextured : public CShaderEyelight
{
public:
	/**
	 * @brief Constructor
	 * @details This is a light-source-free shader
	 * @param color The color of the object
	 * @param fileName The path to the file with texture
	 */
	CShaderEyelightTextured(Vec3f color = RGB(0.5f, 0.5f, 0.5f), const std::string &fileName = {})
		: CShaderEyelight(color), texture(fileName)
	{
	}
	virtual ~CShaderEyelightTextured(void) = default;

	virtual Vec3f Shade(const Ray &ray) const override
	{
		// --- PUT YOUR CODE HERE ---
		//return Vec3f(0, 0, 0);

		//getting the actual shading vector
		Vec2f uv = ray.hit->getUV(ray);
		Vec3f textureShade = texture.GetTexel(uv[0], uv[1]);
		Vec3f eyeShade = CShaderEyelight::Shade(ray);
		return textureShade.mul(eyeShade);
	}

private:
	Texture texture;
};
