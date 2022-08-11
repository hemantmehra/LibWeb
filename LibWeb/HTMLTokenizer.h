#pragma once

#include <optional>
#include <string>
#include "HTMLToken.h"

#define ENUMERATE_TOKENIZER_STATES \
	__ENUMERATE_TOKENIZER_STATE(Data) \
	__ENUMERATE_TOKENIZER_STATE(RCDATA) \
	__ENUMERATE_TOKENIZER_STATE(RAWTEXT) \
	__ENUMERATE_TOKENIZER_STATE(ScriptData) \
	__ENUMERATE_TOKENIZER_STATE(PLAINTEXT) \
	__ENUMERATE_TOKENIZER_STATE(TagOpen) \
	__ENUMERATE_TOKENIZER_STATE(EndTagOpen) \
	__ENUMERATE_TOKENIZER_STATE(TagName) \
	__ENUMERATE_TOKENIZER_STATE(RCDATALessThanSign) \
	__ENUMERATE_TOKENIZER_STATE(RCDATAEndTagOpen) \
	__ENUMERATE_TOKENIZER_STATE(RCDATAEndTagName) \
	__ENUMERATE_TOKENIZER_STATE(RAWTEXTLessThanSign) \
	__ENUMERATE_TOKENIZER_STATE(RAWTEXTEndTagOpen) \
	__ENUMERATE_TOKENIZER_STATE(RAWTEXTEndTagName) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataLessThanSign) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataEndTagOpen) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataEndTagName) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataEscapeStart) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataEscapeStartDash) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataEscaped) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataEscapedDash) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataEscapedDashDash) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataEscapedLessThanSign) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataEscapedEndTagOpen) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataEscapedEndTagName) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscapeStart) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscaped) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscapedDash) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscapedDashDash) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscapedLessThanSign) \
	__ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscapeEnd) \
	__ENUMERATE_TOKENIZER_STATE(BeforeAttributeName) \
	__ENUMERATE_TOKENIZER_STATE(AttributeName) \
	__ENUMERATE_TOKENIZER_STATE(AfterAttributeName) \
	__ENUMERATE_TOKENIZER_STATE(BeforeAttributeValue) \
	__ENUMERATE_TOKENIZER_STATE(AttributeValueDoubleQuoted) \
	__ENUMERATE_TOKENIZER_STATE(AttributeValueSingleQuoted) \
	__ENUMERATE_TOKENIZER_STATE(AttributeValueUnquoted) \
	__ENUMERATE_TOKENIZER_STATE(AfterAttributeValueQuoted) \
	__ENUMERATE_TOKENIZER_STATE(SelfClosingStartTag) \
	__ENUMERATE_TOKENIZER_STATE(BogusComment) \
	__ENUMERATE_TOKENIZER_STATE(MarkupDeclarationOpen) \
	__ENUMERATE_TOKENIZER_STATE(CommentStart) \
	__ENUMERATE_TOKENIZER_STATE(CommentStartDash) \
	__ENUMERATE_TOKENIZER_STATE(Comment) \
	__ENUMERATE_TOKENIZER_STATE(CommentLessThanSign) \
	__ENUMERATE_TOKENIZER_STATE(CommentLessThanSignBang) \
	__ENUMERATE_TOKENIZER_STATE(CommentLessThanSignBangDash) \
	__ENUMERATE_TOKENIZER_STATE(CommentLessThanSignBangDashDash) \
	__ENUMERATE_TOKENIZER_STATE(CommentEndDash) \
	__ENUMERATE_TOKENIZER_STATE(CommentEnd) \
	__ENUMERATE_TOKENIZER_STATE(CommentEndBang) \
	__ENUMERATE_TOKENIZER_STATE(DOCTYPE) \
	__ENUMERATE_TOKENIZER_STATE(BeforeDOCTYPEName) \
	__ENUMERATE_TOKENIZER_STATE(DOCTYPEName) \
	__ENUMERATE_TOKENIZER_STATE(AfterDOCTYPEName) \
	__ENUMERATE_TOKENIZER_STATE(AfterDOCTYPEPublicKeyword) \
	__ENUMERATE_TOKENIZER_STATE(BeforeDOCTYPEPublicIdentifier) \
	__ENUMERATE_TOKENIZER_STATE(DOCTYPEPublicIdentifierDoubleQuoted) \
	__ENUMERATE_TOKENIZER_STATE(DOCTYPEPublicIdentifierSingleQuoted) \
	__ENUMERATE_TOKENIZER_STATE(AfterDOCTYPEPublicIdentifier) \
	__ENUMERATE_TOKENIZER_STATE(BetweenDOCTYPEPublicAndSystemIdentifiers) \
	__ENUMERATE_TOKENIZER_STATE(AfterDOCTYPESystemKeyword) \
	__ENUMERATE_TOKENIZER_STATE(BeforeDOCTYPESystemIdentifier) \
	__ENUMERATE_TOKENIZER_STATE(DOCTYPESystemIdentifierDoubleQuoted) \
	__ENUMERATE_TOKENIZER_STATE(DOCTYPESystemIdentifierSingleQuoted) \
	__ENUMERATE_TOKENIZER_STATE(AfterDOCTYPESystemIdentifier) \
	__ENUMERATE_TOKENIZER_STATE(BogusDOCTYPE) \
	__ENUMERATE_TOKENIZER_STATE(CDATASection) \
	__ENUMERATE_TOKENIZER_STATE(CDATASectionBracket) \
	__ENUMERATE_TOKENIZER_STATE(CDATASectionEnd) \
	__ENUMERATE_TOKENIZER_STATE(CharacterReference) \
	__ENUMERATE_TOKENIZER_STATE(NamedCharacterReference) \
	__ENUMERATE_TOKENIZER_STATE(AmbiguousAmpersand) \
	__ENUMERATE_TOKENIZER_STATE(NumericCharacterReference) \
	__ENUMERATE_TOKENIZER_STATE(HexadecimalCharacterReferenceStart) \
	__ENUMERATE_TOKENIZER_STATE(DecimalCharacterReferenceStart) \
	__ENUMERATE_TOKENIZER_STATE(HexadecimalCharacterReference) \
	__ENUMERATE_TOKENIZER_STATE(DecimalCharacterReference) \
	__ENUMERATE_TOKENIZER_STATE(NumericCharacterReferenceEnd)

namespace Web
{
	class HTMLTokenizer
	{
	public:
		explicit HTMLTokenizer(const std::string input) : m_input(input) {}

		std::optional<HTMLToken> next_token();

	private:
		std::optional<uint32_t> next_codepoint();
		std::optional<uint32_t> peek_codepoint(size_t offset) const;
		bool next_few_characters_are(const std::string& s) const;
		void consume(const std::string& s);
		void emit_current_token();
		void create_new_token(HTMLToken::Type type);

		enum class State
		{
#define __ENUMERATE_TOKENIZER_STATE(x) x,
		ENUMERATE_TOKENIZER_STATES
#undef __ENUMERATE_TOKENIZER_STATE
		};

		static const char* state_name(State state)
		{
			switch (state) {
#define __ENUMERATE_TOKENIZER_STATE(state) \
			case State::state:			   \
				return #state;
				ENUMERATE_TOKENIZER_STATES
#undef __ENUMERATE_TOKENIZER_STATE
			};
			_ASSERT(false);
		}

		void will_switch_to(State new_state);
		void will_reconsume_in(State new_state);

		State m_state{ State::Data };
		State m_return_state{ State::Data };
		HTMLToken m_current_token;
		
		std::string m_input;
		size_t m_cursor{ 0 };
	};
}