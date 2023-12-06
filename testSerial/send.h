#ifndef SEND_H
#define SEND_H

#include <QSerialPort>
#include <QByteArray>
#include <ostream>
#include <iostream>

class SerialCommandSender {
public:
    SerialCommandSender(const QString &portName, int baudRate);
    ~SerialCommandSender();
    void openPort();
    void closePort();
    void sendCommand(const QByteArray &command);
    void startCommand();
    void safeCommand();
    void driveCommand();

private:
    void setupSerial(const QString &portName, int baudRate);
    void sendBasicCommand(int commandCode);
    QSerialPort serial;
};

#endif // SEND_H
