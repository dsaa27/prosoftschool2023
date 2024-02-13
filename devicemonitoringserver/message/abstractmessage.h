#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include <string>

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
	/// Необходимо для инициализации m_type у наследников
	/// </summary>
	/// <see href="https://stackoverflow.com/questions/19808667/c-abstract-class-constructor-yes-or-no"> Статья об этом на Stackoverflow </see>
	AbstractMessage(const MessageType type) : 
		m_type(type)
	{}

	/// <summary>
	/// Получить тип сообщения
	/// </summary>
	/// <returns>Тип сообщения m_type</returns>
	MessageType getMessageType() const { return m_type; }
	
	virtual std::string messageToString() const = 0;
	virtual ~AbstractMessage() = default;

protected:

	/// <summary>
	/// Выбрать конкретные вид сообщения. Инициализируется в момент создания класса
	/// </summary>
	const MessageType m_type = MessageType::None;
};

std::ostream& operator<<(std::ostream& out, const AbstractMessage& msg)
{
	out << msg.messageToString();
	return out;
}

#endif /* ABSTRACTMESSAGE_H */