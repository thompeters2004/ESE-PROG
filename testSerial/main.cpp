#include "main.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    SerialCommandSender commandSender("COM7", QSerialPort::Baud19200);
    commandSender.openPort();

    // Start command
    commandSender.startCommand();
    // Safe mode command
    commandSender.safeCommand();
    // Drive command
    commandSender.driveCommand();

    // Add more commands here if necessary

    commandSender.closePort();
    return a.exec();
}
