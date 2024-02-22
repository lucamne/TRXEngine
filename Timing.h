#pragma once

namespace TRXEngine
{
	class FpsLimiter
	{
	public:
		FpsLimiter();
		~FpsLimiter();

		void init(float max_fps);

		void setMaxFPS(float max_fps);

		void begin();

		// end will return the current fps
		float end();
	private:
		void calcuteFPS();

		float m_fps{};
		float m_max_fps{};
		float m_frame_time{};
		unsigned int m_start_ticks{};
	};
}