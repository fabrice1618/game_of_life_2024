#pragma once

#include <exception>
#include <string>
#include <SDL2/SDL.h>

/*
Exception : InitSDLException
*/
class InitSDLException : public std::exception
{
    std::string msg;
public:
    InitSDLException();
    InitSDLException( const std::string & );
    virtual ~InitSDLException() throw();
    virtual const char * what() const throw();
};
