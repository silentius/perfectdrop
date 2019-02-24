#include "Parser.h"
#include "ParserNode.h"
#include "Variant.h"
#include <cstring>
#include <fstream>

Parser::~Parser() {
    for (auto &entry : m_configs) {
        delete(entry.second);
    }
}

ParserNode *Parser::getRoot(const std::string &symbolName) {
    return m_configs[symbolName];
}

void Parser::parse(const std::string &type, const std::string &file) {
    ParserNode *rootNode = new ParserNode;
    m_configs.insert(std::make_pair(type, rootNode));
    std::ifstream in (file);
    char curChar = 0;
    while (in.good()) {
        in.get(curChar);
        switch(curChar) {
            case ';':
                handleComment(in);
                break;
            case '(':
                parseNode(rootNode, in);
                break;
            case '\t':
            case ' ':
                continue;
        }
    }
    in.close();
}

void Parser::parseNode(ParserNode *curNode, std::ifstream &in) {
    ParserNode *node = new ParserNode;
    curNode->addNode(node);
    char curChar = 0;
    while(in.good()) {
        in.get(curChar);
        switch (curChar) {
            case '(':
                parseNode(node, in);
                break;
            case ')':
                return;
            case ' ':
            case '\r':
            case '\n':
            case '\t':
                continue;
            default:
                in.putback(static_cast<char>(curChar));
                parseElement(node, in);
        }
    }
}

void Parser::handleComment(std::ifstream &in) {
    char curChar = 0;
    int32_t numits = 0;
    while (in.good()) {
        numits++;
        in.get(curChar);
        if (curChar == '\n') {
            return;
        }
    }
}

void Parser::parseElement(ParserNode *curNode, std::ifstream &in) {
    char buffer[512] = {0};
    uint16_t pos = 0;
    char curChar = 0;
    bool isString = false;
    bool finish = false;
    while(!finish && in.good()) {
        in.get(curChar);
        if (curChar == '"') {
            if (isString) {
                finish = true;
            }
            isString = true;
        } else if ((curChar == ' ' && !isString) || curChar == '\t') {
            finish = true;
        }  else if (curChar == '(' || curChar == ')') {
            in.putback(curChar);
            finish = true;
        } else {
            memcpy(buffer + pos++, &curChar, sizeof(uint8_t));
        }
    }
    curNode->add(QString::fromLatin1(buffer, pos));
}
