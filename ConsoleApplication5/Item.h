#pragma once


class Item
{
public:
	virtual void act() = 0;

	void reset() { changed = false; };
	void change() { changed = true; };
	bool hasChanged() { return changed; };

private:
	bool changed = false;
};

