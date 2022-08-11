#include <iostream>
#include "HTMLToken.h"
#include "HTMLDocumentParser.h"

namespace Web
{
	HTMLDocumentParser::HTMLDocumentParser(const std::string& input)
		: m_tokenizer(input)
	{}

	HTMLDocumentParser::~HTMLDocumentParser()
	{}

	void HTMLDocumentParser::run()
	{
		for (;;)
		{
			auto optional_token = m_tokenizer.next_token();
			if (!optional_token.has_value())
				return;

			auto& token = optional_token.value();

			std::cout << "[" << insertion_mode_name() << "] " << token.to_string() << std::endl;

			if (token.type() == HTMLToken::Type::EndOfFile)
				return;

			switch (m_insertion_mode)
			{
			case InsertionMode::Initial:
				if (token.type() == HTMLToken::Type::DOCTYPE)
				{
					
				}
				break;
			
			default:
				break;
			}
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