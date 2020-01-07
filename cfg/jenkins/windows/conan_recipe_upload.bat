echo upload conan recipe

conan remote add --insecure --index 1 -f sxConan %3

cd "%cd%\..\..\..\"

cd conan

SET CONAN_NON_INTERACTIVE=1

conan remote login sxConan %1 -p %2
conan upload seadex-genesis -r=sxConan

conan remote remove sxConan