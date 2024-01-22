#ifndef EBCCOMPILER_H
#define EBCCOMPILER_H

#include <stdio.h>
#include <stdbool.h>

struct position
{
    int line;
    int col;
    const char* filename;
};

enum{
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE
};

struct token
{
    int type;
    int flags;

    union
    {
        char cval;
        const char* sval;
        unsigned int inum;
        unsigned long lnum;
        unsigned long long llnum;
        void* any;
    };
    
    //true if there is whitespace between the token and the next token
    //i.e. * a for operator token * would mean whitespace would be set for token a
    bool whitespace;

    //this would point to a list of charaters(string)
    //for example, if we have (66+77+1000) the value of between_brackets would be a string "66+77+1000"
    const char* between_brackets;
};


enum{
    COMPILER_FILE_COMPILED_OK,
    COMPILER_FAILED_WITH_ERRORS
};

struct compile_process
{
    //flags for how the file will be compiled
    int flags;

    struct compile_process_input_file
    {
        FILE* fp;
        const char* abs_path;
    } cfile;
    
    FILE* ofile;
};


int compile_file(const char* filename, const char* out_filename, int flags);
struct compile_process* compile_process_create(const char* filename, const char* filename_out, int flags);

#endif