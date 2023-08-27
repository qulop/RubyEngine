
#ifndef RUBY_BUILD_H
#define RUBY_BUILD_H

#ifdef RUBYVN_STATIC_DEFINE
#  define RUBY_BUILD
#  define RUBYVN_NO_EXPORT
#else
#  ifndef RUBY_BUILD
#    ifdef RubyVn_EXPORTS
        /* We are building this library */
#      define RUBY_BUILD __declspec(dllexport)
#    else
        /* We are using this library */
#      define RUBY_BUILD __declspec(dllimport)
#    endif
#  endif

#  ifndef RUBYVN_NO_EXPORT
#    define RUBYVN_NO_EXPORT 
#  endif
#endif

#ifndef RUBYVN_DEPRECATED
#  define RUBYVN_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef RUBYVN_DEPRECATED_EXPORT
#  define RUBYVN_DEPRECATED_EXPORT RUBY_BUILD RUBYVN_DEPRECATED
#endif

#ifndef RUBYVN_DEPRECATED_NO_EXPORT
#  define RUBYVN_DEPRECATED_NO_EXPORT RUBYVN_NO_EXPORT RUBYVN_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RUBYVN_NO_DEPRECATED
#    define RUBYVN_NO_DEPRECATED
#  endif
#endif

#endif /* RUBY_BUILD_H */
