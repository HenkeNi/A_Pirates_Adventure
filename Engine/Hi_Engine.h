#pragma once

/* - Core - */
#include "Core/Application/Application.h"
#include "Core/EntryPoint.h"
#include "Core/Physics/Collisions/CollisionManager.h"

/* - Command - */
#include "Core/Base/Command/Command.h"

/* - Rendering - */
#include "Core/Rendering/Camera/Camera.h"
#include "Core/Rendering/Renderers/SpriteRenderer/SpriteRenderer.h"

/* - Messaging - */
#include "Core/Messaging/Dispatcher/Dispatcher.h"
#include "Core/Messaging/Listener/EventListener.h"
#include "Core/Messaging/Events/SystemEvents/SystemEvents.h"

/* - Data Structures - */
#include "Utility/DataStructures/Linear/Dynamic/Stack/Stack.hpp"
#include "Utility/DataStructures/Linear/Dynamic/Queue/Queue.hpp"
#include "Utility/DataStructures/Linear/Static/Array/VectorOnStack.hpp"
#include "Utility/DataStructures/Linear/Static/MemoryPool/MemoryPool.hpp"
#include "Utility/DataStructures/Non-Linear/Factory/Factory.hpp"

/* - Math - */
#include "Utility/Math/Vectors/Vector.hpp"
#include "Utility/Math/Matrices/Matrix3x3.hpp"
#include "Utility/Math/Matrices/Matrix4x4.hpp"
#include "Utility/Math/MathExpression.hpp"

/* - Utility - */
#include "Utility/Utility/UtilityFunctions.hpp"



/* - Data (Expose???) - */
#include "Source/Data/Enumerations.h"
