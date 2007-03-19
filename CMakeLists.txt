set(kritaLineSampler_PART_SRCS
LineSampler.cc LineSamplerConfig.cc LineSamplerWdg.cc     )

kde3_automoc(${kritaLineSampler_PART_SRCS})

kde3_add_ui_files(kritaLineSampler_PART_SRCS
    LineSamplerWdgBase.ui
    )

kde3_add_kpart(kritaLineSampler ${kritaLineSampler_PART_SRCS})

# target_link_libraries(kritablurfilter ${KRITAUI_LIBRARY})

install(TARGETS kritaLineSampler  DESTINATION ${PLUGIN_INSTALL_DIR})

install( FILES  kritaLineSampler.desktop  DESTINATION ${SERVICES_INSTALL_DIR})
