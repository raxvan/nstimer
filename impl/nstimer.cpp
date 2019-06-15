
#include <nstimer.h>

namespace nstimer
{
	#ifdef NSTIMER_DEFAULT_STD
	singleton_adapter_std_timer::callback_ptr_t singleton_adapter_std_timer::_callback = nullptr;
	#endif

	#ifdef NSTIMER_SINGLETON
		singleton_info::storage_t 	singleton_info::g_storage;
	#endif
}