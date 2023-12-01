#pragma once

#include "HLSLBuilderAPI.hh"
#include "ArgParser.hh"
#include "BuilderCommons.hh"
#include "Source.hh"
#include <wrl.h>
#include <dxcapi.h>

#ifdef HLSLB_WINDOWS
#include <d3dcompiler.h>
#endif

using Microsoft::WRL::ComPtr;

namespace HLSLBuilder
{
	/**
	* This Class Manages all Shaders on the Graphics Pipeline Config
	*  * Vertex
	*  * Pixel
	*  * Geometry
	*  * Domain
	*  * Hull
	*/
	class HLSLB_API GraphicsSource : public Source
	{
	public:

		/**
		* This class is built only with the path of the shader group
		*/
		GraphicsSource(std::string_view path);

		/**
		* This method is used to compile all shaders. In this project, is presumed (and tested) that all shaders are saved in the same file
		*/
		void CompileShaders(BuildMode buildMode, OutputTarget outputTarget, Version HLSLVersion, Version VulkanVersion) override;
		
		/**
		* This method recovers all properties of the source:
		*  * BaseName
		*  * VertexFile
		*  * PixelFile
		*/
		const Json::Value* GetProperties() const override;

		/**
		* This method validates all stages, with the graphics pipeline rules.
		*/
		void ValidateStage(ShaderStage stage, bool present) override;

		/**
		* This method set the callback to the compiled shader.
		*/
		void SetCallback(std::function<void(std::string)> callback) override;

		/**
		* This method get the path where the group will be built.
		*/
		std::string GetBuildPath() const override;

		/**
		* This method calls the callback.
		*/
		void BuildMessage(ShaderStage stage);
	private:

		void CompileD3DCGroup(BuildMode buildMode, Version HLSLVersion);
		void CompileDXCGroup(BuildMode buildMode, OutputTarget outputTarget, Version HLSLVersion, Version VulkanVersion);
		
		void D3DCBuildShader(BuildMode buildMode, ShaderStage shaderStage, Version hlslVersion);
		void DXCBuildShader(BuildMode buildMode, OutputTarget outputTarget, Version VulkanVersion, ShaderStage shaderStage, Version hlslVersion);

		void PushDxcArgList(std::vector<std::wstring>* argList, BuildMode buildMode, OutputTarget outputTarget, Version VulkanVersion, ShaderStage shaderStage, Version hlslVersion);

		std::string BuildShaderStageName(ShaderStage shaderStage, Version hlslVersion);
		std::string BuildExtensionName(ShaderStage shaderStage, OutputTarget outputTarget);
		std::string BuildVulkanVersion(Version vulkanVersion);
		std::string BuildBlobRelativePath(ShaderStage shaderStage, OutputTarget outputTarget);

		void RegisterBlob(ShaderStage shaderStage, OutputTarget outputTarget);

		std::string m_BaseName;
		std::string m_SourceCode;
		std::string m_ParentPath;

		Json::Value m_Properties;
		std::unordered_map<ShaderStage, ComPtr<IDxcBlob>> m_Blobs;
		std::function<void(std::string)> m_Callback;

		static const std::unordered_map<ShaderStage, std::string_view> s_FileEndpointMapper;
	};

	/**
	* Exception thrown when the pipeline stage is invalid.
	*/
	class HLSLB_API InvalidGraphicsPipelineException : public InvalidPipelineException
	{
	public:
		InvalidGraphicsPipelineException(std::string message);
	};
}