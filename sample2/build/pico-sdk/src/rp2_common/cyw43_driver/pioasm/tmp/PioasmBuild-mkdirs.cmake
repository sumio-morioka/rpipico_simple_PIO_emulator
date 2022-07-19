# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/rpi_pico/pico-sdk/tools/pioasm"
  "D:/rpi_pico/cq_interface/sample2/build/pioasm"
  "D:/rpi_pico/cq_interface/sample2/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm"
  "D:/rpi_pico/cq_interface/sample2/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/tmp"
  "D:/rpi_pico/cq_interface/sample2/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "D:/rpi_pico/cq_interface/sample2/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src"
  "D:/rpi_pico/cq_interface/sample2/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/rpi_pico/cq_interface/sample2/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/rpi_pico/cq_interface/sample2/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
