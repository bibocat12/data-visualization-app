#pragma once
#include "../../StateMachine/State.h"
#include "../../StateMachine/StateMachine.h"
#include "../../StateMachine/Context.h"
#include "../../GUI/Node.h"
#include "../../GUI/Label.h"
#include "../../GUI/Button.h"

#include "../../GUI/Slider.h"

class AVLMainState :
    public Engine::State
{
public:
	AVLMainState(std::shared_ptr<Context>& context);
	~AVLMainState();
	void init() override;
	void pause() override;
	void resume() override;
	void processEvents() override;
	void update(const sf::Time& dt) override;
	void draw() override;


private:
	std::shared_ptr<Context> m_context;
	
};

