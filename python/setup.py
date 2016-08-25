#!/usr/bin/env python
""" file: setup.py
    author: Jess Robertson, CSIRO Earth Science and Resource Engineering
    date: Wednesday 10 October, 14:59:20 WST 2012
    modified: Mark S. Ghiorso, OFM Research
    date: August 24, 2016

    description: Distutils installer script for PyMELTS.
"""

from distutils.core import setup, Extension, Command

# Bit of hackery to get gcc the right flags in the right order. distuils is 
# doing something strange with the linker flags, see e.g. 
# http://stackoverflow.com/questions/2584595
# was:  -fPIC -shared
import os
os.environ['LDFLAGS'] = '-L../ -lMELTSdynamic'
os.environ['MACOSX_DEPLOYMENT_TARGET'] = '10.7'

## VERSION NUMBERS
# Patch disutils if it can't cope with the 'classifiers' or 'download_url' 
# keywords (for Python < 2.2.3)
from sys import version
if version < '2.2.3':
    from distutils.dist import DistributionMetadata
    DistributionMetadata.classifiers = None
    DistributionMetadata.download_url = None

setup(
    name='pyMELTS',
    version='0.1',
    description='Wrappers for the MELTS library',
    long_description=open('README.txt').read(),
    author='Mark S. Ghiorso',
    author_email='ghiorso@ofm-research.org',
    url='http://melts.ofm-research.org',
    packages=['pymelts', 'pymelts.melts_functions'],
    ext_modules=[
        Extension('melts_bindings', 
            sources=['pymelts/melts_functions/melts_bindings.c'],
            define_macros=[('MAJOR_VERSION', '0'), ('MINOR_VERSION', '1')],
            include_dirs=['pymelts/melts_functions', '/Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/includes', '/usr/local/include'],
            library_dirs=['/usr/local/lib', '/Users/ghiorso/Documents/ARCHIVE_CODE/xMelts'],
            libraries=['MELTSdynamic'])],
    package_data={'pymelts': ['data/*/*.tbl', 'data/*/*.melts*']},
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Environment :: Plugins',
        'Intended Audience :: Developers',
        'Intended Audience :: Education',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: BSD License',
        'Natural Language :: English',
        'Operating System :: OS Independent',
        'Programming Language :: C',
        'Programming Language :: Python',
        'Topic :: Scientific/Engineering',
        'Topic :: Scientific/Engineering :: Chemistry',
        'Topic :: Scientific/Engineering :: Mathematics',
        'Topic :: Scientific/Engineering :: Physics',
        'Topic :: Software Development :: Libraries :: Python Modules'
    ]
)