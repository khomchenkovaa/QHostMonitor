#include "ioHelper.h"

namespace SDPO {

/******************************************************************/

IOHelper::IOHelper()
{
}

/******************************************************************/

IOTestMethodConverter *IOHelper::methodConverter(const TMethodID methodId)
{
    switch (methodId) {
    case TMethodID::Ping :
        return new IOPingConverter();
    case TMethodID::DriveSpace :
        return new IODriveSpaceConverter();
    case TMethodID::FileSize :
        return new IOFolderSizeConverter();
    case TMethodID::FileExists :
        return new IOFileExistsConverter();
    case TMethodID::SNMP :
        return new IOSnmpGetConverter();
    case TMethodID::ShellScript :
        return new IOShellScriptConverter();
    case TMethodID::Oracle :
        return new IOOracleConverter();
    case TMethodID::MySQL :
        return new IOMySqlConverter();
    case TMethodID::Postgre :
        return new IOPostgreSqlConverter();
    case TMethodID::Interbase :
        return new IOInterbaseConverter();
    case TMethodID::ODBC :
        return new IOODBCConverter();
    case TMethodID::Externalprg :
        return new IOExternalPrgConverter();
    case TMethodID::DICOM :
        return new IODICOMConverter();
    case TMethodID::DHCP :
        return new IODHCPConverter();
    case TMethodID::CPU :
        return new IOCPUUsageConverter();
    case TMethodID::CountFiles :
        return new IOCountFilesConverter();
    case TMethodID::FileCompare :
        return new IOCompareFilesConverter();
    default:
        break;
    }
    return new IOTestMethodConverter();
}

/******************************************************************/

} // namespace SDPO
