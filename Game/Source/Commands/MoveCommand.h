#pragma once


class MoveCommand : public Hi_Engine::Command 
{
public:
	MoveCommand(float xDir, float yDir);
	MoveCommand(const CU::Vector2<float>& aDirection);

	void Execute() override;
	MoveCommand* Clone() const override;
	//void Execute(GameObject& aGameObject) override;	// do this instead...?? or pass in constructor as member??

private:
	// Pointer to game object to move?? 

	CU::Vector2<float> m_direction;
};
