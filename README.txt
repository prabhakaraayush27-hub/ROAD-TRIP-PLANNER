ROAD TRIP PLANNER - REPORT-MATCHED QT PROJECT

This version keeps the Road Trip Planner functionality described in the report and
adjusts the GUI layout to closely resemble the screenshots on printed pages 132-134.

Files:
  MainWindow.h/.cpp   Main Qt GUI and event handlers
  Trip.h/.cpp         Trip record/data class
  FileManager.h/.cpp  trips.txt persistence and runtime trip vector
  main.cpp            Application entry point
  RoadTripPlanner.pro qmake project file
  trips.txt           Saved-trip file

GUI:
  - 600 x 480 main window
  - Road Trip Planner (India) title
  - Centered compact input form
  - Five horizontal buttons
  - Light calculation-results panel
  - Saved Road Trips History dialog
  - Runtime trip records are also kept in a std::vector while the application runs

Calculations:
  Fuel Required = Distance / Mileage
  Fuel Cost = Fuel Required * Fuel Price
  Travel Time = Distance / Average Speed

Vehicle defaults shown in the report code:
  Bike = 40.0 km/l
  Car  = 15.0 km/l

The report does not show an automatic SUV mileage value, so SUV remains editable.

Open RoadTripPlanner.pro in Qt Creator and build/run it with a Qt Widgets kit.
