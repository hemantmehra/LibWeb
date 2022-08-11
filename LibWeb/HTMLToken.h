#pragma once

#include <string>
#include <vector>
#include "Attribute.h"
#include "Forward.h"

namespace Web
{
	class HTMLToken
	{
		friend class HTMLDocumentParser;
		friend class HTMLTokenizer;
	public:
		enum class Type
		{
			DOCTYPE,
			StartTag,
			EndTag,
			Comment,
			Character,
			EndOfFile
		};

		Type type() const { return m_type; }
		std::string to_string() const;

	private:
		Type m_type;

		struct {
			std::string name;
			std::string public_identifier;
			std::string system_identifier;
			bool force_quirks{ false };
		} m_doctype;

		struct {
			std::string tag_name;
			bool self_closing{ false };
			std::vector<Attribute> attributes;
		} m_tag;

		struct {
			std::string data;
		} m_comment_or_character;
	};
}