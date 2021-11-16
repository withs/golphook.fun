//
// Created by fleur on 16/11/2021.
//

#ifndef GOLPHOOK_FUN_DT_RECV_H
#define GOLPHOOK_FUN_DT_RECV_H

class RecvTable;
class RecvProp;

class RecvProp {
    public:
         char*                    m_pVarName;
         void*                    m_RecvType;
         int                     m_Flags;
         int                     m_StringBufferSize;
         int                     m_bInsideArray;
         const void*                m_pExtraData;
         RecvProp*                m_pArrayProp;
         void*                    m_ArrayLengthProxy;
         void*                    m_ProxyFn;
         void*                    m_DataTableProxyFn;
         RecvTable* m_pDataTable;
         int                     m_Offset;
         int                     m_ElementStride;
         int                     m_nElements;
         const char*                m_pParentArrayPropName;
};

class RecvTable {
    public:
         RecvProp*    m_pProps;
         int            m_nProps;
         void*        m_pDecoder;
         char*        m_pNetTableName;
         bool        m_bInitialized;
         bool        m_bInMainList;
};

#endif //GOLPHOOK_FUN_DT_RECV_H
