/// This file is part of PerfectDrop.
///
/// PerfectDrop is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License.
///
/// PerfectDrop is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with PerfectDrop.  If not, see <https://www.gnu.org/licenses/>.

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
