#pragma once

#include <string>

namespace Web
{
	class Attribute
	{
	public:
		Attribute(const std::string& name, const std::string& value)
			: m_name(name)
			, m_value(value)
		{}

		const std::string& name() { return m_name; }
		const std::string& value() { return m_value; }

		void set_name(const std::string& value) { m_value = value; }

	private:
		std::string m_name;
		std::string m_value;
	};
}