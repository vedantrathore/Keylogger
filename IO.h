#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"

namespace IO
{
    std::string getPath(const bool append_seperator = false)
    {
        std::string appdata_dir(getenv("APPDATA"));

    }

}


#endif // IO_H
