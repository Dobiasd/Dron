#include "BlurPostEffect.h"

#include <iostream>

BlurPostEffect::BlurPostEffect() :
		enabled_(true)
{

	// Convolution filter with the following kernel:
	// | 1/81  1/81  1/81  1/81  1/81  1/81  1/81 |
	// | 1/81  1/81  1/81  1/81  1/81  1/81  1/81 |
	// | 1/81  1/81  1/81  1/81  1/81  1/81  1/81 |
	// | 1/81  1/81  1/81  1/81  1/81  1/81  1/81 |
	// | 1/81  1/81  1/81  1/81  1/81  1/81  1/81 |
	// | 1/81  1/81  1/81  1/81  1/81  1/81  1/81 |
	// | 1/81  1/81  1/81  1/81  1/81  1/81  1/81 |
	// | 1/81  1/81  1/81  1/81  1/81  1/81  1/81 |
	// | 1/81  1/81  1/81  1/81  1/81  1/81  1/81 |
	// The operation in separated into two runs (X and Y).
	// This reduces the number of texel accesses from 81 to 18 per pixel.
	std::string effectXCode;
	effectXCode += "texture buf // The current frame buffer.\n";
	effectXCode += "vec2 step // The floating point step per pixel.\n";
	effectXCode += "effect\n";
	effectXCode += "{\n";
	effectXCode += "    // No blur on border pixels.\n";
	effectXCode +=
			"    if (_in.x < 3*step.x || _in.x > 1.f - 3*step.x || _in.y < 3*step.y || _in.y > 1.f - 3*step.y)\n";
	effectXCode += "    {\n";
	effectXCode += "        // Just copy the source pixel.\n";
	effectXCode += "        _out = buf(_in);\n";
	effectXCode += "    }\n";
	effectXCode += "    else\n";
	effectXCode += "    {\n";
	effectXCode += "        vec4 c = vec4(0.f, 0.f, 0.f, 0.f);\n";
	effectXCode += "        vec4 sum = vec4(0.f, 0.f, 0.f, 0.f);\n";
	effectXCode += "        float pos = _in.x - 3 * step.x;\n";
	effectXCode += "        for (int i = 0; i < 7; ++i)\n";
	effectXCode += "        {\n";
	effectXCode += "            c = buf(vec2(pos, _in.y));\n";
	effectXCode += "            sum = vec4(sum.r + c.r, sum.g + c.g, sum.b + c.b, sum.a + c.a);\n";
	effectXCode += "            pos += step.x;\n";
	effectXCode += "        }\n";
	effectXCode += "        vec4 avg = vec4(sum.r / 7.f, sum.g / 7.f, sum.b / 7.f, sum.a / 7.f);\n";
	effectXCode += "        _out = avg;\n";
	effectXCode += "    }\n";
	effectXCode += "}\n";

	std::string effectYCode;
	effectYCode += "texture buf // The current frame buffer.\n";
	effectYCode += "vec2 step // The floating point step per pixel.\n";
	effectYCode += "effect\n";
	effectYCode += "{\n";
	effectYCode += "    // No blur on border pixels.\n";
	effectYCode +=
			"    if (_in.x < 3*step.x || _in.x > 1.f - 3*step.x || _in.y < 3*step.y || _in.y > 1.f - 3*step.y)\n";
	effectYCode += "    {\n";
	effectYCode += "        // Just copy the source pixel.\n";
	effectYCode += "        _out = buf(_in);\n";
	effectYCode += "    }\n";
	effectYCode += "    else\n";
	effectYCode += "    {\n";
	effectYCode += "        vec4 c = vec4(0.f, 0.f, 0.f, 0.f);\n";
	effectYCode += "        vec4 sum = vec4(0.f, 0.f, 0.f, 0.f);\n";
	effectYCode += "        float pos = _in.y - 3 * step.y;\n";
	effectYCode += "        for (int i = 0; i < 7; ++i)\n";
	effectYCode += "        {\n";
	effectYCode += "            c = buf(vec2(_in.x, pos));\n";
	effectYCode += "            sum = vec4(sum.r + c.r, sum.g + c.g, sum.b + c.b, sum.a + c.a);\n";
	effectYCode += "            pos += step.y;\n";
	effectYCode += "        }\n";
	effectYCode += "        vec4 avg = vec4(sum.r / 7.f, sum.g / 7.f, sum.b / 7.f, sum.a / 7.f);\n";
	effectYCode += "        _out = avg;\n";
	effectYCode += "    }\n";
	effectYCode += "}\n";

	if (!effectX_.LoadFromMemory(effectXCode))
	{
		std::cout << "BlurPostEffect is not possible on this system." << std::endl;
		enabled_ = false;
	}
	effectX_.SetTexture("buf", nullptr);

	if (!effectY_.LoadFromMemory(effectYCode))
	{
		std::cout << "BlurPostEffect is not possible on this system." << std::endl;
		enabled_ = false;
	}
	effectY_.SetTexture("buf", nullptr);
}

void BlurPostEffect::AdjustToWindowSize(const sf::RenderTarget& renderTarget) const
{
	float width(renderTarget.GetView().GetRect().GetWidth());
	float height(renderTarget.GetView().GetRect().GetHeight());
	effectX_.SetParameter("step", 1.f / std::max(1.0f, width), 1.f / std::max(1.0f, height));
	effectY_.SetParameter("step", 1.f / std::max(1.0f, width), 1.f / std::max(1.0f, height));
}

void BlurPostEffect::Apply(sf::RenderTarget& renderTarget) const
{
	renderTarget.Draw(effectX_);
	renderTarget.Draw(effectY_);
}
