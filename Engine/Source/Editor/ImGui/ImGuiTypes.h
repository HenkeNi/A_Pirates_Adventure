#pragma once
#include <variant>

namespace Hi_Engine
{

	struct ImGuiTextButton
	{
		std::function<void(class ImGuiWindow&)> Callback;
		const char* Label;
	};

	struct ImGuiImageButton
	{
		void* ID;
		std::function<void(class ImGuiWindow&)> Callback;
		const char* Label;
	};

	struct ImGuiCombo
	{
		constexpr static unsigned MaxItems = 5;
		const char* Items[MaxItems];
		const char* Label;
		int ItemAmoun;
		int CurrentItem;
	};

	struct ImGuiSlider
	{
		float Value;
		float MinValue;
		float MaxValue;
		const char* Label;
	};

	struct ImGuiTextInput
	{
		char Buffer[255] = "";
		const char* Header;
		//std::function<int(struct ImGuiInputTextCallbackData*)> Callback;
	};

	struct ImGuiTab
	{
		std::vector<const char*> TabItems;
		const char* Header;
	};


	using ImGuiElement = std::variant<ImGuiTextButton, ImGuiCombo, ImGuiSlider, ImGuiTextInput, ImGuiTab>;

	struct ImGuiGrid
	{
		// elemeents

		std::vector<ImGuiElement> Elements;

	};

	//struct ImGuiWindow
	//{
	//	std::vector<ImGuiButton> Buttons;
	//	FVector2				 Position;
	//	FVector2				 Size;
	//	const char*				 Title;
	//	bool					 IsMovable;
	//	bool					 IsResizable;
	//};


	enum class eImGuiWindowFlags
	{	
		None		= 0,
		NoTitleBar	= 1 << 0,
		NoResize	= 1 << 1,	
		NoMove		= 1 << 2,
		NoScrollbar = 1 << 3,
		NoCollapse	= 1 << 5,
		NoDecoration = NoTitleBar | NoResize | NoScrollbar | NoCollapse
	};

	inline eImGuiWindowFlags operator|(eImGuiWindowFlags a, eImGuiWindowFlags b) {
		return static_cast<eImGuiWindowFlags>(static_cast<int>(a) | static_cast<int>(b));
	}

	inline eImGuiWindowFlags operator&(eImGuiWindowFlags a, eImGuiWindowFlags b) {
		return static_cast<eImGuiWindowFlags>(static_cast<int>(a) & static_cast<int>(b));
	}

	inline eImGuiWindowFlags& operator|=(eImGuiWindowFlags& a, eImGuiWindowFlags b)
	{
		a = a | b;
		return a;
	}

	//enum class eImGuiElementType
	//{
	//	Button,
	//	Combo,
	//	Slider,
	//	Input
	//};

	//struct ImGuiElement
	//{
	//	eImGuiElementType Type;
	//};


	class ImGuiWindow // remae EditorWindow? EditorPanel
	{
	public:
		ImGuiWindow();
		ImGuiWindow(const char* title, const FVector2& position, const FVector2& size);

		void Update();

		void SetTitle(const char* title);
		void SetDimensions(const FVector2& position, const FVector2& size);
		void SetWindowFlags(eImGuiWindowFlags flag, bool enable = true);

	/*	inline void SetUpdateFunction(const std::function<void()>& func)
		{
			m_updateFunction = func;
		}*/

		ImGuiElement& AddElement(int section, const ImGuiElement& element, const char* id);
		// void AddElementsSameLine(int section, const std::vector<std::pair<const char*, const ImGuiElement>>& elements);

		ImGuiElement* GetElement(const char* id);


		//template <typename T>
		//ImGuiElement* GetUIElement()
		//{
		//	auto* element = std::find_if(m_sections.begin(), m_sections.end(),
		//		[](const std::vector<ImGuiElement>& section) 
		//		{
		//			auto* found = std::find_if(section.begin(), section.end(), 
		//			[](const ImGuiElement& element) 
		//				{

		//				});
		//			return found;
		//		});

		//	//std::get_if<T>()
		//}

	private:
		void ProcessElements();

		void UpdateTextButton(ImGuiTextButton& button);
		void UpdateInput(ImGuiTextInput& input);
		void UpdateTab(ImGuiTab& tab);

		// int GetWindowFlags() const;

		//std::function<void()> m_updateFunction;

		// std::vector<ImGuiButton> m_buttons;
		
		FVector2 m_position;
		FVector2 m_size;
		const char* m_title;
		eImGuiWindowFlags m_windowFlags;


		// int section, int order

		static constexpr int s_maxSections = 4;
		//std::array<std::vector<ImGuiElement>, s_maxSections> m_sections;
		std::array<std::unordered_map<const char*, ImGuiElement>, s_maxSections> m_sections; // vector pair
	};



	class EditorWindow
	{
	public:
		~EditorWindow() = default;
		virtual void Update() = 0;
	};

	class AssetBrowser : public EditorWindow
	{
	public:
		void Update() override;
	};
}