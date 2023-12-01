#pragma once

#include <json/json.h>
#include <list>
#include <string>
#include "GraphicsSource.hh"
#include "HLSLBuilderAPI.hh"
#include "ArgParser.hh"
#include "BuilderCommons.hh"
#include <functional>

namespace HLSLBuilder
{
	/**
	* The Builder is the static class to wrap all necessary arguments to be sent to D3DCompiler (until HLSL 5.1) or DXC (since HLSL 6.0)
	*/
	class HLSLB_API Builder
	{
	public:
		/**
		* This method sets all infos, in JSON format, to be sent to the sources.
		*/
		static void SetBuildArgs(Json::Value& solution, BuildMode buildMode, OutputTarget outputTarget);
		/**
		* This method builds all sources on all Source Lists.
		*/
		static void BuildSources();

		/**
		* This method clears all source list.
		*/
		static void Clear();
		
		/**
		* This method sets the callback method when a shader is built.
		*/
		static void SetCallback(std::function<void(std::string)> callback);
		
		/**
		* This method calls the callback method.
		*/
		static void SendBuildMessage(const Source& source);
	private:

		static void ValidateHLSLVersion();
		static void ValidateVulkanVersion();
		static void ValidateOutputTarget();

		static BuildMode s_BuildMode;
		static OutputTarget s_OutputTarget;
		static std::list<GraphicsSource> s_GraphicsSources;
		static Version s_HLSLVersion;
		static Version s_VulkanVersion;
		static std::function<void(std::string)> s_Callback;

		static Json::Value s_Output;
	};
}