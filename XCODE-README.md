# Building Xcode targets in the MELTS project
With the Xcode MELTS project, you can build the following targets:
+ **Melts-rhyolite** The standalone GUI interface, equivalent to the Melts-rhyolite target built using the macOS/Linux makefile procedure
+ **public-Melts-rhyolite** The standalone GUI interface, equivalent to the Melts-rhyolite-public target built using the macOS/Linux makefile procedure
+ **batch-Melts-rhyolite** The command-line version of MELTS, euivalent to the Melts-batch target built using the macOS/Linux makefile procedure
+ **rMELTSframework** A Macintosh framework (static library and include files) built as a dependency for the web service apps 
+ **rMELTSframeworkTestsXC** Builds a facility to test functionality of the rMELTSframework 
+ **MELTS WS BxApp** Generates a debugging version of the app that provides MELTS web service on demand as a component of a Bombax server app communicating with an NGINX web server
+ **MELTS WS BxApp - Release** Generates a release version of the above app
+ **Coarsening** Generates a specialized version of MELTS for use in the analysis of surface energy affects related to cryustal size on thermodynamic stability of mineral phases
+ **cpx-olv-rhm** Generates a clinopyroxene + olivine + rhombohedral oxide geothermometer

The **MELTS WS BxApp** targets require a framework called Bombastic, which is built as part of the Bombax server infrastructure. To build the server and the framework, you can download an Xcode project from GitLab by cloning the [Bombax-Git repository](https://gitlab.com/ENKI-portal/Bombax-Git) within the ENKI-portal repository collection. Refer to the [documentation in the Bombax/docs folder](https://gitlab.com/ENKI-portal/Bombax-Git/blob/master/Bombax/doc/dev-guide/Bombax%20Developers%20Guide.pdf) to learn more about Bombax, its interaction with an NGINX server, and how objective-C web service apps are configured and loaded into the Bombax web service monitor app.
## Run the MELTS web services on your server
Follow these instructions to configure Bombax to run the MELTS web service and to interact with an NGINX server.

1. Start Xcode, and open the BombaxWS workspace. The workspace loads several Xcode projects, including Bombastic and Bombax.
1. Build Bombastic (Mac 64-bit). (The debug version is optional.)
1. Build bxmlparser. (The debug version is optional.)
1. Build BxClientLib (Mac 64-bit). (The debug version is optional.)
1. Build and start the Bombax app.
1. Open the MELTS project, and build and run MELTS WS BxApp.  This action starts the app that listens on a Bombax-debug socket, localport:10288.
1. Interact with the web service in the browser at [http://localport:10288/](http://localport:10288/).


If you want to install the app into a standalone Bombax web service monitor interacting with a public NGINX server, build it in release mode, and drag the app into the setup pane of the monitor.  It self-configures. Then click **Apply** to start the MELTS web service in Bombax, and listen on port 8080 in a browser pointing at the public address of your NGINX server. You may need to stop and restart the server and/or the Bombax app to establish a clean connection to NGINX.