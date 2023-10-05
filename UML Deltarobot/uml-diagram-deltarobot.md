@startuml

!define ACTOR actor
!define USECASE usecase
!define RECTANGLE rectangle

skinparam actor {
  BackgroundColor LightBlue
  BorderColor DarkSlateGray
}

skinparam usecase {
  BackgroundColor LightGray
  BorderColor DarkSlateGray
}

ACTOR "Operator" as Operator
ACTOR "Maintenance Technician" as Technician
CONTROL "Control System" as ControlSystem
RECTANGLE "Delta Robot" as DeltaRobot {
  USECASE "Initialize Robot" as UC1
  USECASE "Load Program" as UC2
  USECASE "Move Robot Arm" as UC3
  USECASE "Execute Task" as UC4
  USECASE "Monitor Robot Status" as UC5
  USECASE "Emergency Stop" as UC6
}

Operator -down-> UC1 : Initiates
Operator --> UC3 : Requests movement
Operator --> UC4 : Requests execution
Operator --> UC5 : Monitors status
Operator -down-> UC6 : Requests stop
Technician -down-> UC6 : Performs
ControlSystem -down-> UC1 : Manages
ControlSystem --> UC2 : Manages
ControlSystem --> UC3 : Manages
ControlSystem --> UC4 : Manages
ControlSystem --> UC5 : Monitors

@enduml