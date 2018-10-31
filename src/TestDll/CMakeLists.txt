project(TestDll)

add_definitions( -DBRAND_NAME=\"${PROJECT_NAME}\")

set(SRC
	main.cpp
)

add_library(${PROJECT_NAME} SHARED ${SRC})
