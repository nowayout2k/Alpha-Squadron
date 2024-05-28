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
			this->id = -1;
			this->delegate = nullptr;
			this->onRelease = false;

		}
		InputData(int id, std::function<void()>& delegate, bool onRelease)
		{
			this->id = id;
			this->delegate = delegate;
			this->onRelease = onRelease;
		}

		int id;
		std::function<void()> delegate;
		bool onRelease;
	};
}

#endif //SFML_CORE_HEADER_INPUT_DATA_H_
