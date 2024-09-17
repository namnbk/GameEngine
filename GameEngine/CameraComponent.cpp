#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
	cout << "Constructor method called for camera component " << endl;
	componentType = CAMERA;
}


void CameraComponent::initialize()
{
	cout << "Initialize method called for Camera component " << endl;

} //end initialize

void CameraComponent::update(const float& deltaTime)
{
	cout << "Update method called for Camera component with time of " << deltaTime << endl;

} //end update

void CameraComponent::processInput()
{
	cout << "ProcessInput method called for Camera component " << endl;

} //end processInput
