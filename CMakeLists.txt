cmake_minimum_required(VERSION 3.5)

project(tboxWidget VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#mosquitto
find_path(MOSQUITTO_INCLUDE_DIRS
    NAMES mosquitto.h
    PATH_SUFFIXES mosquitto
)

find_library(MOSQUITTO_LIBRARIES
    NAMES mosquitto
)

include(FindPackageHandleStandardArgs)

# Handle the QUIETLY and REQUIRED arguments and set the FOUND variable
find_package_handle_standard_args(Mosquitto DEFAULT_MSG MOSQUITTO_LIBRARIES MOSQUITTO_INCLUDE_DIRS)

mark_as_advanced(MOSQUITTO_INCLUDE_DIRS MOSQUITTO_LIBRARIES)

set(INC_DIR /home/tangrui/workspace/mqttDemo/wallInclude)
set(LIB_DIR /home/tangrui/workspace/mqttDemo/wallLib)

include_directories(${INC_DIR})
link_directories(${LIB_DIR})

#protobuf

find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS})
link_directories(${PROTOBUF_LIBRARY_DIRS})

set(PROTO_SRCS
    ./protoBuf/alert.pb.cc
    ./protoBuf/analysis.pb.cc
    ./protoBuf/connection.pb.cc
    ./protoBuf/control.pb.cc
    ./protoBuf/diagnose.pb.cc
    ./protoBuf/envelope.pb.cc
    ./protoBuf/event.pb.cc
    ./protoBuf/fault.pb.cc
    ./protoBuf/gb32960.pb.cc
    ./protoBuf/location.pb.cc
    ./protoBuf/lock.pb.cc
    ./protoBuf/message.pb.cc
    ./protoBuf/ota.pb.cc
    ./protoBuf/status.pb.cc
    ./protoBuf/marks.pb.cc
    )

set(PROTO_HDRS
    ./protoBuf/alert.pb.h
    ./protoBuf/analysis.pb.h
    ./protoBuf/connection.pb.h
    ./protoBuf/control.pb.h
    ./protoBuf/diagnose.pb.h
    ./protoBuf/envelope.pb.h
    ./protoBuf/event.pb.h
    ./protoBuf/fault.pb.h
    ./protoBuf/gb32960.pb.h
    ./protoBuf/location.pb.h
    ./protoBuf/lock.pb.h
    ./protoBuf/message.pb.h
    ./protoBuf/ota.pb.h
    ./protoBuf/status.pb.h
    ./protoBuf/marks.pb.h
    )

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        TBoxWidget.cpp
        TBoxWidget.h
        TBoxWidget.ui
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        FaultReportWidget.cpp
        FaultReportWidget.h
        FaultReportWidget.ui
        EventReportWidget.cpp
        EventReportWidget.h
        EventReportWidget.ui
        AlertReportWidget.cpp
        AlertReportWidget.h
        AlertReportWidget.ui
        StatusReportWidget.cpp
        StatusReportWidget.h
        StatusReportWidget.ui
        BmsSKInfoForm.cpp
        BmsSKInfoForm.h
        BmsSKInfoForm.ui
        TboxSkInfoForm.cpp
        TboxSkInfoForm.h
        TboxSkInfoForm.ui
        HmiForm.cpp
        HmiForm.h
        HmiForm.ui
        CanInfoForm.cpp
        CanInfoForm.h
        CanInfoForm.ui
        CommonDef.h
        ReportParent.cpp
        ReportParent.h
        LocationForm.cpp
        LocationForm.h
        LocationForm.ui
        FaultForm.cpp
        FaultForm.h
        FaultForm.ui
        AlertForm.cpp
        AlertForm.h
        AlertForm.ui
        EventListItemForm.cpp
        EventListItemForm.h
        EventListItemForm.ui
        EventForm.cpp
        EventForm.h
        EventForm.ui
        RemoteControlWid.cpp
        RemoteControlWid.h
        RemoteControlWid.ui
        EfenceForm.cpp
        EfenceForm.h
        EfenceForm.ui
        PointForm.cpp
        PointForm.h
        PointForm.ui
        SeatHeatForm.cpp
        SeatHeatForm.h
        SeatHeatForm.ui
        DiagnoseForm.cpp
        DiagnoseForm.h
        DiagnoseForm.ui
        DiagDiDItem.cpp
        DiagDiDItem.h
        DiagDiDItem.ui
        DIDContentForm.cpp
        DIDContentForm.h
        DIDContentForm.ui
        EcuDtcItem.cpp
        EcuDtcItem.h
        EcuDtcItem.ui
        EcuList.cpp
        EcuList.h
        EcuList.ui
        EcuListItem.cpp
        EcuListItem.h
        EcuListItem.ui
        ReadDtcRespForm.cpp
        ReadDtcRespForm.h
        ReadDtcRespForm.ui
        EcuAddrListForm.cpp
        EcuAddrListForm.h
        EcuAddrListForm.ui
        EcuAddrItem.cpp
        EcuAddrItem.h
        EcuAddrItem.ui
        EcuAddrDtcItemForm.cpp
        EcuAddrDtcItemForm.h
        EcuAddrDtcItemForm.ui
        DiagnoseCodeItemForm.cpp
        DiagnoseCodeItemForm.h
        DiagnoseCodeItemForm.ui
        ControlConfigForm.cpp
        ControlConfigForm.h
        ControlConfigForm.ui
        ApnItemForm.cpp
        ApnItemForm.h
        ApnItemForm.ui
        BmsSKInfoListForm.cpp
        BmsSKInfoListForm.h
        BmsSKInfoListForm.ui
        BatteryInfoForm.cpp
        BatteryInfoForm.h
        BatteryInfoForm.ui
        LampForm.cpp
        LampForm.h
        LampForm.ui
        EcuVersionForm.cpp
        EcuVersionForm.h
        EcuVersionForm.ui
        PathPlanForm.cpp
        PathPlanForm.h
        PathPlanForm.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tboxWidget
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET tboxWidget APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(tboxWidget SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(tboxWidget
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(tboxWidget PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network ${MOSQUITTO_LIBRARIES} -lcyber ${PROTOBUF_LIBRARIES})

set_target_properties(tboxWidget PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tboxWidget)
endif()
