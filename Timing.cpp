#include "Timing.h"

#include <SDL/SDL.h>

namespace TRXEngine
{
	FpsLimiter::FpsLimiter()
	{
	}
	FpsLimiter::~FpsLimiter()
	{
	}
	void FpsLimiter::init(float max_fps)
	{
		setMaxFPS(max_fps);
	}
	void FpsLimiter::setMaxFPS(float max_fps)
	{
		m_max_fps = max_fps;
	}
	void FpsLimiter::begin()
	{
		m_start_ticks = SDL_GetTicks();
	}
	float FpsLimiter::end()
	{
		calcuteFPS();
		
		float frame_ticks{ (float)SDL_GetTicks() - m_start_ticks };

		if (1000.0f / m_max_fps > frame_ticks)
		{
			SDL_Delay((Uint32)(1000.0f / m_max_fps - frame_ticks));
		}

		return m_fps;
	}
	void FpsLimiter::calcuteFPS()
	{
		static const int NUM_SAMPLES{ 10 };

		static float frame_times[NUM_SAMPLES];

		static int current_frame{ 0 };

		static float prev_ticks{ (float)SDL_GetTicks() };
		float current_ticks{ (float)SDL_GetTicks() };

		m_frame_time = current_ticks - prev_ticks;
		frame_times[current_frame % NUM_SAMPLES] = m_frame_time;

		prev_ticks = current_ticks;

		int count{};

		current_frame++;
		if (current_frame < NUM_SAMPLES)
		{
			count = current_frame;
		}
		else
		{
			count = NUM_SAMPLES;
		}

		float frame_time_avg{ 0 };
		for (int i{ 0 }; i < count; i++)
		{
			frame_time_avg += frame_times[i];
		}
		frame_time_avg /= count;

		if (frame_time_avg > 0)
		{
			m_fps = 1000.0f / frame_time_avg;
		}
		else
		{
			m_fps = 60.0f;
		}
	}
}