
#pragma once

#include "nstimer_config.h"
#include "std_timer.h"

#ifdef NSTIMER_SINGLETON
#include <array>
namespace nstimer
{

	struct singleton_info
	{
	public:
		using storage_t = std::array<char,32>;
	protected:

		static storage_t 	g_storage;
		
		friend struct singleton_adapter_std_timer;
		
	};
	//--------------------------------------------------------------------------------------------------------

	template <class T>
	struct singleton_adapter_impl;

	//--------------------------------------------------------------------------------------------------------

#ifdef NSTIMER_DEFAULT_STD
	struct singleton_adapter_std_timer
	{
		using time_capture_t = std_timer::time_capture_t;
		using callback_ptr_t = time_capture_t(*)(const singleton_info::storage_t&);

		static time_capture_t (*_callback)(const singleton_info::storage_t &);
		static inline time_capture_t capture_now_time()
		{
			if(_callback != nullptr)
				return _callback(singleton_info::g_storage);
			return std_timer::capture_now_time();
		}
		static inline singleton_info::storage_t& reset(callback_ptr_t _func)
		{
			_callback = _func;
			return singleton_info::g_storage;
		}
	};
	template <>
	struct singleton_adapter_impl <std_timer>
		: public singleton_adapter_std_timer
	{
	};
#endif

	template <class T>
	struct singleton_timer : public singleton_adapter_impl<T>
	{
	public:
		using base_t = singleton_adapter_impl<T>;
		inline void 		init()
		{
			m_init_time = singleton_adapter_impl<T>::capture_now_time();
		}
		inline int64_t 		getns(const typename base_t::time_capture_t & p) const
		{
			return T::deltans(m_init_time,p);
		}
		
	protected:
		typename base_t::time_capture_t 	m_init_time = singleton_adapter_impl<T>::capture_now_time();
	};

	
}
#endif