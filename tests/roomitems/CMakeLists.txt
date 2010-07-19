# File: tests/roomitems/CMakeLists.txt

SET (SRC_DIR ../../src)

INCLUDE_DIRECTORIES (. ${SRC_DIR})

SET (DEPEND_SRC ${SRC_DIR}/Adjacency.C
                ${SRC_DIR}/Item.C
                ${SRC_DIR}/ItemFactory.C
                ${SRC_DIR}/Map.C
                ${SRC_DIR}/Feature.C
                ${SRC_DIR}/StartRoom.C
                ${SRC_DIR}/Direction.C
                ${SRC_DIR}/ID.C
                ${SRC_DIR}/Name.C
                ${SRC_DIR}/Description.C
                ${SRC_DIR}/Gold.C
                ${SRC_DIR}/Container.C
                ${SRC_DIR}/Lock.C
                ${SRC_DIR}/LockState.C
                ${SRC_DIR}/Carryable.C
                ${SRC_DIR}/Size.C
                ${SRC_DIR}/Weight.C
                )

ADD_EXECUTABLE (test_roomitems test.C ${DEPEND_SRC})

ENABLE_TESTING ()

ADD_TEST (test_roomitems test_roomitems)
