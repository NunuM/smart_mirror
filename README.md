# Smart Mirror Project


## Architecture 

The smart mirror has several CLI programs that have only one requirement: print in JSON format. They are packaged by using the Ubuntu Snap package system in order to provide easy installation on target machines.

The cordinator, triggered by the voice control, executes the respective program, and with the outup of the program, the cordinator makes an RPC call to the UI via DBUS, and the information is presented to the user. Like this, the UI is decoupled from the data, and the widgets can be written in any programing languague.

The GUI was made with QT framework. The comunication is done via DBUS. Several interfaces are exposed via DBUS.

Note: The voice control is a simple service, that uses a specific mic controller, you may need to make your own voice controller.


#### Available widgets  

* Applications: list of widgets that are installed.
* Media: list of movies.
* Weather
* Traffic
* Notes
* Reddit
* Sensor: view of the sensors that you may have interconected.

![alt text](https://i.ibb.co/tzHcP1D/scrren.png)


