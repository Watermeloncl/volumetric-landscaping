#ifndef DATA_CENTER_PARSER_H_
#define DATA_CENTER_PARSER_H_

#include "Objects\worldData.h"

class Parser {
private:
public:
    Parser();
    ~Parser();

    WorldData* ParseFile(char* filename);
};

#endif