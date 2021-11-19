//
// Created by fleur on 14/11/2021.
//

#include "EndScene.hh"

bool __stdcall EndScene::hooked(LPDIRECT3DDEVICE9 withDevice) {
    if ( !EndScene::d3dDevice ) {
        EndScene::d3dDevice = withDevice;

        int32_t w, h;
        InterfacesCollection::i_engineClient->GetScreenSize(w, h);
        App::Get().io.windHeight= h;
        App::Get().io.windWidth = w;

        DrawItemsCollection::makeShared();
        Menu::Get().bootstrap();
    }

    if ( App::Get().ready ) {
        int32_t queueSize = DrawQueue::Get().len();
        for ( int32_t i = 0; i < queueSize ; i++ ) {
            DrawQueue::Get()[i]->draw();
        }
    }

    if ( Menu::Get().isMenuOpened ) {
        Menu::Get().renderShadow();
        Menu::Get().render();
    }


    DrawQueue::Get().clear();
    /*
    for ( auto& elem: DrawQueue::Get() ) {
        elem->draw();
    }*/

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