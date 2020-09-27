#ifndef TYPEINFO_H
#define TYPEINFO_H

template <typename T>
struct TypeInfo;

#define REGISTER_TYPE_INFO(X)    \
    template <>                  \
    struct TypeInfo<X>           \
    {                            \
        static const char *name; \
    };                           \
    const char *TypeInfo<X>::name = #X

#endif