#Usage of TrafficCLI:  
-distance int  
   Required: Int value > 0 and <500 (default -1)    
-locationCodes  
  Optional: Include Location Codes. Default: false  
-point value  
  Required : list of 2 floats representing Latitude and Longitude  
-severity value  
  Optional: list of comma separated integers that represent: 1:LowImpact, 2:Minor, 3:Moderate: 4:Serious  
-type value  
  Optional: list of comma separated integers that represent the following types 1:Accident,2:Congestion,3:DisabledVehicle,4:MassTransit,5:Misc,6:OtherNews,7:PlannedEvent,8:RoadHazard,9:Construction,10:Alert,11:Weather  


#Example Parameters
``-point 41.165082,-8.632557 -distance 10 -severity 1,2,3,4``  
``-point 41.165082,-8.632557 -distance 10 -severity 1,2,3,4 -type 1,2,3,4,5,6,7,8,9,10,11``  
``-point 41.165082,-8.632557 -distance 10 ``  
