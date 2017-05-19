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
      make.add_headers(make.get_proj_root()),
      make.add_src(make.get_proj_root()),
      make.add_doc(make.get_proj_root()),
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
      make.get_proj_root() .. "src/",
    },

    project_dependencies = {
      "Utilities",
      "Math",
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
