#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <map>

class ParserNode;
class Parser {
    using Configs = std::map <std::string, ParserNode*>;
    public:
        /// destructor
        ~Parser();

        /// used to return configuration of a given name
        ParserNode *getRoot(const std::string &symbolName);

        /// used to parse a file
        void parse(const std::string &type, const std::string &file);
    private:
        /// helper method for file parsing
        void parseNode(ParserNode *curNode, std::ifstream &in);
        /// helper method used to skip comments
        void handleComment(std::ifstream &in);

        /// helper method for file parsing
        void parseElement(ParserNode *curNode, std::ifstream &in);

        Configs m_configs;
        QFile m_file;
};

#endif // PARSER_H
