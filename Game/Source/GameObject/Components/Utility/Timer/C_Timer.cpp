#include "Pch.h"
#include "C_Timer.h"


C_Timer::C_Timer(GameObject* anOwner)
	: Component{ anOwner }
{
}

C_Timer::~C_Timer()
{
}

void C_Timer::Init(rapidjson::Value& aValue)
{
}

void C_Timer::HandleMessage(const CompMessage& aMsg)
{
}

void C_Timer::Update(float aDeltaTime)
{
	if (!m_isRunning)
		return;

	m_timer.m_elapsed += aDeltaTime;

	if (m_timer.m_elapsed >= m_timer.m_duration)
	{
		// Notify? 
		// Reset??
	}
}

void C_Timer::OnActivate()
{
	m_isRunning = true;
}

void C_Timer::OnDeactivate()
{
	m_isRunning = false;
}

C_Timer* C_Timer::Copy() const
{
	auto* res = CU::MemoryPool<C_Timer>::GetInstance().GetResource();
	assert(res && "Memory Pool returned invalid memory");

	return new (res) C_Timer{ *this };
}

void C_Timer::SetTimer(const Timer& aTimer)
{
	m_timer = aTimer;
}

void C_Timer::Reset()
{
	m_timer.m_elapsed = 0.f;
}