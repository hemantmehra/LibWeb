#include <cctype>
#include <iostream>
#include <optional>
#include "HTMLToken.h"
#include "HTMLTokenizer.h"

#define SWITCH_TO(new_state) \
	std::cout << "[" << state_name(m_state) << "] Switch to " << state_name(State::new_state) << std::endl; \
	m_state = State::new_state;	\
	current_input_character = next_codepoint(); \
	goto new_state;

#define RECONSUME_IN(new_state) \
	std::cout << "[" << state_name(m_state) << "] Reconsume in " << state_name(State::new_state) << std::endl; \
	m_state = State::new_state;	\
	goto new_state;

#define DONT_CONSUME_NEXT_INPUT_CHARACTER \
	--m_cursor;

#define IGNORE_CHARACTER_AND_CONTINUE_IN(x) SWITCH_TO(x)

#define ON(ch) \
	if (current_input_character.has_value() && current_input_character.value() == ch)

#define ON_WHITESPACE \
	if (current_input_character.has_value() && \
		(current_input_character.value() == '\t') || \
		(current_input_character.value() == '\a') || \
		(current_input_character.value() == '\f') || \
		(current_input_character.value() == ' ')    \
		)
#define ON_ASCII_ALPHA \
	if (current_input_character.has_value() && isalpha(current_input_character.value()))

#define ON_EOF \
	if (!current_input_character.has_value())

#define EMIT_EOF_AND_RETURN \
	create_new_token(HTMLToken::Type::EndOfFile); \
	emit_current_token();	\
	return;

#define ANYTHING_ELSE if(1)

#define BEGIN_STATE(state) \
	state:	\
	case State::state:


#define END_STATE \
	_ASSERT(false); \
	break;

namespace Web
{
	std::optional<uint32_t> HTMLTokenizer::next_codepoint()
	{
		if (m_cursor >= m_input.length())
			return {};
		return m_input[m_cursor++];
	}

	std::optional<uint32_t> HTMLTokenizer::peek_codepoint(size_t offset) const
	{
		if ((m_cursor + offset) >= m_input.length())
			return 0;
		return m_input[m_cursor + offset];
	}
		
	void HTMLTokenizer::run()
	{
		for (;;)
		{
			auto current_input_character = next_codepoint();
			switch (m_state)
			{
				BEGIN_STATE(Data)
				{
					ON('&')
					{
						m_return_state = State::Data;
						SWITCH_TO(CharacterReference);
					}
					ON('<')
					{
						SWITCH_TO(TagOpen);
					}
					ON_EOF
					{
						EMIT_EOF_AND_RETURN;
					}
					ANYTHING_ELSE
					{
						create_new_token(HTMLToken::Type::Character);
						m_current_token.m_comment_or_character.data.push_back(current_input_character.value());
						emit_current_token();
						continue;
					}
				}
				END_STATE;

				BEGIN_STATE(TagOpen)
				{
					ON('!')
					{
						SWITCH_TO(MarkupDeclarationOpen);
					}
					ON('/')
					{
						SWITCH_TO(EndTagOpen);
					}
					ON_ASCII_ALPHA
					{
						create_new_token(HTMLToken::Type::StartTag);
						RECONSUME_IN(TagName);
					}
				}
				END_STATE;

				BEGIN_STATE(TagName)
				{
					ON('>')
					{
						emit_current_token();
						SWITCH_TO(Data);
					}
					ANYTHING_ELSE
					{
						m_current_token.m_tag.tag_name.push_back(current_input_character.value());
						continue;
					}
				}
				END_STATE;

				BEGIN_STATE(EndTagOpen)
				{
					ON_ASCII_ALPHA
					{
						create_new_token(HTMLToken::Type::EndTag);
						RECONSUME_IN(TagName);
					}
				}
				END_STATE;

				BEGIN_STATE(MarkupDeclarationOpen)
				{
					DONT_CONSUME_NEXT_INPUT_CHARACTER
					if (next_few_characters_are("DOCTYPE"))
					{
						consume("DOCTYPE");
						SWITCH_TO(DOCTYPE);
					}
				}
				END_STATE;

				BEGIN_STATE(DOCTYPE)
				{
					ON_WHITESPACE
					{
						SWITCH_TO(BeforeDOCTYPEName);
					}
				}
				END_STATE;

				BEGIN_STATE(BeforeDOCTYPEName)
				{
					ON_WHITESPACE
					{
						continue;
					}

					ANYTHING_ELSE
					{
						create_new_token(HTMLToken::Type::DOCTYPE);
						m_current_token.m_doctype.name.push_back(current_input_character.value());
						SWITCH_TO(DOCTYPEName);
					}
				}
				END_STATE;

				BEGIN_STATE(DOCTYPEName)
				{
					ON('>')
					{
						emit_current_token();
						SWITCH_TO(Data);
					}

					ANYTHING_ELSE
					{
						m_current_token.m_doctype.name.push_back(current_input_character.value());
						continue;
					}
				}
				END_STATE;

				BEGIN_STATE(CharacterReference)
				{

				}
				END_STATE;

				default:
					_ASSERT(false);
					break;
			}
		}
	}

	void HTMLTokenizer::consume(const std::string& s)
	{
		_ASSERT(next_few_characters_are(s));
		m_cursor += s.length();
	}

	bool HTMLTokenizer::next_few_characters_are(const std::string& s) const
	{
		for (size_t i = 0; i < s.length(); i++) {
			auto codepoint = peek_codepoint(i);
			if (!codepoint.has_value())
				return false;
			if (codepoint.value() != (uint32_t) s[i])
				return false;
		}
		return true;
	}

	void HTMLTokenizer::emit_current_token()
	{
		std::string s;
		switch (m_current_token.type())
		{
		case HTMLToken::Type::DOCTYPE:
			s.append("DOCTYPE");
			s.append(" { name: '");
			s.append(m_current_token.m_doctype.name);
			s.append("' }");
			break;
		case HTMLToken::Type::StartTag:
			s.append("StartTag");
			break;
		case HTMLToken::Type::EndTag:
			s.append("EndTag");
			break;
		case HTMLToken::Type::Comment:
			s.append("Comment");
			break;
		case HTMLToken::Type::Character:
			s.append("Character");
			break;
		case HTMLToken::Type::EndOfFile:
			s.append("EndOfFile");
			break;
		default:
			break;
		}

		std::cout << "[" << state_name(m_state)  << "] Emit " << s << std::endl;
		m_current_token = {};
	}

	void HTMLTokenizer::create_new_token(HTMLToken::Type type)
	{
		m_current_token = {};
		m_current_token.m_type = type;
	}
}