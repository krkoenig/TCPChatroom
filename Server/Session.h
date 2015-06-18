#pragma once
class Session
{
public:
	Session();
	~Session();

	unsigned int getID() const;

private:
	unsigned int id;
};

