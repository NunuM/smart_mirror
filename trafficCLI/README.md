#Usage of TrafficCLI:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-distance int  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Required: Int value > 0 and <500 (default -1)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  -locationCodes  
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  	Optional: Include Location Codes. Default: false  
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -point value  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 	Required : list of 2 floats representing Latitude and Longitude  
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -severity value  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    	Optional: list of comma separated integers that represent: 1:LowImpact, 2:Minor, 3:Moderate: 4:Serious  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  -type value  
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   	Optional: list of comma separated integers that represent the following types 1:Accident,2:Congestion,3:DisabledVehicle,4:MassTransit,5:Misc,6:OtherNews,7:PlannedEvent,8:RoadHazard,9:Construction,10:Alert,11:Weather  


#Example Parameters
``-point 41.165082,-8.632557 -distance 10 -severity 1,2,3,4``  
``-point 41.165082,-8.632557 -distance 10 -severity 1,2,3,4 -type 1,2,3,4,5,6,7,8,9,10,11``  
``-point 41.165082,-8.632557 -distance 10 ``  
