#option(USE_GLV "" OFF)

# Main Library
set(core_headers
  include/al/core/app/al_App.hpp
  include/al/core/app/al_AudioApp.hpp
  include/al/core/app/al_DistributedApp.hpp
  include/al/core/app/al_FPS.hpp
  include/al/core/app/al_WindowApp.hpp
  include/al/core/graphics/al_BufferObject.hpp
  include/al/core/graphics/al_DefaultShaders.hpp
  include/al/core/graphics/al_EasyFBO.hpp
  include/al/core/graphics/al_EasyVAO.hpp
  include/al/core/graphics/al_FBO.hpp
  include/al/core/graphics/al_GLEW.hpp
  include/al/core/graphics/al_GLFW.hpp
  include/al/core/graphics/al_GPUObject.hpp
  include/al/core/graphics/al_Graphics.hpp
  include/al/core/graphics/al_Isosurface.hpp
  include/al/core/graphics/al_Lens.hpp
  include/al/core/graphics/al_Light.hpp
  include/al/core/graphics/al_Mesh.hpp
  include/al/core/graphics/al_OpenGL.hpp
  include/al/core/graphics/al_RenderManager.hpp
  include/al/core/graphics/al_Shader.hpp
  include/al/core/graphics/al_Shapes.hpp
  include/al/core/graphics/al_Texture.hpp
  include/al/core/graphics/al_VAO.hpp
  include/al/core/graphics/al_VAOMesh.hpp
  include/al/core/graphics/al_Viewpoint.hpp
  include/al/core/io/al_AudioIO.hpp
  include/al/core/io/al_AudioIOData.hpp
  include/al/core/io/al_ControlNav.hpp
  include/al/core/io/al_CSVReader.hpp
  include/al/core/io/al_File.hpp
  include/al/core/io/al_MIDI.hpp
  include/al/core/io/al_Window.hpp
  include/al/core/math/al_Constants.hpp
  include/al/core/math/al_Mat.hpp
  include/al/core/math/al_Matrix4.hpp
  include/al/core/math/al_Quat.hpp
  include/al/core/math/al_StdRandom.hpp
  include/al/core/math/al_Vec.hpp
  include/al/core/protocol/al_OSC.hpp
  include/al/core/sound/al_Ambisonics.hpp
  include/al/core/sound/al_AudioScene.hpp
  include/al/core/sound/al_Biquad.hpp
  include/al/core/sound/al_Crossover.hpp
  include/al/core/sound/al_Dbap.hpp
  include/al/core/sound/al_Lbap.hpp
  include/al/core/sound/al_Reverb.hpp
  include/al/core/sound/al_Spatializer.hpp
  include/al/core/sound/al_Speaker.hpp
  include/al/core/sound/al_StereoPanner.hpp
  include/al/core/sound/al_Vbap.hpp
  include/al/core/spatial/al_HashSpace.hpp
  include/al/core/spatial/al_Pose.hpp
  include/al/core/system/al_PeriodicThread.hpp
  include/al/core/system/al_Printing.hpp
  include/al/core/system/al_Thread.hpp
  include/al/core/system/al_Time.hpp
  include/al/core/types/al_Color.hpp
)

