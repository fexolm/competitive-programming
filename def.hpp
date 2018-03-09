#pragma once

#ifndef CP_INITMACRO
#define CP_INITMACRO
#ifndef CP_NOTHROW
#define CP_NOEXCEPT
#define CP_THROW(exception) throw (exception)
#define CP_THROW_IF(stmt, exception) if((stmt)) throw (exception)
#define CP_ASSERT(stmt) assert((stmt))
#else
#define CP_NOEXCEPT noexcept
#define CP_THROW(exception)
#define CP_THROW_IF(stmt, exception)
#define CP_ASSERT(stmt)
#endif
#endif