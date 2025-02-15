#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "State.h"

namespace Engine
{


	class StateMachine
	{

	public:
		StateMachine();
		~StateMachine();

		void addState(std::unique_ptr<State> state, bool isReplace);
		void removeState();

		void processStateChanges();
		std::unique_ptr<State>& getActiveState();
	private:
		std::stack<std::unique_ptr<State>> m_states;
		std::unique_ptr<State> m_newState;
		bool isRemoving;
		bool isAdding;
		bool isReplacing;

	};
}
