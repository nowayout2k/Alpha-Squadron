//
// Created by Johnnie on 5/27/2024.
//

#ifndef SFML_CORE_HEADER_INPUT_DATA_H_
#define SFML_CORE_HEADER_INPUT_DATA_H_

#include <functional>

namespace SfmlCoreInput
{
	struct InputData
	{
		InputData()
		{
			this->keyId = -1;
			this->delegate = nullptr;
			this->onRelease = false;
		}
		InputData(int keyId, std::function<void()> delegate, bool onRelease)
		{
			this->keyId = keyId;
			this->delegate = delegate;
			this->onRelease = onRelease;
		}

		int keyId;
		std::function<void()> delegate;
		bool onRelease;
	};
}

#endif //SFML_CORE_HEADER_INPUT_DATA_H_
