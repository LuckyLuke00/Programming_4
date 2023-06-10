#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void CleanUp();

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Render();

		std::shared_ptr<Scene> GetActiveScene() const { return m_scenes.front(); }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
