# Building Xcode targets in the MELTS project
With the Xcode MELTS project the following targets maek be built:
+ **Melts-rhyolite** - The stanalone GUI interface, equivalent to the Melts-rhyolite target built using the MacOS/LINUX makefile proceedure
+ **public-Melts-rhyolite** - The standalone GUI interface, equivalent to the Melts-rhyolite-public target built using the MacOS/LINUX makefile proceedure
+ **batch-Melts-rhyolite** - The command line version of MELTS, euivalent to the Melts-batch target built using the MacOS/LINUX makefile proceedure
+ **rMELTSframework** - A Macintosh framework (static library and include files) built as a dependency for the web service apps 
+ **rMELTSframeworkTestsXC** - Builds a facility to test functionality of the rMELTSframework 
+ **MELTS WS BxApp** - Generates a DEBUGing version of app that provides MELTS web service on demand as a component of a BomBax server app communicating with an NGINX web server
+ **MELTS WS BxApp** - Generates a release version of the above app
+ **Coarsening** - Generates a specialized version of MELTS for use in the analysis of surface energy affects related to cryustal size on thermodynamic stability of mineral phases
+ **cpx-olv-rhm** - Generates a clinopyroxene + olivine + rhombohedral oxide geothermometer

The **MELTS WS BxApp** targets require a framework called Bombastic, which is built as part of the Bombax server infrastructure.  An Xcode project to build the server and the framework may be downloaded from GitLab by cloning the Bombax-Git repository within the ENKI-portal repository collection.  Read teh documentation within the *docs* subfolder of the *Bombax* folder to learn more about Bombax, its interaction with an NGINX server, and how objective-C wen service apps are confugured and loaded into the Bombax web service monitor app.
## How to run the MELTS web services on your server
Brief instructors for configuring Bombax to run the MELTS web service and on setting up the interaction of Bombax with an NGINX server are described below.

- Start Xcode and open the BombaxWS workspace, which will load several Xcode projects incluing Bombaxtic and Bombax
- Build Bombastic (Mac 64-bit) (build debug release is optional)
- Build bxmlparser (build debug release is optional)
- Build BxClientLib (Mac 64-bit) (build debug release is optional)
- Build and start the Bombax app
- Open the Melts project in Xcode and build and run the MELTS WS BxApp.  This action starts the app which listens on a bombax-debug socket, localport:10288
- interact with the webservice in the browser at URL http://localport:10288/
- To install the app into a standalone bombax webservice monitor interacting with a public NGINX server, build it in release mode, and drag the app into the setup pane of the monitor.  It will be self configured.
- After that **apply** the additional service in Bombax and listen on port 8080 in a browser pointing at the public address of your NGINX server.  Note, that it may be necessary to stop and restart the server and/or the Bombax app in order to establish a clean connection to NGINX.