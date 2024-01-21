#pragma once

/* - AI systems - */
#include "AI/BehaviorTreeSystem.h"
#include "AI/BlackboardSystem.h"
#include "AI/SteeringBehaviorSystem.h"
#include "AI/StateMachineSystem.h"

/* - Gameplay systems - */
#include "Gameplay/Combat/CombatSystem.h"
#include "Gameplay/Combat/MeleeCombatSystem.h"
#include "Gameplay/Combat/RangedCombatSystem.h"
#include "Gameplay/Inventory/InventorySystem.h"
#include "Gameplay/Equipment/EquipmentSystem.h"
#include "Gameplay/Stats/StatSystem.h"

#include "Controllers/PlayerControllerSystem.h"
#include "Input/InputSystem.h"

/* - Physics systems - */
#include "Physics/CollisionSystem.h"
#include "Physics/MovementSystem.h"
#include "Physics/ShakeSystem.h"

#include "HUD/HUDSystem.h"
#include "Gameplay/Spawn/EnemySpawnSystem.h"
#include "Gameplay/Spawn/SpawnSystem.h"
#include "Gameplay/Spawn/ResourceSpawnSystem.h"
#include "Map/MapGenerationSystem.h"
#include "Map/MapDecorationSystem.h"
#include "Time/TimeSystem.h"

/* Rendering systems */
#include "Rendering/Animation/SpriteAnimationSystem.h"
#include "Rendering/Camera/CameraSystem.h"
#include "Rendering/Sprite/SpriteRenderSystem.h"
#include "Rendering/Text/TextRenderSystem.h"
#include "Rendering/Debug/DebugRenderSystem.h"
#include "Rendering/Map/MapRenderSystem.h"
#include "Rendering/HUD/HUDRenderSystem.h"