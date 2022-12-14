#pragma once

#include <string>
#include <vector>
#include "HTMLTokenizer.h"
#include "DOM/Node.h"

#define ENUMERATE_INSERTION_MODES \
		__ENUMERATE_INSERTION_MODE(Initial) \
		__ENUMERATE_INSERTION_MODE(BeforeHtml) \
		__ENUMERATE_INSERTION_MODE(BeforeHead) \
		__ENUMERATE_INSERTION_MODE(InHead) \
		__ENUMERATE_INSERTION_MODE(InHeadNoscript) \
		__ENUMERATE_INSERTION_MODE(AfterHead) \
		__ENUMERATE_INSERTION_MODE(InBody) \
		__ENUMERATE_INSERTION_MODE(Text) \
		__ENUMERATE_INSERTION_MODE(InTable) \
		__ENUMERATE_INSERTION_MODE(InTableText) \
		__ENUMERATE_INSERTION_MODE(InCaption) \
		__ENUMERATE_INSERTION_MODE(InColumnGroup) \
		__ENUMERATE_INSERTION_MODE(InTableBody) \
		__ENUMERATE_INSERTION_MODE(InRow) \
		__ENUMERATE_INSERTION_MODE(InCell) \
		__ENUMERATE_INSERTION_MODE(InSelect) \
		__ENUMERATE_INSERTION_MODE(InSelectInTable) \
		__ENUMERATE_INSERTION_MODE(InTemplate) \
		__ENUMERATE_INSERTION_MODE(AfterBody) \
		__ENUMERATE_INSERTION_MODE(InFrameset) \
		__ENUMERATE_INSERTION_MODE(AfterFrameset) \
		__ENUMERATE_INSERTION_MODE(AfterAfterBody) \
		__ENUMERATE_INSERTION_MODE(AfterAfterFrameset) \

namespace Web
{
	class HTMLDocumentParser
	{
	public:
		explicit HTMLDocumentParser(const std::string& input);
		~HTMLDocumentParser();

		void run();

		enum class InsertionMode
		{
#define __ENUMERATE_INSERTION_MODE(mode) mode,
			ENUMERATE_INSERTION_MODES
#undef __ENUMERATE_INSERTION_MODE
		};

		InsertionMode insertion_mode() const { return m_insertion_mode; }

	private:
		const char* insertion_mode_name() const;
		InsertionMode m_insertion_mode{ InsertionMode::Initial };
		std::vector<Node> m_stack_of_open_elements;

		HTMLTokenizer m_tokenizer;
	};
}