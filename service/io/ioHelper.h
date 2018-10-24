#ifndef IOHELPER_H
#define IOHELPER_H

#include "method/sdpoTestMethodConverters.h"

namespace SDPO {

class IOHelper
{
public:
    IOHelper();

    static IOTestMethodConverter* methodConverter(const TMethodID methodId);

private:
    // singleton
    explicit IOHelper(const IOHelper& rhs);
    IOHelper& operator= (const IOHelper& rhs);
};

} // namespace SDPO

#endif // IOHELPER_H
