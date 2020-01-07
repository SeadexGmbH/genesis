from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.microsoft import check_min_vs, is_msvc
from conan.tools.files import export_conandata_patches, copy, get
from conan.tools.build import check_min_cppstd
from conan.tools.scm import Version
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
import os

required_conan_version = ">=1.59"

class SeadexGenesisConan(ConanFile):
    name = "seadex-genesis"
    description = "genesis is a generator library developed by Seadex (written in C++11)."
    license = "MIT"
    url = "https://github.com/SeadexGmbH/genesis"
    homepage = "https://genesis.seadex.de/"
    topics = ("generator", "C++", "library")
    settings = "os", "arch", "compiler", "build_type"
    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "spdlog/*:header_only": True
    }
    exports_sources = "CMakeLists.txt", "src/*", "include/*"

    @property
    def _min_cppstd(self):
        return 17

    @property
    def _compilers_minimum_version(self):
        return {
            "gcc": "8.3",
            "clang": "12",
            "Visual Studio": "16",
            "msvc": "192",
            "apple-clang": "10"
        }

    def export_sources(self):
        export_conandata_patches(self)

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
            self.options.shared = False

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

        if self.settings.compiler == "clang" or self.settings.compiler == "apple-clang":
            self.settings.compiler.cppstd = self._min_cppstd

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("spdlog/1.11.0")
        self.requires("fmt/9.1.0")
        self.requires("seadex-essentials/2.1.2")

    def validate(self):
        if self.settings.os not in ["Linux", "Windows", "Macos"]:
            raise ConanInvalidConfiguration("This recipe supports only Linux, Windows and macOS!")
        if self.settings.compiler.cppstd:
            check_min_cppstd(self, self._min_cppstd)
        check_min_vs(self, 192)
        if not is_msvc(self):
            minimum_version = self._compilers_minimum_version.get(str(self.settings.compiler), False)
            if minimum_version and Version(self.settings.compiler.version) < minimum_version:
                raise ConanInvalidConfiguration(
                    f"{self.ref} requires C++{self._min_cppstd}, which your compiler does not support."
                )
        if is_msvc(self) and self.options.shared:
            raise ConanInvalidConfiguration(f"{self.ref} can not be built as shared on Visual Studio and msvc.")

    def source(self):
        get(self, **self.conan_data["sources"][self.version], strip_root=True)

    def generate(self):
        tc = CMakeToolchain(self)
        if self.options.shared:
            tc.variables["BUILD_SHARED_LIBS"] = "ON"
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE.md", self.source_folder, os.path.join(self.package_folder, "licenses") )
        cmake = CMake(self)
        cmake.configure()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["genesis"]
