#ifndef MP_CONTROLS_H
#define MP_CONTROLS_H

#include <atomic>

struct MpControls {
	std::atomic_bool pause = false;
	std::atomic_bool next = false;
	std::atomic_bool prev = false;
	std::atomic_bool stop = false;
	std::atomic_bool vol_up = false;
	std::atomic_bool vol_down = false;
	std::atomic_bool exit = false;
};

#endif // !MP_CONTROLS_H
