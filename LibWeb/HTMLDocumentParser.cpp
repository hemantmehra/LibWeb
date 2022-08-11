#include <iostream>
#include "HTMLToken.h"
#include "HTMLDocumentParser.h"

namespace Web
{
	HTMLDocumentParser::HTMLDocumentParser(const std::string& input)
		: m_tokenizer(input)
	{}

	void HTMLDocumentParser::run()
	{
		for (;;)
		{
			auto token = m_tokenizer.next_token();

			if (!token.has_value())
				return;

			std::cout << "[" << insertion_mode_name() << "] " << token.value().to_string() << std::endl;

			if (token.value().type() == HTMLToken::Type::EndOfFile)
				return;
		}
	}

	const char* HTMLDocumentParser::insertion_mode_name() const
	{
		switch (m_insertion_mode)
		{
#define __ENUMERATE_INSERTION_MODE(mode) \
			case InsertionMode::mode:    \
				return #mode;
			ENUMERATE_INSERTION_MODES
#undef __ENUMERATE_INSERTION_MODE
		}

		_ASSERT(false);
	}
}