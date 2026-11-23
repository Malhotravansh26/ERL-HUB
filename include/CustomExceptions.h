
#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <exception>
#include <string>

namespace ReliefOps {
namespace Core {

class ERLException : public std::exception {

protected:
    std::string message;

public:
    explicit ERLException(const std::string& msg)
        : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class FileException : public ERLException {

public:
    explicit FileException(const std::string& msg)
        : ERLException("File Error: " + msg) {}
};

class InventoryException : public ERLException {

public:
    explicit InventoryException(const std::string& msg)
        : ERLException("Inventory Error: " + msg) {}
};

class MissionException : public ERLException {

public:
    explicit MissionException(const std::string& msg)
        : ERLException("Mission Error: " + msg) {}
};

class VehicleException : public ERLException {

public:
    explicit VehicleException(const std::string& msg)
        : ERLException("Vehicle Error: " + msg) {}
};

}
}

#endif
