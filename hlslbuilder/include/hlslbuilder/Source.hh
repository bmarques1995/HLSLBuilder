#pragma once

#include "HLSLBuilderAPI.hh"
#include "ArgParser.hh"
#include "BuilderCommons.hh"
#include <json/json.h>
#include <unordered_map>
#include <functional>

namespace HLSLBuilder
{
	/**
	* Displays the currently supported shader stages
	*/
	enum class ShaderStage
	{
		Vertex = 0,
		Pixel
	};

	/**
	* This class is the mother of all pipelines classes.
	*/
	class HLSLB_API Source
	{
	public:

		/**
		* This method is used to compile all shaders. In this project, is presumed (and tested) that all shaders are saved in the same file
		*/
		virtual void CompileShaders(BuildMode buildMode, OutputTarget outputTarget, Version HLSLVersion, Version VulkanVersion) = 0;
		
		/**
		* This method recovers all properties of the source:
		*/
		virtual const Json::Value* GetProperties() const = 0;
		
		/**
		* This method validates all stages, with the pipeline rules.
		*/
		virtual void ValidateStage(ShaderStage stage, bool present) = 0;
		
		/**
		* This method set the callback to the compiled shader.
		*/
		virtual void SetCallback(std::function<void(std::string)> callback) = 0;
		
		/**
		* This method get the path where the group will be built.
		*/
		virtual std::string GetBuildPath() const = 0;
	protected:
		static const std::unordered_map<ShaderStage, std::string_view> s_EntrypointMapper;
	};
	
	class HLSLB_API InvalidPipelineException : public HLSLBuilderException
	{
	
	};
}