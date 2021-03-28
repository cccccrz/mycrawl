#include "ParserSax.h"

void htmlcxx::HTML::ParserSax::parse(const std::string &html)
{
//	std::cerr << "Parsing string" << std::endl;
    parse(html.c_str(), html.c_str() + html.length());
}

void htmlcxx::HTML::ParserSax::foundTag(htmlcxx::HTML::Node node, bool isEnd)
{

}

void htmlcxx::HTML::ParserSax::foundText(htmlcxx::HTML::Node node)
{

}

void htmlcxx::HTML::ParserSax::foundComment(htmlcxx::HTML::Node node)
{

}

void htmlcxx::HTML::ParserSax::endParsing()
{

}
