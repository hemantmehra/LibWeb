// LibWeb.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "HTMLTokenizer.h"
#include "HTMLDocumentParser.h"

const char* src_html =
	"<!DOCTYPE html>\n"
	"<html>\n"
	"<head>\n"
	"</head>\n"
	"</html>\n";

int main()
{
	//Web::HTMLTokenizer tokenizer(src_html);
	Web::HTMLDocumentParser parser(src_html);
	parser.run();
	return 0;
}
