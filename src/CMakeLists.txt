# File: src/CMakeLists.txt

# Executables
ADD_EXECUTABLE (OurAdventure
    Adjacency.C
    Adventurer.C
    Carryable.C
    Container.C
    Description.C
    Direction.C
    DirectionList.C
    Feature.C
    Game.C
    GameCommand.C
    GameCommandProcessor.C
    Gold.C
    ID.C
    Inventory.C
    Item.C
    ItemFactory.C
    Lock.C
    LockState.C
    main.C
    Map.C
    Name.C
    Size.C
    StartRoom.C
    Weight.C
    )

# Installation
INSTALL (TARGETS OurAdventure
         RUNTIME DESTINATION bin)
INSTALL (FILES ${CMAKE_CURRENT_SOURCE_DIR}/cave.dat
         DESTINATION share)
