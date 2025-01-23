#!/bin/bash

echo -e "==========================="
echo -e "= START COMPILING KERNEL  ="
echo -e "==========================="
bold=$(tput bold)
normal=$(tput sgr0)

# Scrip option
while (( ${#} )); do
    case ${1} in
        "-Z"|"--zip") ZIP=true ;;
    esac
    shift
done
[[ -z ${ZIP} ]] && { echo "${bold}LOADING-_-....${normal}"; }

DEFCONFIG="/asus/X01BD_defconfig"
export KBUILD_BUILD_USER=t.me/@IkhsanMah
export KBUILD_BUILD_HOST=Linux-kernel_https://sourceforge.net/projects/kernel-im964-x01bd/
TC_DIR="/workspace/IM/clang"
export PATH="$TC_DIR/bin:$PATH"

if [[ $1 = "-r" || $1 = "--regen" ]]; then
make O=out ARCH=arm64 $DEFCONFIG savedefconfig
cp out/defconfig arch/arm64/configs/$DEFCONFIG
exit
fi

if [[ $1 = "-c" || $1 = "--clean" ]]; then
rm -rf out
fi

mkdir -p out
make O=out ARCH=arm64 $DEFCONFIG


make -j$(nproc --all) O=out ARCH=arm64 CC=clang LD=ld.lld AR=llvm-ar AS=llvm-as NM=llvm-nm OBJCOPY=llvm-objcopy OBJDUMP=llvm-objdump STRIP=llvm-strip CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_ARM32=arm-linux-gnueabi- 2>&1 | tee log.txt

    echo -e "==========================="
    echo -e "   COMPILE KERNEL COMPLETE "
    echo -e "==========================="