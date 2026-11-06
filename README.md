# CHIMERA

## Modular Hardware-in-the-Loop (HIL) Engineering Platform

CHIMERA is an open-source, modular platform for hardware simulation, sensor emulation, signal acquisition, fault injection, and automated testing.

Developed by Working Mayhem.

Build it. Measure it. Figure out why.

## Project Status

### Early Development — Pre-Alpha

Initial development focuses on the STM32G474-based M01 module, firmware architecture, deterministic event scheduling, and sensor emulation.

## Licensing

This repository uses a multi-license structure. Licensing is determined by file location and any explicitly declared file-level license.

### Software — Apache License 2.0

All original source code, including firmware, software, testing utilities, and build automation, is licensed under the Apache License, Version 2.0.

### Documentation & Media — CC BY 4.0

Original documentation, diagrams, illustrations, and media located within the /docs directory are licensed under the Creative Commons Attribution 4.0 International License (CC BY 4.0), unless otherwise specified.

This README.md is also licensed under CC BY 4.0.

### Hardware — License Pending

Hardware designs, including schematics, PCB layouts, mechanical CAD, and manufacturing files, will be governed by a separately designated hardware license.

CERN-OHL-W-2.0 is the proposed license. Hardware designs are not released under this license until explicitly designated.

## Third-Party Components

Third-party libraries, vendor firmware, reference designs, and other external materials retain their respective licenses. Their inclusion does not change the original licensing terms.

### Project Organization

* firmware/ — Embedded firmware and hardware abstraction
* software/ — Host-side utilities and orchestration
* hardware/ — Electronic and mechanical design files
* docs/ — Architecture, specifications, and project documentation
* tests/ — Automated testing and validation
