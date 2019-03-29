#include "CrazyflieUSB.h"

#include <sstream>
#include <stdexcept>

#include <libusb-1.0/libusb.h>

CrazyflieUSB::CrazyflieUSB(uint32_t devid)
    : ITransport()
    , USBDevice(0x0483, 0x5740)
{
    m_devid = devid;
    open(devid);
    setCrtpToUsb(true);
    had_reset = false;
}

CrazyflieUSB::~CrazyflieUSB()
{
    setCrtpToUsb(false);
}

void CrazyflieUSB::reset_link() {
    // Stop the libusb device
    if (m_handle) {
        libusb_release_interface(m_handle, 0);
        libusb_close(m_handle);
    }
    libusb_exit(m_ctx);

    // Reopen the libusb device
    open(m_devid);
    had_reset = true;
}

uint32_t CrazyflieUSB::numDevices()
{
    return USBDevice::numDevices(0x0483, 0x5740);
}

std::string CrazyflieUSB::serial()
{
    return std::string("TODO");
}

float CrazyflieUSB::version() const
{
    return m_version;
}

void CrazyflieUSB::sendPacket(
    const uint8_t* data,
    uint32_t length,
    Ack& result)
{
    int status;
    int transferred;

    if (!m_handle) {
        throw std::runtime_error("No valid device handle!");
    }

    // Send data
    status = libusb_bulk_transfer(
        m_handle,
        /* endpoint*/ (0x01 | LIBUSB_ENDPOINT_OUT),
        (uint8_t*)data,
        length,
        &transferred,
        /*timeout*/ 1000);
    if (status != LIBUSB_SUCCESS) {
        throw std::runtime_error(libusb_error_name(status));
    }
    if (length != (uint32_t)transferred) {
        std::stringstream sstr;
        sstr << "Did transfer " << transferred << " but " << length << " was requested!";
        throw std::runtime_error(sstr.str());
    }

    // Read result
    result.ack = false;
    result.size = 0;
    status = libusb_bulk_transfer(
        m_handle,
        /* endpoint*/ (0x81 | LIBUSB_ENDPOINT_IN),
        (unsigned char*)&result.data[0],
        sizeof(result) - 2,
        &transferred,
        /*timeout*/ 1);
    if (   status != LIBUSB_SUCCESS
        && status != LIBUSB_ERROR_TIMEOUT) {
        throw std::runtime_error(libusb_error_name(status));
    }
    if (status == LIBUSB_SUCCESS) {
        result.ack = true;
        result.size = transferred;
    }
}

void CrazyflieUSB::sendPacketNoAck(
    const uint8_t* data,
    uint32_t length)
{
    int status;
    int transferred;

    if (!m_handle) {
        throw std::runtime_error("No valid device handle!");
    }

    // Send data
    status = libusb_bulk_transfer(
        m_handle,
        /* endpoint*/ (0x01 | LIBUSB_ENDPOINT_OUT),
        (uint8_t*)data,
        length,
        &transferred,
        /*timeout*/ 1000);
    if (status != LIBUSB_SUCCESS) {
        throw std::runtime_error(libusb_error_name(status));
    }
    if (length != (uint32_t)transferred) {
        std::stringstream sstr;
        sstr << "Did transfer " << transferred << " but " << length << " was requested!";
        throw std::runtime_error(sstr.str());
    }
}

void CrazyflieUSB::setCrtpToUsb(bool crtpToUsb)
{
    sendVendorSetup(0x01, 0x01, crtpToUsb, NULL, 0);
}
