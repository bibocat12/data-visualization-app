#include "StateMachine.h"

Engine::StateMachine::StateMachine()
{
	isAdding = false;
	isRemoving = false;
	isReplacing = false;
}

Engine::StateMachine::~StateMachine()
{
}



void Engine::StateMachine::addState(std::unique_ptr<State> state, bool isReplace)
{
	isAdding = true;
	isReplacing = isReplace;
	m_newState = std::move(state);
}

void Engine::StateMachine::removeState()
{
	isRemoving = true;
}

void Engine::StateMachine::processStateChanges()
{
	if (isRemoving && !m_states.empty())
	{
		m_states.pop();
		isRemoving = false;

		if (!m_states.empty())
		{
			m_states.top()->resume();
		}

	}
	if (isAdding)
	{
		if (!m_states.empty())
		{
			if (isReplacing)
			{
				m_states.pop();
				isRemoving = false;
			}
		}
		m_states.push(std::move(m_newState));
		m_states.top()->init();
		m_states.top()->resume();
		isAdding = false;
	}
}

std::unique_ptr<Engine::State>& Engine::StateMachine::getActiveState()
{
	return m_states.top();
}
