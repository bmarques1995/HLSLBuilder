#pragma once

#include <string>
#include <exception>
#include "CommonExceptions.hh"

namespace HLSLBuilder
{
	/**
	* This struct stores an API version, like HLSL or Vulkan, and is used for control its current version, only major and minor updates
	*/
	struct Version
	{
		unsigned Major;
		unsigned Minor;

		Version();

		Version(std::string version);
		Version(unsigned major, unsigned minor);

		bool operator==(Version version) const;
		std::string ToString() const;
	};

	/**
	* Base class of compile time exceptions
	*/
	class CompilerException : public HLSLBuilderException
	{
	};

	/**
	* Exception thrown when the HLSL version evaluated is not avaliable.
	*/
	class InvalidHLSLVersionException : public CompilerException
	{
	public:
		InvalidHLSLVersionException(Version version);
	};

	/**
	* Exception thrown when the Vulkan version evaluated is not avaliable.
	*/
	class InvalidVulkanVersionException : public CompilerException
	{
	public:
		InvalidVulkanVersionException(Version version);
	};

	/**
	* Exception thrown when the HLSL version evaluated doesn't support SPV (before 6.0).
	*/
	class InvalidSPVSupportException : public CompilerException
	{
	public:
		InvalidSPVSupportException();
	};

	/**
	* Exception thrown when the compilation fails.
	*/
	class CompileErrorException : public CompilerException
	{
	public:
		CompileErrorException(std::string error);
	};
}