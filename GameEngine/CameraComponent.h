#pragma once
#include "Component.h"
class CameraComponent :
    public Component
{
public:
	CameraComponent();

	virtual void initialize() override;

	virtual void update(const float& deltaTime) override;

	virtual void processInput() override;
};

