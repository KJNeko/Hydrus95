
#include "executeProc.hpp"

#include <h95/logging.hpp>

#ifdef __linux__

#include <string>

void executeProc( const std::string& path )
{
	spdlog::debug( "Executing game {}", path );

	std::system( path.c_str() );
}

#elif _WIN64

#include <Windows.h>
#include <cstring>

void executeProc( const std::string& path_str )
{
	spdlog::debug( "Executing game {}", path_str );

	LPSTR path;
	path = new char[4096 * 4];
	std::strcpy( path, path_str.c_str() );

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof( si ) );
	si.cb = sizeof( si );
	ZeroMemory( &pi, sizeof( pi ) );

	if ( !CreateProcessA( nullptr, path, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi ) )
		spdlog::error( "Failed to execute process {}", path );
}


#else
#error "No define for handling this OS"
#endif
