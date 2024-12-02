#pragma once
#include "../Base/System.h"

class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem();

	void Draw() override;
	void SetSignature() override;

private:
	void RenderDebugColliders(Entity camera);

	void RenderUIBoundingBoxes(const glm::mat4& proj);
	void RenderPhysicsColliders(const glm::mat4& proj);

	void RenderMapChunks(const glm::mat4& proj);
	void RenderEntities(const glm::mat4& proj);

	void RenderText(const glm::mat4& proj);
	void RenderUI(const glm::mat4& proj);
};