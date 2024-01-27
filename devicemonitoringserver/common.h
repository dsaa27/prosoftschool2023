#ifndef COMMON_H
#define COMMON_H

#define NON_COPYABLE(ClassName)           \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete;

#define UNUSED(x) (void)(x)

enum class MsgType{METRIC, COMMAND, ERROR};
enum class ErrType{NoSchedule, NoTimeStamp, Obsolete};

#endif // COMMON_H
