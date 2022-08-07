// LibWeb.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "HTMLTokenizer.h"

const char* src_html =
	"<!DOCTYPE html>\n"
	"<head>\n"
	"</head>";

int main()
{
	Web::HTMLTokenizer tokenizer(src_html);
	tokenizer.run();
	return 0;
}
