#include "send.h"
#include "qthread.h"

// Constructor: Initializes the SerialCommandSender with specified port and baud rate.
SerialCommandSender::SerialCommandSender(const QString &portName, int baudRate) {
    setupSerial(portName, baudRate);
}

// setupSerial: Configures the serial port with the specified settings.
void SerialCommandSender::setupSerial(const QString &portName, int baudRate) {
    serial.setPortName(portName); // Set the name of the port.
    serial.setBaudRate(baudRate); // Set baud rate for the serial communication.
    serial.setDataBits(QSerialPort::Data8); // Set the number of data bits sent in each byte.
    serial.setParity(QSerialPort::NoParity); // Set parity checking to none.
    serial.setStopBits(QSerialPort::OneStop); // Set the number of stop bits.
    serial.setFlowControl(QSerialPort::NoFlowControl); // Disable flow control.
}

// Destructor: Ensures the serial port is closed when the object is destroyed.
SerialCommandSender::~SerialCommandSender() {
    closePort();
}

// openPort: Opens the serial port for read and write. Exits the program if it fails.
void SerialCommandSender::openPort() {
    if (!serial.open(QIODevice::ReadWrite)) {
        std::cerr << "Cannot open serial port!" << std::endl;
        exit(1);
    }
}

// closePort: Closes the serial port if it is open.
void SerialCommandSender::closePort() {
    if (serial.isOpen()) {
        serial.close();
    }
}

// sendCommand: Sends a command through the serial port. Prints an error if it fails.
void SerialCommandSender::sendCommand(const QByteArray &command) {
    if (!serial.isOpen()) {
        std::cerr << "Serial port is not open!" << std::endl;
        return;
    }
    serial.write(command);
    if (!serial.waitForBytesWritten(1000)) {
        std::cerr << "Error writing to port!" << std::endl;
    }
}

// sendBasicCommand: Sends a basic one-byte command to the Roomba and waits for a response.
void SerialCommandSender::sendBasicCommand(int commandCode) {
    QByteArray dataToSend;
    dataToSend.append(static_cast<char>(commandCode));
    sendCommand(dataToSend);
    QThread::msleep(1000); // Wait for the command to take effect.
}

// startCommand: Sends the 'Start' command to the Roomba.
void SerialCommandSender::startCommand() {
    sendBasicCommand(128); // Start command code
}

// safeCommand: Sends the 'Safe' command to put the Roomba in safe mode.
void SerialCommandSender::safeCommand() {
    sendBasicCommand(131); // Safe command code
}

// driveCommand: Sends the 'Drive' command to move the Roomba at a specified velocity and radius.
void SerialCommandSender::driveCommand() {
    QByteArray dataToSend;
    dataToSend.append(static_cast<char>(137)); // Drive opcode
    dataToSend.append(static_cast<char>(0x00)); // High byte of velocity (0 in this example)
    dataToSend.append(static_cast<char>(75));   // Low byte of velocity (75 mm/s in this example)
    dataToSend.append(static_cast<char>(0x80)); // High byte of radius (0x8000 for straight)
    dataToSend.append(static_cast<char>(0x00)); // Low byte of radius
    sendCommand(dataToSend);
    QThread::msleep(1000); // Wait for the drive command to take effect.
}
