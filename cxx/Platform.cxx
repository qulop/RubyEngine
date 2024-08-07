#if defined(RUBY_WIN32_USED)
    #include "../ruby/src/platform/win32/Win32.cpp"
    #include "../ruby/src/platform/win32/audio/WaveOutAudioOutputStream.cpp"
#elif defined(RUBY_LINUX_USED)
    #include "../ruby/src/platform/linux/Linux.cpp"
#endif
#include "../ruby/src/platform/GLFWWindow.cpp"