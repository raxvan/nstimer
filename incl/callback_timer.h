
#pragma once

#include "nstimer_config.h"
#include "std_timer.h"

#ifdef NSTIMER_CUSTOM
#	include <array>
namespace nstimer
{

	struct callback_timer_storage
	{
	public:
		using storage_t = std::array<char, 32>;

	protected:
		static storage_t g_storage;

		friend struct singleton_adapter_std_timer;
	};
	//--------------------------------------------------------------------------------------------------------

	template <class T>
	struct callback_timer_impl;

	//--------------------------------------------------------------------------------------------------------

#	ifdef NSTIMER_DEFAULT_STD
	struct singleton_adapter_std_timer
	{
		using time_capture_t = std_timer::time_capture_t;
		using callback_ptr_t = time_capture_t (*)(const callback_timer_storage::storage_t&);

		static time_capture_t (*_callback)(const callback_timer_storage::storage_t&);

	public:
		static inline time_capture_t capture_now_time()
		{
			if (_callback != nullptr)
				return _callback(callback_timer_storage::g_storage);
			return std_timer::capture_now_time();
		}
		static inline int64_t delta_ns(const time_capture_t& a, const time_capture_t& b)
		{
			return std_timer::delta_ns(a, b);
		}

	public:
		static inline callback_timer_storage::storage_t& set_global_callback(callback_ptr_t _func)
		{
			_callback = _func;
			return callback_timer_storage::g_storage;
		}
	};
	template <>
	struct callback_timer_impl<std_timer> : public singleton_adapter_std_timer
	{
	};
#	endif

	template <class T>
	struct callback_timer : public callback_timer_impl<T>
	{
	public:
		using base_t = callback_timer_impl<T>;

	public:
		inline void reset()
		{
			m_init_time = callback_timer_impl<T>::capture_now_time();
		}
		inline int64_t cast_ns(const typename base_t::time_capture_t& p) const
		{
			return T::delta_ns(m_init_time, p);
		}

		inline typename base_t::time_capture_t get() const
		{
			return m_init_time;
		}

	protected:
		typename base_t::time_capture_t m_init_time = callback_timer_impl<T>::capture_now_time();
	};
}
#endif