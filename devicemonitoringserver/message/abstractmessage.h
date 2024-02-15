#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include <string>
#include <sstream>

class AbstractMessage
{
public:

	enum class MessageType
	{
		Meterage,
		Command,
		Error,
		None
	};

	/// <summary>
	/// ���������� ��� ������������� m_type � �����������
	/// </summary>
	/// <see href="https://stackoverflow.com/questions/19808667/c-abstract-class-constructor-yes-or-no"> ������ �� ���� �� Stackoverflow </see>
	AbstractMessage(const MessageType type) : 
		m_type(type)
	{}

	/// <summary>
	/// �������� ��� ���������
	/// </summary>
	/// <returns>��� ��������� m_type</returns>
	MessageType getMessageType() const { return m_type; }
	
	virtual std::string messageToString() const = 0;

protected:

	/// <summary>
	/// ������� ���������� ��� ���������. ���������������� � ������ �������� ������
	/// </summary>
	const MessageType m_type = MessageType::None;
};

std::ostream& operator<<(std::ostream& out, const AbstractMessage& msg);

#endif /* ABSTRACTMESSAGE_H */