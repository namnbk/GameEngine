#include "NamComponent.h"

NamComponent::NamComponent()
	:Component(500)
{

} // end NamComponent constructor

void NamComponent::initialize()
{
	cout << "Initialize method called for Nam component " << endl;

} //end initialize

void NamComponent::update(const float& deltaTime)
{
	cout << "Update method called for Nam component with time of " << deltaTime <<  endl;

} //end update

void NamComponent::processInput()
{
	cout << "ProcessInput method called for Nam component " << endl;

} //end processInput


