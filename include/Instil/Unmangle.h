#ifndef UNMANGLE_H
#define UNMANGLE_H

#include <cxxabi.h>
#include <string>

static std::string Unmangle(const char *mangled)
{
  int status = 0;

  const char *realname = abi::__cxa_demangle(mangled, 0, 0, &status);
  std::string realNameStr(realname);
  free((void *)realname);

  if (status == 0)
  {
    return realNameStr;
  }
  else
  {
    return "**CANNOT UNMANGLE**";
  }
}

#endif