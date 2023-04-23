#include "Pch.h"
#include "MoveCommand.h"


MoveCommand::MoveCommand(float xDir, float yDir)
	: m_direction{ xDir, yDir }
{
}

MoveCommand::MoveCommand(const CU::Vector2<float>& aDirection)
	: m_direction{ aDirection }
{
}

void MoveCommand::Execute()
{
	static int x = 20;
	x += 20;
}