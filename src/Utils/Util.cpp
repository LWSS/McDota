#include "Util.h"

#include <chrono> // chrono time stuff

long Util::GetEpochMs()
{
	auto duration = std::chrono::system_clock::now().time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