set(core_sources
  ${al_path}/src/core/app/al_AudioApp.cpp
  ${al_path}/src/core/app/al_FPS.cpp
  ${al_path}/src/core/app/al_WindowApp.cpp
  ${al_path}/src/core/graphics/al_BufferObject.cpp
  ${al_path}/src/core/graphics/al_DefaultShaders.cpp
  ${al_path}/src/core/graphics/al_EasyFBO.cpp
  ${al_path}/src/core/graphics/al_EasyVAO.cpp
  ${al_path}/src/core/graphics/al_FBO.cpp
  ${al_path}/src/core/graphics/al_GLEW.cpp
  ${al_path}/src/core/graphics/al_GLFW.cpp
  ${al_path}/src/core/graphics/al_GPUObject.cpp
  ${al_path}/src/core/graphics/al_Graphics.cpp
  ${al_path}/src/core/graphics/al_Isosurface.cpp
  ${al_path}/src/core/graphics/al_Lens.cpp
  ${al_path}/src/core/graphics/al_Light.cpp
  ${al_path}/src/core/graphics/al_Mesh.cpp
  ${al_path}/src/core/graphics/al_OpenGL.cpp
  ${al_path}/src/core/graphics/al_RenderManager.cpp
  ${al_path}/src/core/graphics/al_Shader.cpp
  ${al_path}/src/core/graphics/al_Shapes.cpp
  ${al_path}/src/core/graphics/al_Texture.cpp
  ${al_path}/src/core/graphics/al_VAO.cpp
  ${al_path}/src/core/graphics/al_VAOMesh.cpp
  ${al_path}/src/core/graphics/al_Viewpoint.cpp
  ${al_path}/src/core/io/al_AudioIO.cpp
  ${al_path}/src/core/io/al_AudioIOData.cpp
  ${al_path}/src/core/io/al_ControlNav.cpp
  ${al_path}/src/core/io/al_CSVReader.cpp
  ${al_path}/src/core/io/al_File.cpp
  ${al_path}/src/core/io/al_MIDI.cpp
  ${al_path}/src/core/io/al_Window.cpp
  ${al_path}/src/core/io/al_WindowGLFW.cpp
  ${al_path}/src/core/math/al_StdRandom.cpp
  ${al_path}/src/core/protocol/al_OSC.cpp
  ${al_path}/src/core/sound/al_Ambisonics.cpp
  ${al_path}/src/core/sound/al_AudioScene.cpp
  ${al_path}/src/core/sound/al_Biquad.cpp
  ${al_path}/src/core/sound/al_Dbap.cpp
  ${al_path}/src/core/sound/al_Vbap.cpp
  ${al_path}/src/core/sound/al_Spatializer.cpp
  ${al_path}/src/core/sound/al_StereoPanner.cpp
  ${al_path}/src/core/spatial/al_HashSpace.cpp
  ${al_path}/src/core/spatial/al_Pose.cpp
  ${al_path}/src/core/system/al_PeriodicThread.cpp
  ${al_path}/src/core/system/al_Printing.cpp
  ${al_path}/src/core/system/al_ThreadNative.cpp
  ${al_path}/src/core/system/al_Time.cpp
  ${al_path}/src/core/types/al_Color.cpp
)

set(util_headers
  include/al/util/al_Array.h
  include/al/util/al_Array.hpp
  include/al/util/imgui/al_Imgui.hpp
  include/al/util/imgui/imgui_impl_glfw_gl3.h
  include/al/util/ui/al_Composition.hpp
  include/al/util/ui/al_Parameter.hpp
  include/al/util/ui/al_ParameterBundle.hpp
  include/al/util/ui/al_ParameterGUI.hpp
  include/al/util/ui/al_ParameterServer.hpp
  include/al/util/ui/al_ParameterMIDI.hpp
  include/al/util/ui/al_Preset.hpp
  include/al/util/ui/al_FileSelector.hpp
  include/al/util/ui/al_HtmlInterfaceServer.hpp
  include/al/util/ui/al_PresetMapper.hpp
  include/al/util/ui/al_PresetMIDI.hpp
  include/al/util/ui/al_Pickable.hpp
  include/al/util/ui/al_PickableManager.hpp
  include/al/util/ui/al_PresetSequencer.hpp
  include/al/util/ui/al_SequenceRecorder.hpp
  include/al/util/ui/al_ControlGUI.hpp
  include/al/util/scene/al_SynthSequencer.hpp
  include/al/util/scene/al_SynthRecorder.hpp
  include/al/util/scene/al_DynamicScene.hpp
  include/al/util/scene/al_DistributedScene.hpp
  include/al/util/scene/al_PolySynth.hpp
  include/al/util/scene/al_SequencerMIDI.hpp
  include/al/util/al_Toml.hpp
  include/al/util/sound/al_OutputMaster.hpp
)

