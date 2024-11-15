#pragma once


/* - Audio systems - */
#include "Audio/AudioSystem.h"

/* - AI systems - */
#include "AI/BehaviorTreeSystem.h"
#include "AI/BlackboardSystem.h"
#include "AI/SteeringBehaviorSystem.h"
// #include "AI/StateMachineSystem.h"

/* - Gameplay systems - */
#include "Gameplay/Combat/CombatSystem.h"
#include "Gameplay/Combat/ProjectileSystem.h"
#include "Gameplay/Inventory/InventorySystem.h"
#include "Gameplay/Equipment/EquipmentSystem.h"
#include "Gameplay/Stats/StatSystem.h"

#include "Controllers/PlayerControllerSystem.h"
#include "Input/InputSystem.h"

#include "Core/Transformation/TransformationSystem.h"

#include "Editor/EditorSystem.h"

/* - Physics systems - */
#include "Physics/CollisionSystem.h"
#include "Physics/MovementSystem.h"
#include "Physics/ShakeSystem.h"
#include "Physics/PhysicsSystem.h"

#include "UI/HUDSystem.h"
#include "UI/UISystem.h"

#include "Gameplay/Spawn/EnemySpawnSystem.h"
#include "Gameplay/Spawn/SpawnSystem.h"
#include "Map/MapGenerationSystem.h"
#include "Map/MapDecorationSystem.h"
#include "Time/TimeSystem.h"

#include "Transition/SceneTransitionSystem.h"
#include "Transition/StateTransitionSystem.h"

/* Rendering systems */
#include "Rendering/Animation/SpriteAnimationSystem.h"
#include "Rendering/Camera/CameraSystem.h"
#include "Rendering/RenderSystem.h"