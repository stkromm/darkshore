#pragma once
#include <vector>
#include <memory>

namespace ds {
	namespace particles {
		struct Particle
		{

		};

		class ParticleSystem
		{

			std::vector<Particle> particles;
		public:
		};

		namespace ParticleManager
		{
			static bool init();
			static void shutdown();
			static void simulate(float millis);
		}
	}
}