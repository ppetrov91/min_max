MODULE_big = min_max
OBJS = min_max.o
EXTENSION = min_max
DATA = min_max--1.0.sql
REGRESS = min_max

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/min_max
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
