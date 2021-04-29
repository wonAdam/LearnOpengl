#pragma once

class GameObject;

class Gui
{
public:
	Gui();
	virtual ~Gui();
	void Update();
	void MakePositioningPanel(GameObject* gameObject);
};