set(util_sources
  ${al_path}/src/util/al_Array_C.c
  ${al_path}/src/util/al_Array.cpp
  ${al_path}/src/util/imgui/al_Imgui.cpp
  ${al_path}/src/util/imgui/imgui_impl_glfw_gl3.cpp
  ${al_path}/src/util/ui/al_Composition.cpp
  ${al_path}/src/util/ui/al_Parameter.cpp
  ${al_path}/src/util/ui/al_ParameterBundle.cpp
  ${al_path}/src/util/ui/al_ParameterGUI.cpp
  ${al_path}/src/util/ui/al_ParameterServer.cpp
  ${al_path}/src/util/ui/al_FileSelector.cpp
  ${al_path}/src/util/ui/al_Preset.cpp
  ${al_path}/src/util/ui/al_HtmlInterfaceServer.cpp
  ${al_path}/src/util/ui/al_PresetMapper.cpp
  ${al_path}/src/util/ui/al_PresetMIDI.cpp
  ${al_path}/src/util/ui/al_PresetSequencer.cpp
  ${al_path}/src/util/ui/al_SequenceRecorder.cpp
  ${al_path}/src/util/ui/al_ControlGUI.cpp
  ${al_path}/src/util/scene/al_SynthSequencer.cpp
  ${al_path}/src/util/scene/al_SynthRecorder.cpp
  ${al_path}/src/util/scene/al_DynamicScene.cpp
  ${al_path}/src/util/scene/al_PolySynth.cpp
  ${al_path}/src/util/al_Toml.cpp
  ${al_path}/src/util/sound/al_OutputMaster.cpp
)

set(al_headers
  ${core_headers}
  ${util_headers}
)

set(al_sources
  ${core_sources}
  ${util_sources}
)

set(module_sources
    modules/module/font/loadFont.cpp
    modules/module/img/loadImage.cpp
)

# Header only files produce a lot of warnings from unused functions,
# So disable these warnings for modules
foreach(src_file IN LISTS module_sources)
#SET_SOURCE_FILES_PROPERTIES(${src_file} PROPERTIES COMPILE_FLAGS "-Wunused-function -Wunused-variable")
endforeach(src_file IN LISTS module_sources)

# OPTIONAL ---------------------------------------------------------------------

#set(glv_headers
#  include/al/glv/al_GLV.hpp
#  include/al/glv/glv.h
#  include/al/glv/glv_behavior.h
#  include/al/glv/glv_buttons.h
#  include/al/glv/glv_conf.h
#  include/al/glv/glv_core.h
#  include/al/glv/glv_font.h
#  include/al/glv/glv_layout.h
#  include/al/glv/glv_model.h
#  include/al/glv/glv_notification.h
#  include/al/glv/glv_rect.h
#  include/al/glv/glv_sliders.h
#  include/al/glv/glv_textview.h
#  include/al/glv/glv_util.h
#  include/al/glv/glv_widget.h
#)

#set(glv_sources
#  src/glv/al_GLV_draw.cpp
#  src/glv/al_GLV_wrapper.cpp
#  src/glv/glv_buttons.cpp
#  src/glv/glv_core.cpp
#  src/glv/glv_font.cpp
#  src/glv/glv_glv.cpp
#  src/glv/glv_inputdevice.cpp
#  src/glv/glv_layout.cpp
#  src/glv/glv_model.cpp
#  src/glv/glv_notification.cpp
#  src/glv/glv_sliders.cpp
#  src/glv/glv_textview.cpp
#  src/glv/glv_view.cpp
#  src/glv/glv_widget.cpp
#)

#if (USE_GLV)
#  list(APPEND al_headers ${glv_headers})
#  list(APPEND al_sources ${glv_sources})
#endif()
