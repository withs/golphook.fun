//
// Created by fleur on 14/11/2021.
//

#include "EndScene.hh"

bool __stdcall EndScene::hooked(LPDIRECT3DDEVICE9 withDevice) {
    if ( !EndScene::d3dDevice ) {
        EndScene::d3dDevice = withDevice;
        PLOGD << "hello from endscene";
    }

    PLOGD << "hello from endscene 2";

    return EndScene::original(EndScene::d3dDevice);
}

void EndScene::getDevice() {
    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    if ( !pD3D )
        throw FatalError::CoreInitException("Failed to create d3d interface");

    IDirect3DDevice9* pDummyDevice = nullptr;

    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = false;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = App::Get().io.windHandle;

    HRESULT dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow,
                                                    D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

    if ( dummyDeviceCreated != S_OK ) {
        for ( uint8_t retry = 0 ; retry <= 5 ; retry++ ) {
            if (dummyDeviceCreated == S_OK)
                break;
            d3dpp.Windowed = !d3dpp.Windowed;
            dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow,
                                                    D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
        }
        if ( dummyDeviceCreated != S_OK ) {
            pD3D->Release();
            throw FatalError::CoreInitException("Failed to create d3d dummy device");
        }
    }

    std::memcpy(EndScene::d3d9DeviceTable, *reinterpret_cast<void***>(pDummyDevice), sizeof(EndScene::d3d9DeviceTable));

    pDummyDevice->Release();
    pD3D->Release();
}