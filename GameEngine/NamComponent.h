#pragma once
#include "Component.h"
class NamComponent : public Component
{
public: 
	NamComponent();

	virtual void initialize() override;

	virtual void update(const float& deltaTime) override;

	virtual void processInput() override;

};

