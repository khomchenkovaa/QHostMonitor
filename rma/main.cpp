#include <QCoreApplication>
#include <QCommandLineParser>
#include "settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setApplicationVersion(APPLICATION_VERSION);
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("RMA (Remote Monitoring Agent for QHostMonitor)");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("cfg_file", "obligatory parameter, path to configuration file");

    QCommandLineOption dMode("d", "daemon mode (default)");
    parser.addOption(dMode);

    QCommandLineOption iMode("i", "interactive mode");
    parser.addOption(iMode);

    QCommandLineOption vMode("v", "verbose mode");
    parser.addOption(vMode);

    QCommandLineOption vdMode("vd", "verbose debugging mode");
    parser.addOption(vdMode);

    QCommandLineOption optPort(QStringList() << "p" << "port", "overrides TCP port number specified in cfg_file", "port");
    parser.addOption(optPort);

    // Process the actual command line arguments given by the user
    parser.process(app);

    const QStringList args = parser.positionalArguments();

    QString mode = "Daemon";
    if (parser.isSet(iMode)) {
        mode = "Interactive";
    }

    bool debug = parser.isSet(vdMode);
    bool verbose = debug || parser.isSet(iMode);

    if (args.isEmpty()) {
        parser.showHelp(-1);
    }

    QSettings sett(args.at(0), QSettings::IniFormat);

    return app.exec();
}
