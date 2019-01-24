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
    case TMethodID::Script :
        return new IOActiveScriptConverter();
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
    case TMethodID::DNS :
        return new IODNSTestConverter();
    case TMethodID::DominantProcess :
        return new IODominantProcessConverter();
    case TMethodID::FileContents :
        return new IOFileContentsConverter();
    case TMethodID::DriveSpace :
        return new IODriveSpaceConverter();
    case TMethodID::Externalprg :
        return new IOExternalPrgConverter();
    case TMethodID::FileExists :
        return new IOFileExistsConverter();
    case TMethodID::FileSize :
        return new IOFolderSizeConverter();
    case TMethodID::HTTP :
        return new IOHTTPConverter();
    case TMethodID::IMAP :
        return new IOIMAPTestConverter();
    case TMethodID::Interbase :
        return new IOInterbaseConverter();
    case TMethodID::Ldap :
        return new IOLDAPTestConverter();
    case TMethodID::MailRelay :
        return new IOMailRelayConverter();
    case TMethodID::MSSQL :
        return new IOMsSqlConverter();
    case TMethodID::MySQL :
        return new IOMySqlConverter();
    case TMethodID::NTLog :
        return new IONtEventLogConverter();
    case TMethodID::NTP :
        return new IONtpTestConverter();
    case TMethodID::ODBC :
        return new IOODBCConverter();
    case TMethodID::Oracle :
        return new IOOracleConverter();
    case TMethodID::PerfCounter :
        return new IOPerformanceCounterConverter();
    case TMethodID::Ping :
        return new IOPingConverter();
    case TMethodID::Postgre :
        return new IOPostgreSqlConverter();
    case TMethodID::ShellScript :
        return new IOShellScriptConverter();
    case TMethodID::SNMP :
        return new IOSnmpGetConverter();
    case TMethodID::Sybase :
        return new IOSybaseConverter();
    case TMethodID::WMI :
        return new IOWmiConverter();
    default:
        break;
    }
    return new IOTestMethodConverter();
}

/******************************************************************/

} // namespace SDPO
