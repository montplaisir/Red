
# Verify Anaconda is loaded. Needed for Cython.Build.
conda_version=$(shell conda --version)
ifeq ("$(conda_version)","")
$(error Anaconda is needed to run this makefile)
else
$(info Anaconda Version $(conda_version))
endif

all:
	python setup_PyReduce.py build_ext --inplace

lib:
	python setup_PyReduce.py install --user

clean:
	@echo Cleaning PyReduce directory...
	@rm -rf build *.so PyReduce.cpp
	@echo done.
