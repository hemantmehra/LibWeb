// LibWeb.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "HTMLTokenizer.h"
#include "HTMLDocumentParser.h"

const char* src_html =
	"<!DOCTYPE html>\n"
	"<head>\n"
	"</head>";

int main()
{
	Web::HTMLTokenizer tokenizer(src_html);
	tokenizer.run();

#if 0
	Web::HTMLDocumentParser parser(src_html);
	parser.run();
#endif

	return 0;
}
