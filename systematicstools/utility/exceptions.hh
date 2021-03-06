#ifndef SYSTTOOLS_UTILITY_EXCEPTIONS_SEEN
#define SYSTTOOLS_UTILITY_EXCEPTIONS_SEEN

#include <sstream>
#include <stdexcept>
#include <string>

#ifndef NO_ART
#include "cetlib_except/exception.h"

#define NEW_SYSTTOOLS_EXCEPT(EXCEPT_NAME)                                      \
  struct EXCEPT_NAME : public cet::exception {                                 \
    EXCEPT_NAME(std::string const &mesg = "")                                  \
        : cet::exception(#EXCEPT_NAME, mesg) {}                               \
  }

#else

namespace systtools {
struct systematicstools_except : public std::exception {
  std::stringstream msgstrm;
  std::string msg;
  systematicstools_except() : msgstrm(), msg() {}
  systematicstools_except(systematicstools_except const &other)
      : msgstrm(), msg() {
    msgstrm << other.msg;
    msg = other.msg;
  }
  const char *what() const noexcept { return msg.c_str(); }

  template <typename T> systematicstools_except &operator<<(T const &obj) {
    msgstrm << obj;
    msg = msgstrm.str();
    return (*this);
  }
};

} // namespace systtools

#define NEW_SYSTTOOLS_EXCEPT(EXCEPT_NAME)                                      \
  struct EXCEPT_NAME : public systtools::systematicstools_except {             \
    EXCEPT_NAME() : systtools::systematicstools_except() {}                    \
    EXCEPT_NAME(EXCEPT_NAME const &other) : systematicstools_except(other) {}  \
    template <typename T> EXCEPT_NAME &operator<<(T const &obj) {              \
      msgstrm << obj;                                                          \
      msg = msgstrm.str();                                                     \
      return (*this);                                                          \
    }                                                                          \
  }

#endif

namespace systtools {

NEW_SYSTTOOLS_EXCEPT(invalid_parameter_name);
NEW_SYSTTOOLS_EXCEPT(invalid_parameter_Id);
NEW_SYSTTOOLS_EXCEPT(invalid_parameter_value);
NEW_SYSTTOOLS_EXCEPT(incorrectly_configured);
NEW_SYSTTOOLS_EXCEPT(parameter_Id_not_handled);
NEW_SYSTTOOLS_EXCEPT(parameter_name_not_handled);
NEW_SYSTTOOLS_EXCEPT(systParamId_collision);

} // namespace systtools

#endif
