BACKGROUND
==========
***BELL*** Equipment has a team called the *Mining and Construction Engineering: 
Electrical and Software*. This team does development on proprieatry software as 
used on ***BELL*** products.

THIS PROJECT
============

A Qt project was created to evaluate the assessment given to GIT/PDx applicants
for positions in our team. The reason was to give a framework within which applicants
can show their C/C++ proficiency. It offers a quicker way than expecting the
applicant to build a full project from scratch, which can be time-consuming and
prohibitive when having full day job and other life pressures.

PROJECT FOLDER STRUCTURE
========================

The folder structure is as follows:
```
.
│   README.md    .......................................... This file you're looking at now
│
├───BELL_Cpp_Assessment      .............................. The folder with the Qt template project
│       BCanMsg.cpp    .................................... (see assignment document for detail)
│       BCanMsg.h      .................................... (see assignment document for detail)
│       BCanMsgsDb.cpp    ................................. (see assignment document for detail)
│       BCanMsgsDb.h      ................................. (see assignment document for detail)
│       BCanSig.cpp    .................................... (see assignment document for detail)
│       BCanSig.h      .................................... (see assignment document for detail)
│       bellDatabase.xml     .............................. A subset of CAN message definitions used by BELL
│       BELL_Cpp_Assessment.pro     ....................... (see assignment document for detail)
│       BELL_Cpp_Assessment.pro.user     .................. Qt's auto generated user-specific project settings
│       BXmlCanDbReader.cpp     ........................... (see assignment document for detail)
│       BXmlCanDbReader.h     ............................. (see assignment document for detail)
│       crc8.cpp     ...................................... (see assignment document for detail)
│       crc8.h     ........................................ (see assignment document for detail)
│       main.cpp     ...................................... (see assignment document for detail)
│       mainwindow.cpp     ................................ (see assignment document for detail)
│       mainwindow.h     .................................. (see assignment document for detail)
│       mainwindow.ui     ................................. (see assignment document for detail)
│       SharedFunctions.cpp     ........................... (see assignment document for detail)
│       SharedFunctions.h     ............................. (see assignment document for detail)
│
└───demo
    │   BELL_Cpp_Assessment.exe     ....................... Executable demo program of the completed project
    │   (various.dll)     ................................. Qt Redisitributable Libraries
    ├───(various-folders-FOO)     ......................... Qt Redisitributable Plugins
    │       (various-platform.dll.dll)     ................ Qt Redisitributable Plugin Libraries
    └───(various-folders-BAR)     ......................... Qt Redisitributable Plugins
            (various-platform.dll.dll)     ................ Qt Redisitributable Plugin Libraries
```