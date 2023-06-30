Process Hiding Linux Kernel Module
==================================

This Linux kernel module allows you to hide a specified process and its memory regions from other processes and the process list.

Prerequisites
-------------

- Linux kernel headers
- GNU Make
- GCC (GNU Compiler Collection)

Building the Module
-------------------

1. Ensure that you have the necessary prerequisites installed on your system.

2. Open a terminal and navigate to the directory containing the module source code.

3. Run the following command to build the module:

> Make

This will compile the module and generate the `hide_module.ko` file.

Loading the Module
------------------

1. Before loading the module, identify the PID (Process ID) of the process you want to hide. You can use the `ps` command or other system monitoring tools to find the PID.

2. Load the module into the kernel by running the following command as root:

> sudo insmod hide_module.ko pid_to_hide=<PID>

Replace `<PID>` with the actual PID of the process you want to hide.

This will hide the specified process and mark it as invisible.

Checking the Hidden Process
---------------------------

To verify that the process is hidden, you can use the `ps` command or other process listing tools. Run the following command:

> ps aux | grep <PROCESS_NAME>

Replace `<PROCESS_NAME>` with the name of the process you hid. If the process is successfully hidden, it should not be visible in the output.

Unloading the Module
--------------------

To unhide the process and restore its visibility, you can unload the module from the kernel. Run the following command as root:

> sudo rmmod hide_module


This will unload the module and unhide the process.

Important Notes
---------------

- Use this module responsibly and in compliance with applicable laws and regulations. Process hiding can have legitimate security and privacy use cases, but it can also be misused.

- Loading kernel modules requires root (superuser) privileges. Ensure that you have appropriate permissions before running the `insmod` command.

- The module may not work on all Linux kernel versions or configurations. Test it in a controlled environment and understand the potential implications before using it in a production system.

- Use this module at your own risk. The author(s) and contributors are not responsible for any damage or loss caused by the use of this module.

License
-------

This module is distributed under the GNU General Public License (GPL). See the LICENSE file for more information.

