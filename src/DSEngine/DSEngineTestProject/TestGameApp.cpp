#include <iostream>
#include "TestGameApp.h"
#include "PressSpaceToPlayAudio.h"
#include "UnlitMaterial.h"

TestGameApp::~TestGameApp()
{
	delete vertexShader;
	delete unlitPixelShader;
}

void TestGameApp::Init()
{
	// Stub logic
	LOG_TRACE << "TestGameApp Init";

	// Load Shaders
	// TODO: Could this be done by a resource manager?
	vertexShader = new SimpleVertexShader(FDirect3D->GetDevice(), FDirect3D->GetDeviceContext());
	unlitPixelShader = new SimplePixelShader(FDirect3D->GetDevice(), FDirect3D->GetDeviceContext());

	vertexShader->LoadShaderFile(L"VertexShader.cso");
	unlitPixelShader->LoadShaderFile(L"UnlitPixelShader.cso");

	// Set Camera
	CurrentActiveScene()->mainCamera->UpdateProjectionMatrix(float(width), float(height), 3.1415926f / 4.0f);

	// Add Objects
	Object* newObj = CurrentActiveScene()->AddObject("NewObject");
	// Add Components
	PressSpaceToPlayAudio* playAudioComponent = newObj->AddComponent<PressSpaceToPlayAudio>();

	// MeshRenderer
	MeshRenderer* meshRendererComponent = newObj->AddComponent<MeshRenderer>();
	// Material
	std::shared_ptr<UnlitMaterial> unlitMaterial = std::make_shared<UnlitMaterial>(vertexShader, unlitPixelShader, FDirect3D->GetDevice());
	// Yellow
	unlitMaterial->parameters.color = { 1.0f, 1.0f, 0.0f, 1.0f };
	meshRendererComponent->SetMaterial(unlitMaterial);
	// Mesh
	Vertex vertices[] =
	{
		{DirectX::XMFLOAT3(+0.0f, +1.0f, +5.0f), DirectX::XMFLOAT3(+0.0f, +0.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(+1.5f, -1.0f, +5.0f), DirectX::XMFLOAT3(+0.0f, +0.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-1.5f, -1.0f, +5.0f), DirectX::XMFLOAT3(+0.0f, +0.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
	};

	int indices[] = { 0, 1, 2 };
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, 3, indices, 3, FDirect3D->GetDevice());
	meshRendererComponent->SetMesh(mesh);
}
