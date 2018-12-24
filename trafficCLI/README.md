#Usage of TrafficCLI:  
&nbsp;-location string  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Required: The name of the local to check the traffic for  
&nbsp;-locationCodes   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Optional: Include Location Codes. Default: false
&nbsp;-severity value  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Optional: list of comma separated integers that represent: 1:LowImpact, 2:Minor, 3:Moderate,4:Serious
&nbsp;-type value  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Optional: list of comma separated integers that represent the following types 1:Accident,2:Congestion,3:DisabledVehicle,4:MassTransit,5:Misc,6:OtherNews,7:PlannedEvent,8:RoadHazard,9:Construction,10:Alert,11:Weather


#Example Parameters
``-location Porto -severity 1,2,3,4``  
``-point Valongo -severity 1,2,3,4 -type 1,2,3,4,5,6,7,8,9,10,11``  
``-point "Marco De Canaveses" ``  
