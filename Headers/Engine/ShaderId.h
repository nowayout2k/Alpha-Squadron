// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file ShaderId.h
 * @brief Declaration of the ShaderId enumeration.
 *
 * This header defines the ShaderId enumeration, which lists identifiers for the various
 * shader passes used in the game. These shaders are utilized in post-processing effects
 * such as brightness adjustment, downsampling, Gaussian blur, additive blending, and a full pass.
 */

#ifndef ALPHA_SQUADRON_HEADERS_SHADERID_H_
#define ALPHA_SQUADRON_HEADERS_SHADERID_H_

namespace Engine
{
	/**
	 * @enum ShaderId
	 * @brief Enumerates the different shader passes.
	 *
	 * The ShaderId enumeration provides identifiers for various shader effects:
	 * - BrightnessPass: Adjusts brightness levels.
	 * - DownSamplePass: Reduces the resolution of the rendered image.
	 * - GaussianBlurPass: Applies a Gaussian blur effect.
	 * - AddPass: Performs additive blending.
	 * - FullPass: Used for a complete vertex shader pass.
	 * - ShaderCount: Represents the total number of shader types.
	 */
	enum class ShaderId
	{
		BrightnessPass,  ///< Shader for brightness adjustment.
		DownSamplePass,  ///< Shader for downsampling the image.
		GaussianBlurPass,///< Shader for applying Gaussian blur.
		AddPass,         ///< Shader for additive blending.
		FullPass,        ///< Vertex shader for a full pass.
		ShaderCount      ///< Total count of shader types.
	};
}
#endif //ALPHA_SQUADRON_HEADERS_SHADERID_H_
