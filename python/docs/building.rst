Building and installing PyMELTS
===============================

.. _installation:

:note: This is currently fairly Unix-centric but should carry over to OSX fairly obviously. I haven't bothered to try to get any of this running on Windows yet. 

To build this you need to have first installed the dynamic melts library (libMELTSdynamic.so) and have it available on your path somewhere so that the linker can find it. For example, I have libMELTSdynamic sitting in /usr/local/lib, and my path is::

    $ echo $PATH
    <snip>:/usr/local/bin:/usr/bin:/bin:<snip>

so gcc can find libMELTSdynamic.so (note in general I'll use :file:`$` to denote something you should enter at a shell prompt (e.g. bash), and :file:`>>>` to denote Python code which can be entered into a Python or IPython interpreter).

Then all you should need to do is enter the python directory, and execute::

    $ ./setup.py build && sudo ./setup.py install

which should build and install the Python bindings for your system.

Building documentation
----------------------

If you want to build the documentation for PyMELTS then you will need to have a version of `sphinx <http://sphinx.pocoo.org/>`_ installed -- you can check by doing the following at a terminal prompt::

  $ python -c 'import sphinx'

If that fails grab the latest version of and install it with::

  $ sudo easy_install -U Sphinx

Now you are ready to build your docs, using make::

  $ cd docs && make html

(or :file:`latexpdf` if you want a LaTeX version - type :file:`make` to see all the options). The documentation will be dumped under :file:`build/<format>`. For HTML, if you point a browser to :file:`build/html/index.html`, you should see a basic sphinx site with the documentation for PyMELTS. For LaTeX you can open :file:`build/latex/pymelts.pdf` in your favourite PDF viewer to browse the documentation.