#!/usr/bin/env python
""" file: setup.py
    modified: Mark S. Ghiorso, OFM Research
    date: December 24, 2016

    description: Distutils installer script for PyMELTS.
"""

from distutils.core import setup, Extension, Command

import os
# FIXME: unclear what setting the MACOSX_DEPLOYMENT_TARGET does
#        when set to 10.7  build breaks on 10.11
#        simply commenting this out for now
#os.environ['MACOSX_DEPLOYMENT_TARGET'] = '10.7'

from sys import version
if version < '2.2.3':
    from distutils.dist import DistributionMetadata
    DistributionMetadata.classifiers = None
    DistributionMetadata.download_url = None

setup(
    name='pyMELTS',
    version='0.1',
    description='Wrappers for the MELTS library',
    long_description=open('python/README.txt').read(),
    author='Mark S. Ghiorso',
    author_email='ghiorso@ofm-research.org',
    url='http://melts.ofm-research.org',
    package_dir={'': 'python'}, 
    packages=['pymelts', 'pymelts.melts_functions'],
    ext_modules=[
        Extension('melts_bindings', 
            sources=['python/pymelts/melts_functions/melts_bindings.c', 'sources/library.c', 'sources/albite.c', 'sources/alloy-liquid.c', 'sources/alloy-solid.c', 'sources/amphibole.c', 'sources/biotite.c', 'sources/biotiteTaj.c', 'sources/check_coexisting_liquids.c', 'sources/check_coexisting_solids.c', 'sources/clinopyroxene.c', 'sources/cummingtonite.c', 'sources/equality_constraints.c', 'sources/est_saturation_state.c', 'sources/est_satState_revised.c', 'sources/evaluate_saturation.c', 'sources/feldspar.c', 'sources/fluid.c', 'sources/fluidPhase.c', 'sources/frac.c', 'sources/garnet.c', 'sources/gibbs.c', 'sources/gradient_hessian.c', 'sources/hornblende.c', 'sources/ilmenite.c', 'sources/lawson_hanson.c', 'sources/leucite.c', 'sources/linear_search.c', 'sources/liquid.c', 'sources/liquid_v34.c', 'sources/liquid_CO2.c', 'sources/liquid_CO2_H2O.c', 'sources/liquidus.c', 'sources/majorite.c', 'sources/melilite.c', 'sources/melts_support.c', 'sources/melts_threads.c', 'sources/mthread.c', 'sources/nash.c', 'sources/nepheline.c', 'sources/kalsilite.c', 'sources/olivine.c', 'sources/olivine-sx.c', 'sources/orthopyroxene.c', 'sources/ortho-oxide.c', 'sources/perovskite.c', 'sources/read_write.c', 'sources/recipes.c', 'sources/rhombohedral.c', 'sources/ringwoodite.c', 'sources/silmin.c', 'sources/silmin_support.c', 'sources/spinel.c', 'sources/subSolidusMuO2.c', 'sources/wadsleyite.c', 'sources/water.c', 'sources/wustite.c', 'sources/rhomsghiorso.c'],
            define_macros=[('MAJOR_VERSION', '0'), ('MINOR_VERSION', '1'), ('BATCH_VERSION', None), ('RHYOLITE_ADJUSTMENTS', None), ('DO_NOT_PRODUCE_OUTPUT_FILES', None)],
            include_dirs=['python/pymelts/melts_functions', 'includes', '/usr/local/include'],
            library_dirs=['/usr/local/lib'])],
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
