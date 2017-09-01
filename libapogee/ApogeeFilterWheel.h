/*! 
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright(c) 2011 Apogee Imaging Systems, Inc. 
*
* \class ApogeeFilterWheel 
* \brief class for apogee's usb filter wheel 
* 
*/ 


#ifndef APOGEEFILTERWHEEL_INCLUDE_H__ 
#define APOGEEFILTERWHEEL_INCLUDE_H__ 

#include <stdint.h>
#include <string>

#ifdef WIN_OS
#include <memory>
#else
#include <tr1/memory>
#endif

#include "DefDllExport.h"


class FilterWheelIo;

class DLL_EXPORT ApogeeFilterWheel
{ 
    public: 
         /*! */
        enum Type
        {
             /*! */
            UNKNOWN_TYPE = 0,
             /*! */
            FW50_9R = 1,
             /*! */
            FW50_7S = 2,
             /*! */
            AFW50_10S = 6,

            AFW31_17R = 9
        };

         /*! Current filter wheel state */
        enum Status
        {
             /*! Error status */
            UNKNOWN_STATUS,
             /*! Filter wheel is not connected either physically 
             * or the ApogeeFilterWheel::Init function has not been
             called*/
            NOT_CONNECTED,
             /*! Filter wheel is at the desired position */
            READY,
             /*! Filter wheel is moving to desired postion*/
            ACTIVE
        };

         /*! 
         *
         */
        ApogeeFilterWheel();

         /*! 
         *
         */
        virtual ~ApogeeFilterWheel(); 

         /*! 
         * Initizes the USB connection from the PC to the filter wheel.  The results strings from
         * the FindDeviceUsb::Find() provide the input into this function.
         * \param [in] User supplied ApogeeFilterWheel::Type
         * \param [in] DeviceAddr specifies the address of the filter wheel on the USB buss
         * \exception std::runtime_error
         */
        void Init( const ApogeeFilterWheel::Type type, 
            const std::string & DeviceAddr );

        /*! 
         * Closes the USB connection to the filter wheel
         * \exception std::runtime_error
         */
        void Close();

        /*! 
         * Returns USB vendor id
         * \exception std::runtime_error
         */
        uint16_t GetVendorId();

        /*! 
         * Returns USB product id
         * \exception std::runtime_error
         */
        uint16_t GetProductId();

        /*! 
         * Returns USB device id
         * \exception std::runtime_error
         */
        uint16_t GetDeviceId();

        /*! 
         * Returns USB firmware version
         * \exception std::runtime_error
         */
        std::string GetUsbFirmwareRev();

        /*! 
         * Returns Current filter wheel type
         */
        ApogeeFilterWheel::Type GetType() { return m_type; }

        /*! 
         * Returns Current filter wheel name
         * \exception std::runtime_error
         */
        std::string	GetName();

        /*! 
         * Returns the current status of the filter wheel
         * \exception std::runtime_error
         */
        ApogeeFilterWheel::Status GetStatus();

        /*! 
         * Returns The maximum number of filter wheel position
         * \exception std::runtime_error
         */
        uint16_t GetMaxPositions();

         /*! 
         * Sets filter wheel positon
         * \param [in]  Position Desired position.  Valid range is 1 to GetMaxPositions()
         * \exception std::runtime_error
         */
        void	SetPosition( uint16_t Position );

        /*! 
         * Returns the current filter wheel position
         * \exception std::runtime_error
         */
        uint16_t GetPosition();

    protected:
//this code removes vc++ compiler warning C4251
//from http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
#ifdef WIN_OS
#if _MSC_VER < 1600
        template class DLL_EXPORT std::shared_ptr<FilterWheelIo>;
#endif
#endif

        std::shared_ptr<FilterWheelIo> m_Usb;

    private:
       
        bool IsConnected();

        ApogeeFilterWheel::Type m_type;
        bool m_connected;

        //disabling the copy ctor and assignment operator
        //generated by the compiler - don't want them
        //Effective C++ Item 6
        ApogeeFilterWheel(const ApogeeFilterWheel&);
        ApogeeFilterWheel& operator=(ApogeeFilterWheel&);

}; 

#endif
