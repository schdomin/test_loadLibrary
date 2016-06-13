#include <iostream>
#include <string>

#ifdef _MSC_VER
    #if _MSC_VER >= 1600
        #include <cstdint>
    #else
        typedef __int8              int8_t;
        typedef __int16             int16_t;
        typedef __int32             int32_t;
        typedef __int64             int64_t;
        typedef unsigned __int8     uint8_t;
        typedef unsigned __int16    uint16_t;
        typedef unsigned __int32    uint32_t;
        typedef unsigned __int64    uint64_t;
    #endif
#elif __GNUC__ >= 3
    #include <cstdint>
#endif

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#define JBAXIWRAPPER_T_LIBHANDLE                     HINSTANCE
#define JBAXIWRAPPER_LOADLIBRARY( path )             LoadLibrary( path )
#define JBAXIWRAPPER_UNLOADLIBRARY( handle )         FreeLibrary( handle )
#define JBAXIWRAPPER_LOADFUNCTION( handle, func )    GetProcAddress( handle, func )
#define JBAXIWRAPPER_T_ERRORINFORMATION              DWORD
#define JBAXIWRAPPER_GETERROR( )                     GetLastError( )
#define JBAXIWRAPPER_IS_ERROR( error )               ( ERROR_SUCCESS != error )
#define JBAXIWRAPPER_LIBRARYNAME                     "jbaxiwrapper.dll"
#define JBAXIWRAPPER_CALLING_CONVENTION              __stdcall
#elif defined(UNIX) || defined(__unix__)
#include <dlfcn.h>
#define JBAXIWRAPPER_T_LIBHANDLE                     void*
#define JBAXIWRAPPER_LOADLIBRARY( path )             dlopen( path, RTLD_NOW )
#define JBAXIWRAPPER_UNLOADLIBRARY( handle )         dlclose( handle )
#define JBAXIWRAPPER_LOADFUNCTION( handle, func )    dlsym( handle, func )
#define JBAXIWRAPPER_T_ERRORINFORMATION              char *
#define JBAXIWRAPPER_GETERROR( )                     dlerror( )
#define JBAXIWRAPPER_IS_ERROR( error )               ( 0 != error )
#define JBAXIWRAPPER_LIBRARYNAME                     "libjbaxiwrapper.so"
#define JBAXIWRAPPER_CALLING_CONVENTION
#else
#error unable to determine dynamic loading
#endif



int32_t main( int32_t argc, char** argv )
{
    std::cout << "(main) launched" << std::endl;

    //ds error buffer
    JBAXIWRAPPER_T_ERRORINFORMATION chError = 0;

    //ds buffer library path
    std::string strPathLibraryToLoad( "" );
    std::cout << "(main) specify library to load (absolute path): "; std::cin >> strPathLibraryToLoad;

    //ds attempt to load the library in the current path
    JBAXIWRAPPER_T_LIBHANDLE m_pLibraryBAXIWrapperJNI = JBAXIWRAPPER_LOADLIBRARY( strPathLibraryToLoad.c_str( ) );
    std::cout << "(main) loading library: " << strPathLibraryToLoad << std::endl;

    chError = JBAXIWRAPPER_GETERROR( );
    if( JBAXIWRAPPER_IS_ERROR( chError ) )
    {
        //ds log
        std::cout << "(main) unable to load library: " << strPathLibraryToLoad << std::endl;
        std::cout << "(main) error information: " << chError << std::endl;
    }
    else
    {
        if( 0 == m_pLibraryBAXIWrapperJNI )
        {
            std::cout << "(main) library load call passed but no handle received" << std::endl;
        }
        else
        {
            std::cout << "(main) library successfully loaded!" << std::endl;
        }
    }

    std::cout << "(main) terminated" << std::endl;
    return 0;
}

