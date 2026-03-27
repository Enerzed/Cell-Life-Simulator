include(FetchContent)

# SFML
FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML
  GIT_TAG 0fa201c969e48ecc253581c5841ce73f44d42f49 # 3.0.2
)
add_subdirectory(sfml)

# Dear ImGui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG f5befd2d29e66809cd1110a152e375a7f1981f06 # 1.91.9b
)

FetchContent_MakeAvailable(imgui)

# ImGui-SFML
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml
  GIT_TAG 5e8f8fb857c8f3cff1096bf3e4402c64e3bcf6af # 3.0
)
add_subdirectory(imgui-sfml)