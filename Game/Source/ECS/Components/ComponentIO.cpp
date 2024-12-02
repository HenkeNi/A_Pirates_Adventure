#include "Pch.h"
#include "ComponentIO.h"
#include "Components.h"


void ComponentIO::Serialize(const struct TransformComponent* component, const SerializationData& data)
{
	rapidjson::Value jsonComponent(rapidjson::kObjectType);

	jsonComponent.AddMember("entity_id", data.Entity, data.Allocator);
	jsonComponent.AddMember("pos_x", component->CurrentPos.x, data.Allocator);
	jsonComponent.AddMember("pos_y", component->CurrentPos.y, data.Allocator);

	data.JsonComponentArray.PushBack(jsonComponent, data.Allocator);


	//auto position = Hi_Engine::JsonKeyValue{ "position", component.CurrentPos };
	//auto scale = Hi_Engine::JsonKeyValue{ "scale", component.Scale };
	//auto pivot = Hi_Engine::JsonKeyValue{ "pivot", component.Pivot };

	//auto rotation = Hi_Engine::JsonKeyValue{ "rotation", component.Rotation };

	//auto& allocator = document.GetAllocator();

	//document.AddMember("name", "MainMenu", allocator);
	//document.AddMember("entity_id", 1, allocator);

	//// Create a position object
	//rapidjson::Value position(rapidjson::kObjectType);
	//position.AddMember("x", 100, allocator);
	//position.AddMember("y", 200, allocator);

	//// Add position to the document
	//document.AddMember("position", position, allocator);

	//// 4. Serialize the document to a string
	//rapidjson::StringBuffer buffer;
	//rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	//document.Accept(writer);

	//// 5. Write the serialized JSON string to a file using std::ofstream
	//std::ofstream file(path);  // Open file to write
	//if (file.is_open()) {
	//	file << buffer.GetString();  // Write the JSON string to the file
	//	file.close();  // Close the file

	//	std::cout << "JSON data has been written to 'output.json'" << std::endl;
	//}
	//else {
	//	std::cerr << "Failed to open file for writing." << std::endl;
	//}
	int ass = 10;
	ass += 20;
}

void ComponentIO::Serialize(const TagComponent* component)
{
}

void ComponentIO::Serialize(const AnimationComponent* component)
{
}

void ComponentIO::Serialize(const BoundingBoxComponent* component)
{
}

void ComponentIO::Serialize(const CameraComponent* component)
{
	int ass = 10;
	ass += 20;
}

void ComponentIO::Serialize(const PhysicsComponent* component)
{
}

void ComponentIO::Serialize(const ColliderComponent* component)
{
}

void ComponentIO::Serialize(const CursorComponent* component)
{
}

void ComponentIO::Serialize(const InputComponent* component)
{
}

void ComponentIO::Serialize(const SpriteComponent* component)
{
}

void ComponentIO::Serialize(const TextComponent* component)
{
}

void ComponentIO::Serialize(const VelocityComponent* component)
{
}

void ComponentIO::Serialize(const SubEntitiesComponent* component)
{
}

void ComponentIO::Serialize(const SceneTransitionComponent* component)
{
}

void ComponentIO::Serialize(const PlayerControllerComponent* component)
{
}

void ComponentIO::Serialize(const AudioComponent* component)
{
}

void ComponentIO::Serialize(const BlackboardComponent* component)
{
}

void ComponentIO::Serialize(const BehaviorTreeComponent* component)
{
}

void ComponentIO::Serialize(const AttributesComponent* component)
{
}

void ComponentIO::Serialize(const PersonalityComponent* component)
{
}

void ComponentIO::Serialize(const FriendlyComponent* component)
{
}

void ComponentIO::Serialize(const HostileComponent* component)
{
}




//void ComponentIO::Deserialize(TransformComponent& component)
//{
//}
