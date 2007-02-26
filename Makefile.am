kritarcdir = $(kde_datadir)/krita/kritaplugins

kde_services_DATA = kritaLineSampler.desktop


INCLUDES  =  -I$(srcdir)/../../../sdk \
	-I$(srcdir)/../../../core \
	-I$(srcdir)/../../../kritacolor/ \
	-I$(srcdir)/../../../ui \
	$(KOFFICE_INCLUDES) \
	$(all_includes)

# Allow exceptions for this plugin so gmm compiles ok
# KDE_CXXFLAGS = $(USE_EXCEPTIONS)

kritaLineSampler_la_SOURCES = LineSampler.cc LineSamplerConfig.cc LineSamplerWdg.cc LineSamplerWdgBase.ui

kde_module_LTLIBRARIES = kritaLineSampler.la
noinst_HEADERS = LineSampler.h LineSamplerConfig.h

kritaLineSampler_la_LDFLAGS = $(all_libraries) -module $(KDE_PLUGIN)
kritaLineSampler_la_LIBADD =  -lkritacommon

kritaLineSampler_la_METASOURCES = AUTO
