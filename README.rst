======================================================================
Board files to compile MicroPython for the WeAct STM32H562RGT6 Pyboard
======================================================================

Background
==========


.. figure:: WEACT_H562RGT6/weact_h562rgt6.jpg
   :width: 1260px
   :align: center
   :alt: The WeAct STM32H562RGT6 Pyboard

   The WeAct STM32H562RGT6 Pyboard.


The `WeAct STM32H562 <https://github.com/WeActStudio/WeActStudio.STM32H5_64Pin_CoreBoard>`__
is a Cortext-M33 running at 250MHz, with 640KB of RAM and 1MB of ROM. It includes an SD card,
a single blue LED, and has a Pyboard form factor.

This repository provides board support and build instructions for running MicroPython
on the WEACT_H562RGT6 (STM32H562RG) Pyboard. If you don't want to build your own a DFU
file is provided.


Defined Pins
============

The pins for the WeAct STM32H562 are defined in the pins.csv file. Some pins have required
remapping to Alternate Function (AF) locations due to conflicts with the SD card.

Two pins for hardware Timer 3 have been changed:

+---------+--------+----------+
| Channel | Pin    | Notes    |
+=========+========+==========+
| CH1     | PC6    | Default  |
+---------+--------+----------+
| CH2     | PC7    | Default  |
+---------+--------+----------+
| CH3     | PB0    | Remapped |
+---------+--------+----------+
| CH4     | PB1    | Remapped |
+---------+--------+----------+

And UARTs 1-3 have been defined at the following locations:

+--------+--------+--------+
| UART   | TX Pin | RX Pin |
+========+========+========+
| UART1  |  PA9   | PA10   |
+--------+--------+--------+
| UART2  |  PA2   | PA3    |
+--------+--------+--------+
| UART3  | PB10   | PB11   |
+--------+--------+--------+


Quick Start: Build and Flash MicroPython Firmware
-------------------------------------------------

Follow these steps to build and flash MicroPython for the WEACT_H562RGT6 board.

.. contents::
    :local:
    :depth: 1



Prerequisites
=============

- Ubuntu/Debian (or similar), macOS, or WSL (Windows Subsystem for Linux)
- Git
- GNU Make
- ARM GCC toolchain (e.g., ``gcc-arm-none-eabi``)
- ``df-util``, ``st-flash`` or STM32CubeProgrammer for flashing


Build Instructions
==================

Install Required Packages (Ubuntu/Debian example)
-------------------------------------------------

.. code-block:: bash

    sudo apt update
    sudo apt install -y git make gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential


Clone MicroPython and Submodules
--------------------------------

.. code-block:: bash

    git clone https://github.com/micropython/micropython.git
    cd micropython
    git submodule update --init --recursive


(Optional) Checkout a Specific MicroPython Version
--------------------------------------------------

.. code-block:: bash

    # For example, to use v1.22.0:
    git checkout v1.22.0
    git submodule update --init --recursive

Add the Board Definition
------------------------

Copy or create your board definition in:

::

    ports/stm32/boards/WEACT_H562RGT6/

You will need at least the following files:

- ``mpconfigboard.h``
- ``mpconfigboard.mk``
- ``pins.csv``
- ``stm32h562_af.csv``
- ``stm32h562rg.ld``

Build the MicroPython Cross Compiler
------------------------------------

.. code-block:: bash

    make -C mpy-cross

Build MicroPython for WEACT_H562RGT6
------------------------------------

The normal build will not proceed without error so a build script has
been created for this purpose. It is executed from micropython root
directory, not ports/stm32/

.. code-block:: bash

    
    build-weactstmh562.sh

The output firmware will be in:

::

    build-WEACT_H562RGT6/firmware.dfu
    build-WEACT_H562RGT6/firmware.hex
    build-WEACT_H562RGT6/firmware.bin

It's highly recommended that you copy and rename the DFU file to match your
build, date and version, e.g.,
`WEACT_STM32H562_20250622-v1.26.0-preview.dfu`
or `WEACT_STM32H562_20250622-v1.26.0-preview.bin`,
depending on what format you plan to use for flashing the board (see below).


Flash the Firmware
==================

Use your preferred STM32 flashing tool.

If using STM32CubeProgrammer or DFU, refer to their documentation. An example using ``st-flash``:

.. code-block:: bash

    st-flash write WEACT_STM32H562_20250622-v1.26.0-preview.bin 0x08000000

or, if using `dfu-util <https://dfu-util.sourceforge.net/>`__:

.. code-block:: bash

    dfu-util --alt 0 -D WEACT_STM32H562_20250622-v1.26.0-preview.dfu

There is a convenient script for this purpose:

.. code-block:: bash

    flash_weact_stm32h562.sh


Troubleshooting
===============

- If you change board files or the linker script, run:

  .. code-block:: bash

      make BOARD=WEACT_H562RGT6 clean

  before rebuilding. This is done for you by the build script.


- For build errors about missing symbols, ensure your ``stm32h562rg.ld`` linker script includes the required MicroPython flash storage symbols (see board documentation or upstream examples).
- For serial REPL access, connect to the board's USB or UART port and use a terminal program (e.g., ``rshell``, ``picocom``, ``minicom``, or ``screen``).


Change Log
==========

**2025-07-01:**

- A pin conflict between Timer 3 and the SD card has been resolved by defining two AF
  pins for Timer 3 for channels 3 and 4. Channels 1 and 2 remain at their default values.
  This is now reflected in the *Defined Pins* section as above.

**2025-06-29:**

- A pin conflict between UART 4 and the SD card was noted, so UART 4 is no
  longer defined, but SD card support has been enabled and tested.


**2025-06-23:**

- Modified ``pins.csv`` with the following mappings supporting UART 1-3.
  This is now reflected in the *Defined Pins* section as above.

- Verified UART1–3 operation with a test script using default pins
  UART 4 is no longer supported (conflicts with the SD card, see 
  the changes for 2025-06-29).


**2025-06-22:**

- Initial MicroPython port for STM32H562 (WEACT_H562RGT6)
- There is currently no ADC support.


Status
======

The UF2 file can be successfully flashed to the board, the SD card functions and
UART 1-3 are enabled. There is no ADC support as a conflict in adc.c was unable
to be successfully patched in the build script.


Support & Liability
===================

This project comes with no promise of support or acceptance of liability. Use at
your own risk.


Copyright & License
===================

All contents Copyright 2020-2025 by Murray Altheim. All rights reserved.

Software and documentation are distributed under the MIT License, see LICENSE
file included with project.


