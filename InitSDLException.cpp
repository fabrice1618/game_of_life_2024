#include "InitSDLException.h"

InitSDLException::InitSDLException() :
    exception(),
    msg( SDL_GetError() )
{
}

InitSDLException::InitSDLException( const std::string & m ) :
    exception(),
    msg( m )
{
}

InitSDLException::~InitSDLException() throw()
{
}

const char * InitSDLException::what() const throw()
{
    return msg.c_str();
}
