#!lua

--[[
  Nil Project Description
]]--

table.insert(
  projects,
  {
    name     = "Nil",
    kind     = "StaticLib",
    language = "C++",
    location = make.get_proj_root(),

    src_files = {
      make.get_proj_root() .. "src/**.hpp",
      make.get_proj_root() .. "src/**.cpp",
      make.get_proj_root() .. "src/**.mm",
      make.get_proj_root() .. "src/**.h",
      make.get_proj_root() .. "src/**.c",
      make.get_proj_root() .. "src/**.m",
      make.get_proj_root() .. "src/**.md",

      make.get_proj_root() .. "include/**.hpp",
      make.get_proj_root() .. "include/**.cpp",
      make.get_proj_root() .. "include/**.mm",
      make.get_proj_root() .. "include/**.h",
      make.get_proj_root() .. "include/**.c",
      make.get_proj_root() .. "include/**.m",
      make.get_proj_root() .. "include/**.md",
    },

    -- asset_dir = "assets/",

    lib_dirs_macosx = {
      "/usr/local/lib/",
    },

    linkoptions_macosx = {
    },

    inc_dirs_macosx = {
      "/usr/local/include",
    },

    inc_dirs = {
      make.get_proj_root() .. "include/",
      make.get_proj_root() .. "include/external",
      make.get_proj_root() .. "src/",
      make.get_proj_root() .. "src/external/",
      make.get_proj_root() .. "src/external/math/",
      make.get_proj_root() .. "src/external/utilities/",
    },

   link_dependencies_macosx = {
      "OpenGL.framework",
      "CoreFoundation.framework",
      "Foundation.framework",
    },

    link_dependencies_windows = {
      "glew32.lib",
      "SDL2.lib",
      "opengl32.lib",
      "shlwapi.lib", -- Move to pragma in utilities?
    },

    linkoption_dependencies_macosx = {
      "-lsdl2",
      "-lsdl2_mixer",
    },
  }
)
