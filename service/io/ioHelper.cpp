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
    case TMethodID::FileCompare :
        return new IOCompareFilesConverter();
    case TMethodID::CountFiles :
        return new IOCountFilesConverter();
    case TMethodID::CPU :
        return new IOCPUUsageConverter();
    case TMethodID::DHCP :
        return new IODHCPConverter();
    case TMethodID::DICOM :
        return new IODICOMConverter();
    case TMethodID::DriveSpace :
        return new IODriveSpaceConverter();
    case TMethodID::Externalprg :
        return new IOExternalPrgConverter();
    case TMethodID::FileExists :
        return new IOFileExistsConverter();
    case TMethodID::FileSize :
        return new IOFolderSizeConverter();
    case TMethodID::Interbase :
        return new IOInterbaseConverter();
    case TMethodID::MySQL :
        return new IOMySqlConverter();
    case TMethodID::ODBC :
        return new IOODBCConverter();
    case TMethodID::Oracle :
        return new IOOracleConverter();
    case TMethodID::Ping :
        return new IOPingConverter();
    case TMethodID::Postgre :
        return new IOPostgreSqlConverter();
    case TMethodID::ShellScript :
        return new IOShellScriptConverter();
    case TMethodID::SNMP :
        return new IOSnmpGetConverter();
    case TMethodID::DNS :
        return new IODNSTestConverter();
    case TMethodID::DominantProcess :
        return new IODominantProcessConverter();
    default:
        break;
    }
    return new IOTestMethodConverter();
}

/******************************************************************/

} // namespace SDPO
