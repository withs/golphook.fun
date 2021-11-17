//
// Created by fleur on 14/11/2021.
//

#include "Netvars.hh"

NetvarsDumper::NetvarsDumper() {

    this->_clientClass=  InterfacesCollection::i_baseClient->GetAllClasses();

    NetvarsCollection::n_localPlayer = this->getNetVarOffset("DT_BasePlayer", "m_vecOrigin");
    PLOGD << NetvarsCollection::n_localPlayer;
};


// both _getOffset and getNetVarOffset are from GH but i modified them to use strings
// TODO: peut etre call un throw si pas trouver et handle ce throw dans getNetVarOffset
intptr_t NetvarsDumper::_getOffset(RecvTable *inTable, std::string withTableName, std::string forNetvarName) noexcept {
    for ( uint32_t i = 0; i < inTable->m_nProps; i++ ) {
        RecvProp prop = inTable->m_pProps[i];

        if ( (std::string(prop.m_pVarName) == forNetvarName) )
            return prop.m_Offset;

        if ( prop.m_pDataTable ) {
            intptr_t offset = this->_getOffset(prop.m_pDataTable, withTableName, forNetvarName);

            if ( offset ) {
                return offset + prop.m_Offset;
            }
        }
    }
    return 0;
}

intptr_t NetvarsDumper::getNetVarOffset(std::string withTableName,std::string forNetvarName) {
    for ( auto currNode = this->_clientClass; currNode; currNode = currNode->m_pNext ) {
        if ( (withTableName == std::string(currNode->m_pRecvTable->m_pNetTableName)) )
            return this->_getOffset(currNode->m_pRecvTable, withTableName, forNetvarName);
    }
    throw FatalError::NetvarNullError("Failed to get netvar: " + forNetvarName + " in table: " + withTableName);
}