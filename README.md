# GuiPkg

EDK2 compatible package to support gui based UEFI application development.
This project is a work in progress and must only be used for testing.

## Dependencies

- [LVGL](https://lvgl.io) is included as submodule
- [EDK2](https://github.com/tianocore/edk2) is needed to build the package

## Setup (Ubuntu 24.04)

- create a new folder and set the WORKSPACE environment variable
```
mkdir edk2-workspace
cd edk2-workspace
export WORKSPACE=$PWD
```

- clone edk2 and initialize it
```
git clone https://github.com/tianocore/edk2 edk2
cd edk2
git checkout edk2-stable202408
git submodule update --init
make -C ./BaseTools
cd $WORKSPACE
```

- clone GuiPkg and initialize it
```
mkdir edk2-packages
git clone https://github.com/MiSimon/edk2-guipkg edk2-packages/GuiPkg
cd edk2-packages/GuiPkg
git submodule update --init
cd $WORKSPACE
```

- finish the edk2 workspace setup
```
export PACKAGES_PATH=$WORKSPACE/edk2:$WORKSPACE/edk2-packages
source $WORKSPACE/edk2/edksetup.sh
```

- build the package
```
build -a X64 -t CLANGDWARF -b RELEASE -p GuiPkg/GuiPkg.dsc
```

- run the demo application in qemu (requires qemu and ovmf)
```
qemu-system-x86_64 -bios /usr/share/qemu/OVMF.fd -nodefaults -display gtk -vga std -drive format=raw,file=fat:rw:$WORKSPACE/Build/Gui/RELEASE_CLANGDWARF/X64/
efi shell> fs0:
efi shell> LvglDemo.efi
```

## Known problems
- replace `#ifdef LV_USE_QRCODE` with `#if LV_USE_QRCODE` in Library/LvglLib/lvgl/src/libs/qrcode/qrcodegen.h
- QEMU does not support the SIMPLE/ABSOLUTE_POINTER_PROTOCOLs