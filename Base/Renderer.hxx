#pragma once

// This is ImGui Renderer file.

// 3rdParty
#include "3rdParty/ImGui/imgui.h"
#include "3rdParty/ImGui/imgui_impl_win32.h"
#include "3rdParty/ImGui/imgui_impl_dx11.h"

namespace Render
{
	ID3D11DeviceContext* m_DeviceCtx = nullptr;
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;

	void InitializeStyle()
	{
		ImGuiStyle& m_Style = ImGui::GetStyle();

		for (ImVec4& m_Color : m_Style.Colors)
		{
			float m_HSV[3];
			ImGui::ColorConvertRGBtoHSV(m_Color.x, m_Color.y, m_Color.z, m_HSV[0], m_HSV[1], m_HSV[2]);

			m_HSV[0] += 0.4f;

			ImGui::ColorConvertHSVtoRGB(m_HSV[0], m_HSV[1], m_HSV[2], m_Color.x, m_Color.y, m_Color.z);
		}
	}

	bool Initialize(HWND p_Window, ID3D11Device* p_Device, ID3D11DeviceContext* p_DeviceCtx, IDXGISwapChain* p_SwapChain)
	{
		m_DeviceCtx = p_DeviceCtx;

		ID3D11Texture2D* m_RenderTargetTexture = nullptr;
		if (SUCCEEDED(p_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&m_RenderTargetTexture))))
		{
			D3D11_RENDER_TARGET_VIEW_DESC m_RenderTargetViewDesc;
			memset(&m_RenderTargetViewDesc, 0, sizeof(m_RenderTargetViewDesc));

			m_RenderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			m_RenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

			p_Device->CreateRenderTargetView(m_RenderTargetTexture, &m_RenderTargetViewDesc, &m_RenderTargetView);
			m_RenderTargetTexture->Release();
		}

		if (!m_RenderTargetView)
			return false;

		ImGui::CreateContext();

		ImGui_ImplWin32_Init(p_Window);
		ImGui_ImplDX11_Init(p_Device, p_DeviceCtx);
		ImGui_ImplDX11_CreateDeviceObjects();

		InitializeStyle();

		ImGuiIO& m_IO = ImGui::GetIO();
		{
			m_IO.IniFilename = 0;
			m_IO.LogFilename = 0;
			m_IO.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
		}

		return true;
	}

	void Uninitialize()
	{
		m_RenderTargetView->Release();

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	bool m_Visible = true;

	void OnFrame()
	{
		if (!m_Visible)
			return;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(ImVec2(10.f, 10.f), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(640.f, 480.f), ImGuiCond_Once);

		if (ImGui::Begin("ImGui Base"))
		{
			ImGui::Text("Hello SDmodding!");
			ImGui::Text("GameStateInGame::UpdateCounter -");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), "%d", static_cast<int>(Global::m_GameStateInGameCounter));

			ImGui::Separator();

			UFG::CSimCharacter* m_LocalPlayer = UFG::LocalPlayer::Get();
			ImGui::Text("LocalPlayer: 0x%p", m_LocalPlayer);
			if (m_LocalPlayer && m_LocalPlayer->m_pTransformNodeComponent)
			{
				UFG::qVector4& m_Position = m_LocalPlayer->m_pTransformNodeComponent->mWorldTransform.v3;
				ImGui::Text("- Position: %.2f, %.2f, %.2f", m_Position.x, m_Position.y, m_Position.z);
			}

			ImGui::End();
		}

		ImGui::EndFrame();
		ImGui::Render();

		m_DeviceCtx->OMSetRenderTargets(1, &m_RenderTargetView, 0);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}